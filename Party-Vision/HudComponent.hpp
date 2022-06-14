#include "AbstractDrawcomponent.hpp"
#include "Texture.hpp"
#include <vector>
#include "PlaneComponent.hpp"
#include "Scene.hpp"
namespace Scene {
	class HudComponent : public AbstractDrawComponent {
	private:
		std::vector<GameObject> _lives;
		std::vector<GameObject> _time;
		std::vector<GameObject> _score;
		std::vector<GameObject> _highScore;
		std::vector<Texture*> _numbers;
		Scene* _scene;
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