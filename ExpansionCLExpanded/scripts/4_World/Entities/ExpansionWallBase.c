modded class ExpansionWallBase extends ExpansionBaseBuilding
{
	override bool HasCodeLock( string selection )
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
		return super.HasCodeLock(selection);
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
		{
			return false;
		}		
		if ( !ctx.Read( m_ECLE_HackID ) )
		{
			m_ECLE_HackID = 0;
			return false;
		}			
		return true;
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave( ctx );
		
		ctx.Write( m_ECLE_HackID );
	}
}