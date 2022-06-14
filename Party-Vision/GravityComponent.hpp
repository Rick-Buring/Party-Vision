#pragma once
#include "AbstractComponent.hpp"

namespace Scene {
	class GravityComponent : public AbstractComponent
	{
	public:
		/// <summary>
		/// Gravity component constructor
		/// </summary>
		/// <param name="gravity">
		/// The amount of gravity effecting the object
		/// </param>
		inline GravityComponent(float gravity = 80) :_gravity(gravity) {}
		
		/// <summary>
		/// Upon being called applies the gravity to the object.
		/// </summary>
		virtual void update(float) override;

	private:
		float _gravity;
	};
}