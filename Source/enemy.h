#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"

class Enemy
{
public:
    Enemy(GameManager& gameManager);
    const sf::Sprite& getSprite() { return m_sprite; }
    void setPostionAndScale(float windowWidth, float windowHeight);
    const int getMaxHP() { return m_maxHp; }
    const int getCurrentHP() { return m_currentHp; }
    const int getDamage() { return m_damage; }
    const bool getIsAlive() { return m_isAlive; }
    void enemyGetBetter(GameManager& gameManager);
    void takeDamage(int damage, Player& player);
    void resetHp() { m_currentHp = m_maxHp; }
    void calculateEnemyStats(GameManager& gameManager);
    void setIsAlive(bool alive) { m_isAlive = alive; }

private:
    sf::Sprite m_sprite;
    sf::Texture m_enemy_texture;
    int m_maxHp;
    int m_currentHp;
    int m_damage;
    GameManager& m_gameManager;
    bool m_isAlive;
};

