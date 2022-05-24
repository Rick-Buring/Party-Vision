#pragma once

namespace Vision {
	class VisionPipeline;
	class VisionPipelineBuilder
	{
		VisionPipeline *_pipeline;

	public:
		VisionPipelineBuilder();
		~VisionPipelineBuilder();

		VisionPipelineBuilder& exampleAdd();
		void reset();
		VisionPipeline build();
	private:
		
	};
}