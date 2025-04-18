#pragma once

#define NO_ZONE 0
#define OWN_HOME 1
#define OWN_TEAM 2
#define ENEMY_HOME 3
#define ENEMY_TEAM 4

#include "System/Vector2f.hpp"
#include "Zones/Zone.hpp"

#include <map>

class Team;
class TacticalZone;
class RasterZone;

/// A namespace which handles several zones for AI calculations.
/// A Zone is an area in space which is useful for tactical
/// calculations, the tutorial and path finding.

namespace zones 
{
    /// Adds a TeamZone.
    /// \param location The location of the Home Planet.
    Zone* addTeamZone(Vector2f const& location);

    /// Adds a HomeZone.
    /// \param location The location of the Home Planet.
    Zone* addHomeZone(Vector2f const& location);

    /// Adds a TutorialZone.
    /// \param location The position in Space.
    /// \param radius The desired size.
    void  addTutorialZone(Vector2f const& location, float radius = 80.f);

    /// Adds some TacticalZones.
    /// Depending on the space layout there may more than one TacticalZone.
    void detectTacticalZones();

    /// Adds some RasterZones.
    /// \param dimX Amount of zones horizontally.
    /// \param dimY Amount of zones vertically.
    void createRaster(int dimX, int dimY);

    /// Updates all zones.
    void update();

    /// Updates all TutorialZones.
    /// Returns true, when there are no TutorialZones left.
    bool updateTutZones();

    /// Draws every Zone.
    void draw();


    std::map<float, TacticalZone*> const toProtect(Team* checker);

    /// Returns a pointer to a not-covered RasterZone.
    /// Useful for escaping behaviour.
    RasterZone*   freeZone();

    /// Returns the total area of all TacticalZones on a side of the Game.
    /// \param homeSide Side of the field to calculate.
    float totalTacticalArea(short homeSide);

    /// Returns a short, indicating in which Zone a SpaceObject is.
    /// \param checker The team who asks for a Zone.
    /// \param toBeChecked The SpaceObject which is checked.
    short isInside(Team* checker, SpaceObject const& toBeChecked);

    /// Removes every Zone.
    void clear();
}


