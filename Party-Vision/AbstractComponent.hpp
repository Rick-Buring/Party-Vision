#pragma once

namespace Scene {
	class GameObject;

	class AbstractComponent
	{
	public:

		virtual void update(float elapsedTime) {};

		inline void setGameObject(GameObject* gameObject) { this->_gameObject = gameObject; }


	private:
		GameObject* _gameObject;
		
	};

}

