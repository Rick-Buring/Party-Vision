#pragma once
#include <glm/ext/vector_int2.hpp>


struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};


void RenderText(GLuint s, std::string text, float x, float y, float scale, glm::vec3 color);
int LoadFont(const char* filepathName);

