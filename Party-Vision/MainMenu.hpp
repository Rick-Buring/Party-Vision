#pragma once
#include "AbstractSceneManager.hpp"
#include <vector>
#include <string>

namespace Minigames {
	typedef struct menuItem {
		std::string text;
		std::string imageFileName;
		//void (* functionPointer)(void*);
		float positionx;
		float positiony;
		float sizeWidth;
		float sizeHeight;
	}MenuItem_t;

	typedef struct menu  {
		std::string title;
		std::string backgroundFileName;
		std::vector<MenuItem_t> menuItems;
	}Menu_t;
	class MainMenu : public AbstractSceneManager
	{
	public:
		float backgroundWidth;
		float backgroundHeight;
		float backgroundx;
		float backgroundy;

		
		
		void (MainMenu::*functionPointerCurrentMenuItem)(void*);
		
		/// <summary>
		/// Executes the function pointer related to the clicked button.
		/// </summary>
		void menuOnClick();

		/// <summary>
		/// creates and add game object of the main menu to the scene.
		/// </summary>
		void menuInit();

		/// <summary>
		/// Constructor for MainMenu which initilizes the scene.
		/// </summary>
		MainMenu();

	private:
		
		
	};

	extern Menu_t currentMenu;
	
}





