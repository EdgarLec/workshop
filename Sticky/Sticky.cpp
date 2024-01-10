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

void update(std::vector<sf::Vector2f> &points, std::vector<sf::Vector2f> &dir) {
    static sf::Clock clock;
    float dt = clock.restart().asSeconds() * 100.f;
    for (ulong i = 0; i < points.size(); i++) {
        points[i] += dir[i] * dt;
        if (points[i].x < 0) {
            points[i].x = 0;
            dir[i].x *= -1;
        }
        if (points[i].x > WIDTH) {
            points[i].x = WIDTH;
            dir[i].x *= -1;
        }
        if (points[i].y < 0) {
            points[i].y = 0;
            dir[i].y *= -1;
        }
        if (points[i].y > HEIGHT) {
            points[i].y = HEIGHT;
            dir[i].y *= -1;
        }
        dir[i] += sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50) / 5000.f;
        dir[i] /= sqrtf(dir[i].x * dir[i].x + dir[i].y * dir[i].y);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Effect with SFML Shaders");

    sf::RectangleShape rectangle(sf::Vector2f(WIDTH, HEIGHT));

    sf::Shader waterShader;
    if (!waterShader.loadFromFile("sticky.frag", sf::Shader::Fragment)) {
        return -1; // Erreur lors du chargement du shader
    }
    std::vector<sf::Vector2f> pointsGlsl;
    for (int i = 0; i < 100; i++) {
        pointsGlsl.push_back(sf::Vector2f(rand() % WIDTH, rand() % HEIGHT));
    }
    std::vector<sf::Vector2f> dir;
    for (int i = 0; i < 100; i++) {
        sf::Vector2f v(rand() % 100, rand() % 100);
        dir.push_back(v / sqrtf(v.x * v.x + v.y * v.y));
    }
    waterShader.setUniformArray("points", pointsGlsl.data(), pointsGlsl.size());


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        update(pointsGlsl, dir);
        waterShader.setUniformArray("points", pointsGlsl.data(), pointsGlsl.size());
        window.draw(rectangle, &waterShader);

        window.display();
    }

    return 0;
}
