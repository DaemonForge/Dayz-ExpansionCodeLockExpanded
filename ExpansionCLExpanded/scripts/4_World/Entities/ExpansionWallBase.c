modded class ExpansionWallBase extends ExpansionBaseBuilding
{
	override bool ExpansionHasCodeLock( string selection )
	{
		if (GetExpansionCodeLockConfig().AllowLockUnlockFromAnywhere){
			if ( m_HasDoor && FindAttachmentBySlotName( "Att_ExpansionCodeLock_1" ) )
			{
				return true;
			}
			if ( m_HasGate && FindAttachmentBySlotName( "Att_ExpansionCodeLock_2" ) )
			{
				return true;
			}
		}
		return super.ExpansionHasCodeLock(selection);
	}
};