#include "ModelLoaderComponent.hpp"
#include "tigl.h"
#include <vector>


namespace Scene {

	ModelLoaderComponent::ModelLoaderComponent(std::string filePath)
	{
		std::vector<tigl::Vertex> test;
		tigl::VBO* t = tigl::createVbo(test);
		

		
	}

	void ModelLoaderComponent::draw()
	{

	}
}