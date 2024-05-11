#include "Enemy.h"
#include <iostream>

Enemy::Enemy(GameManager& gameManager) : m_maxHp(0), m_currentHp(0), m_damage(0), m_isAlive(true), m_gameManager(gameManager)
{
    calculateEnemyStats(gameManager);
    m_enemy_texture.loadFromFile("D:/Documents/GitHub/ConsoleApplication1/Source/Enemy.png");
    m_sprite.setTexture(m_enemy_texture);
}

void Enemy::enemyGetBetter(GameManager& gameManager)
{
    gameManager.increaseAmountOfEnemiesKilled();
    calculateEnemyStats(gameManager);
}

void Enemy::takeDamage(int damage)
{
    m_currentHp -= damage;
    if (m_currentHp <= 0)
    {
        m_gameManager.increaseAmountOfEnemiesKilled();
        std::cout << "DAMAGE" << std::endl;
        m_isAlive = false;
    }
}

void Enemy::calculateEnemyStats(GameManager& gameManager)
{
    if (gameManager.getAmountOfEnemiesKilled() == 0)
    {
        m_maxHp = 20;
        m_currentHp = 20;
        m_damage = 5;
    }
    else
    {
        float percentage = gameManager.getAmountOfEnemiesKilled() * 1.05f;
        m_maxHp = static_cast<int>(percentage * 20); // 20 is the base maxHp
        m_currentHp = m_maxHp;
        m_damage = static_cast<int>(percentage * 5); // 5 is the base damage
    }
}

void Enemy::setPostionAndScale(float windowWidth, float windowHeight)
{
    sf::Vector2u textureSize = m_enemy_texture.getSize();
    float scaleFactor = 0.3f;

    m_sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));

    // Calcul de la position pour centrer l'ennemi un peu à droite de l'écran
    float posX = (0.65f * windowWidth) - (textureSize.x * scaleFactor * 0.5f);
    float posY = 0.5f * windowHeight - (textureSize.y * scaleFactor * 0.5f);
    sf::Vector2f newPosition(posX, posY);
    m_sprite.setPosition(newPosition);
}
