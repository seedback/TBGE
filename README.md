# Text Based Game Engine
This project aims to create a framework and engine to make text-based games in the vein of
[Colossal Cave Adventure](https://en.wikipedia.org/wiki/Colossal_Cave_Adventure), an online
player of that game can be found [here](https://dosgames.com/game/colossal-cave-adventure/).

### How it works:
The main premise of this framework is that it bases itself on Locations and Exits mainly,
as well as other objects.
At any point the player will be in any of a number of Locations, and these Locations have
any number of Exits. put simply an Exit will, given the correct input command from the player,
take the player to another Location. Each Location, Exit and other object has their own descriptions,
which will be printed when the player is in the correct Location or is using an Exit or other object.

Later on the plan is to allow for some simple logic when using the commands alowing for some item to
be needed to do a certain action for example, but this is still a ways away.

### Doxygen
This whole project will be documented with the use of the Doxygen tool, and a link to this
documentation can be found here: Link is coming soon

### New releases
As it stands the first release will happen when I have a rudimentary player-input system in
place allowing for a rudimentary system of interacting with an example game, and with this
release there will be included an example game-file. This example will of course be updated
with each subsequent release.
