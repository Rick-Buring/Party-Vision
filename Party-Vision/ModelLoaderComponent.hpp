#pragma once
#include <string>
#include <vector>

#include "AbstractDrawcomponent.hpp"
#include "tigl.h"

namespace Scene {
	class ModelLoaderComponent : AbstractDrawComponent {
	public:
		/// <summary>
		/// Consturctor for model
		/// </summary>
		/// <param name="filePath">path to model file</param>
		ModelLoaderComponent(std::string filePath);		

		/// <summary>
		/// draws the model
		/// </summary>
		virtual void draw() override;

	private:
		std::vector<tigl::Vertex> verts;

	};
}