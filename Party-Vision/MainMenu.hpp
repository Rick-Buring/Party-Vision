#pragma once
#include "AbstractSceneManager.hpp"
#include <vector>
#include <string>

namespace Minigames {
	class IPointerExecuter {
	public:
		virtual void execute() = 0;
	};
	typedef struct menuItem {
		std::string text;
		std::string imageFileName;
		IPointerExecuter* func;
		float positionx;
		float positiony;
		float sizeWidth;
		float sizeHeight;
	}MenuItem_t;

	typedef struct menu {
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
		Menu_t currentMenu;

		/// <summary>
		/// creates and add game object of the main menu to the scene.
		/// </summary>
		void menuInit(Menu_t);

		/// <summary>
		/// Constructor for MainMenu which initilizes the scene.
		/// </summary>
		MainMenu();
		~MainMenu();

	private:
		
		
	};

	Menu_t buildNinjaMenu();
}





