modded class ExpansionCarAdminKey extends ExpansionCarKey
{
	// ------------------------------------------------------------
	// ExpansionCarAdminKey Constructor
	// ------------------------------------------------------------
	void ExpansionCarAdminKey()
	{

	}
	
	override void SetActions()
	{
		super.SetActions();

        AddAction(ActionRemoveExpansionCodeLockExpanded);
    }
	
}