#pragma once

#include <gl/glew.h>
#include <string>

namespace Scene {
	class Texture
	{
		GLuint id;
	public:
		/// <summary>
		/// Creates a texture.
		/// </summary>
		/// <param name="fileName">File name of the texture</param>
		Texture(const std::string& fileName);
		
		/// <summary>
		/// Binds the texture.
		/// </summary>
		void bind();
	};

	/// <summary>
	/// Unbinds the texture.
	/// </summary>
	void textureUnbind();
}