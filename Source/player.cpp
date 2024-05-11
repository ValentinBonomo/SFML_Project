#include "player.h"
#include <iostream>

Player::Player()
{
	m_maxHp = 100;
	m_currentHp = 100;
	m_damage = 10;
	m_level = 1;
	m_expLevelUp = 100;
	m_currentExp = 0;
	levelPoints = 2;
	m_player_texture.loadFromFile("D:/Documents/GitHub/ConsoleApplication1/Source/Player.png");
	m_sprite.setTexture(m_player_texture);
}

void Player::increaseMaxHP()
{
	if (levelPoints > 0) {
		m_maxHp += 10;
		if (m_currentHp+10 >= m_maxHp)
		{
			m_currentHp = m_maxHp;
		}
		else
		{
			m_currentHp += 10;
		}
        
		levelPoints--;
	}
	else {
		std::cout << "You don't have enough level points" << std::endl;
	}
}

void Player::increaseDamage()
{
	if (levelPoints > 0) {
		m_damage += 5;
		levelPoints--;
	}
	else {
		std::cout << "You don't have enough level points" << std::endl;
	}
}

void Player::takeDamage(int damage)
{
	m_currentHp -= damage;
	if (m_currentHp <= 0)
	{
		// Player defeated
		std::cout << "Player defeated" << std::endl;
		// You can handle the player defeat logic here
	}
}

void Player::levelUp()
{
	if (m_currentExp >= m_expLevelUp)
	{
		m_level++;
		m_expLevelUp *= 1.15f;
		m_currentExp = 0;
		m_maxHp *= 1.1f;
		m_currentHp += (m_maxHp*0.25f);
		levelPoints ++;
	}
}

void Player::setPostionAndScale(float windowWidth, float windowHeight)
{
	sf::Vector2u textureSize = m_player_texture.getSize();
	float scaleFactor = 0.3f;

	m_sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));

	// Calcul de la position pour centrer le joueur un peu à gauche de l'écran
	float posX = (0.35f * windowWidth) - (textureSize.x * scaleFactor * 0.5f);
	float posY = 0.5f * windowHeight - (textureSize.y * scaleFactor * 0.5f);
	sf::Vector2f newPosition(posX, posY);
	m_sprite.setPosition(newPosition);
}
