#pragma once
namespace Vision {
	 __interface IVisionHandler {

		virtual void process(char imageArray[]);
	};
}