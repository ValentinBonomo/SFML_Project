#include "Enemy.h"
#include <iostream>

Enemy::Enemy(GameManager& gameManager) : m_maxHp(20), m_currentHp(20), m_damage(5), m_isAlive(true), m_gameManager(gameManager)
{
    calculateEnemyStats(gameManager);
    m_enemy_texture.loadFromFile("Enemy.png");
    m_sprite.setTexture(m_enemy_texture);
}

void Enemy::enemyGetBetter(GameManager& gameManager)
{
    gameManager.increaseAmountOfEnemiesKilled();
    calculateEnemyStats(gameManager);
}

void Enemy::takeDamage(int damage, Player& player)
{
    m_currentHp -= damage;
    if (m_currentHp <= 0)
    {
        m_gameManager.increaseAmountOfEnemiesKilled();
        if (m_gameManager.getIsPlayerFarming() == false)
        {
            m_gameManager.increasePurcentStats();
            m_gameManager.increaseGold();
        }
        m_gameManager.resetPlayerHp(player);
        m_isAlive = false;
    }
}

void Enemy::calculateEnemyStats(GameManager& gameManager)
{
    float percentage = m_gameManager.getPurcentStatsIncrease();
    m_maxHp = static_cast<int>(percentage * m_maxHp);
    m_currentHp = m_maxHp;
    m_damage = static_cast<int>(percentage * m_damage);
}

void Enemy::setPostionAndScale(float windowWidth, float windowHeight)
{
    sf::Vector2u textureSize = m_enemy_texture.getSize();
    float scaleFactor = 0.3f;

    m_sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));

    float posX = (0.65f * windowWidth) - (textureSize.x * scaleFactor * 0.5f);
    float posY = 0.5f * windowHeight - (textureSize.y * scaleFactor * 0.5f);
    sf::Vector2f newPosition(posX, posY);
    m_sprite.setPosition(newPosition);
}
