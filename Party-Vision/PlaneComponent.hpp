#pragma once
#include <vector>
#include "tigl.h"
#include "AbstractDrawcomponent.hpp"

namespace Scene {
	class PlaneComponent : public AbstractDrawComponent {
	private:

		std::vector<tigl::Vertex> verts;
	public:
		PlaneComponent(float width, float height);
		virtual void draw() override;
	};
};