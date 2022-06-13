#include <thread>

#include "SchoolNinja.hpp"
#include "SchoolNinjaComponent.hpp"
#include "CursorPosition.hpp"
#include "HandDetection.hpp"
#include "WindowManager.hpp"
#include "Convert.hpp"

namespace Minigames {
	thread visionT;
	Mat frame;

	void updateVision()
	{
		while (true) {
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
		//todo initialize game
		std::shared_ptr<Scene::GameObject> schoolNinja = std::make_shared<Scene::GameObject>();
		schoolNinja->addComponent(std::make_shared<Scene::SchoolNinja>(scene.get()));

		scene->addGameObject(schoolNinja);

		
		visionT = thread(updateVision);
		//updateVision();

		double mouseWidth = 20, mouseHeight = 20;
		SchoolNinja::createMouse(mouseWidth, mouseHeight);
		SchoolNinja::scene->setRunning(true);
	}

	void SchoolNinja::sceneUpdate() {
		/*Point position;
		Mat frame;

		Vision::HandDetection_run(position, frame);
		static int width, height;
		glfwGetWindowSize(window, &width, &height);
		convertCoordinates(frame, height, width, position, position);

		cursorPosition = glm::vec2(position.x, position.y);*/
	
		if (!frame.empty()) cv::imshow("First frame", frame);
		AbstractSceneManager::sceneUpdate();
	}
	 
}