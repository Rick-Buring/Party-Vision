#pragma once
#include <memory>
#include <list>

namespace Scene {
	class AbstractComponent;
	class GameObject
	{
	public:

	private:
		std::list<std::shared_ptr<AbstractComponent>> components;
	};
}