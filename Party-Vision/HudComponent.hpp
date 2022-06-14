#include "AbstractDrawcomponent.hpp"
#include "Texture.hpp"
#include <vector>
#include "PlaneComponent.hpp"
#include "Scene.hpp"
namespace Scene {
	class HudComponent : public AbstractDrawComponent {
	private:
		std::vector<GameObject> lives;
		std::vector<GameObject> time;
		std::vector<GameObject> score;
		std::vector<GameObject> highScore;
		std::vector<Texture*> numbers;
		Scene* scene;
		void initLives();
		void initScore();
		void initHighScore();
	public:
		HudComponent();
		void removeLife();
		void setTime(int timeInSeconds);
		void setScore(int score);
		void setHighScore(int score);
		virtual void draw() override;
	};
};