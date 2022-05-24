#include "DrawObjectComponent.hpp"
#include "Texture.hpp"

namespace Scene {
	void DrawObjectComponent::draw()
	{
		for (auto d : _object) {
			d.texture->bind();
			tigl::drawVertices(GL_TRIANGLES, d.vbo);
		}
	}
}