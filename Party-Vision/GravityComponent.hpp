#pragma once
#include "AbstractComponent.hpp"

namespace Scene {
	class GravityComponent : public AbstractComponent
	{
	public:
		inline GravityComponent(float gravity = 9.8f) :_gravity(gravity) {}
		
		virtual void update(float) override;

	private:
		float _gravity;
	};
}