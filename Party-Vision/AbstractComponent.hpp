#pragma once

namespace Scene {
	class GameObject;

	class AbstractComponent
	{
	public:
		/// <summary>
		///function called once every frame 
		/// </summary>
		/// <param name="elapsedTime">time passsed since last frame</param>
		virtual void update(float elapsedTime) {};

		inline void setGameObject(GameObject* gameObject) { this->_gameObject = gameObject; }


	private:
		GameObject* _gameObject;
		
	};

}

