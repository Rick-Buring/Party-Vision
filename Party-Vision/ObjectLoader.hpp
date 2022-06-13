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

	/// <summary>
	/// Reads an object file and returns it as a vector<VBO_Textures_t>
	/// </summary>
	/// <param name="filename">File location of the object file</param>
	std::vector<VBO_Textures_t> loadObject(const std::string& filename);

}