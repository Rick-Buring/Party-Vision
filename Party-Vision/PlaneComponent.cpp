#include "PlaneComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>
namespace Scene {
	
	PlaneComponent::PlaneComponent(float width, float height)
	{
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		PlaneComponent::projectionOrtho = glm::ortho(0.0f, (float)viewport[2], (float)viewport[3], 0.0f, -1.0f, 5.0f);

		glm::vec3 s(width / 2, height / 2, 0);
		glm::vec4 color(1, 1, 1, 1);
		glm::vec3 p((width / 2), (height / 2), 0);

		PlaneComponent::verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, 1)));
		PlaneComponent::verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 0), glm::vec3(0, 0, 1)));
		PlaneComponent::verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, 1)));
		PlaneComponent::verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	}

	void PlaneComponent::draw() {
		glm::mat4 projectionMatrix = tigl::shader->getProjectionMatrix();
		tigl::shader->setProjectionMatrix(PlaneComponent::projectionOrtho);
		tigl::drawVertices(GL_QUADS, verts);
		tigl::shader->setProjectionMatrix(projectionMatrix);
	}
}
