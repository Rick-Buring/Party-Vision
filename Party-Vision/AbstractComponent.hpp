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

		/// <summary>
		/// set the gameObject referention to this component
		/// </summary>
		/// <param name="gameObject"></param>
		inline void setGameObject(GameObject* gameObject) { this->_gameObject = gameObject; }


	protected:
		GameObject* _gameObject = nullptr;
		
	};

}

