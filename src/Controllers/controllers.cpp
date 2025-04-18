#include "Controllers/KeyController.hpp"
#include "Controllers/BotController.hpp"
#include "System/settings.hpp"
#include "Players/Player.hpp"

#include <SFML/Window.hpp>


namespace controllers 
{
    namespace
	{
        KeyController* keyControllers1_ = nullptr;
        KeyController* keyControllers2_ = nullptr;
        std::vector<BotController*> botControllers_;
    }

    void update()
    {
        if (keyControllers1_ && (settings::bPlayer1teamL || settings::bPlayer1teamR))
            keyControllers1_->update();
        if (keyControllers2_ && (settings::bPlayer2teamL || settings::bPlayer2teamR))
            keyControllers2_->update();

        for (auto& it : botControllers_)
            it->update();
    }

    void singleKeyEvent(Key const& keyCode)
    {
        if (keyControllers1_ && (settings::bPlayer1teamL || settings::bPlayer1teamR))
            keyControllers1_->update(keyCode);
        if (keyControllers2_ && (settings::bPlayer2teamL || settings::bPlayer2teamR))
            keyControllers2_->update(keyCode);
    }

    void draw()
    {
        for (const auto& it : botControllers_)
            it->draw();
    }

    BotController* addBotController(Player* slave, float strength)
    {
        BotController* bot = new BotController(slave, strength);
        botControllers_.push_back(bot);
        return bot;
    }

    KeyController* addKeyController(Player* slave)
    {
        switch (slave->type())
        {
            case cPlayer1:
                keyControllers1_ = new KeyController(slave);
                return keyControllers1_;
            default:
                keyControllers2_ = new KeyController(slave);
                return keyControllers2_;
        }
    }

    void resetBots()
    {
        for (auto& it : botControllers_)
            it->reset();
    }

    void clear()
    {
        delete keyControllers1_;
        delete keyControllers2_;
        keyControllers1_ = nullptr;
        keyControllers2_ = nullptr;

        for (auto& it : botControllers_)
            delete it;
        botControllers_.clear();
    }
}
