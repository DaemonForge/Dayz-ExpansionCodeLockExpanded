class ActionHackExpansionCodeLockOnDoorCB extends ActionContinuousBaseCB {
    override void CreateActionComponent() {
		float circleTime = GetExpansionCodeLockConfig().HackStartTimeDoors; 
      	m_ActionData.m_ActionComponent = new CAContinuousRepeat(circleTime);
    }
}

class ActionHackExpansionCodeLockOnDoor : ActionContinuousBase {

	bool continueHack = false;
    void ActionHackExpansionCodeLockOnDoor() {
        m_CallbackClass = ActionHackExpansionCodeLockOnDoorCB;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
        m_FullBody = true;
    }

    override void CreateConditionComponents() {
        m_ConditionItem = new CCINonRuined();
        m_ConditionTarget = new CCTNone();
    }

    override string GetText() {
		if (continueHack){
			return "Resume Hacking";
		}
        return "Hack Codelock";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        if (GetExpansionCodeLockConfig().AllowHackingDoors){
			BaseBuildingBase base_building = BaseBuildingBase.Cast(target.GetObject());
			ECLETablet tablet = ECLETablet.Cast(item);
			
			if (base_building && tablet) {
				if (base_building.IsLocked() && !tablet.IsRuined() && (!tablet.HasHackingStarted() || tablet.WasHackingInterrupted())) {
					continueHack = tablet.WasHackingInterrupted();
					ExpansionCodeLock codelock = ExpansionCodeLock.Cast(base_building.GetAttachmentByConfigTypeName("ExpansionCodeLock"));
					if ( codelock ) {
						return true;
					}
				}
	        }
		}
        return false;
    }

    override void OnFinishProgressServer(ActionData action_data) {

        ItemBase target = ItemBase.Cast(action_data.m_Target.GetObject());    
		ECLETablet tablet = ECLETablet.Cast(action_data.m_MainItem);
		PlayerBase sourcePlayer = PlayerBase.Cast(action_data.m_Player);

        if (tablet && sourcePlayer && target) {
            tablet.StartHackServer(target, sourcePlayer);
        }
    }
	
	protected void OnFinishProgressClient( ActionData action_data )
	{  
		ECLETablet tablet = ECLETablet.Cast(action_data.m_MainItem);

        if (tablet) {
            tablet.StartHackClient();
        }
	}
}