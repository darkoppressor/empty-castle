# To do

Bug: Player's lighting color is wonky. It looks like certain positions cause the player to show as fully in darkness.

Need ability to link tiles to other maps, allowing travel between maps

Ambient light for map

Implement attack, defense, health, taking damage for tiles and creatures (taking attack type vs material if needed)

Figure out "max acceptable light sources within certain distance" based on some base value factored by runtime system CPU power
Add function (triggered by console command) for walking through ALL maps, determining if there are any points affected by more than max acceptable lights
Function logs this data for all maps to log files
This will help me make sure light sources are generally spaced out enough in my maps to ensure great performance
