modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();
		GetExpansionCodeLockConfig();
	}
	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);
		if ( identity )
		{
			string playerID = identity.GetPlainId();
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "SendExpansionCodeLocksExpandedSettings", 1500, false, new Param1<ref PlayerBase >( player ));
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "SendExpansionCodeLocksExpandedSettings", 3500, false, new Param1<ref PlayerBase >( player ));
		}
	}
			
	void SendExpansionCodeLocksExpandedSettings( PlayerBase player ){
		if (player.IsPlayerDisconnected()) { return; }
		PlayerIdentity identity = player.GetIdentity();
		if (identity){
			GetRPCManager().SendRPC("ECLE", "RPCExpansionCodeLocksExpandedSettings", new Param1< ExpansionCodeLockConfig >( GetExpansionCodeLockConfig() ), true, identity);
		}
	}
	
}


