
#pragma once
#include "AbstractSceneManager.hpp"
#include "SchoolNinja.hpp"
#include "MainMenu.hpp"
#include <iostream>

/// <summary>
/// pointer to the current scene manager
/// </summary>
extern Minigames::AbstractSceneManager* sceneManager;

class StartGame : public Minigames::IPointerExecuter {
	/// <summary>
	/// deletes current scene and starts the game scene SchoolNinja
	/// </summary>
	void execute() override {
		Minigames::AbstractSceneManager* removeScene = sceneManager;
		delete removeScene;
		sceneManager = new Minigames::SchoolNinja();
	}
};

class OpenCredits : public Minigames::IPointerExecuter {
	/// <summary>
	/// prints Credits to the consol
	/// </summary>
	void execute() override {
		std::cout << "Credits " << std::endl;
	}
};

class OpenHowToPlay : public Minigames::IPointerExecuter {
	/// <summary>
	/// prints how to play to the console
	/// </summary>
	void execute() override {
		std::cout << "How To Play " << std::endl;
	}
};

class NextMenu : public Minigames::IPointerExecuter {
	/// <summary>
	/// prints next to the console
	/// </summary>
	void execute() override {
		std::cout << "Next " << std::endl;
	}
};

class PreviousMenu : public Minigames::IPointerExecuter {
	/// <summary>
	/// prints previous to the console
	/// </summary>
	void execute() override {
		std::cout << "Previous " << std::endl;
	}
};