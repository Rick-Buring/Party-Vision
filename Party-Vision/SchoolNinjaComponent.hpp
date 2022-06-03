#pragma once
#include "AbstractComponent.hpp"
#include "Scene.hpp"
#include <vector>
#include "ObjectLoader.hpp"

class DrawObjectComponent;

namespace Scene {

	typedef struct {
		std::vector<VBO_Textures_t> object;
		std::vector<VBO_Textures_t> childObject;
	} parentObject_t;

	class SchoolNinja : public AbstractComponent {
	public:
		SchoolNinja(Scene* scene);

		void update(float deltaTime) override;
		
		void removeLife();
		void increaseScore(int score);

	private:
		std::vector<parentObject_t> _objects;
		std::vector<std::shared_ptr<AbstractComponent>>_textureList;
		Scene* _scene;

		char _lifes = 3;
		long int _score = 0;
		float _durationSeconds = 180;


	};
}