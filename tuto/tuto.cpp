//
// Created by edo on 20/12/23.
//

//
// Created by edo on 20/12/23.
//

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <random>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Effect with SFML Shaders");

    sf::RectangleShape rectangle(sf::Vector2f(WIDTH, HEIGHT));

    sf::Shader shader;
    if (!shader.loadFromFile("tuto.frag", sf::Shader::Fragment)) {
        return -1; // Erreur lors du chargement du shader
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        mousePos.y = HEIGHT - mousePos.y;
        shader.setUniform("pos", sf::Vector2f(mousePos.x, mousePos.y));
        window.draw(rectangle, &shader);

        window.display();
    }

    return 0;
}
