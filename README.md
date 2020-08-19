# Expansion CodeLock Expanded
 
Allows you to use Expansion Code Locks on Tents and on Vanilla Gates
Also works with Base Building Plus
(With Known non critical Bug See known issues below)

It also allows for raiding of tents with a hacksaw, with a config file to help you adjust the raiding to your liking

#### Link to published mod: 
[https://steamcommunity.com/sharedfiles/filedetails/?id=2173711903](https://steamcommunity.com/sharedfiles/filedetails/?id=2173711903)

## Raiding Config
```javascript
{
    "AllowRaiding": 1, // 1 enabled / 0 Disabled - If enabled will allow raiding of tents with a hacksaw
    "RaidTime": 600, // Raid time in Seconds how long it will take to raid a tent with a hacksaw
    "RaidIncrements": 5, // How many increments the raiding broken into
    "HackSawDamage": 300 // how much damage the Hacksaw will take after a success full raid 
}
```


## Known Issues
- Code Lock model not showing on Gates(Waiting for Fix)
- In base building plus you will get the next dial and change dial option when looking at the door when its locked with empty hands
- If a Fence is built with admin hatchet and you don't attach a wire to make it a gate after restart you can't reattach a code lock

[Please Report Bugs Here](https://steamcommunity.com/workshop/filedetails/discussion/2173711903/4078523564610860692/)

### Other Info
Native integration with Heroes And Bandits, Action is "ExpansionCodeLockTentRaid"
`#define` is "`EXPANSIONCODELOCKEXPANDED`"

### Repacking/Building from Source Code Rules
For anyone interested in repacking please read all this
- 1st I heavily discourage Repacking/Building from my source code, as it would greatly impact your ability to receive feature updates and bug fixes
- 2nd I will not support any repacks if its is causing conflict that I can't reproduce with the my published mod 
- 3rd YOU MUST PROVIDE CREDIT on the steam page and you must link to the Orginal Mod or the Source Code 
- 3rd B All of the credits I have provided must also be transfered to your page as well otherwise you could be breaking copyright laws as the models are licenced under [Creative Commons](https://creativecommons.org/licenses/by/4.0/)
- 4th Any repacks or builds can only be for personal use no redistributing my mod for public use, should only be for your own servers and players and you must be able to enfore this
- 5th Please ask for permission prior to repacking, almost all request will be approved as long as you have a valid reason to repack
- 6th Also note that the Source Code is the activly developing version so it may not work as it sits here right now so just be warnned.
- 7th Must include the NOTICE file in side the mod with out modification to my text

### Credits
- Huge thanks to @Creep from the Modders discord for his help and work on the textures and updating the model for the tablets
- 3D Model for the Tablet is from https://sketchfab.com/3d-models/tablet-320a95934b0d455e9affcf18859c9937
- 3D Model for the Battery https://sketchfab.com/3d-models/micro-fission-battery-e514d9b7708742878d4cc45db9066da0
