modded class ExpansionActionEnterCodeLock
{
	// -----------------------------------------------------------
	// Override ActionCondition
	// -----------------------------------------------------------
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		TentBase tent = TentBase.Cast( target.GetParent() );

		if ( tent )
		{
			m_Target = ItemBase.Cast( target.GetParent() );
			if ( m_Target )
			{
				string selection = m_Target.GetActionComponentName( target.GetComponentIndex() );
				if (m_Target.HasCodeLock( selection ) && !m_Target.IsOpened()){
					return true;
				} else if (m_Target.IsLocked() || (m_Target.HasCode() && !m_Target.IsOpened())){
					return true;
				}
			}		
			return false;
		}
		
		return super.ActionCondition( player, target, item );
	}
}