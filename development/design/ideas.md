# Ideas

No enemies for now
Mostly or entirely, player should be faster than other creatures
Everyone should be pretty slow though

Player light radius becomes exception, depends on equipped light item

Tile light items have concept of being on or off
Player can "use" them to toggle their light state
Or maybe not? Maybe magic needed

Have passage of time

Story stuff happens regardless of player's presence?
Could mean some stuff will be missed on first playthrough
Big theme is knowledge

No Mana?
Some spells have costs of various sorts
gods are involved with magic
Some spells might need to be repeated to take effect
Little or no equipment items in game
Equipment is created, and possibly maintained, through magic

Various enemies or obstacles where magical knowledge, items, cleverness is needed

Powerful enemies that fight you in essentially a magic duel

Written spells in the world provide clues to the way magic works
With knowledge of enough spells, the player can begin to be creative with magic

Magic source material should be incomplete, maybe sometimes conflicting, to show that the source material itself is not a complete list of possibilities

Reputation with various gods affects various magic
Cost might be applied for some spells, like need for a sacrifice, or permanently losing some of a stat
Sanity might affect spell possibilities and effects, as well as be affected by magic, creating a sort of feedback loop

Maybe one kind of magic uses up light, thus making it darker in the area/world as spells are cast
Darkness carries its own dangers...

Play with the player's perceptions
Possibility of falling asleep and dreaming, and more adventure can happen in the dream state

Tiles could affect movement speed potentially

I see a lot of design stuff calling for a concept of "nearby"
This should be defined as a constant in tiles and used for any of these things centered on the source looking "nearby"

I might want to setup submaterials, e.g., TYPES of wood as submaterials of the wood material

Tiles should have HP, as should creatures
If a creature takes damage, it is subtracted from their HP, and they die if their HP hits 0
If a tile takes damage, it has a damage threshold, and doing damage past that "kills" the tile, otherwise it does no damage
Damage is =>
If attack is of type "normal"
    Attack of Source - Defense of Target
If attack is of type "<some element>"
    Attack of Source - Defense of Target (adjusted by Source Attack Type (which element) vs Target Material)

Creatures have a base material which represents what their body is made of
Creatures also have armor which adds defense of the armor material
Armor has a single equipment slot for creatures
Creatures can carry items (including armor) in their inventory (currently thinking no weight system or item limit)

The ultimate "antagonist", if there is such a thing, is the castle itself
Not explicitly inhabited or possessed by anything, it just has its own self somehow

Design principle:
Avoid large open spaces with unseen corners, at least when being symmetric, as this is super tedious if you want to explore everywhere
IF spaces like this exist, don't put anything in them, leave them as pure decoration

I might want to remove background colors for tiles and creatures

I think health and related values should be as small as possible

Maybe one element should be a sort of "negative" element, and it cancels out any other elements

Elements vs elements or elements vs materials have relations which can be "does less damage to", "does more damage to", "takes less damage from", "takes more damage from", "worthless against", "immune to"

For some or all magic, maybe a good rule is a 1-3 range of possible strength values

What can spell strength do?
Need to decide for each effect

Spell strength is always increased by adding more costs
What the costs are depend on the spell effect

Is the magic circle a component or an effect?
Either way could protect the caster from some types of undead (e.g., spirits)

No experience or leveling up
I do want progression, but I want it to be focused on more specific things found (more magic information, a specific item allowing more powerful spells, armor, etc.)
Absolutely nothing can be grinded for

I DO NOT want permadeath
This is more of an exploration game, with difficult sections
Honestly I love the way Soulsborne games handle this
There are specific save spots that are safe, fully heal you, and save your game
The game should also be saved whenever you leave, so you can instantly resume your game
I do want permanent consequences, just not death and the ending of the game
This means that the player should NOT be able to get the game into an unwinnable state
The game SHOULD have pausing support
Respect the player's life and time
Gameplay is mainly real time
You can pause anywhere
You CANNOT cast spells while paused
You CAN look at your inventory, stats, etc. while paused
So allow pausing, and allow any information to be seen while paused, but prevent any gameplay actions to be taken while paused
Singleplayer only
While the game has a lot of the hallmarks, it is in no way a Roguelike or Roguelite
No character selection or creation

For now at least, nothing is randomly generated

Gods exist in the game, and your reputation with them should be easy to understand and influence
They should all be neutral to most actions by the player, and positively influenced by specific player actions
Things can anger them, but those things can't be simple repeatable things like "X god is angered every time you kill something"
Instead, they can be angered by the player essentially choosing to anger them to please another god

Maybe "general" or "natural" spells that don't require a god are actually secretly also calling on a god, just a specific one that hides behind the scenes
So you can use magic based on various gods (some are mutually exclusive), or use "general" magic, but even that is actually secretly appealing a special very secretive god
So magic based on all but one god MUST specifically call upon that god for the spell to work, that god must approve, and there are often other requirements
But "general" magic works for anyone and appears to be simply natural
However, in reality it too relies on a supportive god
There should be ONE god that expects complete devotion with no other god worship
This god basically represents something like a monotheistic religion

Common actions like killing simple creatures have no effect on any god's relation to the player
HOWEVER, the player can dedicate certain actions to a specific god, and this WILL affect the relation with that god

Maybe knowing a specific thing's name might aid in targeting?
I.e., you know the true name of a spirit, thus you can control it much more directly

Magic design:
-------------

Logical magic system

A spell has:
Required components
Effect (what it does)
Target (what is affected by the effect)
Strength (what this does depends on the spell's effect, could be range, damage, etc.)

Components:
Magic circle
Items placed around the circle in a certain way
Words spoken aloud (using the text parser) (does order of words matter? TODO)
Conditions such as time, weather?, seasons?, stars? (time can be relative to an event, e.g., within X minutes of something happening, as well as specifically something like a time of day)
Dead body nearby for sacrifice purposes
Light source nearby (includes ambient light)
Approval of deity
Same spell recently cast nearby

Effects (improved variously by strength):
Move something through space (to a place, or some distance away from something) (moving something some distance might be cheaper than moving something to a specific place)
Change something's material
Summon some element (would want several elements)
Open something
Close something
Summon armor
Kill something

Extra effect thoughts:
"Moving" would depend on several things, like strength of spell, weight of target creature OR material of target tile, pushing vs teleporting
"Changing the material" of a creature affects its base material
Each element, when used to damage something, will be factored by that thing's material's resistance to the element
When an element is summoned (if it doesn't immediately explode due to touching something), it floats in the air in place for a set period of time and then explodes
If an element runs into anything (INCLUDING another element), it explodes
When an element explodes, it affects its tile, plus its tile radius' tiles, plus any creatures in those tiles, AND any elements in those tiles
When two elements collide, if their attack is roughly equal (taking into account elemental strengths vs weaknesses) (within a constant percentage of each other) they both explode,
else the weaker element explodes and the stronger element has its attack reduced by the weaker element's attack (adjusted by element relation) (it and its resulting explosion having no other effect on the stronger element)
When an element is summoned, it is always summoned directly in front of the caster
The "front of the caster" will need to be a special angle from the caster, representing one tile in front of the source
"Opening" a tile might open a door or a window, not affecting most tiles
"Opening" a creature could remove its armor, or even rip it open at greater strengths (strength check must pass armor removal first, affected by armor material, then must pass again to rip creature open, affected by creature heath (note this is NOT affected by defense))
"Closing" a tile or creature does the opposite of "opening" it, so closes tiles or could "squish" a creature, still needing to get past its armor material and health first
Ripping and squishing creatures works almost just like regular damage to creatures, but the damage is => IF Spell strength > Target defense + Target health
So at a general level, spell strengths equate to spell damage, which equates to health (lots of these numbers can fall in similar ranges)
Summon armor summons more powerful armor with greater strength
Summoned armor is automatically equipped, temporarily replacing any regular armor already equipped
Summoned armor lasts until the end of a duration (should there be a duration?), or creature death (armor can be removed early via casting open on self)
"Killing" something outright kills it if possible, otherwise does nothing
Killing might be very expensive, but almost perfectly effective against living creatures
However, killing would be completely ineffective against the undead or inanimate things

Targets:
None (some spells need no target specified)
Self
Nearest other creature(s, depending on strength for some effects)
Nearest tile(s, depending on strength for some effects)
Tile in front of caster (greater strength for some effects might increase the number of tiles affected, up to a circle around the caster)

Technical:
----------

Tab completion for text parser, using known words

Only rerun fov in a given frame if lighting conditions have changed
