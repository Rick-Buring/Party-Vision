#pragma once
#include "AbstractComponent.hpp"
namespace Scene {

	/// <summary>
	/// Abstract component for drawing 
	/// </summary>
	class AbstractDrawComponent : public AbstractComponent {
	public:
		virtual void draw() = 0;
	};
}