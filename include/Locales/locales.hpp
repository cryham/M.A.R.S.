/* locales.hpp

Copyright (c) 2010 by Felix Lauer und Simon Schneegans

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

# ifndef LOCALES_HPP_INCLUDED
# define LOCALES_HPP_INCLUDED

# include <SFML/System.hpp>
# include <vector>

namespace locales {
    enum LocaleType {StartLocalGame, StartNetworkGame, JoinNetworkGame, Options, About, Quit, Continue, RestartGame,
                     HideMenu, QuitCurrentGame, Start, Cancel, Info, Close, License, Ok, ShowAgainButton, LeftTeam,
                     RightTeam, BotsLeft, BotsRight, Bots, Pointlimit, InfoSB, ShortDescriptionSB, InfoDM,
                     ShortDescriptionDM, InfoTDM, ShortDescriptionTDM, InfoCK, ShortDescriptionCK, DebuggingInformation,
                     BotsOrientation, Zones, AIPaths, GameInformation, FramesPerSecond, ParticleCount,
                     ParticleCountSlider, ParticleLifetime, ShowStars, Fullscreen, VerticalSynchronisation, MusicVolume,
                     SoundVolume, AnnouncerVolume, Name, Accelerate, TurnLeft, TurnRight, Weapon, ShipName, Hue,
                     Saturation, Value, KeyEditHover, TextEditHover, AboutText, LicenseText, QuitText,
                     QuitCurrentGameText, StartNetworkText, JoinNetworkText, HideMenuText, Add, BackSlash, Comma, Dash,
                     Delete, Divide, Down, End, Equal, Home, Insert, LeftAlt, LeftBracket, LeftControl, Left, LeftShift,
                     LeftSuper, Menu, Multiply, PageDown, PageUp, Pause, Period, Quote, RightAlt, RightBracket,
                     RightControl, Return,Right, RightShift, RightSuper, SemiColon, Slash, Space, Subtract, Tilde, Tab,
                     Up, Display, Audio, WindowSettings, StartTutorial,Next, Tut01, TutText01, Tut02, TutText02, Tut03,
                     TutText03, Tut04, TutText04, Tut05, TutText05, Tut06, TutText06, Tut07, TutText07, Tut08, TutText08,
                     TutText08b, Tut09, TutText09, Tut10, TutText10, TutText10b, TutText10c, Tut11, TutText11, Tut12,
                     TutText12, Tut13, TutText13, Tut14, TutText14, Tut15, TutText15, Tut16, TutText16, Tut17, TutText17,
                     Tut18, TutText18, Tut19, TutText19, Tut20, TutText20, Interface, StarsHigh, StarsLow, StarsNo, COUNT};

    void                          load();
    std::vector<sf::String> const getLanguages();
    sf::String*                   getLocale(LocaleType);
}

# endif // LOCALES_HPP_INCLUDED

