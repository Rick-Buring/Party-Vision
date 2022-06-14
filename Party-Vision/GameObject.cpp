#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"

#include "GameObject.hpp"
#include "AbstractComponent.hpp"
#include "AbstractDrawcomponent.hpp"
#include "TransformComponent.hpp"

namespace Scene {
	GameObject::~GameObject()
	{
		GameObject::_components.clear();
	}
	void GameObject::addComponent(std::shared_ptr<AbstractComponent> component)
	{
		component->setGameObject(this);
		GameObject::_components.push_back(component);


		if (GameObject::_drawComponent == nullptr)
			GameObject::_drawComponent = std::dynamic_pointer_cast<AbstractDrawComponent>(component);
		if (GameObject::Transform == nullptr)
			GameObject::Transform = std::dynamic_pointer_cast<TransformComponent>(component);

	}

	std::list<std::shared_ptr<AbstractComponent>> GameObject::getComponents()
	{
		return _components;
	}

	void GameObject::update(float elapsedTime)
	{
		for (auto& c : _components)
			c->update(elapsedTime);
	}

	void GameObject::draw(const glm::mat4& parentMatrix) {
		if (!_drawComponent || !GameObject::Transform)
			return;

		glm::mat4 modelMatrix = parentMatrix;
		modelMatrix = glm::translate(modelMatrix, GameObject::Transform->position);
		modelMatrix = glm::rotate(modelMatrix, GameObject::Transform->rotation.x, glm::vec3(1, 0, 0));
		modelMatrix = glm::rotate(modelMatrix, GameObject::Transform->rotation.y, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, GameObject::Transform->rotation.z, glm::vec3(0, 0, 1));
		modelMatrix = glm::scale(modelMatrix, GameObject::Transform->scale);

		tigl::shader->setModelMatrix(modelMatrix);
		_drawComponent->draw();
	}
	GameObject* GameObject::getGameObject()
	{
		return this;
	}
}