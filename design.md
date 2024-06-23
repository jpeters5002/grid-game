# GAMEPLAY

Different types of weapons (limited ammo?)
- pellet shooter (shoots projectiles forward)
- lazer gun (shoots hitscan forward)
- heavier weaponry, etc
maybe primary weapon with infinite ammo and secondary has limited, which is used via the 'shoot' command

small amount of credits earned over time, with killing enemies being the primary way of earning credits and the way that scales late game

# COMMANDS

- move <left|right|^up|^down> (Syntax: move(l), move(r), etc.)
- shoot [^direction] (or maybe auto shoot at interval) (Syntax: fire(), altfire()[?], ^aim(<angle/enemy>))
- ^get\_nearest\_enemy [^type] (Syntax: scan([enemy\_type]))

# ONE-TIME-UPGRADES (other than the indicated in commands)

gps -- know current location in the grid
scanner/radar -- get list of enemy position (or position of closest enemy)

# SCALING-UPGRADES

code ram -- increases the number of lines of code for your program
firing speed -- how fast you shoot your primary weapon
health -- how much damage you can take
shields -- extra damage you can take, which regenerates if damage is not taken for awhile
multishot -- shoots 3 projectiles instead of 1 every once in awhile
script command speed -- decreases the time between script commands being run
script branch speed -- decreases the time it takes for a branch in script to be run
script syscall speed -- decreases the time it takes for a syscall in script to be run (things like obtaining data from a radar)
movement speed -- decreases the time it takes to move from one grid cell to the next via move command

# STARTING-OPTIONS

starting difficulty and credit scale -- higher difficulty means higher credits from enemies, not (or really not much) from time passed

