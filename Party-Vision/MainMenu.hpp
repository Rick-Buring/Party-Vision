#pragma once
#include "AbstractSceneManager.hpp"
#include <vector>
#include <string>

namespace Minigames {
	/// <summary>
	/// Interface to execute a function and store it in a menu
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
	class MainMenu : public AbstractSceneManager
	{
	public:
		Menu_t currentMenu;

		/// <summary>
		/// creates and adds game object of the main menu to the scene.
		/// </summary>
		/// <param name="">The current menu that needs to be initialized</param>
		void menuInit(Menu_t);

		/// <summary>
		/// Constructor for MainMenu which initilizes the scene.
		/// </summary>
		MainMenu();

		~MainMenu();
	private:
		
		
	};
	/// <summary>
	/// Creates the struct for the school ninja menu and returns it.
	/// </summary>
	/// <returns>The struct for the school ninja menu</returns>
	Menu_t buildNinjaMenu();

	/// <summary>
	/// Start the music.
	/// </summary>
	void startMusic();
}





