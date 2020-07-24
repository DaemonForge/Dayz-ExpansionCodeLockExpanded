# Expansion CodeLock Expanded
 
Allows you to use Expansion Code Locks on Tents and on Vanilla Gates
Also works with Base Building Plus
(With Known non critical Bug See known issues below)

It also allows for raiding of tents with a hacksaw, with a config file to help you adjust the raiding to your liking

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
