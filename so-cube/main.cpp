#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

#define F(x) float(x)

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(2000, 1000), "hello");

float Ox = window.getSize().x % 2 == 0 ? float(window.getSize().x + 1) / 2 : float(window.getSize().x) / 2;
float Oy = window.getSize().y % 2 == 0 ? float(window.getSize().y + 1) / 2 : float(window.getSize().y) / 2;

class Polygon {
public:
    explicit Polygon(float d) : depth(d), displacement(0, 0, 0) {
        color = Color::Transparent;
    }

    void move(Vector3f v, float alpha, float beta, float gamma) {
        unprojection();
        for (auto &i: vec) {
            i -= displacement;

            i = {cos(beta) * cos(gamma) * i.x - sin(gamma) * cos(beta) * i.y + sin(beta) * i.z,
                       sin(alpha) * sin(beta) * cos(gamma) * i.x + sin(gamma) * cos(alpha) * i.x -
                       sin(alpha) * sin(beta) * sin(gamma) * i.y + cos(alpha) * cos(gamma) * i.y -
                       sin(alpha) * cos(beta) * i.z,
                       sin(alpha) * sin(gamma) * i.x - sin(beta) * cos(alpha) * cos(gamma) * i.x +
                       sin(alpha) * cos(gamma) * i.y + sin(beta) * sin(gamma) * cos(alpha) * i.y +
                       cos(alpha) * cos(beta) * i.z};

            i += (displacement + v);
        }
        displacement += v;
        projection();
    }

    void setUp(vector<Vector3f> v, Color c) {
        vec = std::move(v);
        color = c;
        projection();
    }

    int size() {
        return int(vec.size());
    }

    vector<Vertex> getVer() {
        vector<Vertex> v;
        for(auto & i : vec)
            v.emplace_back(Vector2f(tx(i.x), ty(i.y)), color);
        return v;
    }

    bool operator>=(const Polygon& other) const {
        return v_length(center(vec)) >= v_length(center(other.vec));
    }
    bool operator<=(const Polygon& other) const {
        return v_length(center(vec)) <= v_length(center(other.vec));
    }
    bool operator>(const Polygon& other) const {
        return v_length(center(vec)) > v_length(center(other.vec));
    }
    bool operator<(const Polygon& other) const {
        return v_length(center(vec)) < v_length(center(other.vec));
    }
    ~Polygon() = default;
private:
    vector<Vector3f> vec;
    Vector3f displacement;
    Color color;
    float depth;

    [[nodiscard]] Vector3f center(const vector<Vector3f>& v) const {
        float x(0), y(0), z(0);
        for(auto & i: v) {
            x += i.x;
            y += i.y;
            z += i.z;
        } return Vector3f(x, y, z) / float(vec.size());
    }

    static float v_length (Vector3f v) {
        return float(sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
    }

    static float tx(float x) {
        return Ox + x;
    }

    static float ty(float y) {
        return Oy - y;
    }

    void projection() {
        for(Vector3f & i : vec) {
            i.x *= depth / i.z;
            i.y *= depth / i.z;
        }
    }

    void unprojection() {
        for(Vector3f & i : vec) {
            i.x /= depth / i.z;
            i.y /= depth / i.z;
        }
    }
};

void FRot(vector<Polygon>& v);
void _FRot(vector<Polygon>& v);
void DRot(vector<Polygon>& v);
void _DRot(vector<Polygon>& v);
void URot(vector<Polygon>& v);
void _URot(vector<Polygon>& v);
void BRot(vector<Polygon>& v);
void _BRot(vector<Polygon>& v);
void RRot(vector<Polygon>& v);
void _RRot(vector<Polygon>& v);
void LRot(vector<Polygon>& v);
void _LRot(vector<Polygon>& v);

void rotate(vector<Polygon>& v);

bool compare(const Polygon& left,  const Polygon& right) {
    return left > right;
}

[[maybe_unused]] void rotate(vector<Polygon>& v, float delta);

int main() {
    //init
    float a = 130, b = 10;
    float x, y, z, alpha, beta, gamma;
    vector<vector<vector<Vector3f>>> v(6, vector<vector<Vector3f>>(9, vector<Vector3f>(4)));
    vector<Color> colors = {Color::White, Color::Yellow, Color::Blue,
                            Color::Green, Color(255, 165, 0, 255), Color::Red};
    vector<Polygon> sides;

    for (int i = 0; i < 9 * 6; i++)
        sides.emplace_back(600);

    for (int i = 0; i < 3; i++) {
        float c = (2 * a - 4 * b) / 3;
        for (int j = 0; j < 3; j++) {
            for (int k = 0, flag; k < 4; k++) {
                flag = k;
                v[0][i * 3 + j][k] = Vector3f((b * F(j + 1) + c * F(j) + c * F(flag % 2)) - a, 0, -a);
                flag /= 2;
                v[0][i * 3 + j][k] += Vector3f(0, (b * F(i + 1) + c * F(i) + c * F(flag % 2)) - a, 0);
                flag = k;
                v[1][i * 3 + j][k] = Vector3f(a - (b * F(j + 1) + c * F(j) + c * F(flag % 2)), 0, a);
                flag /= 2;
                v[1][i * 3 + j][k] += Vector3f(0, a - (b * F(i + 1) + c * F(i) + c * F(flag % 2)), 0);
                flag = k;
                v[2][i * 3 + j][k] = Vector3f(a, a - (b * F(j + 1) + c * F(j) + c * F(flag % 2)), 0);
                flag /= 2;
                v[2][i * 3 + j][k] += Vector3f(0, 0, a - (b * F(i + 1) + c * F(i) + c * F(flag % 2)));
                flag = k;
                v[3][i * 3 + j][k] = Vector3f(-a, (b * F(j + 1) + c * F(j) + c * F(flag % 2)) - a, 0);
                flag /= 2;
                v[3][i * 3 + j][k] += Vector3f(0, 0, (b * F(i + 1) + c * F(i) + c * F(flag % 2)) - a);
                flag = k;
                v[4][i * 3 + j][k] = Vector3f(a - (b * F(j + 1) + c * F(j) + c * F(flag % 2)), a, 0);
                flag /= 2;
                v[4][i * 3 + j][k] += Vector3f(0, 0, a - (b * F(i + 1) + c * F(i) + c * F(flag % 2)));
                flag = k;
                v[5][i * 3 + j][k] = Vector3f((b * F(j + 1) + c * F(j) + c * F(flag % 2)) - a, -a, 0);
                flag /= 2;
                v[5][i * 3 + j][k] += Vector3f(0, 0, (b * F(i + 1) + c * F(i) + c * F(flag % 2)) - a);
            }
        }
    } //create polygons

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 9; j++) {
            sides[i * 9 + j].setUp(v[i][j], colors[i]);
            sides[i * 9 + j].move({0, 0, 600}, 0, 0, 0);
            sides[i * 9 + j].move({0, 0, 0}, 0, 0, M_PI / 2);
            sides[i * 9 + j].move({0, 0, 0}, M_PI / 2, 0, 0);
        }
    } //setup/move

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
                if (event.key.code == sf::Keyboard::F) {
                    std::sort(begin(sides), end(sides), compare);

                    for (int frames = 0; frames < 1000; frames++) {
                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                if (event.key.code == sf::Keyboard::G) {
                    std::sort(begin(sides), end(sides), compare);

                    for (int frames = 0; frames < 1000; frames++) {
                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                if (event.key.code == sf::Keyboard::B) {
                    for (int frames = 0; frames < 1000; frames++) {

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, M_PI, 0);

                        std::sort(begin(sides), end(sides), compare);

                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, -M_PI, 0);

                        std::sort(begin(sides), end(sides), compare);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                if (event.key.code == sf::Keyboard::N) {
                    for (int frames = 0; frames < 1000; frames++) {

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, M_PI, 0);

                        std::sort(begin(sides), end(sides), compare);

                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, -M_PI, 0);

                        std::sort(begin(sides), end(sides), compare);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                if (event.key.code == sf::Keyboard::U) {
                    for (int frames = 0; frames < 1000; frames++) {

                        for (auto &i: sides)
                            i.move({0, 0, 0}, -M_PI / 2, 0, 0);

                        std::sort(begin(sides), end(sides), compare);

                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

                        for (auto &i: sides)
                            i.move({0, 0, 0}, M_PI / 2, 0, 0);

                        std::sort(begin(sides), end(sides), compare);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                if (event.key.code == sf::Keyboard::I) {
                    for (int frames = 0; frames < 1000; frames++) {

                        for (auto &i: sides)
                            i.move({0, 0, 0}, -M_PI / 2, 0, 0);

                        std::sort(begin(sides), end(sides), compare);

                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

                        for (auto &i: sides)
                            i.move({0, 0, 0}, M_PI / 2, 0, 0);

                        std::sort(begin(sides), end(sides), compare);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                if (event.key.code == sf::Keyboard::R) {
                    for (int frames = 0; frames < 1000; frames++) {

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, M_PI / 2, 0);

                        std::sort(begin(sides), end(sides), compare);

                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, -M_PI / 2, 0);

                        std::sort(begin(sides), end(sides), compare);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                if (event.key.code == sf::Keyboard::T) {
                    for (int frames = 0; frames < 1000; frames++) {

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, M_PI / 2, 0);

                        std::sort(begin(sides), end(sides), compare);

                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, -M_PI / 2, 0);

                        std::sort(begin(sides), end(sides), compare);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                if (event.key.code == sf::Keyboard::L) {
                    for (int frames = 0; frames < 1000; frames++) {

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, -M_PI / 2, 0);

                        std::sort(begin(sides), end(sides), compare);

                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, -M_PI / 2000);

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, M_PI / 2, 0);

                        std::sort(begin(sides), end(sides), compare);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                if (event.key.code == sf::Keyboard::K) {
                    for (int frames = 0; frames < 1000; frames++) {

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, -M_PI / 2, 0);

                        std::sort(begin(sides), end(sides), compare);

                        for (int i = 33; i < 54; i++)
                            sides[i].move({0, 0, 0}, 0, 0, M_PI / 2000);

                        for (auto &i: sides)
                            i.move({0, 0, 0}, 0, M_PI / 2, 0);

                        std::sort(begin(sides), end(sides), compare);

                        window.clear();
                        for (auto &i: sides)
                            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
                        window.display();
                    }
                }

                for (auto &i: sides)
                    i.move({x, y, z}, alpha, beta, gamma);
            } //press key check
        }
        std::sort(begin(sides), end(sides), compare);

        window.clear();
        for (auto &i: sides)
            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
        window.display();

    } //rendering
}

void rotate(vector<Polygon>& v) {
    FRot(v);
}

void FRot(vector<Polygon>& v) {
    for(int i = 33; i < 54; i++)
        v[i].move({0, 0, 0}, 0, 0, -M_PI / 2);
}

void _FRot(vector<Polygon>& v) {
    for(int i = 33; i < 54; i++)
        v[i].move({0, 0, 0}, 0, 0, M_PI / 2);
}

void BRot(vector<Polygon>& v) {
    for(auto &i: v)
        i.move({0, 0, 0}, 0, M_PI, 0);
    std::sort(begin(v), end(v), compare);
    FRot(v);
    for(auto &i: v)
        i.move({0, 0, 0}, 0, M_PI, 0);
}

void _BRot(vector<Polygon>& v) {
    for(auto &i: v)
        i.move({0, 0, 0}, 0, M_PI, 0);
    std::sort(begin(v), end(v), compare);
    _FRot(v);
    for(auto &i: v)
        i.move({0, 0, 0}, 0, M_PI, 0);
}
