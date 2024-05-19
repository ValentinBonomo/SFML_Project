#include "player.h"
#include <iostream>

Player::Player()
{
    m_maxHp = 100;
    m_currentHp = 100;
    m_damage = 10;
    upgradeCostHP = 50;
    upgradeCostDMG = 50;
    hpIncreaseAmount = 10;
    dmgIncreaseAmount = 5;
    m_player_texture.loadFromFile("D:/Documents/GitHub/ConsoleApplication1/Source/Player.png");
    m_sprite.setTexture(m_player_texture);
    isAlive = true;
}

void Player::upgradeHPWithGold(int gold)
{
    if (gold >= upgradeCostHP) {
        m_maxHp += hpIncreaseAmount;
        m_currentHp = m_maxHp;
        upgradeCostHP *= 1.5;
    } else {
        std::cout << "Not enough gold to upgrade HP" << std::endl;
    }
}

void Player::upgradeDamageWithGold(int gold)
{
    if (gold >= upgradeCostDMG) {
        m_damage += dmgIncreaseAmount;
        upgradeCostDMG *= 1.5;
    } else {
        std::cout << "Not enough gold to upgrade damage" << std::endl;
    }
}

void Player::takeDamage(int damage)
{
    m_currentHp -= damage;
    if (m_currentHp <= 0)
    {
        std::cout << "Player defeated" << std::endl;
        isAlive = false;
    }
}

void Player::setPostionAndScale(float windowWidth, float windowHeight)
{
    sf::Vector2u textureSize = m_player_texture.getSize();
    float scaleFactor = 0.3f;

    m_sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));

    float posX = (0.35f * windowWidth) - (textureSize.x * scaleFactor * 0.5f);
    float posY = 0.5f * windowHeight - (textureSize.y * scaleFactor * 0.5f);
    sf::Vector2f newPosition(posX, posY);
    m_sprite.setPosition(newPosition);
}
