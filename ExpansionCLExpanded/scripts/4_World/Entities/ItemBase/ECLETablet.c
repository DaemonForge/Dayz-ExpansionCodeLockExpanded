class ECLETablet extends ItemBase{
	
	protected bool m_HackingStarted = false;
	protected bool m_HackingInterrupted = false;
	protected bool m_HackingInterruptedLocal = false;
	
	protected bool m_HackingCompleted = false;
	protected bool m_HackingCompletedLocal = false;
	
	protected bool m_TabletON = false;
	protected bool m_TabletONLocal = false;
	
	protected float m_HackTimeRemaining;
		
	protected float HackingRadius = 10;
	
	protected bool RequireInHands = true;
	
	override void SetActions()
	{
		super.SetActions();

        AddAction(ActionHackExpansion);
    }

	void ECLETablet(){
		
	}
	
	void ~ECLETablet(){
		if (m_HackingStarted && !m_HackingInterrupted && !m_HackingCompleted){ // to make less null pointers
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).Remove(this.CheckHackProgress); 
		}
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
		RegisterNetSyncVariableBool("m_TabletON");
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if ( m_HackingInterrupted && !m_HackingInterruptedLocal )
		{
			HackInterruptedClient();
		} else if ( !m_HackingInterrupted){
			m_HackingInterruptedLocal = m_HackingInterrupted;
		}
		
		if ( m_HackingCompleted && !m_HackingCompletedLocal )
		{
			HackCompletedClient();
		} else if ( !m_HackingCompleted){
			m_HackingCompletedLocal = m_HackingCompleted;
		}
		
		if ( m_TabletON && !m_TabletONLocal ) {
			TurnOnTablet();
		} else if ( !m_TabletON && m_TabletONLocal ) {
			TurnOffTablet();
		}
		
	}
	
	void HackInterruptedClient(){
		m_HackingInterruptedLocal = m_HackingInterrupted;
		SEffectManager.PlaySoundOnObject("landmine_end_SoundSet", this);
		SetAnimationPhase("top",0);
	}
	
	void HackCompletedClient(){
		m_HackingCompletedLocal = m_HackingCompleted;
		SEffectManager.PlaySoundOnObject("Expansion_CodeLock_Unlock_SoundSet", this);
		SetAnimationPhase("top",0);
	}
	
	
	void StartHackServer(ItemBase HackingTarget, PlayerBase Hacker){
		PlayerBase hacker = PlayerBase.Cast(Hacker);
		ItemBase hackingTarget = ItemBase.Cast(HackingTarget);
		string heading = "HACK STARTED";
		string resumed = " has started";
		if (hacker && hackingTarget){
			m_HackingCompleted = false;
			m_HackingInterrupted = false;
			
			if ( hackingTarget.ECLE_GetHackID() != this.ECLE_GetHackID() || hackingTarget.ECLE_GetHackID() == 0){ //Starting A hack on a new object
				m_HackingStarted = true;
				m_HackTimeRemaining = GetExpansionCodeLockConfig().GetHackTime(hackingTarget.GetType()) * 1000;
				
				int HackID = GetGame().GetTime();
				HackID = HackID * 10000;
				HackID = HackID + Math.RandomInt(0,9999);
				this.ECLE_HackInit(HackID);
				hackingTarget.ECLE_HackInit(HackID);
				if (hacker.GetIdentity() && GetExpansionCodeLockConfig().ScriptLogging){
					Print("[CodeLockExpanded][Raid] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") has started hacking " + hackingTarget.GetType() + " with ID: " + HackID + " at " + hackingTarget.GetPosition());
				}
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") has started hacking " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition());
			} else {
				this.ECLE_HackInit(ECLE_GetHackID());
				hackingTarget.ECLE_HackInit(ECLE_GetHackID());
				heading = "HACK RESUMED";
				resumed = " has resumed";
				if (hacker.GetIdentity() && GetExpansionCodeLockConfig().ScriptLogging){
					Print("[CodeLockExpanded][Raid] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") has resumed hacking " + hackingTarget.GetType() + " with ID: " + ECLE_GetHackID() + " at " + hackingTarget.GetPosition());
				}
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") has resumed hacking " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition());
			}
			SendPlayerMessage(hacker, heading, "The hacking of " + hackingTarget.GetDisplayName() + resumed);
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(this.CheckHackProgress, 2000, false, hackingTarget, hacker);
			SetSynchDirty();
		}
	}
	
	void StartHackClient(){
		SetAnimationPhase("top",1);
		SEffectManager.PlaySoundOnObject("defibrillator_ready_SoundSet", this);
	}
	
	
	bool CheckHackInterrupt(ItemBase HackingTarget, PlayerBase Hacker){
		bool IsInterrupted = false;
		PlayerBase hacker = PlayerBase.Cast(Hacker);
		ItemBase hackingTarget = ItemBase.Cast(HackingTarget);
		if (hacker && hackingTarget){
            ExpansionCodeLock codelock = ExpansionCodeLock.Cast(hackingTarget.GetAttachmentByConfigTypeName("ExpansionCodeLock"));
			ECLEHackableItem hackingData = GetExpansionCodeLockConfig().GetHackableItem( hackingTarget.GetType() );
			bool hasCodeLock = false;
			if (codelock){
				hasCodeLock = true;
			}
            if ( hasCodeLock && hackingData.Type != "" && !hackingData.IsSafe && !HackingTarget.IsLocked()) {
				//Code Lock not locked
				IsInterrupted = true;
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to codelock being unlocked");
			} 
			if (!HackingTarget.IsLocked() && hackingData.Type != "" && hackingData.IsSafe){
				//Code Lock not locked
				IsInterrupted = true;
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to safe being unlocked");
			
			} 
			if ( !hasCodeLock && hackingData.Type != "" && !hackingData.IsSafe){ //Code Lock Removed
				IsInterrupted = true;
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to codelock missing");
			}
			//Missing Batteries
			if (!GetExpansionCodeLockConfig().CanHack( hackingTarget.GetType(), this.CountBatteries(), hasCodeLock)){
				IsInterrupted = true;
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to Missing Batteries");
			}
			//Random Chance Calcuations
			float DoInterrupt = Math.RandomFloat(0,1000);
			float InterruptChance = hackingData.ChanceOfInterrupt * 1000;
			if (DoInterrupt < InterruptChance){
				IsInterrupted = true;
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to interrupt Chance");
			}
			//Tablet is in hands
			if (hacker.GetItemInHands() != this && RequireInHands){
				IsInterrupted = true;
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to tablet dropped from hands");
			}
			//Hacker Left Radius
			if (vector.Distance(hackingTarget.GetPosition(), hacker.GetPosition()) > HackingRadius){
				IsInterrupted = true;
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to Hacker Leaving the hacking radius");
			}
			//Tablet is ruined
			if (this.IsRuined()){
				IsInterrupted = true;
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to Tablet Being Destroyed");
			}
			//Player has Disconnected
			if (hacker.IsPlayerDisconnected()){
				IsInterrupted = true;
				GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to Player Disconected");
			}
		} else {
			//This shouldn't happen, but Player and Target are inviald
			IsInterrupted = true;
			GetGame().AdminLog("[CodeLockExpanded][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") had their hacking of " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition() + " Interrupted due to invalid Target or Player");
		}
		return IsInterrupted;
	}
	
	
	void CheckHackProgress(ItemBase HackingTarget, PlayerBase Hacker){
		ItemBase hackingTarget = ItemBase.Cast(HackingTarget);
		PlayerBase hacker = PlayerBase.Cast(Hacker);
		if (hackingTarget && hacker){
           	m_HackingInterrupted = CheckHackInterrupt(hackingTarget, hacker);
			if (!m_HackingInterrupted){
				m_HackTimeRemaining = m_HackTimeRemaining - 2000;
				if (m_HackTimeRemaining > 2000){
					GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(this.CheckHackProgress, 2000, false, hackingTarget, hacker);
				} else if (m_HackTimeRemaining > 500){ //if its this close to finishing just finish
					GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(this.CheckHackProgress, m_HackTimeRemaining, false, hackingTarget, hacker);
				} else {
					m_HackTimeRemaining = 0; //incase it was made negitive
					GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(this.HackCompleted, 200, false, hackingTarget, hacker);
				}
			} else {
				hackingTarget.ECLE_InterruptHack();
				this.ECLE_InterruptHack();
				SendPlayerMessage(hacker, "HACK INTERRUPTED", "The hacking of " + hackingTarget.GetDisplayName() + " has been interrupted");
			}
		}else{
			m_HackingStarted = false;
			m_HackingInterrupted = false;
		}
		SetSynchDirty();
	}
	
	void HackCompleted(ItemBase HackingTarget, PlayerBase Hacker){
		PlayerBase hacker = PlayerBase.Cast(Hacker);
		ItemBase hackingTarget = ItemBase.Cast(HackingTarget);
		float itemMaxHealth = 0;
        if (hackingTarget && hacker) {
            ExpansionCodeLock codelock = ExpansionCodeLock.Cast(hackingTarget.GetAttachmentByConfigTypeName("ExpansionCodeLock"));
			ECLEHackableItem hackingData = GetExpansionCodeLockConfig().GetHackableItem( hackingTarget.GetType());
            if ( hackingData.Type != "") {
				if (codelock){
					itemMaxHealth = codelock.GetMaxHealth("", "Health");
					itemMaxHealth++;
					codelock.AddHealth("", "Health", -itemMaxHealth);
					hackingTarget.GetInventory().DropEntity(InventoryMode.SERVER, hackingTarget, codelock);
				}
				
                hackingTarget.Unlock();
                hackingTarget.SetCode( "" );
				
				#ifdef HEROESANDBANDITSMOD
					if (hacker.GetIdentity()){
						GetHeroesAndBandits().NewPlayerAction(hacker.GetIdentity().GetPlainId(), "Hack" + hackingData.Type + "Raid");
					}
				#endif
				if (hacker.GetIdentity() && GetExpansionCodeLockConfig().ScriptLogging){
					Print("[HackingMod][Raid] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") Hacked  " + hackingTarget.GetType() + " with ID: " + ECLE_GetHackID() + " at " + hackingTarget.GetPosition());
				}
				GetGame().AdminLog("[HackingMod][Raid][ID:" + ECLE_GetHackID() + "] " + hacker.GetIdentity().GetName() + "(" +  hacker.GetIdentity().GetPlainId() + ") Hacked  " + hackingTarget.GetType() + " at " + hackingTarget.GetPosition());
					
				this.AddHealth("", "Health", -hackingData.TabletDamage);
				DestoryBatteries( hackingData.Batteries );
				
				this.ECLE_CompleteHack();
				hackingTarget.ECLE_CompleteHack();
				
				m_HackingStarted = false;
				m_HackingInterrupted = false;
				m_HackingCompleted = true;
            }
        }
		if (CountBatteries() == 0){
			m_TabletON = false;
		}
		if (m_HackingCompleted){
			SendPlayerMessage(Hacker, "HACK FINISHED", "The hacking of " + hackingTarget.GetDisplayName() + " has finished");
		}
		SetSynchDirty();
	}
	
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);	
		AddHealth( "GlobalHealth", "Health", -damageResult.GetDamage( "", "Health" ) );
	}

	void TurnOnTablet(){
		m_TabletON = true;
		m_TabletONLocal = true;
		if(!IsRuined()){
			SetObjectTexture(0, "ExpansionCLExpanded\\Data\\textures\\ECLE_tablet_on_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("zbytek"), "ExpansionCLExpanded\\Data\\textures\\ECLE_tablet_on_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("tablet_on"), "ExpansionCLExpanded\\Data\\textures\\ECLE_tablet_on_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("tablef_off"), "ExpansionCLExpanded\\Data\\textures\\ECLE_tablet_on_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("top"), "ExpansionCLExpanded\\Data\\textures\\ECLE_tablet_on_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("background"), "ExpansionCLExpanded\\Data\\textures\\ECLE_tablet_on_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("screen"), "ExpansionCLExpanded\\Data\\textures\\ECLE_tablet_on_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("backscreen"), "ExpansionCLExpanded\\Data\\textures\\ECLE_tablet_on_co.paa");
			SetObjectMaterial( GetHiddenSelectionIndex("backscreen"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_screen_on.rvmat" );
		}
	}
	
	void TurnOffTablet(){
		m_TabletON = false;
		m_TabletONLocal = false;
		if(!IsRuined()){
			SetObjectTexture(0, "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_off_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("zbytek"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_off_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("tablet_on"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_off_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("tablef_off"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_off_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("top"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_off_co.paa");
			SetObjectTexture( GetHiddenSelectionIndex("background"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_off_co.paa");
			SetObjectTexture(GetHiddenSelectionIndex("screen"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_off_co.paa");
			SetObjectMaterial( GetHiddenSelectionIndex("backscreen"), "ExpansionCLExpanded\\Data\\textures\\ECLE_Tablet_on.rvmat" );
		}
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave( ctx );
		
		ctx.Write( m_HackingStarted );
		ctx.Write( m_HackingInterrupted );
		ctx.Write( m_HackingCompleted );
		ctx.Write( m_HackTimeRemaining );
		ctx.Write( m_TabletON );
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
		if ( !ctx.Read( m_TabletON ) )
		{
			loadingsuccessfull = false;
		}
		
		if ( loadingsuccessfull && m_HackingStarted && m_HackTimeRemaining > 0 && !m_HackingCompleted ){
			m_HackingInterrupted = true;
		}
		
		SetSynchDirty();
		
		return loadingsuccessfull;
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		if (m_TabletON){
			 TurnOnTablet();
		} else {
			TurnOffTablet();
		}
		SetSynchDirty();
	}
	
	int CountBatteries(){
		int count = 0;
		ECLETabletBattery tempBattery1;
		ECLETabletBattery tempBattery2;
		ECLETabletBattery tempBattery3;
		ECLETabletBattery tempBattery4;
		ECLETabletBattery tempBattery5;
		
		if (Class.CastTo(tempBattery1, FindAttachmentBySlotName("Att_ECLETabletBattery_1"))){
			if (!tempBattery1.IsRuined()){
				count++;
			}
		}
		if (Class.CastTo(tempBattery2, FindAttachmentBySlotName("Att_ECLETabletBattery_2"))){
			if (!tempBattery2.IsRuined()){
				count++;
			}
		}
		if (Class.CastTo(tempBattery3, FindAttachmentBySlotName("Att_ECLETabletBattery_3"))){
			if (!tempBattery3.IsRuined()){
				count++;
			}
		}
		if (Class.CastTo(tempBattery4, FindAttachmentBySlotName("Att_ECLETabletBattery_4"))){
			if (!tempBattery4.IsRuined()){
				count++;
			}
		}
		if (Class.CastTo(tempBattery5, FindAttachmentBySlotName("Att_ECLETabletBattery_5"))){
			if (!tempBattery4.IsRuined()){
				count++;
			}
		}
		return count;
	}
	
	void DestoryBatteries( int number){
		int count = 0;
		ECLETabletBattery tempBattery1;
		ECLETabletBattery tempBattery2;
		ECLETabletBattery tempBattery3;
		ECLETabletBattery tempBattery4;
		ECLETabletBattery tempBattery5;
		
		if (Class.CastTo(tempBattery5, FindAttachmentBySlotName("Att_ECLETabletBattery_5"))){
			if (!tempBattery5.IsRuined()){
				tempBattery5.AddHealth("", "Health", -21);
				count++;
			}
			if (count >= number){
				return;
			}
		}
		if (Class.CastTo(tempBattery4, FindAttachmentBySlotName("Att_ECLETabletBattery_4"))){
			if (!tempBattery4.IsRuined()){
				tempBattery4.AddHealth("", "Health", -21);
				count++;
			}
			if (count >= number){
				return;
			}
		}
		if (Class.CastTo(tempBattery3, FindAttachmentBySlotName("Att_ECLETabletBattery_3"))){
			if (!tempBattery3.IsRuined()){
				tempBattery3.AddHealth("", "Health", -21);
				count++;
			}
			if (count >= number){
				return;
			}
		}
		if (Class.CastTo(tempBattery2, FindAttachmentBySlotName("Att_ECLETabletBattery_2"))){
			if (!tempBattery2.IsRuined()){
				tempBattery2.AddHealth("", "Health", -21);
				count++;
			}
			if (count >= number){
				return;
			}
		}
		if (Class.CastTo(tempBattery1, FindAttachmentBySlotName("Att_ECLETabletBattery_1"))){
			if (!tempBattery1.IsRuined()){
				tempBattery1.AddHealth("", "Health", -21);
				count++;
			}
			if (count >= number){
				return;
			}
		}
	}
	
	override void EEItemAttached(EntityAI item, string slot_name){
		super.EEItemAttached(item, slot_name);
		if (GetGame().IsServer() && (slot_name == "Att_ECLETabletBattery_1" || slot_name == "Att_ECLETabletBattery_2" || slot_name == "Att_ECLETabletBattery_3" || slot_name == "Att_ECLETabletBattery_4" || slot_name == "Att_ECLETabletBattery_5")){
			m_TabletON = true;
			SetSynchDirty();
		}
	}
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		if (GetGame().IsServer() && (slot_name == "Att_ECLETabletBattery_1" || slot_name == "Att_ECLETabletBattery_2" || slot_name == "Att_ECLETabletBattery_3"  || slot_name == "Att_ECLETabletBattery_4"  || slot_name == "Att_ECLETabletBattery_5")){
			if (CountBatteries() == 0){
				m_TabletON = false;
				SetSynchDirty();
			}
		}
		
	}
	
	void SendPlayerMessage(PlayerBase hacker, string heading, string text){
		PlayerBase Hacker = PlayerBase.Cast(hacker);
		if (Hacker.GetIdentity()){
			string Heading = heading;
			string Message = text;
			string Icon = "ExpansionCLExpanded/GUI/Images/hacking.paa";
			GetNotificationSystem().CreateNotification(new ref StringLocaliser(Heading), new ref StringLocaliser(Message), Icon, -938286307, 15, Hacker.GetIdentity());
		}
	}
	
};