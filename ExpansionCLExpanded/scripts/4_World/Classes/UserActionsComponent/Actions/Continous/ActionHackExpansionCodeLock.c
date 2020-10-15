class ActionHackExpansionCB extends ActionContinuousBaseCB {
    override void CreateActionComponent() {
		float circleTime = 60; 
		if (m_ActionData) {		
			if (m_ActionData.m_Target) {
				ItemBase hacking_target;
				if (Class.CastTo(hacking_target, m_ActionData.m_Target.GetObject()) || Class.CastTo(hacking_target, m_ActionData.m_Target.GetParent()) ) {
					circleTime = GetExpansionCodeLockConfig().GetStartTime(hacking_target.GetType());
				}
			}
		}
      	m_ActionData.m_ActionComponent = new CAContinuousRepeat(circleTime);
    }
};

class ActionHackExpansion : ActionContinuousBase {

	bool continueHack = false;
	bool isSafe = false;
    void ActionHackExpansionCodeLock() {
        m_CallbackClass = ActionHackExpansionCB;
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
		if (isSafe){
			return "Hack Safe";
		}
        return "Hack Codelock";
    }
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
   		ItemBase hacking_target;
		ECLETablet tablet = ECLETablet.Cast(item);
		if (Class.CastTo(hacking_target, target.GetObject()) || Class.CastTo(hacking_target, target.GetParent()) ){
			if (tablet && hacking_target.IsLocked()){
				ExpansionCodeLock codelock = ExpansionCodeLock.Cast(hacking_target.GetAttachmentByConfigTypeName("ExpansionCodeLock"));
				bool hasCodeLock = false;
				if (codelock){
					hasCodeLock = true;
				}
				if (tablet.WasHackingInterrupted() && tablet.ECLE_GetHackID() != 0 && tablet.ECLE_GetHackID() == hacking_target.ECLE_GetHackID()) {
					continueHack = true;
					if ( GetExpansionCodeLockConfig().CanHack( hacking_target.GetType(), tablet.CountBatteries(), hasCodeLock) ) {
						if (!hasCodeLock){
							isSafe = true;
						}
						return true;
					}
				} else if ((!tablet.HasHackingStarted() || tablet.WasHackingInterrupted())) {
					continueHack = false;
					if ( GetExpansionCodeLockConfig().CanHack( hacking_target.GetType(), tablet.CountBatteries(), hasCodeLock )) {
						if (!hasCodeLock){
							isSafe = true;
						}
						return true;
					}
				}
			}
		}
        return false;
    }

    override void OnFinishProgressServer(ActionData action_data) {

   		ItemBase hacking_target;
		ECLETablet tablet = ECLETablet.Cast(action_data.m_MainItem);
		PlayerBase sourcePlayer = PlayerBase.Cast(action_data.m_Player);
		if (Class.CastTo(hacking_target, action_data.m_Target.GetObject()) || Class.CastTo(hacking_target, action_data.m_Target.GetParent()) ){
	        if (tablet && sourcePlayer && hacking_target) {
	            tablet.StartHackServer(hacking_target, sourcePlayer);
	        }
		}
    }
	
	override void OnFinishProgressClient( ActionData action_data )
	{  
		ECLETablet tablet = ECLETablet.Cast(action_data.m_MainItem);

        if (tablet) {
            tablet.StartHackClient();
        }
	}
};