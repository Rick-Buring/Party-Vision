#pragma once
#include "AbstractSceneManager.hpp"
#include <vector>
#include <string>
typedef struct menu Menu_t;
typedef struct menuItem MenuItem_t;
namespace Minigames {
	class MainMenu : AbstractSceneManager
	{
	public:

	private:

		
	};

}

struct menuItem {
	std::string text;
	void (*functionPointer)(void*);
};

struct menu {
	std::string title;
	std::vector<MenuItem_t> MenuItem_t;
};
