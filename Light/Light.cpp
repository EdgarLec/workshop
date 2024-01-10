//
// Created by edo on 20/12/23.
//

//
// Created by edo on 20/12/23.
//

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

const int WIDTH = 1024;
const int HEIGHT = 1024;

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Light Effect with SFML Shaders");

    // Créer un rectangle qui couvre toute la fenêtre
    sf::RectangleShape rectangle(sf::Vector2f(WIDTH, HEIGHT));

    // Charger le shader d'eau depuis un fichier
    sf::Shader lightShader;
    if (!lightShader.loadFromFile("light.frag", sf::Shader::Fragment)) {
        return -1; // Erreur lors du chargement du shader
    }
    sf::Texture texture;
    texture.loadFromFile("diffuse.png");
    sf::Sprite sprite(texture);

    sf::Texture normalMap;
    normalMap.loadFromFile("normal.png");
    lightShader.setUniform("normalMap", normalMap);
    

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }



        // Effacer l'écran
        window.clear();

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        mousePos.y = HEIGHT - mousePos.y;
        lightShader.setUniform("lightPos", sf::Vector2f(mousePos.x, mousePos.y));
        window.draw(sprite, &lightShader);
        window.display();
    }

    return 0;
}
