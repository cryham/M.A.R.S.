## CryHam's Fork

This is my fork with many **new** features and changes:
- Gameplay
   - New **keys** for player ship:  
     - *Backwards* accelerate
     - *Boost* - holding does accelerate faster
       and with left/right goes *sideways* instead of turning
     - Next, previous *weapon change*, at any time
   - **Mouse aim** and ship rotation (option, for one player)
   - **New Weapons** - 16 total:  
     - 7 new **Weapons** - fast, excessive:  
       AFK-85 (more short lasers), Plasma (fast, straight balls),  
       H2O-Storm (fast, random balls), Flamer2 (strong),  
       Shotgun2 (fast), MiniRockets, Rifle2
     - 9 new **Weapons**:  
       Laser (long), Minigun (fast), Seekers (homing rockets),  
       WIP: Gauss (cannon), Grenades (explosives),  
       Pulse (arc area), Cloud (area), WIP: Freezers, Lightning
   - **Map Options** window, with sliders for:  
     - min,max count of space objects (planets, stars, black holes)
     - and their radius range, also minimal gap between
     - radius of: ships, home planets, ball
     - *Cyclic borders*, gravity scale
   - **Game options** window with sliders:
     - Damage scale, Respawn delay, Life and fuel *regeneration*
     - Ship turn speed, ship glow amount
   - more possible bots, more kills to end game
   - Ship thrusters now blue
   - ToDo: turrets, near team homes, or any middle, destroyable, respawned
- **Gui**
  - **Scale** slider for whole Gui in Options
  - bigger Gui, font, by default, added some colors
  - color Skyblue, not Pink-Red, transparent, single window
  - split Options to 2 new **tabs**: Ship (colors etc) and View (Fps, debug etc)
  - new options:
    - to disable flashes when using post effect shaders
    - no confirmation dialogs
    - no logo, signs
    - countdown seconds, 0 will disable
  - fast fade in/out
- Sources - complete change of code formatting, by hand in all files
  - new cpp standard, using auto, not iterator, pragma once
  - braces in own line, at same width for { and }, only when needed
  - 2 line separators after all includes, and between big methods
  - split long lines, add empty lines for clarity


M.A.R.S
=======

**M.A.R.S. - a ridiculous shooter** is a 2D space shooter with awesome visual effects and attractive physics.  
Players can battle each other or computer controlled enemies in exciting game modes. 

Feel free to visit its old **homepage** at http://mars-game.sourceforge.net/

## The Story

In year 3547, civilizations all over the galaxy have settled their own planets, living in peace and harmony with its environment. But outside the contemplative habitats, the GREAT WAR is raging. As a famous fighter on your way to never ending honor and prosperity, you have to protect your planet from the oncoming doom of your jealous neighbours!


## Compiling and installing from source

For information on how to compile the game from source, please feel free to visit [BUILD.md](BUILD.md)


## Doxygen

Documentation for sources, class list, members, hierarchy, diagrams etc.  
can be generated using [Doxygen](https://www.doxygen.nl/).  
Setup for it is in [Doxyfile](../Doxyfile).  
After installing Doxygen (and its needed deps for diagrams), start by `doxygen`.  
Then access it by opening created [doxygen/html/index.html](doxygen/html/index.html).


## License

Copyright (C) 2025 Crystal Hammer
Copyright (C) 2013-2025 Contributors
Copyright (C) 2010-2012 Simon Schneegans and Felix Lauer <marscoreteam@googlemail.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>.
