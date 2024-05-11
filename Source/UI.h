#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <iostream>

class UI
{
public:
    UI();
    void setLevelTextPosition(Player& player, float windowWidth, float windowHeight);
    void drawLevelText(sf::RenderWindow& window);
    void drawHPButton(sf::RenderWindow& window);
    bool isHPButtonClicked(sf::RenderWindow& window, Player& player);
    void drawHP(sf::RenderWindow& window);
    void setHPTextPosition(Player& player, float windowWidth, float windowHeight);
    void setEnemyHPTextPosition(Enemy& enemy);
    void drawEnemyHP(sf::RenderWindow& window, Enemy& enemy);

private:
    sf::Font m_font;
    sf::Text m_levelText;
    sf::RectangleShape m_hpButton;
    sf::Text m_hpText;
    sf::Text m_enemyHPText; // Ajout du texte des points de vie de l'ennemi
};

