class CfgPatches
{
	class ECLEDefines
	{
		requiredVersion=0.1;
		requiredAddons[]={
		};
	};
};

class CfgMods
{
	class ECLEDefines
	{
		dir="ECLEDefines";
        name="ECLEDefines";
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
					"ECLEDefines/scripts/Common"
				};
            };
			
			class worldScriptModule
            {
                value="";
                files[]={ 
					"ECLEDefines/scripts/Common"
				};
            };
			
	        class missionScriptModule
            {
                value="";
                files[]={
					"ECLEDefines/scripts/Common"
				};
            };
        };
    };
};