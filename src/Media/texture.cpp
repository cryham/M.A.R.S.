#include "Media/texture.hpp"

#include "System/settings.hpp"
#include "System/randomizer.hpp"

#include <SFML/System.hpp>
#include <vector>
#include <iostream>


namespace texture 
{
    namespace
	{
        std::vector<GLuint*> textures_(COUNT);

        void loadTexture_(TextureType type, std::string fileName)
        {
            textures_[type] = new GLuint;
            sf::Image img;
            img.loadFromFile(fileName);

            // convert sf::Image to GLuint
            const sf::Uint8* ptr = img.getPixelsPtr();
            glGenTextures(1, textures_[type]);
            glBindTexture(GL_TEXTURE_2D, *textures_[type]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA,GL_UNSIGNED_BYTE, ptr);

            if (type == Interface ||
                type == Stars1_large || type == Stars2_large ||
                type == Stars1_medium || type == Stars2_medium)
            {
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
            }
            else {
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            }
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    GLuint const& getTexture(TextureType type)
    {
        // if texture is already loaded
        if (textures_[type])
        {
            return *textures_[type];
        }
        else  // load it from file
        {
            auto path = settings::sDataPath;
            switch (type)
            {
                case Home:           loadTexture_(type, path + "tex/spaceObjects/planetPlayer.png"); break;
                case Planet1:        loadTexture_(type, path + "tex/spaceObjects/planet1.png");   break;
                case Planet2:        loadTexture_(type, path + "tex/spaceObjects/planet2.png");   break;
                case Planet3:        loadTexture_(type, path + "tex/spaceObjects/planet3.png");   break;
                case Planet4:        loadTexture_(type, path + "tex/spaceObjects/planet4.png");   break;
                case Planet5:        loadTexture_(type, path + "tex/spaceObjects/planet5.png");   break;
                case Planet6:        loadTexture_(type, path + "tex/spaceObjects/planet6.png");   break;
                case Planet7:        loadTexture_(type, path + "tex/spaceObjects/planet7.png");   break;
                case Planet8:        loadTexture_(type, path + "tex/spaceObjects/planet8.png");   break;
                case Planet9:        loadTexture_(type, path + "tex/spaceObjects/planet9.png");   break;
                case Planet10:       loadTexture_(type, path + "tex/spaceObjects/planet10.png");  break;
                case Planet11:       loadTexture_(type, path + "tex/spaceObjects/planet11.png");  break;
                case Planet12:       loadTexture_(type, path + "tex/spaceObjects/planet12.png");  break;
                case Planet13:       loadTexture_(type, path + "tex/spaceObjects/planet13.png");  break;
                case Planet14:       loadTexture_(type, path + "tex/spaceObjects/planet14.png");  break;
                case Planet15:       loadTexture_(type, path + "tex/spaceObjects/planet15.png");  break;

                case Asteroid1:      loadTexture_(type, path + "tex/spaceObjects/planet3rock1.png");   break;
                case Asteroid2:      loadTexture_(type, path + "tex/spaceObjects/planet3rock2.png");   break;
                case Asteroid3:      loadTexture_(type, path + "tex/spaceObjects/planet3rock3.png");   break;
                case Asteroid4:      loadTexture_(type, path + "tex/spaceObjects/planet13rock1.png");   break;
                case Asteroid5:      loadTexture_(type, path + "tex/spaceObjects/planet13rock2.png");   break;
                case Asteroid6:      loadTexture_(type, path + "tex/spaceObjects/planet13rock3.png");   break;
                case Asteroid7:      loadTexture_(type, path + "tex/spaceObjects/planet14rock1.png");   break;
                case Asteroid8:      loadTexture_(type, path + "tex/spaceObjects/planet14rock2.png");   break;
                case Asteroid9:      loadTexture_(type, path + "tex/spaceObjects/planet14rock3.png");   break;
                case Asteroid10:     loadTexture_(type, path + "tex/spaceObjects/planet7rock1.png");  break;
                case Asteroid11:     loadTexture_(type, path + "tex/spaceObjects/planet7rock2.png");  break;
                case Asteroid12:     loadTexture_(type, path + "tex/spaceObjects/planet7rock3.png");  break;

                case Sun1:           loadTexture_(type, path + "tex/spaceObjects/sun1.png");      break;
                case Sun2:           loadTexture_(type, path + "tex/spaceObjects/sun2.png");      break;
                case Sun3:           loadTexture_(type, path + "tex/spaceObjects/sun3.png");      break;
                case Sun4:           loadTexture_(type, path + "tex/spaceObjects/sun4.png");      break;
                case SunHeat:        loadTexture_(type, path + "tex/spaceObjects/sunHeat.png");   break;
                
                case Ice:            loadTexture_(type, path + "tex/ice.png");                    break;
                case Bolt:           loadTexture_(type, path + "tex/bolt.png");                   break;
                case Cracks:         loadTexture_(type, path + "tex/cracks.png");                 break;
                case Hole1:          loadTexture_(type, path + "tex/spaceObjects/hole1.png");     break;
                case Ball:           loadTexture_(type, path + "tex/ball.png");                   break;
                case Particles:      loadTexture_(type, path + "tex/particles.png");              break;
                case PowerUps:       loadTexture_(type, path + "tex/powerUps.png");               break;
                case Ships:          loadTexture_(type, path + "tex/ships.png");                  break;
                case Weapons:        loadTexture_(type, path + "tex/weapons.png");                break;
                
                // case MotherShip:            loadTexture_(type, path + "tex/motherShip.png");             break;
                // case MotherShipPlayerLayer: loadTexture_(type, path + "tex/motherShipPlayerLayer.png");  break;
                
                case Sign1:          loadTexture_(type, path + "tex/signs/sign1.png");            break;
                case Sign2:          loadTexture_(type, path + "tex/signs/sign2.png");            break;
                case Logo1:          loadTexture_(type, path + "tex/logos/logo1.png");            break;

                case Cannon:         loadTexture_(type, path + "tex/cannon.png");                 break;
                case CannonSocket:   loadTexture_(type, path + "tex/cannonSocket.png");           break;
                case Stars1_large:   loadTexture_(type, path + "tex/background/starfield_1_large.jpg");    break;
                case Stars1_medium:  loadTexture_(type, path + "tex/background/starfield_1_medium.jpg");   break;
                case Stars2_large:   loadTexture_(type, path + "tex/background/starfield_2_large.jpg");    break;
                case Stars2_medium:  loadTexture_(type, path + "tex/background/starfield_2_medium.jpg");   break;
                case Star:           loadTexture_(type, path + "tex/background/star.png");        break;

                case EnergyBars:     loadTexture_(type, path + "tex/interface/energyBars.png");   break;
                case Widgets:        loadTexture_(type, path + "tex/interface/widgets.png");      break;
                case Interface:      loadTexture_(type, path + "tex/interface/interface.png");    break;
                case CountDown0:     loadTexture_(type, path + "tex/countdown/0.png");            break;
                case CountDown1:     loadTexture_(type, path + "tex/countdown/1.png");            break;
                case CountDown2:     loadTexture_(type, path + "tex/countdown/2.png");            break;
                case CountDown3:     loadTexture_(type, path + "tex/countdown/3.png");            break;
                case CountDown4:     loadTexture_(type, path + "tex/countdown/4.png");            break;
                case ShockWave:      loadTexture_(type, path + "tex/shockwave.png");              break;
                case COUNT:
                    std::cout << "COUNT is not a valid Texturetype..." << std::endl;
            }
            return *textures_[type];
        }
    }

    TextureType const randomPlanet()
    {
        int randomInt = randomizer::random(1, 15);
        switch (randomInt)
        {
            case  1:  return Planet1;
            case  2:  return Planet2;
            case  3:  return Planet3;
            case  4:  return Planet4;
            case  5:  return Planet5;
            case  6:  return Planet6;
            case  7:  return Planet7;
            case  8:  return Planet8;
            case  9:  return Planet9;
            case 10:  return Planet10;
            case 11:  return Planet11;
            case 12:  return Planet12;
            case 13:  return Planet13;
            case 14:  return Planet14;
            default:  return Planet15;
        }
    }

    Color3f const getMudColor(TextureType type)
    {
        switch (type)
        {
            case Planet1:   return Color3f(1.0f, 1.0f, 0.3f);
            case Planet2:   return Color3f(1.0f, 0.3f, 0.9f);
            case Planet3:   return Color3f(1.0f, 0.6f, 1.0f);
            case Planet4:   return Color3f(0.6f, 0.3f, 1.0f);
            case Planet5:   return Color3f(1.0f, 0.5f, 0.8f);
            case Planet6:   return Color3f(0.0f, 0.8f, 1.0f);
            case Planet7:   return Color3f(0.3f, 0.3f, 0.3f);
            case Planet8:   return Color3f(0.2f, 1.0f, 0.2f);
            case Planet9:   return Color3f(1.0f, 0.0f, 0.0f);
            case Planet10:  return Color3f(1.0f, 1.0f, 0.5f);
            case Planet11:  return Color3f(0.7f, 0.7f, 0.2f);
            case Planet12:  return Color3f(1.0f, 0.6f, 0.8f);
            case Planet13:  return Color3f(0.5f, 1.0f, 1.0f);
            case Planet14:  return Color3f(1.0f, 1.0f, 0.0f);
            case Planet15:  return Color3f(1.0f, 0.7f, 0.0f);
            default :       return Color3f(1.f, 1.f, 1.f);
        }
    }
}
