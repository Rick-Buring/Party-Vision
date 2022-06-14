#include "HudComponent.hpp"
#include "WindowManager.hpp"
#include "TransformComponent.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace Scene {
	HudComponent::HudComponent()
	{
		_lives = std::vector<GameObject>();
		_time = std::vector<GameObject>();
		_score = std::vector<GameObject>();
		_highScore = std::vector<GameObject>();
		_numbers = std::vector<Texture*>();
		for (int i = 0; i < 10; i++)
		{
			char file[30];
			sprintf_s(file, "textures/%d.png", i);
			_numbers.push_back(new Texture(file));
		}
		initLives();
		initScore();
		initHighScore();
	}

	void HudComponent::draw()
	{
		for (auto life : _lives) {
			life.draw();
		}
		for (auto number : _time) {
			number.draw();
		}
		for (auto number : _score) {
			number.draw();
		}
		for (auto number : _highScore) {
			number.draw();
		}
	}

	void HudComponent::initLives() {
		double livesHeight = 25;
		double livesWidth = 30;
		for (int i = 0; i < 3; i++) {
			GameObject life = GameObject();
			std::shared_ptr<PlaneComponent> lifePlane = std::make_shared<PlaneComponent>(livesWidth * scalex, livesHeight * scaley, new Texture("textures/heart.png"));

			life.addComponent(lifePlane);

			std::shared_ptr <TransformComponent> lifeTransform = std::make_shared <TransformComponent>(glm::vec3(((windowWidth / 2) - (livesWidth * 1.5) * scalex) + ((livesWidth * i) * scalex), (livesHeight * scaley) * 2, -69));

			life.addComponent(lifeTransform);

			_lives.push_back(life);
		}
	}

	void HudComponent::removeLife() {
		GameObject life = *(_lives.end() - 1);
		_lives.pop_back();
	}

	void HudComponent::initScore() {
		constexpr double scoreHeight = 15;
		constexpr double scoreWidth = 10;
		constexpr double scoreTextHeight = 15;
		constexpr double scoreTextWidth = 60;
		constexpr double scoreTextx = 25;
		constexpr double scoreTexty = 25;
		GameObject scoreText = GameObject();
		std::shared_ptr<PlaneComponent> scoreTextPlane = std::make_shared<PlaneComponent>(scoreTextWidth * scalex, scoreTextHeight * scaley, new Texture("textures/score.png"));

		scoreText.addComponent(scoreTextPlane);

		std::shared_ptr <TransformComponent> scoreTextTransform = std::make_shared <TransformComponent>(glm::vec3(scoreTextx * scalex, scoreTexty * scaley, -69));

		scoreText.addComponent(scoreTextTransform);
		this->_score.push_back(scoreText);
		for (int i = 0; i < 5; i++) {
			GameObject score = GameObject();
			std::shared_ptr<PlaneComponent> scorePlane = std::make_shared<PlaneComponent>(scoreWidth * scalex, scoreHeight * scaley, _numbers[0]);

			score.addComponent(scorePlane);

			std::shared_ptr <TransformComponent> scoreTransform = std::make_shared <TransformComponent>(glm::vec3(((scoreTextx * scalex) + (scoreTextWidth * scalex) + 10) + ((scoreWidth * i) * scalex), scoreTexty * scaley, -69));

			score.addComponent(scoreTransform);

			this->_score.push_back(score);
		}
	}

	void HudComponent::setScore(int score) {
		
		for (size_t i = 5; i > 0; i--)
		{
			int digit = score % 10;

			this->_score[i].getComponent<PlaneComponent>()->texture = _numbers[digit];

			score /= 10;
		}
	}

	void HudComponent::initHighScore() {
		constexpr double highScoreHeight = 15;
		constexpr double highScoreWidth = 10;
		constexpr double highScoreTextHeight = 25;
		constexpr double highScoreTextWidth = 90;
		constexpr double highScoreTextx = 30;
		constexpr double highScoreTexty = 25;
		const double highScoreTextxCalc = windowWidth - ((highScoreTextx * scaley) + ((highScoreWidth * scalex) * 5) + (highScoreTextWidth * scalex));
		GameObject highScoreText = GameObject();
		std::shared_ptr<PlaneComponent> highScoreTextPlane = std::make_shared<PlaneComponent>(highScoreTextWidth * scalex, highScoreTextHeight * scaley, new Texture("textures/highscore.png"));

		highScoreText.addComponent(highScoreTextPlane);

		std::shared_ptr <TransformComponent> highScoreTextTransform = std::make_shared <TransformComponent>(glm::vec3(highScoreTextxCalc, highScoreTexty * scaley, -69));

		highScoreText.addComponent(highScoreTextTransform);
		this->_highScore.push_back(highScoreText);
		for (int i = 0; i < 5; i++) {
			GameObject highScore = GameObject();
			std::shared_ptr<PlaneComponent> highScorePlane = std::make_shared<PlaneComponent>(highScoreWidth * scalex, highScoreHeight * scaley, _numbers[0]);

			highScore.addComponent(highScorePlane);

			std::shared_ptr <TransformComponent>highScoreTransform = std::make_shared <TransformComponent>(glm::vec3(((highScoreTextxCalc) + (highScoreTextWidth * scalex) + 10) + ((highScoreWidth * i) * scalex), highScoreTexty * scaley, -69));

			highScore.addComponent(highScoreTransform);

			this->_highScore.push_back(highScore);
		}
	}

	void HudComponent::setHighScore(int score) {
		
		for (size_t i = 5; i > 0; i--)
		{
			int digit = score % 10;

			this->_highScore[i].getComponent<PlaneComponent>()->texture = _numbers[digit];

			score /= 10;
		}
	}


	void HudComponent::setTime(int timeInSeconds) {
		_time.clear();
		constexpr double timeHeight = 25;
		constexpr double timeWidth = 20;
		int i = 0;
		int j = 0;
		float digits;
		int t = timeInSeconds;

		do {
			t /= 10;
			j++;
		} while (t);

		while (timeInSeconds){

			int currentDigit = timeInSeconds % 10;
			GameObject digit = GameObject();
			std::shared_ptr<PlaneComponent> timePlane = std::make_shared<PlaneComponent>(timeWidth * scalex, timeHeight * scaley, _numbers[currentDigit]);

			digit.addComponent(timePlane);

			std::shared_ptr <TransformComponent> timeTransform = std::make_shared <TransformComponent>(glm::vec3(((windowWidth / 2.0) + ((timeWidth * (j/2.0-1)) * scalex)) - ((timeWidth * i) * scalex), timeHeight * scaley, -69));

			digit.addComponent(timeTransform);

			_time.push_back(digit);
			timeInSeconds /= 10;
			i++;
		}
	}


}



