class ExpansionCodeLockConfig
{ 

	private static string ExpansionCodeLockPATH = "$profile:\\ExpansionCodeLockExpanded.json";
	//Default Values
	string ConfigVersion = "6";
	bool AllowLockUnlockFromAnywhere = false;
	bool AllowCodeLocksOnTents = true;
	
	bool ResetLifeTimeOnOpen = true;
	
	
	bool AllowHacksawRaiding = false;
	float HacksawRaidTime = 600;
	float HacksawRaidIncrements = 5;
	float HackSawDamage = 300;
	
	
	// 0 - Native Notification
	// 1 - Chat Notification
	// 2 - BuiltIn Notification
	ref array<ref ECLEHackableItem> HackableItems = new ref array<ref ECLEHackableItem>;
	bool ScriptLogging = false;
		
	bool NEW_SETUP = true;
	
	// Load config file or create default file if config doesn't exsit
	void Load(){
		if (GetGame().IsServer()){
			if (FileExist(ExpansionCodeLockPATH)){ //If config exist load File
				JsonFileLoader<ExpansionCodeLockConfig>.JsonLoadFile(ExpansionCodeLockPATH, this);
				if (ConfigVersion != "6"){
					ref OldExpansionCodeLockConfig oldConfig = new ref OldExpansionCodeLockConfig;
					JsonFileLoader<OldExpansionCodeLockConfig>.JsonLoadFile(ExpansionCodeLockPATH, oldConfig);
					if (oldConfig.ConfigVersion == "5"){
						if (oldConfig.AllowHackingTents){
							HackableItems.Insert( new ref ECLEHackableItem("tent", oldConfig.HackStartTimeTents, oldConfig.HackingTimeTents, oldConfig.BatteriesTents, false));
							HackableItems.Insert( new ref ECLEHackableItem("expansionsafe", oldConfig.HackStartTimeTents+30, oldConfig.HackingTimeTents+300, oldConfig.BatteriesTents+1, true));
						}
						if (oldConfig.AllowHackingDoors){
							HackableItems.Insert( new ref ECLEHackableItem("fence", oldConfig.HackStartTimeDoors, oldConfig.HackingTimeDoors, oldConfig.BatteriesDoors, false));
							HackableItems.Insert( new ref ECLEHackableItem("ExpansionWall", oldConfig.HackStartTimeDoors, oldConfig.HackingTimeDoors, oldConfig.BatteriesDoors, false));
							HackableItems.Insert( new ref ECLEHackableItem("bbp_t1", oldConfig.HackStartTimeDoors, oldConfig.HackingTimeDoors, oldConfig.BatteriesDoors, false));
							HackableItems.Insert( new ref ECLEHackableItem("bbp_t2", oldConfig.HackStartTimeDoors, oldConfig.HackingTimeDoors, oldConfig.BatteriesDoors,  false));
							HackableItems.Insert( new ref ECLEHackableItem("bbp_t3", oldConfig.HackStartTimeDoors, oldConfig.HackingTimeDoors, oldConfig.BatteriesDoors,  false));
						}
						
						AllowLockUnlockFromAnywhere = oldConfig.AllowLockUnlockFromAnywhere;
						AllowCodeLocksOnTents = oldConfig.AllowCodeLocksOnTents;
	
						ResetLifeTimeOnOpen = true;
	
	
						AllowHacksawRaiding = oldConfig.AllowHacksawRaiding;
						HacksawRaidTime = oldConfig.HacksawRaidTime;
						HacksawRaidIncrements = oldConfig.HacksawRaidIncrements;
						HackSawDamage = oldConfig.HackSawDamage;
						ScriptLogging = false;
						NEW_SETUP = true;
						
					} else {
						HackableItems.Insert( new ref ECLEHackableItem("tent", 45, 600, 1, false));
						HackableItems.Insert( new ref ECLEHackableItem("fence", 60, 600, 2, false));
						HackableItems.Insert( new ref ECLEHackableItem("expansionwall", 60, 600, 2, false));
						HackableItems.Insert( new ref ECLEHackableItem("expansionfloor", 90, 1200, 3, false));
						HackableItems.Insert( new ref ECLEHackableItem("bbp_t1", 60, 900, 2, false));
						HackableItems.Insert( new ref ECLEHackableItem("bbp_t2", 90, 1200, 3, false));
						HackableItems.Insert( new ref ECLEHackableItem("bbp_t3", 120, 1800, 5, false));
						HackableItems.Insert( new ref ECLEHackableItem("expansionsafe", 90, 1200, 3, true));
						
						AllowLockUnlockFromAnywhere = false;
						AllowCodeLocksOnTents = true;
	
						ResetLifeTimeOnOpen = true;
	
	
						AllowHacksawRaiding = false;
						HacksawRaidTime = 600;
						HacksawRaidIncrements = 5;
						HackSawDamage = 300;
						ScriptLogging = false;
						NEW_SETUP = true;
					}
					Save();
				}
			}else{ //File does not exist create file
				HackableItems.Insert( new ref ECLEHackableItem("tent", 45, 600, 1, false));
				HackableItems.Insert( new ref ECLEHackableItem("fence", 60, 600, 2, false));
				HackableItems.Insert( new ref ECLEHackableItem("expansionwall", 60, 600, 3, false));
				HackableItems.Insert( new ref ECLEHackableItem("expansionfloor", 60, 600, 3, false));
				HackableItems.Insert( new ref ECLEHackableItem("bbp_t1", 60, 900, 2, false));
				HackableItems.Insert( new ref ECLEHackableItem("bbp_t2", 90, 1200, 3, false));
				HackableItems.Insert( new ref ECLEHackableItem("bbp_t3", 120, 1800, 5, false));
				HackableItems.Insert( new ref ECLEHackableItem("expansionsafe", 90, 1200, 3, true));
				Save();
			}
		} else {
			Print("[ExpansionCodeLock] Trying to load settings before they were received by the server.");
		}
	}
	
	void Save(){
		JsonFileLoader<ExpansionCodeLockConfig>.JsonSaveFile(ExpansionCodeLockPATH, this);
	}
	
	bool CanHack(string ItemType, int Batteries, bool hasCodeLock = true){
		ECLEHackableItem target = GetHackableItem( ItemType );
		if ( target.Type != ""){
			if (Batteries >= target.Batteries){
				return true;
			}
		}
		return false;
	}
	
	float GetStartTime(string ItemType){
		return GetHackableItem(ItemType).StartTime;
	}
	
	
	float GetHackTime(string ItemType){
		return GetHackableItem(ItemType).HackingTime;
	}
	
	ECLEHackableItem GetHackableItem( string ItemType){
		string itemType = ItemType;
		itemType.ToLower();		
		for (int i = 0; i < HackableItems.Count(); i++){
			string toFind = HackableItems.Get(i).Type;
			toFind.ToLower();
			if (itemType.Contains(toFind)){
				return HackableItems.Get(i);
			}
		}
		return new ECLEHackableItem();
	}
	
	bool NewSetup(){
		return NEW_SETUP;
	}
	
	void SetupComplete(){
		NEW_SETUP = false;
		Save();
	}
};



class ECLEHackableItem {
	string Type = "";
	bool IsSafe = false;
	float StartTime = 90;
	float HackingTime = 600;
	int Batteries = 3;
	float TabletDamage = 15;
	float ChanceOfInterrupt = 0.01;
	
	void ECLEHackableItem( string type = "", float start = 60, float time = 600, int bat = 1, bool isSafe = false)
	{
		Type = type;
		StartTime = start;
		HackingTime = time;
		Batteries = bat;
		IsSafe = isSafe;
	}
};


ref ExpansionCodeLockConfig m_ExpansionCodeLockConfig;

//Helper function to return Config
static ref ExpansionCodeLockConfig GetExpansionCodeLockConfig()
{
	if (!m_ExpansionCodeLockConfig)
	{
		m_ExpansionCodeLockConfig = new ExpansionCodeLockConfig;
		m_ExpansionCodeLockConfig.Load();
	}
	return m_ExpansionCodeLockConfig;
};