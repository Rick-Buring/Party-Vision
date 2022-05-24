#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"

#include "GameObject.hpp"
#include "AbstractComponent.hpp"
#include "AbstractDrawcomponent.hpp"
#include "TransformComponent.hpp"

namespace Scene {
	GameObject::~GameObject()
	{
		GameObject::components.clear();
	}
	void GameObject::addComponent(std::shared_ptr<AbstractComponent> component)
	{
		component->setGameObject(this);
		GameObject::components.push_back(component);


		if (GameObject::_drawComponent == nullptr)
			GameObject::_drawComponent = std::dynamic_pointer_cast<AbstractDrawComponent>(component);
		if (GameObject::_transformComponent == nullptr)
			GameObject::_transformComponent = std::dynamic_pointer_cast<TransformComponent>(component);

	}

	std::list<std::shared_ptr<AbstractComponent>> GameObject::getComponents()
	{
		return components;
	}

	void GameObject::update(float elapsedTime)
	{
		for (auto& c : components)
			c->update(elapsedTime);
	}

	void GameObject::draw(const glm::mat4& parentMatrix) {
		if (!_drawComponent || !_transformComponent)
			return;

		glm::mat4 modelMatrix = parentMatrix;
		modelMatrix = glm::translate(modelMatrix, _transformComponent->position);
		modelMatrix = glm::rotate(modelMatrix, _transformComponent->rotation.x, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, _transformComponent->rotation.y, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, _transformComponent->rotation.z, glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, _transformComponent->scale);

		tigl::shader->setModelMatrix(modelMatrix);
		_drawComponent->draw();
	}
	GameObject* GameObject::getGameObject()
	{
		return this;
	}
}