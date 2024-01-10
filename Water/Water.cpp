//
// Created by edo on 20/12/23.
//

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

const int WIDTH = 512;
const int HEIGHT = 512;

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Water Effect with SFML Shaders");

    // Créer un rectangle qui couvre toute la fenêtre
    sf::RectangleShape rectangle(sf::Vector2f(WIDTH, HEIGHT));

    // Charger le shader d'eau depuis un fichier
    sf::Shader waterShader;
    if (!waterShader.loadFromFile("water_shader.frag", sf::Shader::Fragment)) {
        return -1; // Erreur lors du chargement du shader
    }
    sf::Texture texture;
    texture.loadFromFile("stone.jpg");
    texture.setRepeated(true);
    sf::Sprite sprite(texture, sf::IntRect(0, 0, WIDTH / 4, HEIGHT / 4));
    sprite.setScale(4, 4);

    sf::Texture noise;
    noise.setRepeated(true);
    noise.loadFromFile("noise.png");
    waterShader.setUniform("noise", noise);
    sf::Texture noise2;
    noise2.setRepeated(true);
    noise2.loadFromFile("noise2.png");
    waterShader.setUniform("noise2", noise2);

    // Définir la position du rectangle au centre de la fenêtre
    sf::Clock clock;
    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Mettre à jour le temps du shader pour l'effet de mouvement


        // Effacer l'écran
        window.clear();

        waterShader.setUniform("time", clock.getElapsedTime().asSeconds());
        window.draw(sprite, &waterShader);
        // Appliquer le shader sur le rectangle

        // Afficher le résultat à l'écran
        window.display();
    }

    return 0;
}
