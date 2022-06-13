
#pragma once
#include "AbstractSceneManager.hpp"
#include "SchoolNinja.hpp"
#include "MainMenu.hpp"
#include <iostream>

extern Minigames::AbstractSceneManager* sceneManager;

class StartGame : public Minigames::IPointerExecuter {
	void execute() override {
		Minigames::AbstractSceneManager* removeScene = sceneManager;
		delete removeScene;
		sceneManager = new Minigames::SchoolNinja();
	}
};

class OpenCredits : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "Credits " << std::endl;
	}
};

class OpenHowToPlay : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "How To Play " << std::endl;
	}
};

class NextMenu : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "Next " << std::endl;
	}
};

class PreviousMenu : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "Previous " << std::endl;
	}
};