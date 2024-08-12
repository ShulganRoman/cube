#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

using namespace std;
using namespace sf;

RenderWindow window(VideoMode(2000, 600), "hello");

float Ox = window.getSize().x % 2 == 0 ? float(window.getSize().x + 1) / 2 : float(window.getSize().x) / 2;
float Oy = window.getSize().y % 2 == 0 ? float(window.getSize().y + 1) / 2 : float(window.getSize().y) / 2;

class Polygon {
public:
    explicit Polygon(float d) : depth(d), displacement(0, 0, 0) {
        for(auto i: vec) {
            i.first = {0, 0, 0};
            i.second = Color::Transparent;
        }
    }

    void move(Vector3f v, float alpha, float beta, float gamma) {
        unprojection();
        for (auto &i: vec) {
            i.first -= displacement;

            i.first = {cos(beta) * cos(gamma) * i.first.x - sin(gamma) * cos(beta) * i.first.y + sin(beta) * i.first.z,
                       sin(alpha) * sin(beta) * cos(gamma) * i.first.x + sin(gamma) * cos(alpha) * i.first.x -
                       sin(alpha) * sin(beta) * sin(gamma) * i.first.y + cos(alpha) * cos(gamma) * i.first.y -
                       sin(alpha) * cos(beta) * i.first.z,
                       sin(alpha) * sin(gamma) * i.first.x - sin(beta) * cos(alpha) * cos(gamma) * i.first.x +
                       sin(alpha) * cos(gamma) * i.first.y + sin(beta) * sin(gamma) * cos(alpha) * i.first.y +
                       cos(alpha) * cos(beta) * i.first.z};

            i.first += (displacement + v);
        }
        displacement += v;
        projection();
    }

    void setUp(vector<pair<Vector3f, Color>> v) {
        this->vec = std::move(v);
        projection();
    }

    int size() {
        return int(vec.size());
    }

    vector<Vertex> getVer() {
        vector<Vertex> v;
        for(auto & i : vec)
            v.emplace_back(Vector2f(tx(i.first.x), ty(i.first.y)), i.second);
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
private:
    vector<pair<sf::Vector3f, Color>> vec;
    Vector3f displacement;
    float depth;

    [[nodiscard]] Vector3f center(const vector<pair<Vector3f, Color>>& v) const {
        float x(0), y(0), z(0);
        for(auto & i : v) {
            x += i.first.x;
            y += i.first.y;
            z += i.first.z;
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
        for(pair<Vector3f, Color> & i : vec) {
            i.first.x *= depth / i.first.z;
            i.first.y *= depth / i.first.z;
        }
    }

    void unprojection() {
        for(pair<Vector3f, Color> & i : vec) {
            i.first.x /= depth / i.first.z;
            i.first.y /= depth / i.first.z;
        }
    }
};

float a = 130;
Vector3f v0(a, a, a);
Vector3f v1(-a, a, a);
Vector3f v2(a, -a, a);
Vector3f v3(-a, -a, a);
Vector3f v4(a, a, -a);
Vector3f v5(-a, a, -a);
Vector3f v6(a, -a, -a);
Vector3f v7(-a, -a, -a);

//vector<Polygon> white_side;
//vector<vector<pair<Vector3f, Color>>> ws(9);

bool compare(const Polygon& left,  const Polygon& right) {
    return left > right;
}

void rotate(vector<Polygon>& v, float delta);

int main() {
    vector<vector<pair<Vector3f, Color>>> v(6);
    vector<Polygon> vp;
    float x, y, z, alpha, beta, gamma;

    for (int i = 0; i < v.size(); i++)
        vp.emplace_back(600);

    vector<Color> colors = {Color::Yellow, Color::White, Color::Blue, Color::Green, Color(255, 165, 0, 255),
                            Color::Red};

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; j++)
            v[i].emplace_back(Vector3f(), colors[i]);

    v[0][0].first = v0;
    v[0][1].first = v1;
    v[0][2].first = v2;
    v[0][3].first = v3;

    v[1][0].first = v4;
    v[1][1].first = v5;
    v[1][2].first = v6;
    v[1][3].first = v7;

    v[2][0].first = v0;
    v[2][1].first = v2;
    v[2][2].first = v4;
    v[2][3].first = v6;

    v[3][0].first = v1;
    v[3][1].first = v3;
    v[3][2].first = v5;
    v[3][3].first = v7;

    v[4][0].first = v0;
    v[4][1].first = v1;
    v[4][2].first = v4;
    v[4][3].first = v5;

    v[5][0].first = v2;
    v[5][1].first = v3;
    v[5][2].first = v6;
    v[5][3].first = v7;

    for (int i = 0; i < v.size(); i++) {
        vp[i].setUp(v[i]);
        vp[i].move({0, 0, 600}, M_PI / 2, 0, 0);
        vp[i].move({0, 0, 0}, 0, M_PI / 4, 0);
        vp[i].move({0, 0, 0}, -M_PI / 8, 0, 0);
    }


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

                for(auto &i: vp)
                    i.move({x, y, z}, alpha, beta, gamma);
            }
        }

        window.clear();

        for(auto& i: vp) {
            i.move({0, 0, 0}, M_PI / 8, 0, 0);
            i.move({0, 0, 0}, 0, -M_PI / 4, 0);

            i.move({0, 0, 0}, 0, -M_PI / (360 * 50), 0);

            i.move({0, 0, 0}, 0, M_PI / 4, 0);
            i.move({0, 0, 0}, -M_PI / 8, 0, 0);
        }

        std::sort(begin(vp), end(vp), compare);

        for (auto i: vp)
            window.draw(&i.getVer()[0], i.size(), TriangleStrip);

//        for (auto i : white_side)
//            window.draw(&i.getVer()[0], i.size(), TriangleStrip);

        window.display();
    }
}