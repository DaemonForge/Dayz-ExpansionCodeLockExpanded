ref ExpansionCodeLockConfig m_ExpansionCodeLockConfig;

static string ExpansionCodeLockPATH = "$profile:\\ExpansionCodeLockExpanded.json";

class ExpansionCodeLockConfig
{ 
	//Default Values
	string ConfigVersion = "3";
	bool AllowLockUnlockFromAnywhere = false;
	bool AllowCodeLocksOnTents = true;
	bool AllowRaiding = true;
	float RaidTime = 600;
	float RaidIncrements = 5;
	
	float HackSawDamage = 300;
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
				if (ConfigVersion != "2"){
					ConfigVersion = "2";
					ScriptLogging = true;
					JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
				}
				if (ConfigVersion != "3"){
					ConfigVersion = "3";
					AllowLockUnlockFromAnywhere = false;
					JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
				}
				
			}else{ //File does not exist create file
				JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
			}
		}
	}	
}


//Helper function to return Config
static ref ExpansionCodeLockConfig GetExpansionCodeLockConfig()
{
	if (!m_ExpansionCodeLockConfig)
	{
		m_ExpansionCodeLockConfig = new ExpansionCodeLockConfig;
		m_ExpansionCodeLockConfig.Load();
	}
	return m_ExpansionCodeLockConfig;
}
