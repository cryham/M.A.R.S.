#include <Shaders/postFX.hpp>

#include "System/timer.hpp"
#include "System/settings.hpp"
#include "Particles/particles.hpp"
#include "DecoObjects/decoObjects.hpp"

#include <SFML/OpenGL.hpp>
#include <iostream>


namespace postFX
{
    namespace
    {
        sf::Shader        postFX_;
        sf::RenderTexture bumpMap_;
        float             exposure_(1.f);
        float             flashTimer_(0.f);
    }

    void update()
    {
        if (settings::bShaders)
        {
            bumpMap_.setActive(true);
            bumpMap_.clear(sf::Color(127, 0, 127));

            // glViewport(0, 0, settings::C_MapXsize*0.5f / window::scale_x(), settings::C_MapYsize*0.5f / window::scale_y());
            glViewport(0, 0, settings::iMapXsize*0.5f, settings::iMapYsize*0.5f);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();

            // glOrtho(0.f, settings::C_MapXsize / window::scale_x(), settings::C_MapYsize / window::scale_y(), 0.f, -1, 1);
            glOrtho(0.f, settings::iMapXsize, settings::iMapYsize, 0.f, -1, 1);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            

            particles::drawHeat();
            decoObjects::drawHeat();

            bumpMap_.display();

            if (flashTimer_ > 0)
            {   flashTimer_ -= timer::frameTime();

                if (flashTimer_ > 0.4f)
                    exposure_ = (0.5f - flashTimer_)*5.f + 1.f;
                else if (flashTimer_ > 0)
                    exposure_ = flashTimer_ * 1.25f + 1;
                else
                    exposure_ = 1.f;
            }
            if (!settings::bFlashes)  // disables
                exposure_ = 1.f;
            postFX_.setUniform("Exposure", exposure_);
        }
    }

    void onExplosion()
    {
        flashTimer_ = 0.5f;
    }

    sf::Shader* get()
    {
        return &postFX_;
    }

    bool supported()
    {
        return (sf::Shader::isAvailable());
    }

    void load()
    {
        if (supported())
        {
            postFX_.loadFromFile(settings::sDataPath + "shaders/bump.frag", sf::Shader::Fragment);
            bumpMap_.create(settings::iMapXsize*0.5f, settings::iMapYsize*0.5f);
            // glViewport(0,0,settings::C_MapXsize*0.5f, settings::C_MapYsize*0.5f);
            // glOrtho(0, settings::C_MapXsize, settings::C_MapYsize, 0, -1, 1);
            // glEnable(GL_BLEND);
            // glMatrixMode(GL_MODELVIEW);
            postFX_.setUniform("BumpMap", bumpMap_.getTexture());
            postFX_.setUniform("Exposure", exposure_);
        }
        else
            std::cout << "Shaders are not supported on your hardware! There will be no fancy graphics..." << std::endl;
    }
}
