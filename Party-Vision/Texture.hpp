#pragma once

#include <gl/glew.h>
#include <string>

namespace Scene {
	class Texture
	{
		GLuint id;
	public:
		Texture(const std::string& fileName);
		void bind();
		
	};
	void textureUnbind();
}