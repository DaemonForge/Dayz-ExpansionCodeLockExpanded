modded class ActionConstructor
{
	override void RegisterActions( TTypenameArray actions )
	{
		super.RegisterActions( actions );	
		actions.Insert( ActionDestroyExpansionCodeLockOnTent );
		actions.Insert( ActionHackExpansionCodeLockOnTent );
		actions.Insert( ActionHackExpansionCodeLockOnDoor );
		actions.Insert( ActionRemoveExpansionCodeLockExpanded );

	}
};