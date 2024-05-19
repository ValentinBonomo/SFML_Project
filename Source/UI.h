#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "GameManager.h"
#include <iostream>
class UI {
public:
    UI();

    void drawLevelText(sf::RenderWindow& window);

    void drawHPButton(sf::RenderWindow& window);
    void drawDMGButton(sf::RenderWindow& window);
    bool isHPButtonClicked(sf::RenderWindow& window, Player& player);
    bool isDMGButtonClicked(sf::RenderWindow& window, Player& player);
    void setHPButtonPosition(float windowWidth, float windowHeight);
    void setDMGButtonPosition(float windowWidth, float windowHeight);

    void setHPTextPosition(Player& player);
    void setEnemyHPTextPosition(Enemy& enemy);
    void drawHP(sf::RenderWindow& window, Player& player);
    void drawEnemyHP(sf::RenderWindow& window, Enemy& enemy);

    void setGoldTextPosition(GameManager& gameManager, float windowWidth);
    void drawGold(sf::RenderWindow& window, GameManager& gameManager);

    void setDamageTextPosition(Player& player);
    void drawDamage(sf::RenderWindow& window, Player& player);

private:
    sf::Font m_font;
    sf::Text m_levelText;
    sf::Text m_hpText;
    sf::Text m_enemyHPText;
    sf::Text m_goldText;
    sf::Text m_hpButtonText;
    sf::Text m_dmgButtonText;
    sf::RectangleShape m_hpButton;
    sf::RectangleShape m_dmgButton;
    sf::Text m_damageText;
};
