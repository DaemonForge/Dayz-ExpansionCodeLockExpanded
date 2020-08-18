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
				//Hacking is fresh Start
				if (base_building.IsLocked() && !tablet.IsRuined()){
					ExpansionCodeLock codelock = ExpansionCodeLock.Cast(base_building.GetAttachmentByConfigTypeName("ExpansionCodeLock"));
					if (tablet.WasHackingInterrupted() && tablet.ECLE_GetHackID() == base_building.ECLE_GetHackID()) {
						continueHack = true;
						if ( tablet.CountBatteries() >= GetExpansionCodeLockConfig().BatteriesDoors && codelock ) {
							return true;
						}
					}else if(!tablet.HasHackingStarted() || tablet.WasHackingInterrupted()) {
						continueHack = false;
						if ( tablet.CountBatteries() >= GetExpansionCodeLockConfig().BatteriesDoors && codelock ) {
							return true;
						}
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