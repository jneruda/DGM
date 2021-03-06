/**
 *  \file Controller.hpp
 *  \author doomista
 */
 
#pragma once

#include <map>
#include <DGM/dgm.hpp>

namespace dgm {
	class AbstractController {
	public:
		virtual bool keyPressed(const int code) =0;
		
		virtual bool keyPressed(const int code, float &intensity) const =0;
		
		virtual void releaseKey(const int code) =0;
	};

	/**
	 * \brief Class with enumerator object for X360 inputs
	 */
	enum class X360 {
		Empty = -1,
		A = 0, B = 1, X = 2, Y = 3,
		LBumper = 4, RBumper = 5,
		Select = 6, Start = 7,
		LStick = 8, RStick = 9,
		LTrigger = 100, RTrigger,
		LStick_Left = 200, LStick_Up, LStick_Right, LStick_Down,
		RStick_Left = 300, RStick_Up, RStick_Right, RStick_Down,
		POV_Left = 400, POV_Up, POV_Right, POV_Down,
	};

	class Binding {
	public:
		bool released;
		sf::Keyboard::Key key;
		dgm::X360 joy;
	};

	class Controller : public AbstractController {
	protected:
		std::vector<Binding> bindings;
		float deadzone;
		int index;

		float getJoystickAxis(const dgm::X360 joy) const;

	public:

		/**
		 * \brief Tests whether keyboard key or X360 input is pressed for action with code id
		 *
		 * \details This function only returns TRUE/FALSE based on whether input
		 * is pressed, disregarding intensity any axii can be pressed with. Also this
		 * function is affected by releaseKey() call.
		 */
		bool keyPressed(const int code);

		/**
		 * \brief Tests whether keyboard key or X360 input is pressed for action with code id,
		 * also returns intensity of the press
		 *
		 * \details This function is not affected by releaseKey() call. Function will return
		 * TRUE/FALSE if input is pressed. For keys and buttons, intensity will be either 0.f/100.f.
		 * For axii, intensity will return actual intensity of press from interval (0.f,deadzone - 100.f)
		 */
		bool keyPressed(const int code, float &intensity) const;

		/**
		 * \brief Marks input as released
		 *
		 * \details Only works in conjuction with simpler version of
		 * keyPressed(). Once an action is marked as released then
		 * keyPressed() will return FALSE until point where user
		 * had released the input physically and then pressed it again.
		 * With this, one can emulate sf::Event::keyPressed behaviour.
		 *
		 * \note In order to function properly, keyPressed should be called
		 * every frame (to ensure that controller will notice the released key)
		 */
		void releaseKey(const int code);

		/**
		 * \brief Bind the keyboard key and X360 input to an action
		 *
		 * \note Key is required, joy can be dgm::X360::Empty
		 */
		void setBinding(const int code, sf::Keyboard::Key key, dgm::X360 joy = dgm::X360::Empty);

		/**
		 * \brief Sets the threshold for X360 axii
		 *
		 * \details Any input with power less than threshold
		 * will be dropped. 25.f is recommended.
		 */
		void setDeadzone(const float threshold);

		/**
		 * \brief Sets the index of X360 controller to use
		 */
		void setIndex(const int index);

		Controller();
		~Controller();
	};
}