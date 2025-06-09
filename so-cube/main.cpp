#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <functional>
#include "Polygon.h"

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(), "hello", Style::Fullscreen);

float Ox = window.getSize().x % 2 == 0 ? float(window.getSize().x + 1) / 2 : float(window.getSize().x) / 2;
float Oy = window.getSize().y % 2 == 0 ? float(window.getSize().y + 1) / 2 : float(window.getSize().y) / 2;

bool compare(const Polygon &left, const Polygon &right) {
    return left > right;
}

[[maybe_unused]] void rotate(vector<Polygon>& v, float delta);

int main() {
    vector<Color> colors = {Color::White, Color::Red, Color::Yellow, Color(255, 165, 0, 255), Color::Green, Color::Blue};
    vector<vector<Vector3f>> vv(9, vector<Vector3f>(4));
    vector<Polygon> temp(9, Polygon(600));
    vector<Vector3f> vvv(4);
    vector<Polygon> sides;

    float x, y, z, alpha, beta, gamma;
    float a = 120, b = 0, c = (a * 2 - b * 4) / 3; //init

    vvv[0] = {b - a, b - a, -a};
    vvv[1] = {b + c - a, b - a, -a};
    vvv[2] = {b - a, b + c - a, -a};
    vvv[3] = {b + c - a, b + c - a, -a};

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 4; k++)
                vv[i * 3 + j][k] = vvv[k] + Vector3f(float(i) * (c + b), float(j) * (c + b), 0);

    for(int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            temp[j].setUp(vv[j], colors[i]);
            temp[j].move({0, 0, 0}, -float(i * M_PI / 2), 0, 0);
        }
        sides.insert(sides.end(), temp.begin(), temp.end());
    }

    for(int i = 4; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            temp[j].setUp(vv[j], colors[i]);
            temp[j].move({0, 0, 0}, 0, float((1 + i * 2) * M_PI / 2), 0);
        }
            sides.insert(sides.end(), temp.begin(), temp.end());
    }

    for(auto &i: sides)
        i.move({0, 0, 600}, 2 * M_PI / 5, 0, -M_PI / 4); //create polygons

    std::unordered_map<sf::Keyboard::Key, std::function<void(std::vector<Polygon>&)>> commands;

    commands[sf::Keyboard::F] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }
            std::sort(begin(sides), end(sides), compare);

            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::G] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::B] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, M_PI, 0);

            std::sort(begin(sides), end(sides), compare);

            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, -M_PI, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::N] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, M_PI, 0);

            std::sort(begin(sides), end(sides), compare);

            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, -M_PI, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::U] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, -M_PI / 2, 0, 0);

            std::sort(begin(sides), end(sides), compare);

            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, M_PI / 2, 0, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::I] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, -M_PI / 2, 0, 0);

            std::sort(begin(sides), end(sides), compare);

            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, M_PI / 2, 0, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::D] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, M_PI / 2, 0, 0);

            std::sort(begin(sides), end(sides), compare);
            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, -M_PI / 2, 0, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::S] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, M_PI / 2, 0, 0);

            std::sort(begin(sides), end(sides), compare);

            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, -M_PI / 2, 0, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::R] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, M_PI / 2, 0);

            std::sort(begin(sides), end(sides), compare);

            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, -M_PI / 2, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::T] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, M_PI / 2, 0);

            std::sort(begin(sides), end(sides), compare);

            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, -M_PI / 2, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::L] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, -M_PI / 2, 0);

            std::sort(begin(sides), end(sides), compare);

            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, M_PI / 2, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    commands[sf::Keyboard::K] = [&](std::vector<Polygon>& sides) {
        for (int frames = 0; frames < 1000; frames++) {
            for(auto &i: sides) {
                i.move({0, 0, 0}, M_PI / 8, 0, 0);
                i.move({0, 0, 0}, 0, -3 * M_PI / 4, 0);
            }

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, -M_PI / 2, 0);

            std::sort(begin(sides), end(sides), compare);

            for (int i = 33; i < 54; i++)
                sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

            for (auto &i: sides)
                i.move({0, 0, 0}, 0, M_PI / 2, 0);

            for(auto &i: sides) {
                i.move({0, 0, 0}, 0, 3 * M_PI / 4, 0);
                i.move({0, 0, 0}, -M_PI / 8, 0, 0);
            }

            std::sort(begin(sides), end(sides), compare);
            window.clear();
            for (auto &i: sides)
                window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
            window.display();
        }
    };

    while (window.isOpen()) {
        Event event{};

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();

            window.clear();
            if (event.type == sf::Event::KeyPressed) {
                x = y = z = alpha = beta = gamma = 0;

                if (event.key.code == sf::Keyboard::Down) y = -50;
                if (event.key.code == sf::Keyboard::Up) y = 50;
                if (event.key.code == sf::Keyboard::Left) x = -50;
                if (event.key.code == sf::Keyboard::Right) x = 50;
                if (event.key.code == sf::Keyboard::Equal) z = -50;
                if (event.key.code == sf::Keyboard::Hyphen) z = 50;
                if (event.key.code == sf::Keyboard::Num1) alpha = -M_PI / 60;
                if (event.key.code == sf::Keyboard::Num2) alpha = M_PI / 60;
                if (event.key.code == sf::Keyboard::Num3) beta = -M_PI / 60;
                if (event.key.code == sf::Keyboard::Num4) beta = M_PI / 60;
                if (event.key.code == sf::Keyboard::Num5) gamma = -M_PI / 60;
                if (event.key.code == sf::Keyboard::Num6) gamma = M_PI / 60;
                for (auto &i: sides)
                    i.move({x, y, z}, alpha, beta, gamma); //cube move

                auto it = commands.find(event.key.code);
                if (it != commands.end())
                    it->second(sides);

            } //press key check
        }
        std::sort(begin(sides), end(sides), compare);

        window.clear();
        for (auto &i: sides)
            window.draw(&i.getVer(Ox, Oy)[0], i.size(), TriangleStrip);
        window.display();

    } //rendering
}