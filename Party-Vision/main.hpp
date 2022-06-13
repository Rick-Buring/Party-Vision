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

class testClas : public Minigames::IPointerExecuter {
	void execute() override {
		std::cout << "Hello" << std::endl;
	}
};