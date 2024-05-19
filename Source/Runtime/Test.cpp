#include <SFML/Window.hpp>
#include <iostream>
#include "Header.h"
#include "../GameManager.h"
#include "../player.h"
#include "../ui.h"
#include "../Enemy.h"
#include <vector>

int main() {
    Player player;

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Idle Game");
    sf::Vector2u windowSize = window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);
    player.setPostionAndScale(windowWidth, windowHeight);

    GameManager gameManager;
    std::vector<Enemy*> enemyList;
    enemyList.push_back(new Enemy(gameManager));
    enemyList[0]->setPostionAndScale(windowWidth, windowHeight);

    UI ui;
    ui.setHPTextPosition(player);
    ui.setEnemyHPTextPosition(*enemyList[0]);
    ui.setGoldTextPosition(gameManager, windowWidth);
    ui.setHPButtonPosition(windowWidth, windowHeight);
    ui.setDMGButtonPosition(windowWidth, windowHeight);
    ui.setDamageTextPosition(player);

    sf::Clock clock;
    sf::Clock enemyTimer;
    float deltaTime = 0.0f;
    float damageTimer = 0.0f;

    bool mousePressed = false;
    bool canEnemySpawn = false;

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed && !mousePressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (ui.isHPButtonClicked(window, player)) {
                        int upgradeCost = player.getUpgradeCostHP();
                        if (gameManager.canAffordUpgrade(upgradeCost)) {
                            player.upgradeHPWithGold(upgradeCost);
                            gameManager.removeGold(upgradeCost);
                            ui.setHPTextPosition(player);
                            ui.setGoldTextPosition(gameManager, windowWidth);
                            ui.setHPButtonPosition(windowWidth, windowHeight);
                        } else {
                            std::cout << "Not enough gold to upgrade HP" << std::endl;
                        }
                        mousePressed = true;
                    } else if (ui.isDMGButtonClicked(window, player)) {
                        int upgradeCost = player.getUpgradeCostDMG();
                        if (gameManager.canAffordUpgrade(upgradeCost)) {
                            player.upgradeDamageWithGold(upgradeCost);
                            gameManager.removeGold(upgradeCost);
                            ui.setDamageTextPosition(player);
                            ui.setGoldTextPosition(gameManager, windowWidth);
                            ui.setDMGButtonPosition(windowWidth, windowHeight);
                        } else {
                            std::cout << "Not enough gold to upgrade damage" << std::endl;
                        }
                        mousePressed = true;
                    }
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                mousePressed = false;
            }
        }

        damageTimer += deltaTime;
        if (damageTimer >= 1.0f) {
            if (!enemyList.empty()) {
                enemyList[0]->takeDamage(player.getDamage(), player);

                if (enemyList[0]->getIsAlive() == false) {
                    delete enemyList[0];
                    enemyList.erase(enemyList.begin());
                    gameManager.increaseGold();
                    ui.setGoldTextPosition(gameManager, windowWidth);
                    enemyTimer.restart();
                    canEnemySpawn = true;
                } else {
                    player.takeDamage(enemyList[0]->getDamage());
                    if (player.getisAlive() == false) {
                        player.resetHp();
                        player.setIsAlive(true);
                        if (gameManager.getIsPlayerFarming() == false) {
                            gameManager.setIsPlayerFarming(true);
                            gameManager.decreasePurcentStats();
                            enemyList[0]->calculateEnemyStats(gameManager);
                            ui.setGoldTextPosition(gameManager, windowWidth);
                        }
                        enemyList[0]->resetHp();
                    }
                }
            }
            damageTimer -= 1.0f;
            if (damageTimer < 0.0f) {
                damageTimer = 0.0f;
            }
        }

        if (enemyTimer.getElapsedTime().asSeconds() >= 2.0f && canEnemySpawn) {
            enemyList.push_back(new Enemy(gameManager));
            enemyList.back()->setPostionAndScale(windowWidth, windowHeight);
            ui.setEnemyHPTextPosition(*enemyList.back());
            enemyTimer.restart();
            canEnemySpawn = false;
        }

        window.clear();
        window.draw(player.getSprite());
        if (!enemyList.empty()) {
            window.draw(enemyList[0]->getSprite());
            ui.drawEnemyHP(window, *enemyList[0]);
            std::cout << "Enemy HP: " << enemyList[0]->getCurrentHP() << std::endl;
        }
        ui.drawHP(window, player);
        ui.drawHPButton(window);
        ui.drawDMGButton(window);
        ui.drawHP(window, player);
        ui.drawGold(window, gameManager);
        ui.drawDamage(window, player);
        window.display();
    }
    for (Enemy* enemy : enemyList) {
        delete enemy;
    }
    enemyList.clear();

    return 0;
}

