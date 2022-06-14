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
		/// <summary>
		/// Creates the objects for the lives and adds them to the vector lives.
		/// </summary>
		void initLives();

		/// <summary>
		/// Creates the objects for the score and adds them to the vector score.
		/// </summary>
		void initScore();

		/// <summary>
		/// Creates the objects for the highscore and adds them to the vector highscore.
		/// </summary>
		void initHighScore();
	public:
		HudComponent();

		/// <summary>
		/// Removes 1 object that represent a life form the vector lives.
		/// </summary>
		void removeLife();

		/// <summary>
		/// Creates drawable objects that reperesent the time left in the game and adds them to the vector time.
		/// </summary>
		/// <param name="timeInSeconds">The time left in the game</param>
		void setTime(int timeInSeconds);

		/// <summary>
		/// Updates the drawable object for the score in the vector score to represent the current score.
		/// </summary>
		/// <param name="score">The current score</param>
		void setScore(int score);

		/// <summary>
		/// Updates the drawable object for the highscore in the vector highscore to represent the current highscore.
		/// </summary>
		/// <param name="score">The current highscore</param>
		void setHighScore(int score);

		/// <summary>
		/// Draws the object present in the vectors time, lives, score and highscore.
		/// </summary>
		virtual void draw() override;
	};
};