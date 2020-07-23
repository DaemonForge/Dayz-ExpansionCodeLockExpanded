ref ExpansionCodeLockConfig m_ExpansionCodeLockConfig;

static string ExpansionCodeLockPATH = "$profile:\\ExpansionCodeLockExpanded.json";

class ExpansionCodeLockConfig
{ 
	//Default Values
	bool AllowRaiding = true;
	float RaidTime = 600;
	float RaidIncrements = 5;
	
	float HackSawDamage = 300;
		
	
	void ExpansionCodeLockConfig()
	{

	}
	
	// Load config file or create default file if config doesn't exsit
	void Load(){
		if(GetGame().IsServer()){
			if (FileExist(ExpansionCodeLockPATH)) //If config exist load File
			{
				JsonFileLoader<ExpansionCodeLockConfig>.JsonLoadFile(ExpansionCodeLockPATH, this);
				if(!RaidIncrements){
					ExpansionCodeLockConfigOld oldconfig;
					JsonFileLoader<ExpansionCodeLockConfigOld>.JsonLoadFile(ExpansionCodeLockPATH, oldconfig);
					RaidIncrements = oldconfig.RaidIncerments;
					JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
				}
			}else{ //File does not exist create file
				JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
			}
		}
	}	
}

class ExpansionCodeLockConfigOld
{ 
	//Default Values
	bool AllowRaiding = true;
	float RaidTime = 600;
	float RaidIncerments = 5;
	
	float HackSawDamage = 300;
		
	
	void ExpansionCodeLockConfigOld()
	{

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
