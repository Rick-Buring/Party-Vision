#pragma once
#include <vector>
#include "tigl.h"
#include "AbstractDrawcomponent.hpp"
#include <string>
#include "Texture.hpp"

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
		Texture* texture;
	public:
		/// <summary>
		/// Constructor used to create the plane
		/// </summary>
		/// <param name="width">width of the plane</param>
		/// <param name="height">height of the plane</param>
		/// <param name="texture">texture that needs to be drawn on the plane</param>
		PlaneComponent(float width, float height, Texture* texture = nullptr, bool ortho = true);
		virtual void draw() override;
	};
};