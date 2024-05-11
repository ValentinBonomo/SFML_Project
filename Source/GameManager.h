#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class GameManager
{
public:
		GameManager();
		void isGameOver(float currentHp);
		void increaseAmountOfEnemiesKilled();
		const int getAmountOfEnemiesKilled() { return m_amountOfEnemieskilled; }
		void drawingEverything(sf::RenderWindow &window);

private:
		Player m_player;
		bool m_gameOver;
		int m_amountOfEnemieskilled;
};
