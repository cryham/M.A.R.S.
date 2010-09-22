/* texture.hpp

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

# ifndef TEXTURE_HPP_INCLUDED
# define TEXTURE_HPP_INCLUDED

# include "System/Color3f.hpp"

# include <SFML/OpenGL.hpp>

namespace texture {
    enum TextureType {Home, Planet1, Planet2, Planet3, Planet4, Planet5, Planet6,
                      Planet7, Planet8, Planet9, Planet10, Planet11, Planet12, Planet13,
                      Sun1, Hole1, Fuel, Ball, BallShade, BallHot, Blub, Flame, Smoke, Fragment,
                      Star, Shield, Sleep, Confused, PoGlare, PoReverse, PoMedikit, PoShield,
                      PoSleep, Glow, Highlight1, Exhaust1, ShipPlayerLayer1, Exhaust2, ShipPlayerLayer2,
                      Exhaust3, ShipPlayerLayer3, Exhaust4, ShipPlayerLayer4, Exhaust5,
                      ShipPlayerLayer5, Exhaust6, ShipPlayerLayer6, Exhaust7, ShipPlayerLayer7, Exhaust8,
                      ShipPlayerLayer8, Exhaust9, ShipPlayerLayer9, Exhaust10,
                      ShipPlayerLayer10, Exhaust11, ShipPlayerLayer11, MotherShip, MotherShipPlayerLayer, Sign1,
                      Sign2, Logo1, Logo1off, Explode, Cannon, CannonSocket, CannonControl, HasControl,
                      WindowOn, WindowOff, EnergyBars, LeftHandle, RightHandle, BottomHandle, TopHandle, COUNT};

    GLuint const& getTexture(TextureType);

    TextureType randomPlanet();

    Color3f getMudColor(TextureType planetTexture);
}

# endif // TEXTURE_HPP_INCLUDED
