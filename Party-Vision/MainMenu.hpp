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
		Menu_t currentMenu;
		/// <summary>
		/// Executes the function pointer related to the clicked button.
		/// </summary>
		void menuOnClick();

		/// <summary>
		/// creates and add game object of the main menu to the scene
		/// </summary>
		void menuInit();

		/// <summary>
		/// updates the main menu scene
		/// </summary>
		void menuUpdate();
	private:
		
		
	};


	
}

struct menuItem {
	std::string text;
	std::string imageFileName;
	void (*functionPointer)(void*);
	int positionx;
	int positiony;
	int sizeHeight;
	int sizeWidth;
};

struct menu {
	std::string title;
	std::string backgroundFileName;
	std::vector<MenuItem_t> menuItems;
};



