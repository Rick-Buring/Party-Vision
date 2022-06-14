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
		std::vector<tigl::Vertex> _verts;
		glm::mat4 _projectionOrtho;
	public:
		Texture* texture;
		/// <summary>
		/// Constructor used to create the plane
		/// </summary>
		/// <param name="width">width of the plane</param>
		/// <param name="height">height of the plane</param>
		/// <param name="texture">texture that needs to be drawn on the plane</param>
		/// <param name="ortho">draw the plane in ortho graphic view</param>
		PlaneComponent(float width, float height, Texture* texture = nullptr, bool ortho = true);

		/// <summary>
		/// draws the plane in ortho mode or projection mode based on the boolean
		/// </summary>
		virtual void draw() override;
	};
};