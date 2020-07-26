class ActionRemoveExpansionCodeLockExpandedCB : ActionContinuousBaseCB {
    override void CreateActionComponent() {
		float circleTime = 15; 
      	m_ActionData.m_ActionComponent = new CAContinuousRepeat(circleTime);
    }
}

class ActionRemoveExpansionCodeLockExpanded : ActionContinuousBase {

    void ActionRemoveExpansionCodeLockExpanded() {
        m_CallbackClass = ActionRemoveExpansionCodeLockExpandedCB;
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
        return "Remove Codelock";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
			ItemBase itemParent = ItemBase.Cast(target.GetParent());
			ExpansionCarAdminKey key = ExpansionCarAdminKey.Cast(item);
	

	        if (itemParent && key) {
				if (itemParent.IsLocked() || ExpansionCodeLock.Cast(itemParent.FindAttachmentBySlotName( "Att_ExpansionCodeLock" )) || itemParent.HasCode()) {
						return true;
				}
	        }
    }

    override void OnFinishProgressServer(ActionData action_data) {
        ItemBase itemParent = ItemBase.Cast(action_data.m_Target.GetParent());
		itemParent.Unlock();
		itemParent.SetCode("");
		ExpansionCodeLock codelock = ExpansionCodeLock.Cast(itemParent.FindAttachmentBySlotName( "Att_ExpansionCodeLock" ));
		if(codelock){
			itemParent.GetInventory().DropEntity(InventoryMode.SERVER, itemParent, codelock);
		}
    }
}
