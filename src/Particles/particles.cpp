/* particles.cpp

Copyright (c) 2025 Crystal Hammer
Copyright (c) 2010 - 2011 by Felix Lauer and Simon Schneegans

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

#include "Particles/particles.hpp"

#include "System/settings.hpp"
#include "System/timer.hpp"

#include "Media/text.hpp"
#include "Particles/AmmoAFK47.hpp"
#include "Particles/AmmoBurner.hpp"
#include "Particles/AmmoFlubba.hpp"
#include "Particles/Fuel.hpp"
#include "Particles/Mud.hpp"
#include "Particles/Smoke.hpp"
#include "Particles/Eruption.hpp"
#include "Particles/AmmoROFLE.hpp"
#include "Particles/Dust.hpp"
#include "Particles/Explode.hpp"
#include "Particles/BurningFragment.hpp"
#include "Particles/FragmentFlame.hpp"
#include "Particles/MiniFlame.hpp"
#include "Particles/AmmoShotgun.hpp"
#include "Particles/MiniAmmoFlubba.hpp"
#include "Particles/CannonBall.hpp"
#include "Particles/Spark.hpp"
#include "Particles/AmmoInsta.hpp"
#include "Particles/Fragment.hpp"
#include "Particles/AmmoH2OMG.hpp"
#include "Particles/Heat.hpp"
#include "Particles/HeatJet.hpp"
#include "Particles/ShockWave.hpp"
#include "Particles/HeatBurner.hpp"
#include "Particles/MiniFlameSmoke.hpp"
#include "Particles/AmmoRocket.hpp"
#include "Particles/PowerUpCollect.hpp"
#include "Particles/AmmoFist.hpp"
#include "Particles/Number.hpp"
#include "Particles/CrushedIce.hpp"
#include "Particles/Star.hpp"

#include "Particles/AmmoAFK85.hpp"
#include "Particles/AmmoFlamer2.hpp"
#include "Particles/AmmoPlasma.hpp"
#include "Particles/AmmoRifle2.hpp"
#include "Particles/AmmoShotgun2.hpp"
#include "Particles/AmmoH2OStorm.hpp"
#include "Particles/AmmoMiniRocket.hpp"

#include "Particles/AmmoPulse.hpp"
#include "Particles/AmmoCloud.hpp"
#include "Particles/AmmoFreezers.hpp"
#include "Particles/AmmoLaser.hpp"
#include "Particles/AmmoLightning.hpp"

#include "Particles/AmmoMinigun.hpp"
#include "Particles/AmmoGauss.hpp"
#include "Particles/AmmoGrenades.hpp"
#include "Particles/AmmoSeekers.hpp"

#include "TrailEffects/trailEffects.hpp"


namespace particles 
{
    void update()
    {
        AmmoAFK47::        updateAll();
        AmmoBurner::       updateAll();
        AmmoFlubba::       updateAll();
        Fuel::             updateAll();
        Mud::              updateAll();
        Smoke::            updateAll();
        Eruption::         updateAll();
        AmmoROFLE::        updateAll();
        AmmoShotgun::      updateAll();
        Dust::             updateAll();
        Explode::          updateAll();
        BurningFragment::  updateAll();
        FragmentFlame::    updateAll();
        MiniFlame::        updateAll();
        MiniAmmoFlubba::   updateAll();
        CannonBall::       updateAll();
        Spark::            updateAll();
        Fragment::         updateAll();
        AmmoH2OMG::        updateAll();
        Heat::             updateAll();
        HeatJet::          updateAll();
        ShockWave::        updateAll();
        HeatBurner::       updateAll();
        MiniFlameSmoke::   updateAll();
        AmmoRocket::       updateAll();
        PowerUpCollect::   updateAll();
        AmmoFist::         updateAll();
        Number::           updateAll();
        CrushedIce::       updateAll();
        AmmoInsta::        updateAll();
        Star::             updateAll();
        //  new
        AmmoAFK85::        updateAll();
        AmmoFlamer2::      updateAll();
        AmmoPlasma::       updateAll();
        AmmoRifle2::       updateAll();
        AmmoShotgun2::     updateAll();
        AmmoH2OStorm::     updateAll();
        AmmoMiniRocket::   updateAll();
        //  new 2
        AmmoPulse::        updateAll();
        AmmoCloud::        updateAll();
        AmmoFreezers::     updateAll();
        AmmoLaser::        updateAll();
        AmmoLightning::    updateAll();

        AmmoMinigun::      updateAll();
        AmmoGauss::        updateAll();
        AmmoGrenades::     updateAll();
        AmmoSeekers::      updateAll();
    }

    void drawStars()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Star));
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBegin(GL_QUADS);

            Star::drawAll();

        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void drawLower()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Particles));
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBegin(GL_QUADS);

            AmmoAFK47::        drawAll();
            AmmoFlubba::       drawAll();
            Explode::          drawAll();
            MiniAmmoFlubba::   drawAll();
            MiniFlame::        drawAll();
            AmmoH2OMG::        drawAll();
            Eruption::         drawAll();
            Mud::              drawAll();
            AmmoShotgun::      drawAll();
            AmmoROFLE::        drawAll();
            BurningFragment::  drawAll();
            AmmoInsta::        drawAll();
            FragmentFlame::    drawAll();
            //  new
            AmmoAFK85::        drawAll();
            AmmoFlamer2::      drawAll();
            AmmoPlasma::       drawAll();
            AmmoRifle2::       drawAll();
            AmmoShotgun2::     drawAll();
            AmmoH2OStorm::     drawAll();
            AmmoMiniRocket::   drawAll();
            //  new 2
            AmmoPulse::        drawAll();
            AmmoCloud::        drawAll();
            AmmoFreezers::     drawAll();
            AmmoLaser::        drawAll();
            AmmoLightning::    drawAll();

            AmmoMinigun::      drawAll();
            AmmoGauss::        drawAll();
            AmmoGrenades::     drawAll();
            AmmoSeekers::      drawAll();
        glEnd();

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);

            MiniFlameSmoke::   drawAll();
            Smoke::            drawAll();
            Dust::             drawAll();

        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        Fragment::         drawAll();
    }

    void drawHigher()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Particles));
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBegin(GL_QUADS);

            AmmoBurner::       drawAll();
            Fuel::             drawAll();
            CannonBall::       drawAll();
            Spark::            drawAll();
            CrushedIce::       drawAll();
            //HeatJet::       drawAll();
            //AmmoFist::         drawAll();

        glEnd();

        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);

            AmmoRocket::       drawAll();

        glEnd();
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::PowerUps));
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBegin(GL_QUADS);

            PowerUpCollect::    drawAll();

        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void drawHeat()
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Particles));
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);

            Heat::        drawAll();
            HeatJet::     drawAll();
            HeatBurner::  drawAll();

        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::ShockWave));
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);

            ShockWave::   drawAll();

        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void drawNumbers()
    {
        text::drawFooText();
        Number::drawAll();
        text::drawFooText();
    }

    void spawn(ParticleType const& type, Vector2f const& location, Vector2f const& direction,
               Vector2f const& velocity, Color3f const& color, Player* damageSource)
    {
        switch (type)
        {
            //  new
            case pAmmoAFK85:        AmmoAFK85::        spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoFlamer2:      AmmoFlamer2::      spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoPlasma:       AmmoPlasma::       spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoRifle2:       AmmoRifle2::       spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoShotgun2:     AmmoShotgun2::     spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoH2OStorm:     AmmoH2OStorm::     spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoMiniRocket:   AmmoMiniRocket::   spawn(location, direction, velocity, color, damageSource); break;
            //  new 2
            case pAmmoPulse:        AmmoPulse::        spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoCloud:        AmmoCloud::        spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoFreezers:     AmmoFreezers::     spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoLaser:        AmmoLaser::        spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoLightning:    AmmoLightning::    spawn(location, direction, velocity, color, damageSource); break;

            case pAmmoMinigun:      AmmoMinigun::      spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoGauss:        AmmoGauss::        spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoGrenades:     AmmoGrenades::     spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoSeekers:      AmmoSeekers::      spawn(location, direction, velocity, color, damageSource); break;
            //  org
            case pAmmoAFK47:        AmmoAFK47::        spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoBurner:       AmmoBurner::       spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoH2OMG:        AmmoH2OMG::        spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoShotgun:      AmmoShotgun::      spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoFlubba:       AmmoFlubba::       spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoROFLE:        AmmoROFLE::        spawn(location, direction, velocity, color, damageSource); break;
            
            //  common
            case pFuel:             Fuel::             spawn(location, direction, velocity, color, damageSource); break;
            case pMud:              Mud::              spawn(location, direction, velocity, color, damageSource); break;
            case pSmoke:            Smoke::            spawn(location, direction, velocity, color, damageSource); break;
            case pEruption:         Eruption::         spawn(location, direction, velocity, color, damageSource); break;

            case pDust:             Dust::             spawn(location, direction, velocity, color, damageSource); break;
            case pExplode:          Explode::          spawn(location, direction, velocity, color, damageSource); break;
            case pBurningFragment:  BurningFragment::  spawn(location, direction, velocity, color, damageSource); break;
            case pFragmentFlame:    FragmentFlame::    spawn(location, direction, velocity, color, damageSource); break;

            case pMiniFlame:        MiniFlame::        spawn(location, direction, velocity, color, damageSource); break;
            case pMiniAmmoFlubba:   MiniAmmoFlubba::   spawn(location, direction, velocity, color, damageSource); break;

            case pCannonBall:       CannonBall::       spawn(location, direction, velocity, color, damageSource); break;
            case pSpark:            Spark::            spawn(location, direction, velocity, color, damageSource); break;
            case pFragment:         Fragment::         spawn(location, direction, velocity, color, damageSource); break;

            case pHeat:             Heat::             spawn(location, direction, velocity, color, damageSource); break;
            case pHeatJet:          HeatJet::          spawn(location, direction, velocity, color, damageSource); break;
            case pShockWave:        ShockWave::        spawn(location, direction, velocity, color, damageSource); break;
            case pHeatBurner:       HeatBurner::       spawn(location, direction, velocity, color, damageSource); break;
            case pMiniFlameSmoke:   MiniFlameSmoke::   spawn(location, direction, velocity, color, damageSource); break;

            case pPowerUpCollect:   PowerUpCollect::   spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoRocket:       AmmoRocket::       spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoFist:         AmmoFist::         spawn(location, direction, velocity, color, damageSource); break;
            case pNumber:           Number::           spawn(location, direction, velocity, color, damageSource); break;

            case pCrushedIce:       CrushedIce::       spawn(location, direction, velocity, color, damageSource); break;
            case pAmmoInsta:        AmmoInsta::        spawn(location, direction, velocity, color, damageSource); break;
            case pStar:             Star::             spawn(location, direction, velocity, color, damageSource); break;
        }
    }

    void spawnMultiple(float amount, ParticleType const& type, Vector2f const& location,
                       Vector2f const& direction, Vector2f const& velocity, Color3f const& color, Player* damageSource)
    {
        for (int i = 0; i <= (amount * settings::iParticleCount)/10; ++i)
            spawn(type, location, direction, velocity, color, damageSource);
    }

    void spawnTimed(float amount, ParticleType const& type, Vector2f const& location,
                       Vector2f const& direction, Vector2f const& velocity, Color3f const& color, Player* damageSource)
    {
        for (int i = 0; i <= (amount * settings::iParticleCount)*timer::frameTime(); ++i)
            spawn(type, location, direction, velocity, color, damageSource);
    }

    void collideWith(MobileSpaceObject* target)
    {
        AmmoShotgun::collideWith(target);
        AmmoRocket::collideWith(target);
        AmmoROFLE::collideWith(target);
        AmmoAFK47::collideWith(target);
        AmmoFist::collideWith(target);
        AmmoBurner::collideWith(target);
        AmmoFlubba::collideWith(target);
        //  new
        AmmoAFK85::collideWith(target);
        AmmoFlamer2::collideWith(target);
        // AmmoPlasma::collideWith(target);
        AmmoRifle2::collideWith(target);
        AmmoShotgun2::collideWith(target);
        AmmoH2OStorm::collideWith(target);
        AmmoMiniRocket::collideWith(target);
        //  new 2
        // AmmoPulse::collideWith(target);
        // AmmoCloud::collideWith(target);
        // AmmoFreezers::collideWith(target);
        AmmoLaser::collideWith(target);
        // AmmoLightning::collideWith(target);

        AmmoMinigun::collideWith(target);
        AmmoGauss::collideWith(target);
        AmmoGrenades::collideWith(target);
        AmmoSeekers::collideWith(target);
    }

    void shockWave(Vector2f const& location, float strength, float radius)
    {
        Smoke::         shockWave(location, strength, radius);
        Dust::          shockWave(location, strength, radius);
        AmmoFlubba::    shockWave(location, strength, radius);
        MiniAmmoFlubba::shockWave(location, strength, radius);
        MiniFlameSmoke::shockWave(location, strength, radius);
    }

    int count()
    {
        return trailEffects::count() + Fuel::count() + Mud::count() + Smoke::count() + Eruption::count()
            + AmmoAFK47::count() + AmmoROFLE::count() + Dust::count() + Explode::count()
            + BurningFragment::count() + FragmentFlame::count() + AmmoShotgun::count()
            + MiniFlame::count() + AmmoFlubba::count() + MiniAmmoFlubba::count()
            + CannonBall::count() + Spark::count() + Fragment::count() + AmmoBurner::count()
            + AmmoH2OMG::count() + Heat::count() + HeatJet::count() + ShockWave::count()
            + HeatBurner::count() + MiniFlameSmoke::count() + AmmoRocket::count()+ PowerUpCollect::count()
            + AmmoFist::count() + Number::count() + CrushedIce::count() + AmmoInsta::count() + Star::count()
            //  new
            + AmmoAFK85::count() + AmmoFlamer2::count() + AmmoPlasma::count() +
            + AmmoRifle2::count() + AmmoShotgun2::count() + AmmoH2OStorm::count() + AmmoMiniRocket::count()
            //  new 2
            + AmmoPulse::count() + AmmoCloud::count() + AmmoFreezers::count()
            + AmmoLaser::count() + AmmoLightning::count()
            + AmmoMinigun::count() + AmmoGauss::count() + AmmoGrenades::count() + AmmoSeekers::count();
    }

    void clear()
    {
        //  org
        AmmoAFK47::        clear();
        AmmoBurner::       clear();
        AmmoFlubba::       clear();
        AmmoROFLE::        clear();
        AmmoShotgun::      clear();
        AmmoH2OMG::        clear();
        //  common
        Fuel::             clear();
        Mud::              clear();
        Smoke::            clear();
        Eruption::         clear();
        Dust::             clear();
        Explode::          clear();
        BurningFragment::  clear();
        FragmentFlame::    clear();
        MiniFlame::        clear();
        MiniAmmoFlubba::   clear();
        CannonBall::       clear();
        Spark::            clear();
        Fragment::         clear();
        Heat::             clear();
        HeatJet::          clear();
        ShockWave::        clear();
        HeatBurner::       clear();
        MiniFlameSmoke::   clear();
        AmmoRocket::       clear();
        PowerUpCollect::   clear();
        AmmoFist::         clear();
        Number::           clear();
        CrushedIce::       clear();
        AmmoInsta::        clear();
        Star::             clear();
        //  new
        AmmoAFK85::        clear();
        AmmoFlamer2::      clear();
        AmmoPlasma::       clear();
        AmmoRifle2::       clear();
        AmmoShotgun2::     clear();
        AmmoH2OStorm::     clear();
        AmmoMiniRocket::   clear();
        //  new 2
        AmmoPulse::       clear();
        AmmoCloud::       clear();
        AmmoFreezers::    clear();
        AmmoLaser::       clear();
        AmmoLightning::   clear();

        AmmoMinigun::     clear();
        AmmoGauss::       clear();
        AmmoGrenades::    clear();
        AmmoSeekers::     clear();
    }
}
