#pragma once
#include "AbstractDrawcomponent.hpp"
#include <vector>
#include "ObjectLoader.hpp"

namespace Scene {
	class DrawObjectComponent : public AbstractDrawComponent {
	public:
		/// <summary>
		/// Component responsible for visually representing the object
		/// </summary>
		/// <param name="object"> The textures to be used</param>
		DrawObjectComponent(std::vector<VBO_Textures_t> object);

		/// <summary>
		/// Visualizes the component
		/// </summary>
		void draw() override;
	private:
		std::vector<VBO_Textures_t> _object;

	};
}