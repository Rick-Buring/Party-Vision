#include "PlaneComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.hpp"

namespace Scene {
	
	std::string fileName;
	PlaneComponent::PlaneComponent(float width, float height, Texture* texture)
	{
		
		PlaneComponent::texture = texture;
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		PlaneComponent::projectionOrtho = glm::ortho(0.0f, (float)viewport[2], (float)viewport[3], 0.0f, 0.1f, 100.0f);

		glm::vec3 s(width / 2, height / 2, 0);
		glm::vec4 color(1, 1, 1, 1);
		glm::vec3 p((width / 2), (height / 2), 0);

		PlaneComponent::verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, 1)));
		PlaneComponent::verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 0), glm::vec3(0, 0, 1)));
		PlaneComponent::verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, 1)));
		PlaneComponent::verts.push_back(tigl::Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	}


	void PlaneComponent::draw() {
		if (texture) {
			texture->bind();
		}
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glm::mat4 projectionMatrix = tigl::shader->getProjectionMatrix();
		tigl::shader->setProjectionMatrix(PlaneComponent::projectionOrtho);
		tigl::drawVertices(GL_QUADS, verts);
		tigl::shader->setProjectionMatrix(projectionMatrix);
		textureUnbind();
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

	}
}
