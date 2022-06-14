#include "IncreaseScoreComponent.hpp"
namespace Scene {
	IncreaseScoreComponent::IncreaseScoreComponent(SchoolNinjaComponent* game) : _game(game)
	{

	}
	void IncreaseScoreComponent::OnDeath()
	{
		_game->increaseScore(100);
	}
}