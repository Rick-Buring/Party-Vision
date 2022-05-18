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
	std::string imageFileName;
	void (*functionPointer)(void*);
	
};

struct menu {
	std::string title;
	std::string backgroundFileName;
	std::vector<MenuItem_t> MenuItem_t;
};

/// <summary>
/// Executes the function pointer related to the clicked button.
/// </summary>
void menuOnClick();

/// <summary>
/// TODO
/// </summary>
void menuInit();

/// <summary>
/// draws game game object of the main menu
/// </summary>
void menuDraw();
