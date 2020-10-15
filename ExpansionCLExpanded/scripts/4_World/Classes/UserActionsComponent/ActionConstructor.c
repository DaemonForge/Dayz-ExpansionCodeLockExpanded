modded class ActionConstructor
{
	override void RegisterActions( TTypenameArray actions )
	{
		super.RegisterActions( actions );	
		actions.Insert( ActionDestroyExpansionCodeLockOnTent );
		actions.Insert( ActionHackExpansion );
		actions.Insert( ActionRemoveExpansionCodeLockExpanded );

	}
};