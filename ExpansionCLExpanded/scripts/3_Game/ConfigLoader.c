class ExpansionCodeLockConfig
{ 
	private static string ExpansionCodeLockPATH = "$profile:\\ExpansionCodeLockExpanded.json";
	
	//Default Values
	string ConfigVersion = "5";
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
		
	
	void ExpansionCodeLockConfig()
	{
		
	}
	
	// Load config file or create default file if config doesn't exsit
	void Load(){
		if(GetGame().IsServer()){
			if (FileExist(ExpansionCodeLockPATH)) //If config exist load File
			{
				JsonFileLoader<ExpansionCodeLockConfig>.JsonLoadFile(ExpansionCodeLockPATH, this);
				if (!ConfigVersion){
					ConfigVersion = "1";
					AllowCodeLocksOnTents = true;
					JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
				}
				if (ConfigVersion == "1"){
					ConfigVersion = "2";
					ScriptLogging = true;
					JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
				}
				if (ConfigVersion == "2"){
					ConfigVersion = "3";
					AllowLockUnlockFromAnywhere = false;
					JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
				}
				
				if (ConfigVersion == "3" || ConfigVersion == "4" ){
					ConfigVersion = "5";
					AllowHacksawRaiding = false;
					HacksawRaidTime = 600;
					HacksawRaidIncrements = 5;
					HackSawDamage = 300;
					AllowLockUnlockFromAnywhere = false;
					AllowHackingTents = true;
					HackStartTimeTents = 45;
					HackingTimeTents = 600;
					TabletDamageTents = 15;
					
					AllowHackingDoors = true;
					HackStartTimeDoors = 90;
					HackingTimeDoors = 900;
					BatteriesDoors = 3;
					TabletDamageDoors = 35;
					ChanceOfInterrupt = 0.01;
					Save();
				}
				
			}else{ //File does not exist create file
				Save();
			}
		}
	}
	
	void Save(){
		JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
	}
	
	bool NewSetup(){
		return false;
	}
	
	void SetupComplete(){
		Print("[ExpansionCodeLock] Running m_ExpansionCodeLockConfig SetupComplete");
		//Save();
	}
};