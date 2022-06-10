#pragma once
#include <vector>
#include "tigl.h"
#include "AbstractDrawcomponent.hpp"

namespace Scene {
	/// <summary>
	/// simple plane visualization
	/// </summary>
	class PlaneComponent : public AbstractDrawComponent {
	private:
		bool _ortho;
		//variable to store plane vertesies
		std::vector<tigl::Vertex> verts;
		glm::mat4 projectionOrtho;
	public:
		/// <summary>
		/// Constructor used to create the plane
		/// </summary>
		/// <param name="width">width of the plane</param>
		/// <param name="height">height of the plane</param>
		PlaneComponent(float width, float height, bool ortho = true); 
		virtual void draw() override;
	};
};