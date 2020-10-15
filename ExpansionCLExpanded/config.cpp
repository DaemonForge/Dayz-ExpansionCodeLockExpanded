class CfgPatches
{
	class ExpansionCLExpanded
	{
		requiredVersion=0.1;
		requiredAddons[]={
			"DayZExpansion_Scripts"
		};
	};
};

class CfgMods
{
	class ExpansionCLExpanded
	{
		dir="ExpansionCLExpanded";
        name="ExpansionCLExpanded";
        credits="DaemonForge, Expansion Mod Team";
        author="DaemonForge";
        authorID="0";
        version="0.1";
        extra=0;
        type="mod";
	    dependencies[]={  "Game", "World", "Mission"};
	    class defs
	    {
			class gameScriptModule
            {
				value = "";
                files[]={
					"ExpansionCLExpanded/scripts/Common",
					"ExpansionCLExpanded/scripts/3_Game" 
				};
            };
			
			class worldScriptModule
            {
                value="";
                files[]={ 
					"ExpansionCLExpanded/scripts/Common",
					"ExpansionCLExpanded/scripts/4_World" 
				};
            };
			
	        class missionScriptModule
            {
                value="";
                files[]={
					"ExpansionCLExpanded/scripts/Common",
					"ExpansionCLExpanded/scripts/5_Mission" 
				};
            };
        };
    };
};
class CfgSlots
{
	class Slot_Att_ECLETabletBattery_1
	{
		name = "Att_ECLETabletBattery_1";
		displayName = "Tablet Battery";
		selection = "att_ECLETabletBattery";
		ghostIcon = "batteryd";
	};
	class Slot_Att_ECLETabletBattery_2
	{
		name = "Att_ECLETabletBattery_2";
		displayName = "Tablet Battery";
		selection = "att_ECLETabletBattery";
		ghostIcon = "batteryd";
	};
	class Slot_Att_ECLETabletBattery_3
	{
		name = "Att_ECLETabletBattery_3";
		displayName = "Tablet Battery";
		selection = "att_ECLETabletBattery";
		ghostIcon = "batteryd";
	};
	class Slot_Att_ECLETabletBattery_4
	{
		name = "Att_ECLETabletBattery_4";
		displayName = "Tablet Battery";
		selection = "att_ECLETabletBattery";
		ghostIcon = "batteryd";
	};
	class Slot_Att_ECLETabletBattery_5
	{
		name = "Att_ECLETabletBattery_5";
		displayName = "Tablet Battery";
		selection = "att_ECLETabletBattery";
		ghostIcon = "batteryd";
	};
};
class CfgVehicles
{
	class Container_Base;
	class CombinationLock;
	class Inventory_Base;
	class Battery9V;
	
	class MediumTent: Container_Base
	{
		attachments[] = {"CamoNet","Lights","Att_ExpansionCodeLock"};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				name = "$STR_CfgVehicles_Fence_Att_Category_Attachments";
				description = "";
				attachmentSlots[] = {"Att_ExpansionCodeLock"};
				icon = "cat_bb_attachments";
				selection = "wall";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 0;
			};
		};
	};
	class LargeTent: Container_Base
	{
		attachments[] = {"CamoNet","Lights","Att_ExpansionCodeLock"};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				name = "$STR_CfgVehicles_Fence_Att_Category_Attachments";
				description = "";
				attachmentSlots[] = {"Att_ExpansionCodeLock"};
				icon = "cat_bb_attachments";
				selection = "wall";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 0;
			};
		};
	};
	class CarTent: Container_Base
	{
		attachments[] = {"CamoNet","Lights","Att_ExpansionCodeLock"};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				name = "$STR_CfgVehicles_Fence_Att_Category_Attachments";
				description = "";
				attachmentSlots[] = {"Att_ExpansionCodeLock"};
				icon = "cat_bb_attachments";
				selection = "wall";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 0;
			};
		};
	};
	
	class PartyTent: Container_Base
	{
		attachments[] = {"CamoNet","Lights","Att_ExpansionCodeLock"};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				name = "$STR_CfgVehicles_Fence_Att_Category_Attachments";
				description = "";
				attachmentSlots[] = {"Att_ExpansionCodeLock"};
				icon = "cat_bb_attachments";
				selection = "wall";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 0;
			};
		};
	};
	
	class ExpansionCodeLock: Inventory_Base
	{
		inventorySlot[] = {"Att_ExpansionCodeLock","Att_ExpansionCodeLock_1","Att_ExpansionCodeLock_2", "Att_CombinationLock"};
	};
	
	class ECLETablet: Inventory_Base
	{
		scope = 2;
		displayName  = "Decoder Tablet";
		descriptionShort  = "A Tablet Used for hacking into buildings or tents protected by a code lock";
		model = "ExpansionCLExpanded\Data\ECLE_Tablet.p3d"; // "/" was deleted at the begining of path 
		itemSize[] = {3,2};
		weight = 800;
		rotationFlags = 1;
		attachments[] = {"Att_ECLETabletBattery_1", "Att_ECLETabletBattery_2", "Att_ECLETabletBattery_3","Att_ECLETabletBattery_4","Att_ECLETabletBattery_5"};
		hiddenSelections[] = 
		{        
			"zbytek",
			"tablet_on",
			"tablef_off",
			"screen",
			"background",
			"backscreen",
			"top"		
		};
		hiddenSelectionsTextures[] = 
		{
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_off_co.paa",
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_on_co.paa",
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_off_co.paa",
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_off_co.paa",
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_off_co.paa",
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_off_co.paa",
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_off_co.paa"
			
			
			// added  texture to selection
		};        
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_on.rvmat"}},{0.7,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_on.rvmat"}},{0.5,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_damage.rvmat"}},{0.3,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_damage.rvmat"}},{0.0,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_destruct.rvmat"}}};
				};
			};
			/*class DamageZones
			{
				class tablet
				{
					class Health
					{
						hitpoints = 100;
						transferToGlobalCoef = 1;
						healthLevels[] = {{1.0,{}},{0.7,{}},{0.5,{}},{0.3,{}},{0.0,{}}};
					};
					componentNames[] = {"tablet"};
				};
			};*/
		};
		class AnimationSources
        {
            class top
            {
                source="user";
                animPeriod=1.0;
                initPhase=0;
            };
        };
	};
	class ECLETabletBattery: Battery9V
	{
		scope = 2;
		displayName  = "Tablet Battery";
		descriptionShort  = "A Battery to put in tablets";
		model = "ExpansionCLExpanded\Data\ECLE_TabletBattery.p3d";
		itemSize[] = {1,1};
		weight = 100;
		rotationFlags = 1;
		inventorySlot[] = {"Att_ECLETabletBattery_1", "Att_ECLETabletBattery_2", "Att_ECLETabletBattery_3","Att_ECLETabletBattery_4","Att_ECLETabletBattery_5"};
		hiddenSelections[] = 
		{        
			"zbytek"
		};
		hiddenSelectionsTextures[] = 
		{
			"ExpansionCLExpanded\Data\textures\ECLE_Battery_co.paa" 
		};        
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 20;
					healthLevels[] = {{1.0,{"ExpansionCLExpanded\Data\textures\ECLE_Battery.rvmat"}},{0.7,{"ExpansionCLExpanded\Data\textures\ECLE_Battery.rvmat"}},{0.5,{"ExpansionCLExpanded\Data\textures\ECLE_Battery.rvmat"}},{0.3,{"ExpansionCLExpanded\Data\textures\ECLE_Battery.rvmat"}},{0.0,{"ExpansionCLExpanded\Data\textures\ECLE_Battery_Ruined.rvmat"}}};
				};
			};
		};
		
	};
};

