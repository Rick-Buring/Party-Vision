#include "AbstractSceneManager.hpp"

namespace Minigames {
	void AbstractSceneManager::sceneUpdate() {
		scene->draw();
		scene->update();
	}

}
