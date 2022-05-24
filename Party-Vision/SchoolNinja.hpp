#pragma once
#include "AbstractComponent.hpp"
#include "Scene.hpp"
#include <vector>
#include "ObjectLoader.hpp"

namespace Scene {

	typedef struct {
		std::vector<VBO_Textures_t> object;
		std::vector<VBO_Textures_t> childObject;
	} parentObject_t;
	
	class SchoolNinja : public AbstractComponent {
	public:
		SchoolNinja(Scene* scene);
		void update(float deltaTime) override;
		
		void increaseScore(int score);

	private:
		std::vector<parentObject_t> _objects;
		Scene* _scene;
		long int _score = 0;
		float _durationSeconds = 180;


	};
}