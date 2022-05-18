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
		//variable to store plane vertesies
		std::vector<tigl::Vertex> verts;
	public:
		/// <summary>
		/// Constructor used to create the plane
		/// </summary>
		/// <param name="width">width of the plane</param>
		/// <param name="height">height of the plane</param>
		PlaneComponent(float width, float height); 
		virtual void draw() override;
	};
};