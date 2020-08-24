class ActionDestroyExpansionCodeLockOnTentCB extends ActionContinuousBaseCB {
    override void CreateActionComponent() {
		float circleTime = GetExpansionCodeLockConfig().HacksawRaidTime / GetExpansionCodeLockConfig().HacksawRaidIncrements; 
      	m_ActionData.m_ActionComponent = new CAContinuousRepeat(circleTime);
    }
};

class ActionDestroyExpansionCodeLockOnTent : ActionContinuousBase {
    protected float m_Health;
    protected float m_MaxHealth;

    void ActionDestroyExpansionCodeLockOnTent() {
        m_CallbackClass = ActionDestroyExpansionCodeLockOnTentCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
        m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
        m_FullBody = true;
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINonRuined();
        m_ConditionTarget = new CCTNone();
    }

    override string GetText() {
        return "Destroy Codelock";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (GetExpansionCodeLockConfig().AllowHacksawRaiding){
			TentBase tent = TentBase.Cast(target.GetParent());
			Hacksaw saw = Hacksaw.Cast(item);
	        m_Health = 0;
	        m_MaxHealth = 0;
	
	        if (tent && saw) {
				if (tent.IsLocked() && !saw.IsRuined()) {
					ExpansionCodeLock codelock = ExpansionCodeLock.Cast(tent.FindAttachmentBySlotName( "Att_ExpansionCodeLock" ));
					if ( codelock ) {
						m_Health = codelock.GetHealth("", "");
						m_MaxHealth = codelock.GetMaxHealth("", "Health");
						return true;
					}
				}
	        }
		}
        return false;
    }

    override void OnFinishProgressServer(ActionData action_data) {

        TentBase tent = TentBase.Cast(action_data.m_Target.GetParent());
        float raidIncrementAmount = m_MaxHealth / GetExpansionCodeLockConfig().HacksawRaidIncrements;
		raidIncrementAmount++; //Just to make sure their are no rounding issues
       

        if (tent) {
            ExpansionCodeLock codelock = ExpansionCodeLock.Cast(tent.FindAttachmentBySlotName( "Att_ExpansionCodeLock" ));
			PlayerBase sourcePlayer = PlayerBase.Cast(action_data.m_Player);
			
            if (codelock && sourcePlayer) {
                codelock.AddHealth("", "Health", -raidIncrementAmount);

                float m_Health = codelock.GetHealth("", "");

                if (m_Health <= 0) {
					int toolDamage = GetExpansionCodeLockConfig().HackSawDamage;
                    tent.Unlock();
                    tent.SetCode( "" );
					tent.GetInventory().DropEntity(InventoryMode.SERVER, tent, codelock);
					#ifdef HEROESANDBANDITSMOD
						if (sourcePlayer){
							string sourcePlayerID = sourcePlayer.GetIdentity().GetPlainId();
							GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "ExpansionCodeLockTentRaid");
						}
					#endif
					if (GetExpansionCodeLockConfig().ScriptLogging){
						Print("[CodeLockExpanded][Raid] " + sourcePlayer.GetIdentity().GetName() + "(" +  sourcePlayer.GetIdentity().GetPlainId() + ") Raided  " + tent.GetType() + " at " + tent.GetPosition());
					}
					action_data.m_MainItem.DecreaseHealth(toolDamage, false);
                }
            }
        }

    }
};