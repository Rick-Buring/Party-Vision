#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include "IVisionHandler.hpp"

namespace Vision {
	class VisionPipeline
	{
	public:
		VisionPipeline();
		~VisionPipeline();
		void ProcessImage(char imageArray[]);
		VisionPipeline addHandler(IVisionHandler& handler);
	private:
		
	};

	typedef union
	{
		char imageArray[];
		glm::vec3 position;
	}ImageInfo;

	
}