modded class ExpansionCarAdminKey extends ExpansionCarKey
{	
	override void SetActions()
	{
		super.SetActions();
        AddAction(ActionRemoveExpansionCodeLockExpanded);
    }
	
};