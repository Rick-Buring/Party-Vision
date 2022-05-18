#pragma once
#include "AbstractComponent.hpp"
namespace Scene {
	class AbstractDrawComponent : public AbstractComponent {
	public:
		virtual void draw() = 0;
	};
}