#include "PlaneComponent.hpp"
namespace Scene {
	
	PlaneComponent::PlaneComponent(float width, float height)
	{
		glm::vec3 s(width / 2, height / 2, 0);
		glm::vec4 color(1, 0, 1, 1);
		glm::vec3 p((width / 2), (height / 2), 0);

		verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, 1)));
		verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 0), glm::vec3(0, 0, 1)));
		verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, 1)));
		verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, 0, 1)));

	}

	void PlaneComponent::draw() {
		tigl::drawVertices(GL_QUADS, verts);
	}

}
