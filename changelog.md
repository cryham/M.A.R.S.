Version 0.8.0

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
   - **Turrets** WIP
     - possible on team home or any planets
     - destroyable, respawned
   - **Map Options** window, with sliders for:  
     - *map size*, with 7 button presets (from Tiny to Huge)
     - min,max count of space objects (planets, stars, black holes)
     - and their radius range, also minimal gap between
     - percentage of black holes and now *3 types* of suns
     - radius of: ships, home planets, ball
     - *Cyclic borders*, gravity scale
   - **Game options** window with sliders:
     - Damage scale, Respawn delay, Life and fuel *regeneration*
     - Ship turn speed, ship glow amount, Aiming ray
   - more possible bots, more kills to end game
   - Ship thrusters now blue
- ToDo:
   - game effects from weapons: shock no weapons, chill slow move
   - 2nd weapon? timed regen or passive ability
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
  - immediate clicking, on mouse press, not release
  - anti aliasing, slider
- Sources - complete change of code formatting, by hand in all files
  - new cpp standard, using auto, not iterator, pragma once
  - braces in own line, at same width for { and }, only when needed
  - 2 line separators after all includes, and between big methods
  - split long lines, add empty lines for clarity
