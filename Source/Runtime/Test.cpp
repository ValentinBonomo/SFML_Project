#include <SFML/Window.hpp>
#include <iostream>
#include "Header.h"
#include "../GameManager.h"
#include "../player.h"
#include "../ui.h"
#include "../Enemy.h" // Inclure le fichier d'en-tête de l'ennemi
#include <vector>

int main()
{
    Player player;
    std::cout << player.getLevelPoints();

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Idle Game");
    sf::Vector2u windowSize = window.getSize();
    float windowWidth = static_cast<float>(windowSize.x);
    float windowHeight = static_cast<float>(windowSize.y);
    player.setPostionAndScale(windowWidth, windowHeight);

    GameManager gameManager; // Instancier le gestionnaire de jeu
    std::vector<Enemy*> enemyList; // Créer une liste de pointeurs d'ennemis
    enemyList.push_back(new Enemy(gameManager)); // Ajouter un ennemi à la liste
    enemyList[0]->setPostionAndScale(windowWidth, windowHeight); // Définir la position et l'échelle de l'ennemi

    UI ui; // Instancier l'interface utilisateur
    ui.setLevelTextPosition(player, windowWidth, windowHeight); // Définir la position du texte du niveau
    ui.setHPTextPosition(player, windowWidth, windowHeight); // Définir la position du texte des points de vie du joueur
    ui.setEnemyHPTextPosition(*enemyList[0]); // Définir la position du texte des points de vie de l'ennemi

    // Déclaration des variables pour le contrôle du temps
    sf::Clock clock;
    sf::Clock enemyTimer; // Timer pour le nouvel ennemi
    float deltaTime = 0.0f;
    float damageTimer = 0.0f;

    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    bool mousePressed = false; // Variable pour suivre l'état de l'appui sur le bouton de la souris
    bool canEnemySpawn = false; // Variable pour suivre l'état de l'apparition de l'ennemi
    
    while (window.isOpen())
    {
        // Calcul du delta time
        deltaTime = clock.restart().asSeconds();

        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && !mousePressed) // Vérifiez si le bouton de la souris est pressé et qu'il n'a pas déjà été détecté
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (ui.isHPButtonClicked(window, player)) {
                        // Si le bouton d'augmentation des points de vie est cliqué
                        // Augmenter les points de vie maximum du joueur
                        player.increaseMaxHP();
                        // Mettre à jour la position du texte des points de vie du joueur
                        ui.setHPTextPosition(player, windowWidth, windowHeight);
                        mousePressed = true; 
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                mousePressed = false; // Réinitialisez l'état de l'appui sur le bouton de la souris lorsqu'il est relâché
            }
            // évènement "fermeture demandée" : on ferme la fenêtre
        }

        // Gestion du temps pour infliger des dégâts à l'ennemi
        damageTimer += deltaTime;
        if (damageTimer >= 1.0f)
        {
            if (!enemyList.empty()) {
                enemyList[0]->takeDamage(player.getDamage());
                if (enemyList[0]->getIsAlive() == false)
                {
                    for (Enemy* enemy : enemyList) {
                        delete enemy;
                    }
                    enemyList.clear();
                    // Stopper le timer pour un nouvel ennemi
                    enemyTimer.restart();
                    canEnemySpawn = true;
                }
            }
            // Réinitialiser le compteur de temps pour tenir compte du temps restant
            damageTimer -= 1.0f;
            // S'assurer que damageTimer reste positif pour éviter la perte de temps
            if (damageTimer < 0.0f)
            {
                damageTimer = 0.0f;
            }
        }

        // Si le timer pour un nouvel ennemi dépasse une certaine durée
        if (enemyTimer.getElapsedTime().asSeconds() >= 2.0f && canEnemySpawn) {
            // Ajouter un nouvel ennemi à la liste
            enemyList.push_back(new Enemy(gameManager));
            enemyList.back()->setPostionAndScale(windowWidth, windowHeight);
            ui.setEnemyHPTextPosition(*enemyList.back());
            // Stopper le timer pour un nouvel ennemi
            enemyTimer.restart();
            canEnemySpawn = false; // Arrêter le timer au lieu de le redémarrer
        }

        window.clear();
        window.draw(player.getSprite()); // Dessiner le joueur
        // Dessiner l'ennemi si la liste n'est pas vide
        if (!enemyList.empty()) {
            window.draw(enemyList[0]->getSprite());
            ui.drawEnemyHP(window, *enemyList[0]);
            std::cout << "Enemy HP: " << enemyList[0]->getCurrentHP() << std::endl; // Afficher les points de vie de l'ennemi dans la console
        }
        ui.drawLevelText(window); // Dessiner le texte du niveau
        ui.drawHPButton(window); // Dessiner le bouton d'augmentation des points de vie du joueur
        ui.drawHP(window); // Dessiner les points de vie du joueur
        window.display();
    }

    // Libérer la mémoire allouée pour les ennemis
    for (Enemy* enemy : enemyList) {
        delete enemy;
    }
    enemyList.clear(); // Vider la liste

    return 0;
}
