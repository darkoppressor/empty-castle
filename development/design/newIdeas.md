# New ideas

Spell strength could affect:
Range
Duration
Damage
Healing
Number of targets
Success chance

Spell effect ideas:
Restore health
Restore sanity
Render invisible
Create field of protection (from elements, creatures cannot pass, other magic?) This could be combined with dispelling elements and or magic
Create field of paralysis
Summon creature
Bind creature (make it an ally) temporarily
Banish creature

I think I'll want the game to begin in some kind of peaceful setting
There will likely be friendly human creatures
They might be interactive, so the player can speak to them
The player ultimately ends up entering the castle somehow, and at some point inside is transported to the main location of the game and cannot go back

Sanity is a resource that the player has
Certain things reduce sanity, such as seeing monsters or horrible things, or casting sanity magic
Also maybe spending time in complete darkness
Sanity is probably refilled when resting
Sanity can maybe also be restored with magic
Maybe also with drugs that only restore it temporarily
Mostly though, it should act kind of like a second health bar that is tougher to refill on the go
Lower sanity has negative effects of some kind, ideas:
When sanity is gone, health is decreased instead of it
Low enough sanity outright kills the player
Low enough sanity causes creatures to phase in
Even lower sanity makes them hostile
Low enough sanity causes hallucinations

I want pausing

Save points should provide light

I think I might want to generalize the summoning effect so it can summon whatever
I might also merge it with healing magic (like create in Ars Magical)

There could certainly be light magic of some kind
Maybe this fits into summoning
This would cause the player to cast inner light
Inner light doesn't time out
Inner light can be consumed by dark magic, and will be used before equipped item light (if lit), which is used before ambient light

Probably no spell stuff just simply times out

No experience points or levels
No skills or improving of skills or anything either
No way to gain max health probably
There might be equipment that improves stats
There is definitely magic equipment that improves stats
However, many creatures in the game will be far too powerful for the player throughout the game
I believe I want sanity to be a mechanic
Save spots exist and work like in soulsbornes

One cool idea is a room that exists in a different time, so in there the castle is still occupied

Should probably have stamina for physical attacks
Should there be sprinting? Probably

I'm going to want to somehow limit the use of magic from the beginning
I didn't want to originally but I may decide it is necessary
To do so, I could limit the acquisition of items needed for casting

Creatures wear equipment
Equipment is armor, weapon, or light, one slot max for each per creature
Armor provides a defense against physical damage
Armor is made of some material
Elemental damage is affected by armor's material, in that the damage is reduced or increased depending on the element material relationship
Creatures are themselves made of a material
Creature material affects the damage from elemental damage
Physical damage is simply reduced by defense and then subtracted from health
Elemental damage is modifed first by armor material, then by creature material, and this can even lead to the damage being completely negated
Weapons are melee weapons
Weapons have a physical damage value
Weapons have a material
Melee attacks are carried out by running into the target, as in standard roguelikes
Lights have all the various features of light sources

The player should only have very limited equipment options
Equipment exists in the world as an item that can be "used" to swap it with the player's current equipment

Summoned or enchanted armor (whichever I go with) should have options for adding protection against physical or an element (only one at a time)
This will allow for quickly casting a spell to swap armor type to protect against a specific threat
Probably no enchantment or whatever for weapons

Maybe no need for sub materials
Might need to rethink how physical attacks are actually done, since the "running into" mechanic doesn't make much sense here
Should have creatures cast shadows (except for spirits)
Need to add creature collision
Creatures should be able to toggle their light item
Creatures should be able to be larger than one tile (probably still square though)
If I ever add tile graphics, I want you to be able to switch back and forth between those and ASCII whenever you want

If nonplayer creature loses equipment, it is gone forever
They can't gain or change equipment

Creatures can use magic to apply elemental defense to themselves

Physical attacks are only made by one creature against another creature
When a physical attack is made, the attacker's weapon material is checked against the material it is attacking (armor if worn by the target, otherwise target material)
Damage is modified by the material relationship
Damage is then subtracted from the target's health
If the target has elemental defense, the attacker takes elemental damage of the element type
Counter damage is determined by the physical attack's damage (after modifications)
Both damage and counter damage happen simultaneously

Elemental attacks can be made by elements (summoned items) or as counter damage when a creature with elemental defense is attacked physically
Elements can damage creatures and tiles
Counter damage obviously only damages creatures
Elemental damage is first modified by the relation to the target's elemental defense, if any
It is then modified by the relation to the target's material
If the target is a creature, the damage is then subtracted from the target's health
If the target is a tile, the damage is checked against the tile's threshold, and the tile is destroyed if the threshold is passed

Spirit is a special element
A creature can be a spirit
If it is, the creature is composed of the spirit element instead of a material
Physical attacks with any material are ineffective against spirits
Spirits cannot cause counter damage
Spirits cannot wear any equipment
Spirits' physical attacks are replaced by a spirit element melee attack
Spirits' melee attack is ineffective against any material
Spirits cannot have elemental defense
Spirits are affected by sight and tiles like any other creature
Spirits only have creature collision with other spirits
Can the spirit element be used in spells like other elements?
Spirits should probably only be seeable by non spirits sometimes

Damage relationships can be:
Normal: 1x
Weak: 0.5x
Strong: 2x
Ineffective: 0x

Materials:
Stone
Wood
Leather
Flesh
Bone
Metal

Elements:
Fire
Water
Earth
Air
Spirit

Fire is weak against fire
Fire is weak against water
Fire is strong against earth
Fire is normal against air
Fire is ineffective against spirit

Water is strong against fire
Water is weak against water
Water is normal against earth
Water is weak against air
Water is ineffective against spirit

Earth is weak against fire
Earth is normal against water
Earth is weak against earth
Earth is strong against air
Earth is ineffective against spirit

Air is normal against fire
Air is strong against water
Air is weak against earth
Air is weak against air
Air is ineffective against spirit

Spirit is ineffective against fire
Spirit is ineffective against water
Spirit is ineffective against earth
Spirit is ineffective against air
Spirit is strong against spirit

For magic involving circles, they must be made with salt
There should be a magic salt bag in the game that enables this
This bag has a limited number of uses (circles that can be formed) before it is empty
It is refilled when resting
So circle magic has limited uses between rests

Physical attack base damage comes from adding together the creature's attack and the weapon's attack, if any
