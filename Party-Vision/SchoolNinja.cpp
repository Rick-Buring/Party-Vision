//the headerfile associated with this cpp file
#include "SchoolNinja.hpp"

//std library
#include <thread>
#include <iostream>
#include <fstream>

//own objects
#include "SchoolNinjaComponent.hpp"
#include "PlaneComponent.hpp"
#include "TransformComponent.hpp"
#include "CursorPosition.hpp"
#include "HandDetection.hpp"
#include "Convert.hpp"
#include "MainMenu.hpp"
#include "WindowManager.hpp"
#include "HudComponent.hpp"
#include "main.hpp"
#include "preprocessorCommands.hpp"

namespace Minigames {
	thread visionT;
	bool threadIsRunning = false;
	Mat frame;

	void updateVision()
	{
		Point position;

		//get window size
		static int width, height;
		glfwGetWindowSize(window, &width, &height);

		while (threadIsRunning) {
			//get hand position
			Vision::HandDetection_run(position, frame);
			//convert camera cooridinates to screen coordinates
			convertCoordinates(frame, height, width, position, position);
			//update the cursor position
			cursorPosition = glm::vec2(position.x, position.y);
		}
	}

	SchoolNinja::SchoolNinja()
	{	
		//create the background for the scene
		std::shared_ptr <Scene::GameObject> background = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::PlaneComponent> backgroundPlane = std::make_shared<Scene::PlaneComponent>(windowWidth, windowHeight, new Scene::Texture("textures/backgroundimageflipped.png"));
		background->addComponent(backgroundPlane);
		std::shared_ptr<Scene::TransformComponent> backgroundTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, -70));
		background->addComponent(backgroundTransform);
		SchoolNinja::scene->addGameObject(background);
		
		//create the gameManager object
		std::shared_ptr<Scene::GameObject> schoolNinja = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::SchoolNinjaComponent> schoolNinjaComponent = std::make_shared<Scene::SchoolNinjaComponent>(scene.get());
		schoolNinja->addComponent(schoolNinjaComponent);
		std::shared_ptr<Scene::HudComponent> schoolNinjaHud = std::make_shared<Scene::HudComponent>();
		schoolNinja->addComponent(schoolNinjaHud);
		
		//read highscore from file
		std::ifstream highScoreFile("highScore.txt");
		std::string highScoreString;
		std::getline(highScoreFile, highScoreString);
		highScoreFile.close();

		//set the highscore in the scene
		schoolNinjaComponent->_highScore = std::stoi(highScoreString);
		schoolNinjaHud->setHighScore(schoolNinjaComponent->_highScore);

		schoolNinja->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0)));
		scene->addGameObject(schoolNinja);

		//start the vision thread
		threadIsRunning = true;
		visionT = thread(updateVision);

		//create the plane to visualize hand position
		double mouseWidth = 12.5 * scalex, mouseHeight = 15 * scaley;
		SchoolNinja::createMouse(mouseWidth, mouseHeight);
		SchoolNinja::scene->setRunning(true);
	}

	void SchoolNinja::sceneUpdate() {
#if __Debug_Mode
		if (!frame.empty()) cv::imshow("First frame", frame);
#endif
		AbstractSceneManager::sceneUpdate();

		//check if the game should end
		if (endScene) {
			AbstractSceneManager* manager = sceneManager;
			sceneManager = new MainMenu();
			delete manager;
			sceneManager->scene->setRunning(true);
		}
	}


	SchoolNinja::~SchoolNinja() {
		//on destroy remove thread
		threadIsRunning = false;
		visionT.join();
	}
}