modded class ActionDialCombinationLockOnTarget: ActionContinuousBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (super.ActionCondition( player, target, item )){
			Fence building = Fence.Cast( target.GetObject() );
			if ( building )
			{
				if ( building.HasCodeLock( "codelock" ) )
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
	
}
