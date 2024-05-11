#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

GameManager::GameManager()
{
	m_amountOfEnemieskilled = 0;
	m_gameOver = false;
};

void GameManager::isGameOver(float currentHp)
{
	m_gameOver = true;
}

void GameManager::increaseAmountOfEnemiesKilled()
{
	m_amountOfEnemieskilled++;
	m_player.resetHp();
}

void GameManager::drawingEverything(sf::RenderWindow& window)
{
	window.clear();
	window.draw(m_player.getSprite());
	window.display();
}
