class ECLETablet extends ItemBase{
	
	protected bool m_HackingStarted = false;
	protected bool m_HackingInterrupted = false;
	protected bool m_HackingInterruptedLocal = false;
	
	protected bool m_HackingCompleted = false;
	protected bool m_HackingCompletedLocal = false;
	
	protected float m_HackTimeRemaining;
		
	override void SetActions()
	{
		super.SetActions();

        AddAction(ActionHackExpansionCodeLockOnTent);
        AddAction(ActionHackExpansionCodeLockOnDoor);
    }

	void ~ECLETablet()
	{
		
	}

	bool HasHackingStarted(){
		return m_HackingStarted;
	}

	bool WasHackingInterrupted(){
		return m_HackingInterrupted;
	}
		
	override void InitItemVariables()
	{
		super.InitItemVariables();
		RegisterNetSyncVariableBool("m_HackingStarted");
		RegisterNetSyncVariableBool("m_HackingInterrupted");
		RegisterNetSyncVariableFloat("m_HackTimeRemaining");
		RegisterNetSyncVariableBool("m_HackingCompleted");
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if ( m_HackingInterrupted && !m_HackingInterruptedLocal )
		{
			HackInterruptedClient();
		} 	
		
		if ( m_HackingCompleted && !m_HackingCompletedLocal )
		{
			HackCompletedClient();
		} 		
	}
	
	void HackInterruptedClient(){
		m_HackingInterruptedLocal = m_HackingInterrupted;
		SEffectManager.PlaySoundOnObject("landmine_end_SoundSet", this);
	}
	
	void HackCompletedClient(){
		m_HackingCompletedLocal = m_HackingCompleted;
		SEffectManager.PlaySoundOnObject("Expansion_CodeLock_Unlock_SoundSet", this);
		TurnOffTablet();
	}
	
	
	void StartHackServer(ItemBase hackingTarget, PlayerBase hacker){
		PlayerBase Hacker = PlayerBase.Cast(hacker);
		ItemBase HackingTarget = ItemBase.Cast(hackingTarget);
		if (Hacker && HackingTarget){
			m_HackingInterrupted = false;
			if (!m_HackingStarted){
				
				
				m_HackingStarted = true;
				m_HackTimeRemaining = GetExpansionCodeLockConfig().HackingTimeTents * 1000;
				if( BaseBuildingBase.Cast(hackingTarget)){
					m_HackTimeRemaining = GetExpansionCodeLockConfig().HackingTimeDoors * 1000;
				}
			}
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(this.CheckHackProgress, 2000, false, hackingTarget, hacker);
			SetSynchDirty();
		}
	}
	
	void StartHackClient(){
		SEffectManager.PlaySoundOnObject("defibrillator_ready_SoundSet", this);
	}
	
	void CheckHackProgress(ItemBase hackingTarget, PlayerBase hacker){
		PlayerBase Hacker = PlayerBase.Cast(hacker);
		ItemBase HackingTarget = ItemBase.Cast(hackingTarget);
		if (Hacker && HackingTarget){
			float DoInterrupt = Math.RandomFloat(0,1);
			float InterruptChance = GetExpansionCodeLockConfig().ChanceOfInterrupt * 0.33333;
			if (DoInterrupt < InterruptChance){
				m_HackingInterrupted = true;
			}
			if (!m_HackingInterrupted && !HackingTarget.IsRuined() && vector.Distance(HackingTarget.GetPosition(), Hacker.GetPosition()) < 10 && Hacker.GetItemInHands() == this){
				m_HackTimeRemaining = m_HackTimeRemaining - 2000;
				if(m_HackTimeRemaining > 2000){
					GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(this.CheckHackProgress, 2000, false, hackingTarget, Hacker);
				}else if (m_HackTimeRemaining > 500){
					GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(this.CheckHackProgress, m_HackTimeRemaining, false, hackingTarget, Hacker);
				} else {
					GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(this.HackCompleted, 500, false, hackingTarget, Hacker);
				}
			} else {
				this.AddHealth("GlobalHealth", "Health", -20);
				m_HackingInterrupted = true;
				if(Hacker.GetIdentity()){
					string InterruptedHeading = "Hacking Interrupted";
					string InterruptedMessage = "The Hacking of " + hackingTarget.GetDisplayName() + " has been Interrupted";
					string InterruptedIcon = "ExpansionCLExpanded/GUI/Images/hacking.paa";
					GetNotificationSystem().CreateNotification(new ref StringLocaliser(InterruptedHeading), new ref StringLocaliser(InterruptedMessage), InterruptedIcon, -938286307, 15, Hacker.GetIdentity());
				}
			}
		}else{
			m_HackingStarted = false;
			m_HackingInterrupted = false;
		}
		SetSynchDirty();
	}
	
	void HackCompleted(ItemBase hackingTarget, PlayerBase hacker){
		PlayerBase Hacker = PlayerBase.Cast(hacker);
		BaseBuildingBase HackingTarget = BaseBuildingBase.Cast(hackingTarget);
		float itemMaxHealth = 0;
		float toolDamage = GetExpansionCodeLockConfig().HackSawDamage;
        TentBase tent = TentBase.Cast(hackingTarget); 
        if (tent && Hacker) {
            ExpansionCodeLock codelock = ExpansionCodeLock.Cast(tent.FindAttachmentBySlotName( "Att_ExpansionCodeLock" ));
			
            if (codelock ) {
				itemMaxHealth = codelock.GetMaxHealth("", "Health");
				itemMaxHealth++;
				codelock.AddHealth("", "Health", -itemMaxHealth);
				toolDamage++
                tent.Unlock();
                tent.SetCode( "" );
				tent.GetInventory().DropEntity(InventoryMode.SERVER, tent, codelock);
				#ifdef HEROESANDBANDITSMOD
					if (Hacker){
						GetHeroesAndBandits().NewPlayerAction(Hacker.GetIdentity().GetPlainId(), "HackExpansionCodeLockTentRaid");
					}
				#endif
				if (GetExpansionCodeLockConfig().ScriptLogging){
					Print("[CodeLockExpanded][Raid] " + Hacker.GetIdentity().GetName() + "(" +  Hacker.GetIdentity().GetPlainId() + ") Hacked  " + tent.GetType() + " at " + tent.GetPosition());
				}
				this.AddHealth("GlobalHealth", "Health", -500);
				m_HackingStarted = false;
				m_HackingInterrupted = false;
				m_HackingCompleted = true;
            }
        }
		if (HackingTarget && Hacker) {
            ExpansionCodeLock codelock2 = ExpansionCodeLock.Cast(HackingTarget.GetAttachmentByConfigTypeName("ExpansionCodeLock"));
			
            if (codelock2 ) {
				itemMaxHealth = codelock2.GetMaxHealth("", "Health");
				itemMaxHealth++;
				codelock2.AddHealth("", "Health", -itemMaxHealth);
				toolDamage++;
                HackingTarget.Unlock();
                HackingTarget.SetCode( "" );
				HackingTarget.GetInventory().DropEntity(InventoryMode.SERVER, HackingTarget, codelock2);
				#ifdef HEROESANDBANDITSMOD
					if (Hacker){
						GetHeroesAndBandits().NewPlayerAction(Hacker.GetIdentity().GetPlainId(), "HackExpansionCodeLockTentRaid");
					}
				#endif
				if (GetExpansionCodeLockConfig().ScriptLogging){
					Print("[CodeLockExpanded][Raid] " + Hacker.GetIdentity().GetName() + "(" +  Hacker.GetIdentity().GetPlainId() + ") Hacked  " + HackingTarget.GetType() + " at " + HackingTarget.GetPosition());
				}
				this.AddHealth("", "Health", -500);
				m_HackingStarted = false;
				m_HackingInterrupted = false;
				m_HackingCompleted = true;
            }
        }
		if (m_HackingCompleted && Hacker.GetIdentity()){
			TurnOffTablet();
			string CompletedHeading = "Hacking Finished";
			string CompletedMessage = "The Hacking of " + hackingTarget.GetDisplayName() + " has Finished";
			string CompletedIcon = "ExpansionCLExpanded/GUI/Images/hacking.paa";
			GetNotificationSystem().CreateNotification(new ref StringLocaliser(CompletedHeading), new ref StringLocaliser(CompletedMessage), CompletedIcon, -938286307, 15, Hacker.GetIdentity());
		}
		SetSynchDirty();
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);	
		AddHealth( "GlobalHealth", "Health", -damageResult.GetDamage( "", "Health" ) );
	}

	void TurnOnTablet(){
		this.SetObjectTexture( this.GetHiddenSelectionIndex("tablet_on"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_Good.paa" );
	}
	
	void TurnOffTablet(){
		this.SetObjectTexture( this.GetHiddenSelectionIndex("tablet_off"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_Ruined.paa" );
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave( ctx );
		
		ctx.Write( m_HackingStarted );
		ctx.Write( m_HackingInterrupted );
		ctx.Write( m_HackingCompleted );
		ctx.Write( m_HackTimeRemaining );
	}


	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
		{
			return false;
		}
		bool loadingsuccessfull = true;
		if ( !ctx.Read( m_HackingStarted ) )
		{
			loadingsuccessfull = false;
		}
		if ( !ctx.Read( m_HackingInterrupted ) )
		{
			loadingsuccessfull = false;
		}
		if ( !ctx.Read( m_HackingCompleted ) )
		{
			loadingsuccessfull = false;
		}
		if ( !ctx.Read( m_HackTimeRemaining ) )
		{
			loadingsuccessfull = false;
		}
		
		if ( loadingsuccessfull && m_HackingStarted && m_HackTimeRemaining > 0 && !m_HackingCompleted ){
			m_HackingInterrupted = true;
		}
		
		SetSynchDirty();
		
		return loadingsuccessfull;
	}
	
}