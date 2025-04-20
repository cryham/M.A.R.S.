#pragma once

#include "Controllers/controllers.hpp"

class Ship;


/// A base class which controls a Player's Ship.
/// It provides some basic functionallity which directly
/// interacts with the Ship.

class Controller
{
    public:
        /// Constructs an Controller, attached to a Player.
        /// \param slave The controlled Player.
        /// \param type The type of the Controller.
        Controller(Player* slave);

        /// Returns the Ship of the controlled PLayer.
        Ship* ship() const;

        /// Returns the type of the Controller.
        controllers::ControlType type() const;

    protected:
        /// Accelerates the Ship. (continous action)
        void slaveUp    (int up)    const;

        /// Backward accelerates the Ship. (continous action)
        void slaveDown  (int down)  const;

        /// Boost accelerates the Ship. (continous action)
        void slaveBoost (int down)  const;


        /// Turns the Ship left. (continous action)
        void slaveLeft  (int left)  const;

        /// Turns the Ship right. (continous action)
        void slaveRight (int right) const;

        /// Fires the Ship's Weapon. (continous action)
        void slaveFire  (int fire)  const;


        /// "Presses" the Special-key. (single action)
        void slaveSpecial (int special) const;

        /// "Presses" the Up-key. (single action)
        void slaveUp    () const;

        /// "Presses" the Down-key. (single action)
        void slaveDown  () const;

        /// "Presses" the Left-key. (single action)
        void slaveLeft  () const;

        /// "Presses" the Boost-key. (single action)
        void slaveBoost () const;


        /// "Presses" the Right-key. (single action)
        void slaveRight () const;

        /// "Presses" the Fire-key. (single action)
        void slaveFire  () const;

        /// "Presses" the Special-key. (single action)
        void slaveSpecial () const;


        /// "Presses" the Weapon-next key. (single action)
        void slaveNext  () const;

        /// "Presses" the Weapon-previous key. (single action)
        void slavePrev  () const;


        /// The type of the controller.
        controllers::ControlType type_;

        /// The controlled Player.
        Player* slave_;
};
