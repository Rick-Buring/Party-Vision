#include "ft2build.h"
#include "freetype/freetype.h"
#include <iostream>
#include "TextRenderer.hpp"



int LoadFont(const char* filepathName) {

    

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, filepathName, 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }
}

