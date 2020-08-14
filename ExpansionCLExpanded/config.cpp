#define _ARMA_

class CfgPatches
{
	class ExpansionCLExpanded
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={
			"DZ_Data",
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
	    dependencies[]={ "World", "Mission"};
	    class defs
	    {
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
		displayName = "Battery";
		selection = "att_ECLETabletBattery";
		ghostIcon = "batteryd";
	};
	class Slot_Att_ECLETabletBattery_2
	{
		name = "Att_ECLETabletBattery_2";
		displayName = "Battery";
		selection = "att_ECLETabletBattery";
		ghostIcon = "batteryd";
	};
	class Slot_Att_ECLETabletBattery_3
	{
		name = "Att_ECLETabletBattery_3";
		displayName = "Battery";
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
		displayName  = "Hacking Tablet";
		descriptionShort  = "A Tablet Used for hacking code locks";
		model = "ExpansionCLExpanded\Data\ECLE_Tablet.p3d";
		itemSize[] = {3,2};
		weight = 800;
		rotationFlags = 1;
		attachments[] = {"Att_ECLETabletBattery_1", "Att_ECLETabletBattery_2", "Att_ECLETabletBattery_3"};
		hiddenSelections[] = 
		{        
			"zbytek",
			"screen"
			
		};
		hiddenSelectionsTextures[] = 
		{
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Good.paa",
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Good.paa"
		};       
		hiddenSelectionsMaterials[] = 
		{
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Good.rvmat",
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Glow.rvmat"
		};       
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Good.rvmat"}},{0.7,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Good.rvmat"}},{0.5,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Good.rvmat"}},{0.3,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Ruined.rvmat"}},{0.0,{"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Ruined.rvmat"}}};
				};
			};
			class DamageZones
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
		inventorySlot[] = {"Att_ECLETabletBattery_1", "Att_ECLETabletBattery_2", "Att_ECLETabletBattery_3"};
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

