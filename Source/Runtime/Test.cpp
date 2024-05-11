#include <SFML/Window.hpp>
#include <iostream>
#include "Header.h"
#include "../GameManager.h"
#include "../player.h"
#include "../ui.h"
#include "../Enemy.h" // Inclure le fichier d'en-t�te de l'ennemi
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
    std::vector<Enemy*> enemyList; // Cr�er une liste de pointeurs d'ennemis
    enemyList.push_back(new Enemy(gameManager)); // Ajouter un ennemi � la liste
    enemyList[0]->setPostionAndScale(windowWidth, windowHeight); // D�finir la position et l'�chelle de l'ennemi

    UI ui; // Instancier l'interface utilisateur
    ui.setLevelTextPosition(player, windowWidth, windowHeight); // D�finir la position du texte du niveau
    ui.setHPTextPosition(player, windowWidth, windowHeight); // D�finir la position du texte des points de vie du joueur
    ui.setEnemyHPTextPosition(*enemyList[0]); // D�finir la position du texte des points de vie de l'ennemi

    // D�claration des variables pour le contr�le du temps
    sf::Clock clock;
    sf::Clock enemyTimer; // Timer pour le nouvel ennemi
    float deltaTime = 0.0f;
    float damageTimer = 0.0f;

    // on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
    bool mousePressed = false; // Variable pour suivre l'�tat de l'appui sur le bouton de la souris
    bool canEnemySpawn = false; // Variable pour suivre l'�tat de l'apparition de l'ennemi
    
    while (window.isOpen())
    {
        // Calcul du delta time
        deltaTime = clock.restart().asSeconds();

        // on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && !mousePressed) // V�rifiez si le bouton de la souris est press� et qu'il n'a pas d�j� �t� d�tect�
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (ui.isHPButtonClicked(window, player)) {
                        // Si le bouton d'augmentation des points de vie est cliqu�
                        // Augmenter les points de vie maximum du joueur
                        player.increaseMaxHP();
                        // Mettre � jour la position du texte des points de vie du joueur
                        ui.setHPTextPosition(player, windowWidth, windowHeight);
                        mousePressed = true; 
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                mousePressed = false; // R�initialisez l'�tat de l'appui sur le bouton de la souris lorsqu'il est rel�ch�
            }
            // �v�nement "fermeture demand�e" : on ferme la fen�tre
        }

        // Gestion du temps pour infliger des d�g�ts � l'ennemi
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
            // R�initialiser le compteur de temps pour tenir compte du temps restant
            damageTimer -= 1.0f;
            // S'assurer que damageTimer reste positif pour �viter la perte de temps
            if (damageTimer < 0.0f)
            {
                damageTimer = 0.0f;
            }
        }

        // Si le timer pour un nouvel ennemi d�passe une certaine dur�e
        if (enemyTimer.getElapsedTime().asSeconds() >= 2.0f && canEnemySpawn) {
            // Ajouter un nouvel ennemi � la liste
            enemyList.push_back(new Enemy(gameManager));
            enemyList.back()->setPostionAndScale(windowWidth, windowHeight);
            ui.setEnemyHPTextPosition(*enemyList.back());
            // Stopper le timer pour un nouvel ennemi
            enemyTimer.restart();
            canEnemySpawn = false; // Arr�ter le timer au lieu de le red�marrer
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

    // Lib�rer la m�moire allou�e pour les ennemis
    for (Enemy* enemy : enemyList) {
        delete enemy;
    }
    enemyList.clear(); // Vider la liste

    return 0;
}
