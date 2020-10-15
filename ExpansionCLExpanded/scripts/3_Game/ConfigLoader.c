class OldExpansionCodeLockConfig
{ 
	private static string ExpansionCodeLockPATH = "$profile:\\ExpansionCodeLockExpanded.json";
	
	//Default Values
	string ConfigVersion = "0";
	bool AllowLockUnlockFromAnywhere = false;
	bool AllowCodeLocksOnTents = true;
	
	bool AllowHacksawRaiding = false;
	float HacksawRaidTime = 600;
	float HacksawRaidIncrements = 5;
	float HackSawDamage = 300;
	
	bool AllowHackingTents = true;
	float HackStartTimeTents = 45;
	float HackingTimeTents = 600;
	int BatteriesTents = 1;
	float TabletDamageTents = 15;
	
	bool AllowHackingDoors = true;
	float HackStartTimeDoors = 90;
	float HackingTimeDoors = 900;
	int BatteriesDoors = 3;
	float TabletDamageDoors = 35;
	
	float ChanceOfInterrupt = 0.01;
	
	bool ScriptLogging = true;
		
	
	void OldExpansionCodeLockConfig()
	{
		
	}
	
	// Load config file or create default file if config doesn't exsit
	
	bool NewSetup(){
		return false;
	}
	
	void SetupComplete(){
		Print("[ExpansionCodeLock] Running m_ExpansionCodeLockConfig SetupComplete");
		//Save();
	}
};
