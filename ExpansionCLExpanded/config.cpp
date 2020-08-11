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
class CfgVehicles
{
	class Container_Base;
	class CombinationLock;
	class Inventory_Base;
	
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
		model = "\ExpansionCLExpanded\Data\ECLE_Tablet.p3d";
		itemSize[] = {3,2};
		weight = 800;
		rotationFlags = 1;
		attachments[] = {"BatteryD","BatteryD","BatteryD"};
		hiddenSelections[] = 
		{        
			"tablet_on",
			"tablet_off"
		};
		hiddenSelectionsTextures[] = 
		{
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Good.paa",
			"ExpansionCLExpanded\Data\textures\ECLE_Tablet_Ruined.paa",
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
	
};

