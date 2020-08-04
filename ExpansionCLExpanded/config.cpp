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
};


