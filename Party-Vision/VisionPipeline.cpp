#include <list>
#include "VisionPipeline.hpp"
#include "IVisionHandler.hpp"

namespace Vision {
	

	std::list<IVisionHandler*> _handlers;

	VisionPipeline::VisionPipeline()
	{
	}

	VisionPipeline::~VisionPipeline()
	{
	}

	//Adds an IVisionHandler
	VisionPipeline& VisionPipeline::addHandler(IVisionHandler& handler) {
		_handlers.push_back(&handler);
		return *this;
	}

	//Processes given char[] using given avalaible handlers
	void VisionPipeline::ProcessImage(char imageArray[]) {
		for (IVisionHandler* handler : _handlers) {
			handler->process(imageArray);
		}
	}
}
