#pragma once
#include <glm/gtc/matrix_transform.hpp>

namespace Vision {
	class VisionPipeline
	{
	public:
		VisionPipeline();
		~VisionPipeline();

	private:

	};

	typedef union
	{
		char imageArray[];
		glm::vec3 position;
	}ImageInfo;

	
}