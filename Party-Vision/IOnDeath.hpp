#pragma once
#include "AbstractComponent.hpp"

namespace Scene {
	__interface IOnDeath {
		/// <summary>
		/// Method get's called on object death.
		/// </summary>
		virtual void OnDeath();
	};
}