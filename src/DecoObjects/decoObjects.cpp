/* decoObjects.cpp

Copyright (c) 2010 by Felix Lauer and Simon Schneegans

This program is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option)
any later version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
more details.

You should have received a copy of the GNU General Public License along with
this program.  If not, see <http://www.gnu.org/licenses/>. */

# include "DecoObjects/decoObjects.hpp"

# include "DecoObjects/Cannon.hpp"
# include "DecoObjects/PlanetSign.hpp"
# include "DecoObjects/ShipName.hpp"
# include "DecoObjects/ShipHighlight.hpp"
# include "DecoObjects/Evil.hpp"

# include <SFML/System.hpp>
# include <vector>

namespace decoObjects {

    namespace {
        Cannon* cannon_(NULL);
        std::vector<DecoObject*> decos_;
        std::vector<DecoObject*> names_;
    }

    void update() {
        if (cannon_)
            cannon_->update();
    }

    void draw() {
        if (cannon_)
            cannon_->draw();
        for (std::vector<DecoObject*>::iterator it = decos_.begin(); it != decos_.end(); ++it)
            (*it)->draw();
    }

    void drawNames() {
        for (std::vector<DecoObject*>::iterator it = names_.begin(); it != names_.end(); ++it)
            (*it)->draw();
    }

    void addCannon() {
        cannon_ = new Cannon();
        decos_.push_back(new Evil());
    }

    void addPlanetSign(Planet* planet) {
        decos_.push_back(new PlanetSign(planet));
    }

    void addName(Ship* ship) {
        names_.push_back(new ShipName(ship));
    }

    void addHighlight(Ship* ship) {
        decos_.push_back(new ShipHighlight(ship));
    }

    void clear() {
        if (cannon_) {
            delete cannon_;
            cannon_ = NULL;
        }
        for (std::vector<DecoObject*>::iterator it = decos_.begin(); it != decos_.end(); ++it)
            delete *it;
        for (std::vector<DecoObject*>::iterator it = names_.begin(); it != names_.end(); ++it)
            delete *it;
        decos_.clear();
        names_.clear();
    }
}
