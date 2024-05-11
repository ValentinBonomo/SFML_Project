#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    void increaseMaxHP();
    void increaseDamage();
    void takeDamage(int damage); // Nouvelle fonction ajoutée
    void levelUp();
    void setPostionAndScale(float windowWidth, float windowHeight);

    int getCurrentHP() const { return m_currentHp; }
    int getMaxHP() const { return m_maxHp; }
    int getDamage() const { return m_damage; }
    int getLevel() const { return m_level; }
    int getExpToNextLevel() const { return m_expLevelUp - m_currentExp; }
    int getCurrentExp() const { return m_currentExp; }

private:
    int m_maxHp;
    int m_currentHp;
    int m_damage;
    int m_level;
    int m_expLevelUp;
    int m_currentExp;
    int levelPoints;

    sf::Texture m_player_texture;
    sf::Sprite m_sprite;
};

#endif // PLAYER_H
