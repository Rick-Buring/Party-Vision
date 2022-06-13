
#pragma once
#include "AbstractSceneManager.hpp"
#include "SchoolNinja.hpp"
#include "MainMenu.hpp"
#include <iostream>


/// <summary>
/// current sceneManager
/// </summary>
extern Minigames::AbstractSceneManager* sceneManager;

/// <summary>
/// class to start a game of schoolNinja
/// </summary>
class StartGame : public Minigames::IPointerExecuter {
	void execute() override {
		Minigames::AbstractSceneManager* removeScene = sceneManager;
		delete removeScene;
		sceneManager = new Minigames::SchoolNinja();
	}
};

/// <summary>
/// class to show credits
/// </summary>
class OpenCredits : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "Credits " << std::endl;
	}
};

/// <summary>
/// class to show how to play
/// </summary>
class OpenHowToPlay : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "How To Play " << std::endl;
	}
};

/// <summary>
/// class to switch menu
/// </summary>
class NextMenu : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "Next " << std::endl;
	}
};

/// <summary>
/// class to switch menu
/// </summary>
class PreviousMenu : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "Previous " << std::endl;
	}
};