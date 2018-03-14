#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#ifndef NO_AUDIO
	#include <SFML/Audio.hpp>
#endif

#ifndef NO_NETWORK
	#include <SFML/Network.hpp>
#endif

#ifndef _DEBUG
	#pragma comment(lib, "sfml-main.lib")
	#pragma comment(lib, "sfml-system.lib")
	#pragma comment(lib, "sfml-graphics.lib")
	#pragma comment(lib, "sfml-window.lib")
#ifndef NO_AUDIO
	#pragma comment(lib, "sfml-audio-d.lib")
#endif

#ifndef NO_NETWORK
	#pragma comment(lib, "sfml-network-d.lib")
#endif
#else
	#pragma comment(lib, "sfml-main-d.lib")
	#pragma comment(lib, "sfml-system-d.lib")
	#pragma comment(lib, "sfml-graphics-d.lib")
	#pragma comment(lib, "sfml-window-d.lib")

#ifndef NO_AUDIO
	#pragma comment(lib, "sfml-audio-d.lib")
#endif

#ifndef NO_NETWORK
	#pragma comment(lib, "sfml-network-d.lib")
#endif
#endif

#include <ciso646>	// keywords: and, or, and_eq, or_eq, xor, xor_eq, bitand, bitor, not, compl, not_eq

#include "classes/Buffer.hpp"
#include "classes/Strings.hpp"
#include "classes/Objects.hpp"
#include "classes/ConfigItem.hpp"
#include "classes/Config.hpp"
#include "classes/Collision.hpp"
#include "classes/Conversion.hpp"
#include "classes/Controller.hpp"
#include "classes/Time.hpp"
#include "classes/Clip.hpp"
#include "classes/ResourceManager.hpp"
#include "classes/Window.hpp"
#include "classes/App.hpp"
#include "classes/AppState.hpp"
#include "classes/Animation.hpp"