#include "UI.h"

UI::UI() {
    if (!m_font.loadFromFile("Exo-Regular.ttf")) {
        std::cout << "Failed to load font" << std::endl;
    }

    m_hpButton.setSize(sf::Vector2f(150, 75)); // Augmenter la taille des boutons
    m_hpButton.setFillColor(sf::Color::Green);

    m_dmgButton.setSize(sf::Vector2f(150, 75)); // Augmenter la taille des boutons
    m_dmgButton.setFillColor(sf::Color::Red);

    m_hpText.setFont(m_font);
    m_hpText.setCharacterSize(16);
    m_hpText.setFillColor(sf::Color::White);
    m_hpText.setStyle(sf::Text::Bold);

    m_goldText.setFont(m_font);
    m_goldText.setCharacterSize(20); // Taille plus grande
    m_goldText.setFillColor(sf::Color::Yellow); // Couleur jaune
    m_goldText.setStyle(sf::Text::Bold);
    m_goldText.setPosition(10, 50); // Nouvelle position à gauche

    m_enemyHPText.setFont(m_font);
    m_enemyHPText.setCharacterSize(16);
    m_enemyHPText.setFillColor(sf::Color::Red);
    m_enemyHPText.setStyle(sf::Text::Bold);

    m_hpButtonText.setFont(m_font);
    m_hpButtonText.setCharacterSize(16);
    m_hpButtonText.setFillColor(sf::Color::White);
    m_hpButtonText.setStyle(sf::Text::Bold);

    m_dmgButtonText.setFont(m_font);
    m_dmgButtonText.setCharacterSize(16);
    m_dmgButtonText.setFillColor(sf::Color::White);
    m_dmgButtonText.setStyle(sf::Text::Bold);

    m_damageText.setFont(m_font);
    m_damageText.setCharacterSize(16);
    m_damageText.setFillColor(sf::Color::White);
    m_damageText.setStyle(sf::Text::Bold);
}

void UI::drawHPButton(sf::RenderWindow& window) {
    window.draw(m_hpButton);
    window.draw(m_hpButtonText);
}

void UI::drawDMGButton(sf::RenderWindow& window) {
    window.draw(m_dmgButton);
    window.draw(m_dmgButtonText);
}

bool UI::isHPButtonClicked(sf::RenderWindow& window, Player& player) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f buttonPosition = m_hpButton.getPosition();
    sf::Vector2f buttonSize = m_hpButton.getSize();

    if (mousePosition.x >= buttonPosition.x && mousePosition.x <= buttonPosition.x + buttonSize.x &&
        mousePosition.y >= buttonPosition.y && mousePosition.y <= buttonPosition.y + buttonSize.y) {
        return true;
    }

    return false;
}

bool UI::isDMGButtonClicked(sf::RenderWindow& window, Player& player) {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f buttonPosition = m_dmgButton.getPosition();
    sf::Vector2f buttonSize = m_dmgButton.getSize();

    if (mousePosition.x >= buttonPosition.x && mousePosition.x <= buttonPosition.x + buttonSize.x &&
        mousePosition.y >= buttonPosition.y && mousePosition.y <= buttonPosition.y + buttonSize.y) {
        return true;
    }

    return false;
}

void UI::setHPTextPosition(Player& player) {
    m_hpText.setString("HP: " + std::to_string(player.getCurrentHP()) + "/" + std::to_string(player.getMaxHP()));
    sf::Vector2u textureSize = player.getSprite().getTexture()->getSize();
    float scaleFactor = player.getSprite().getScale().x;

    sf::FloatRect textBounds = m_hpText.getLocalBounds();
    float posX = player.getSprite().getPosition().x + (textureSize.x * scaleFactor * 0.5f) - (textBounds.width * 0.5f);
    float posY = player.getSprite().getPosition().y - textBounds.height - 10;

    m_hpText.setPosition(posX, posY);
}

void UI::setEnemyHPTextPosition(Enemy& enemy) {
    m_enemyHPText.setString("Enemy HP: " + std::to_string(enemy.getCurrentHP()) + "/" + std::to_string(enemy.getMaxHP()));
    sf::Vector2u textureSize = enemy.getSprite().getTexture()->getSize();
    float scaleFactor = enemy.getSprite().getScale().x;

    sf::FloatRect textBounds = m_enemyHPText.getLocalBounds();
    float posX = enemy.getSprite().getPosition().x + (textureSize.x * scaleFactor * 0.5f) - (textBounds.width * 0.5f);
    float posY = enemy.getSprite().getPosition().y - textBounds.height - 10;

    m_enemyHPText.setPosition(posX, posY);
}

void UI::drawHP(sf::RenderWindow& window, Player& player) {
    setHPTextPosition(player);
    window.draw(m_hpText);
}

void UI::drawEnemyHP(sf::RenderWindow& window, Enemy& enemy) {
    setEnemyHPTextPosition(enemy);
    window.draw(m_enemyHPText);
}

void UI::setGoldTextPosition(GameManager& gameManager, float windowWidth) {
    m_goldText.setPosition(10, 100); // Nouvelle position à gauche
    m_goldText.setString("Gold: " + std::to_string(gameManager.getGold()));
}

void UI::drawGold(sf::RenderWindow& window, GameManager& gameManager) {
    window.draw(m_goldText);
}

void UI::setHPButtonPosition(float windowWidth, float windowHeight) {
    float buttonX = 10.0f; // Position X fixe à gauche
    float buttonY = windowHeight - 200.0f; // Position Y en bas avec un décalage ajusté
    m_hpButton.setPosition(buttonX, buttonY);

    m_hpButtonText.setString("+ " + std::to_string(10) + " HP\nCost: " + std::to_string(50) + " golds"); // Mise à jour du texte du bouton HP
    sf::FloatRect textBounds = m_hpButtonText.getLocalBounds();
    m_hpButtonText.setPosition(buttonX + (m_hpButton.getSize().x / 2.0f) - (textBounds.width / 2.0f),
                               buttonY + (m_hpButton.getSize().y / 2.0f) - (textBounds.height / 2.0f));
}

void UI::setDMGButtonPosition(float windowWidth, float windowHeight) {
    float buttonX = 10.0f; // Position X fixe à gauche
    float buttonY = windowHeight - 300.0f; // Position Y en bas avec un décalage ajusté au-dessus du bouton HP
    m_dmgButton.setPosition(buttonX, buttonY);

    m_dmgButtonText.setString("+ " + std::to_string(5) + " DMG\nCost: " + std::to_string(50) + " golds"); // Mise à jour du texte du bouton DMG
    sf::FloatRect textBounds = m_dmgButtonText.getLocalBounds();
    m_dmgButtonText.setPosition(buttonX + (m_dmgButton.getSize().x / 2.0f) - (textBounds.width / 2.0f),
                                buttonY + (m_dmgButton.getSize().y / 2.0f) - (textBounds.height / 2.0f));
}

void UI::setDamageTextPosition(Player& player) {
    m_damageText.setString("Damage: " + std::to_string(player.getDamage())); // Afficher les dégâts du joueur
    sf::Vector2u textureSize = player.getSprite().getTexture()->getSize();
    float scaleFactor = player.getSprite().getScale().x;

    sf::FloatRect textBounds = m_damageText.getLocalBounds();
    float posX = player.getSprite().getPosition().x + (textureSize.x * scaleFactor * 0.5f) - (textBounds.width * 0.5f);
    float posY = player.getSprite().getPosition().y - textBounds.height - 40; // Position au-dessus des HP

    m_damageText.setPosition(posX, posY);
}

void UI::drawDamage(sf::RenderWindow& window, Player& player) {
    setDamageTextPosition(player);
    window.draw(m_damageText);
}

