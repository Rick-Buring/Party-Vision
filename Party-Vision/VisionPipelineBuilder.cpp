#include "VisionPipelineBuilder.hpp"
#include "VisionPipeline.hpp"

namespace Vision {
	class VisionPipeline;

	VisionPipeline *_pipeline;

	VisionPipelineBuilder::VisionPipelineBuilder()
	{
		this->_pipeline = new VisionPipeline();
	}

	VisionPipelineBuilder::~VisionPipelineBuilder()
	{
		delete _pipeline;
	}

	//method not tested for correct functionility as of now due to missing implementation of the builder
	void VisionPipelineBuilder::reset() {
		if (_pipeline != NULL) {
			delete _pipeline;
		}
		this->_pipeline = new VisionPipeline();
	}

	//This method has no functionality, it only serves as an example how to create an add function.
	VisionPipelineBuilder& VisionPipelineBuilder::exampleAdd() {
		//_pipeline->addHandler();
		return *this;
	}

	//returns the pipeline
	VisionPipeline VisionPipelineBuilder::build() {
		return *_pipeline;
	}

}
