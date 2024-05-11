#include "ui.h"

UI::UI() {
    if (!m_font.loadFromFile("D:/Documents/GitHub/ConsoleApplication1/Source/Exo-Regular.ttf")) {
        std::cout << "Failed to load font" << std::endl;
    }
    m_levelText.setFont(m_font);
    m_levelText.setCharacterSize(20);
    m_levelText.setFillColor(sf::Color::White);
    m_levelText.setStyle(sf::Text::Bold);

    m_hpButton.setSize(sf::Vector2f(100, 50));
    m_hpButton.setFillColor(sf::Color::Yellow);

    m_hpText.setFont(m_font);
    m_hpText.setCharacterSize(16);
    m_hpText.setFillColor(sf::Color::White);
    m_hpText.setStyle(sf::Text::Bold);

    m_enemyHPText.setFont(m_font); // Initialisation du texte des points de vie de l'ennemi
    m_enemyHPText.setCharacterSize(16);
    m_enemyHPText.setFillColor(sf::Color::Red); // Couleur rouge pour les points de vie de l'ennemi
    m_enemyHPText.setStyle(sf::Text::Bold);
}

void UI::setLevelTextPosition(Player& player, float windowWidth, float windowHeight) {
    // Positionner le texte du niveau au milieu de l'écran
    m_levelText.setString("Level " + std::to_string(player.getLevel()));
    sf::Vector2u textureSize = player.getSprite().getTexture()->getSize();
    float scaleFactor = player.getSprite().getScale().x;

    float posX = (0.35f * windowWidth) - (textureSize.x * scaleFactor * 0.5f);
    float posY = 0.5f * windowHeight - (textureSize.y * scaleFactor * 0.5f);

    sf::FloatRect textBounds = m_levelText.getLocalBounds();
    m_levelText.setPosition(posX + (textureSize.x * scaleFactor * 0.5f) - (textBounds.width * 0.5f),
                          posY + (textureSize.y * scaleFactor) + 10);

    // Positionner le bouton d'augmentation des points de vie
    m_hpButton.setPosition(windowWidth - 150, 20); // Positionner à droite en haut
}

void UI::drawLevelText(sf::RenderWindow& window) {
    window.draw(m_levelText);
}

void UI::drawHPButton(sf::RenderWindow& window) {
    window.draw(m_hpButton);
}

bool UI::isHPButtonClicked(sf::RenderWindow& window, Player& player) {
    // Vérifier si le bouton est cliqué
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f buttonPosition = m_hpButton.getPosition();
    sf::Vector2f buttonSize = m_hpButton.getSize();

    if (mousePosition.x >= buttonPosition.x && mousePosition.x <= buttonPosition.x + buttonSize.x &&
        mousePosition.y >= buttonPosition.y && mousePosition.y <= buttonPosition.y + buttonSize.y) {
        // Si le clic se trouve à l'intérieur des limites du bouton
        // Augmenter les points de vie maximum du joueur
        return true;
    }

    return false;
}

void UI::setHPTextPosition(Player& player, float windowWidth, float windowHeight) {
    // Positionner le texte des points de vie du joueur au-dessus du joueur
    m_hpText.setString("HP: " + std::to_string(player.getCurrentHP()) + "/" + std::to_string(player.getMaxHP()));
    sf::Vector2u textureSize = player.getSprite().getTexture()->getSize();
    float scaleFactor = player.getSprite().getScale().x;

    // Calculer la position pour placer le texte au-dessus du joueur
    sf::FloatRect textBounds = m_hpText.getLocalBounds();
    float posX = player.getSprite().getPosition().x + (textureSize.x * scaleFactor * 0.5f) - (textBounds.width * 0.5f);
    float posY = player.getSprite().getPosition().y - textBounds.height - 10; // Décalage vers le haut

    m_hpText.setPosition(posX, posY);
}

void UI::setEnemyHPTextPosition(Enemy& enemy) {
    // Positionner le texte des points de vie de l'ennemi au-dessus de l'ennemi
    m_enemyHPText.setString("Enemy HP: " + std::to_string(enemy.getCurrentHP()) + "/" + std::to_string(enemy.getMaxHP()));
    sf::Vector2u textureSize = enemy.getSprite().getTexture()->getSize();
    float scaleFactor = enemy.getSprite().getScale().x;

    // Calculer la position pour placer le texte au-dessus de l'ennemi
    sf::FloatRect textBounds = m_enemyHPText.getLocalBounds();
    float posX = enemy.getSprite().getPosition().x + (textureSize.x * scaleFactor * 0.5f) - (textBounds.width * 0.5f);
    float posY = enemy.getSprite().getPosition().y - textBounds.height - 10; // Décalage vers le haut

    m_enemyHPText.setPosition(posX, posY);
}

void UI::drawHP(sf::RenderWindow& window) {
    window.draw(m_hpText);
}

void UI::drawEnemyHP(sf::RenderWindow& window, Enemy& enemy) {
    // Dessiner le texte des points de vie de l'ennemi
    setEnemyHPTextPosition(enemy);
    window.draw(m_enemyHPText);
}

