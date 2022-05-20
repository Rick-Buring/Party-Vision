#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "tigl.h"
#include <vector>

namespace Scene {
	
	class Texture;
	

	typedef struct {
		tigl::VBO* vbo;
		Texture* texture;
	} VBO_Textures_t;

	std::vector<VBO_Textures_t> loadObject(const std::string& filename);

}