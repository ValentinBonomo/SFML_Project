#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"

GameManager::GameManager()
{
	m_amountOfEnemieskilled = 0;
	m_gameOver = false;
	m_purcentageOfStats = 1.05f;
}

void GameManager::increaseAmountOfEnemiesKilled()
{
	m_amountOfEnemieskilled++;
	m_player.resetHp();
}

void GameManager::increaseGold()
{
	gold += 20 * m_purcentageOfStats;
	m_purcentageOfStats += .0005f;
}
