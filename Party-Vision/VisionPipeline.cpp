#include <list>
#include "VisionPipeline.hpp"


namespace Vision {
	

	std::list<IVisionHandler*> _handlers;

	VisionPipeline::VisionPipeline()
	{
	}
	VisionPipeline::~VisionPipeline()
	{
	}

	VisionPipeline VisionPipeline::addHandler(IVisionHandler& handler) {
		_handlers.push_back(&handler);
		return *this;
	}

	void VisionPipeline::ProcessImage(char imageArray[]) {
		for (IVisionHandler* handler : _handlers) {
			handler->process(imageArray);
		}
	}
}
