#include <thread>

#include "SchoolNinja.hpp"
#include "SchoolNinjaComponent.hpp"
#include "PlaneComponent.hpp"
#include "TransformComponent.hpp"
#include "CursorPosition.hpp"
#include "HandDetection.hpp"
#include "WindowManager.hpp"
#include "Convert.hpp"
#include "main.hpp"

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
		glGetIntegerv(GL_VIEWPORT, viewport);
		std::shared_ptr <Scene::GameObject> background = std::make_shared<Scene::GameObject>();
		std::shared_ptr<Scene::PlaneComponent> backgroundPlane = std::make_shared<Scene::PlaneComponent>(viewport[2], viewport[3], new Scene::Texture("textures/backgroundimageflipped.png"));

		background->addComponent(backgroundPlane);

		std::shared_ptr<Scene::TransformComponent> backgroundTransform = std::make_shared<Scene::TransformComponent>(glm::vec3(0, 0, -70));

		background->addComponent(backgroundTransform);

		SchoolNinja::scene->addGameObject(background);
		//todo initialize game
		std::shared_ptr<Scene::GameObject> schoolNinja = std::make_shared<Scene::GameObject>();
		schoolNinja->addComponent(std::make_shared<Scene::SchoolNinjaComponent>(scene.get()));

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