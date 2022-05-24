#pragma once
#include "AbstractDrawcomponent.hpp"
#include <vector>
#include "ObjectLoader.hpp"

namespace Scene {
	class DrawObjectComponent : public AbstractDrawComponent {
	public:
		DrawObjectComponent(std::vector<VBO_Textures_t> object);

		void draw() override;
	private:
		std::vector<VBO_Textures_t> _object;

	};
}