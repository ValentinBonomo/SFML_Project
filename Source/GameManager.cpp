#include "GameManager.h"
#include "Player.h"

GameManager::GameManager()
{
	// Initialisation des attributs
	m_amountOfEnemieskilled = 0;
	m_gameOver = false;
	m_purcentageOfStats = 1.05f;
}

void GameManager::increaseAmountOfEnemiesKilled()
{
	// Incrémentation du nombre d'ennemis tués
	m_amountOfEnemieskilled++;
	// Réinitialisation des points de vie du joueur
	m_player.resetHp();
}

void GameManager::increaseGold()
{
	// Ajout de l'or et augmentation du pourcentage des statistiques
	gold += 20 * m_purcentageOfStats;
	m_purcentageOfStats += .0005f;
}
