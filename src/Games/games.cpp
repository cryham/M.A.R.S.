#include "Games/games.hpp"

#include "Games/Game.hpp"
#include "Games/CannonKeep.hpp"
#include "Games/DeathMatch.hpp"
#include "Games/MenuGame.hpp"
#include "Games/SpaceBall.hpp"
#include "Games/GraveItation.hpp"
#include "Games/TeamDeathMatch.hpp"
#include "Games/Rally.hpp"
#include "Games/Tutorial.hpp"
#include "System/settings.hpp"
#include "System/timer.hpp"
#include "Media/music.hpp"
#include "Menu/menus.hpp"
#include "Hud/hud.hpp"
#include "System/window.hpp"
#include "Shaders/postFX.hpp"

#include <SFML/OpenGL.hpp>


namespace games
{
    namespace
    {
        Game* currentGame_= nullptr;
        bool restart_ = false;
        bool newGame_ = true;
        GameType newGameType_ = gNoGame;
        bool fadeOut_ = false;
        bool fadeIn_ = false;
        float fadeFactor_ = 1.f;

        void fade()
        {
            if (fadeIn_)
            {
                fadeFactor_ -= timer::frameTime()*9.f;
                if (fadeFactor_ <= 0.f)
                {   fadeFactor_ = 0.f;
                    fadeIn_ = false;
                }
            }
            else if (fadeOut_)
            {
                fadeFactor_ += timer::frameTime()*9.f;
                if (fadeFactor_ >= 1.f)
                {   fadeFactor_ = 1.f;
                    fadeOut_ = false;
                }
            }

            Vector2f viewPort = window::getViewPort();

            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin(GL_QUADS);
                glColor4f(0.0,0.0,0.0,fadeFactor_);
                glVertex2f(0.f, 0.f);
                glVertex2f(0.f, viewPort.y_);
                glVertex2f(viewPort.x_, viewPort.y_);
                glVertex2f(viewPort.x_, 0.f);
            glEnd();
        }
    }


    void update()
    {
        music::update();

        if (!fadeIn_ && !fadeOut_)
            currentGame_->update();
        
        if (restart_ && !fadeOut_)
            restart();
        
        if (newGame_ && !fadeOut_)
            start(newGameType_);
    }


    void draw()
    {
        postFX::update();

        window::startDrawSpace();

        currentGame_->draw();

        window::startDrawHUD();

        hud::draw();
        menus::draw();
        hud::drawMessages();

        if (fadeIn_ || fadeOut_)
            fade();
    }


    void start(GameType const& type)
    {
        if (!newGame_)
        {
            newGameType_ = type;
            newGame_ = true;
            fadeOut_ = true;
        }else
        {
            if (currentGame_)
            {
                delete currentGame_;
                currentGame_ = 0;
            }
            switch (type)
            {
                case gMenu:              currentGame_ = new MenuGame();       break;
                case gSpaceBall:         currentGame_ = new SpaceBall();      break;
                case gDeathMatch:        currentGame_ = new DeathMatch();     break;
                case gTeamDeathMatch:    currentGame_ = new TeamDeathMatch(); break;
                case gCannonKeep:        currentGame_ = new CannonKeep();     break;
                case gGraveItation:      currentGame_ = new GraveItation();   break;
                case gTutorial:          currentGame_ = new Tutorial();       break;
                case gRally:             currentGame_ = new Rally();       break;
                default: break;
            }
            newGame_ = false;
            fadeIn_  = true;
        }
    }

    void restart()
    {
        if (!restart_)
        {
            restart_ = true;
            fadeOut_ = true;
        }else
        {   currentGame_->restart();
            restart_ = false;
            fadeIn_  = true;
        }
    }

    bool active()
    {
        return !fadeIn_ && !fadeOut_;
    }

    bool ended()
    {
        return currentGame_->ended();
    }

    GameType type()
    {
        if (currentGame_)
            return currentGame_->type();
        else
            return gNoGame;
    }

    float elapsedTime()
    {
        if (currentGame_)
            return currentGame_->elapsedTime();
        else
            return 0.f;
    }
}
