#include <thread>

#include "SchoolNinja.hpp"
#include "SchoolNinjaComponent.hpp"
#include "PlaneComponent.hpp"
#include "TransformComponent.hpp"
#include "CursorPosition.hpp"
#include "HandDetection.hpp"
#include "Convert.hpp"
#include "MainMenu.hpp"
#include "WindowManager.hpp"
#include "HudComponent.hpp"
#include <iostream>
#include <fstream>
namespace Minigames {
	thread visionT;
	bool threadIsRunning = false;
	Mat frame;

	void updateVision()
	{
		while (threadIsRunning) {
			Point position;

			Vision::HandDetection_run(position, frame);
			static int width, height;
			glfwGetWindowSize(window, &width, &height);
			convertCoordinates(frame, height, width, position, position);

			cursorPosition = glm::vec2(position.x, position.y);
			//waitKey(1);
		}
	}

	SchoolNinja::SchoolNinja()
	{
		
		std::shared_ptr <Scene::GameObject> background = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::PlaneComponent> backgroundPlane = std::make_shared<Scene::PlaneComponent>(windowWidth, windowHeight, new Scene::Texture("textures/backgroundimageflipped.png"));

		background->addComponent(backgroundPlane);

		std::shared_ptr<Scene::TransformComponent> backgroundTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, -70));

		background->addComponent(backgroundTransform);

		SchoolNinja::scene->addGameObject(background);
		
		//todo initialize game
		std::shared_ptr<Scene::GameObject> schoolNinja = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::SchoolNinjaComponent> schoolNinjaComponent = std::make_shared<Scene::SchoolNinjaComponent>(scene.get());
		schoolNinja->addComponent(schoolNinjaComponent);
		std::shared_ptr<Scene::HudComponent> schoolNinjaHud = std::make_shared<Scene::HudComponent>();
		schoolNinja->addComponent(schoolNinjaHud);
		
		std::ifstream highScoreFile("highScore.txt");
		std::string highScoreString;
		std::getline(highScoreFile, highScoreString);
		highScoreFile.close();
		schoolNinjaComponent->_highScore = std::stoi(highScoreString);
		schoolNinjaHud->setHighScore(schoolNinjaComponent->_highScore);

		schoolNinja->addComponent(std::make_shared<Scene::TransformComponent>(glm::vec3(0)));
		scene->addGameObject(schoolNinja);

		threadIsRunning = true;
		visionT = thread(updateVision);
		//updateVision();

		double mouseWidth = 20, mouseHeight = 20;
		SchoolNinja::createMouse(mouseWidth, mouseHeight);
		SchoolNinja::scene->setRunning(true);
	}

	void SchoolNinja::sceneUpdate() {
		if (!frame.empty()) cv::imshow("First frame", frame);
		AbstractSceneManager::sceneUpdate();

		if (endScene) {
			AbstractSceneManager* manager = sceneManager;
			sceneManager = new MainMenu();
			delete manager;
			sceneManager->scene->setRunning(true);
		}
	}


	SchoolNinja::~SchoolNinja() {
		threadIsRunning = false;
		visionT.join();
	}
}