#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void upgradeHPWithGold(int gold);
    void upgradeDamageWithGold(int gold);
    void takeDamage(int damage);
    void setPostionAndScale(float windowWidth, float windowHeight);

    int getCurrentHP() const { return m_currentHp; }
    int getMaxHP() const { return m_maxHp; }
    int getDamage() const { return m_damage; }
    int getUpgradeCostHP() const { return upgradeCostHP; }
    int getUpgradeCostDMG() const { return upgradeCostDMG; }
    bool getisAlive() const { return isAlive; }
    void setIsAlive(bool alive) { isAlive = alive; }
    void resetHp() { m_currentHp = m_maxHp; }
    
    int getHPIncreaseAmount() const { return hpIncreaseAmount; }
    int getDMGIncreaseAmount() const { return dmgIncreaseAmount; }
    
    const sf::Sprite& getSprite() const { return m_sprite; }

private:
    int m_maxHp;
    int m_currentHp;
    int m_damage;
    int upgradeCostHP;
    int upgradeCostDMG;
    bool isAlive;

    int hpIncreaseAmount;
    int dmgIncreaseAmount;

    sf::Texture m_player_texture;
    sf::Sprite m_sprite;
};
