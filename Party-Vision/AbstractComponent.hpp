#pragma once

namespace Scene {
	class GameObject;

	class AbstractComponent
	{
	public:
		inline void setGameObject(GameObject* gameObject) { this->_gameObject = gameObject; }
		void update(float elapsedTime);

	private:
		GameObject* _gameObject;
		
	};

}

