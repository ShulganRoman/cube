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
            sides[i * 9 + j].move({0, 0, 600}, M_PI / 2, 0, 0);
            sides[i * 9 + j].move({0, 0, 0}, 0, M_PI / 4, 0);
            sides[i * 9 + j].move({0, 0, 0}, -M_PI / 8, 0, 0);
        }
    } //setup/move

    while (window.isOpen()) {
        Event event{};

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                x = y = z = alpha = beta = gamma = 0;

                if (event.key.code == sf::Keyboard::S) y = -50;
                if (event.key.code == sf::Keyboard::W) y = 50;
                if (event.key.code == sf::Keyboard::A) x = -50;
                if (event.key.code == sf::Keyboard::D) x = 50;
                if (event.key.code == sf::Keyboard::Q) z = -50;
                if (event.key.code == sf::Keyboard::E) z = 50;
                if (event.key.code == sf::Keyboard::L) alpha = -M_PI / 60;
                if (event.key.code == sf::Keyboard::J) alpha = M_PI / 60;
                if (event.key.code == sf::Keyboard::O) beta = -M_PI / 60;
                if (event.key.code == sf::Keyboard::U) beta = M_PI / 60;
                if (event.key.code == sf::Keyboard::I) gamma = -M_PI / 60;
                if (event.key.code == sf::Keyboard::K) gamma = M_PI / 60;

                for (auto &i: sides)
                    i.move({x, y, z}, alpha, beta, gamma);
            } //press key check
        }

        window.clear();

        rotate(sides);
        std::sort(begin(sides), end(sides), compare);
        for (auto i: sides)
            window.draw(&i.getVer()[0], i.size(), TriangleStrip);
        window.display();
    }
}

void rotate(vector<Polygon>& v) {
    for (auto &i: v) {
        i.move({0, 0, 0}, M_PI / 8, 0, 0);
        i.move({0, 0, 0}, 0, -M_PI / 4, 0);

        i.move({0, 0, 0}, 0, -M_PI / (360 * 50), 0);

        i.move({0, 0, 0}, 0, M_PI / 4, 0);
        i.move({0, 0, 0}, -M_PI / 8, 0, 0);
    }
}