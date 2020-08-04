modded class Hacksaw extends ToolBase
{
    override void SetActions()
	{
		super.SetActions();

        AddAction(ActionDestroyExpansionCodeLockOnTent);
    }
}