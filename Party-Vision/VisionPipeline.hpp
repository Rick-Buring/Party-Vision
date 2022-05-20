#pragma once
#include <glm/gtc/matrix_transform.hpp>

namespace Vision {

	__interface IVisionHandler;
	class VisionPipeline
	{
	public:
		VisionPipeline();
		~VisionPipeline();

		void ProcessImage(char imageArray[]);
		VisionPipeline& addHandler(IVisionHandler& handler);
	private:
		
	};

	typedef union
	{
		glm::vec3 position;
		char *imageArray; //Pointer is to be used as an array
	}ImageInfo;

	
}