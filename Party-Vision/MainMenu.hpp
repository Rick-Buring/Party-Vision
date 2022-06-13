#pragma once
#include "AbstractSceneManager.hpp"
#include <vector>
#include <string>

namespace Minigames {
	/// <summary>	
	/// execute interface for menu items
	/// </summary>
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

	/// <summary>
	/// Menu visualizer
	/// </summary>
	class MainMenu : public AbstractSceneManager
	{
	public:
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

		/// <summary>
		/// Create plane that follows mouse that is used for collision check.
		/// </summary>
		void createMouse();

	private:
		int _viewPort[4], _width, _height;
		
	};
	/// <summary>
	/// Creates the struct for the school ninja menu and returns it.
	/// </summary>
	/// <returns>The struct for the school ninja menu</returns>
	Menu_t buildNinjaMenu();
}





