#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class GameManager
{
public:
	GameManager();
	void increaseAmountOfEnemiesKilled();
	const int getAmountOfEnemiesKilled() { return m_amountOfEnemieskilled; }
	float getPurcentStatsIncrease() { return m_purcentageOfStats; }
	void resetPlayerHp(Player& player) { player.resetHp(); }
	void setIsPlayerFarming(bool isFarming) { isPlayerFarming = isFarming; }
	bool getIsPlayerFarming() { return isPlayerFarming; }
	void increasePurcentStats() { m_purcentageOfStats += .05f; }
	void decreasePurcentStats() { m_purcentageOfStats -= .05f; }
	int getGold() { return gold; }
	void increaseGold();
	void removeGold(int goldToRemove) { gold -= goldToRemove; }
	bool canAffordUpgrade(int cost) const { return gold >= cost; }

private:
	Player m_player;
	bool m_gameOver;
	int m_amountOfEnemieskilled;
	float m_purcentageOfStats;
	bool isPlayerFarming = false;
	int gold = 0;
};
