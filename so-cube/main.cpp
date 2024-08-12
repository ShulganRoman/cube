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
    explicit Polygon(float d) : depth(d) {
        projection();
    }

    void update(vector<pair<Vector3f, Color>> v) {
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
};

float a = 130;

Vector3f vec_x = {a, 0, 0};
Vector3f vec_y = {0, a, 0};
Vector3f vec_z = {0, 0, a};

Vector3f v_xyz, v0, v1, v2, v3, v4, v5, v6, v7, v8;

vector<vector<pair<Vector3f, Color>>> v(6);
vector<Polygon> vp;

//vector<Polygon> white_side;
//vector<vector<pair<Vector3f, Color>>> ws(9);

void rot_space(Vector3f& vec, float alpha, float beta, float gamma) {
    vec = {cos(beta) * cos(gamma) * vec.x - sin(gamma) * cos(beta) * vec.y + sin(beta) * vec.z,
           sin(alpha) * sin(beta) * cos(gamma) * vec.x + sin(gamma) * cos(alpha) * vec.x -
           sin(alpha) * sin(beta) * sin(gamma) * vec.y + cos(alpha) * cos(gamma) * vec.y -
           sin(alpha) * cos(beta) * vec.z,
           sin(alpha) * sin(gamma) * vec.x - sin(beta) * cos(alpha) * cos(gamma) * vec.x +
           sin(alpha) * cos(gamma) * vec.y + sin(beta) * sin(gamma) * cos(alpha) * vec.y +
           cos(alpha) * cos(beta) * vec.z};
}



void update(float x = 0, float y = 0, float z = 0, float alpha = 0, float beta = 0, float gamma = 0) {
    v_xyz += {x, y, z};

    rot_space(vec_x, alpha, beta, gamma);
    rot_space(vec_y, alpha, beta, gamma);
    rot_space(vec_z, alpha, beta, gamma);

    v1 = vec_z + vec_y - vec_x + v_xyz,
    v2 = vec_z + vec_y + vec_x + v_xyz,
    v3 = vec_z - vec_y - vec_x + v_xyz,
    v4 = vec_z - vec_y + vec_x + v_xyz,
    v5 = vec_x - vec_y - vec_z + v_xyz,
    v6 = -vec_x - vec_y - vec_z + v_xyz,
    v7 = vec_x + vec_y - vec_z + v_xyz,
    v8 = -vec_x + vec_y - vec_z + v_xyz;

    v[0][0].first = v1;
    v[0][1].first = v2;
    v[0][2].first = v3;
    v[0][3].first = v4;

    v[1][0].first = v1;
    v[1][1].first = v3;
    v[1][2].first = v8;
    v[1][3].first = v6;

    v[2][0].first = v2;
    v[2][1].first = v4;
    v[2][2].first = v7;
    v[2][3].first = v5;

    v[3][0].first = v5;
    v[3][1].first = v6;
    v[3][2].first = v7;
    v[3][3].first = v8;

    v[4][0].first = v1;
    v[4][1].first = v2;
    v[4][2].first = v8;
    v[4][3].first = v7;

    v[5][0].first = v3;
    v[5][1].first = v4;
    v[5][2].first = v6;
    v[5][3].first = v5;

    for(int i = 0; i < v.size(); i++)
        vp[i].update(v[i]);
}

bool compare(const Polygon& left,  const Polygon& right) {
    return left > right;
}

int main() {
    float x, y, z, alpha, beta, gamma;

    for (int i = 0; i < v.size(); i++)
        vp.emplace_back(600);

    vector<Color> colors = {Color(255, 165, 0, 255), Color::Blue, Color::Green, Color::Red, Color::Yellow,
                            Color::White};

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 4; j++)
            v[i].emplace_back(Vector3f(), colors[i]);

    update(0, 0, 600, -M_PI / 10, M_PI / 4, M_PI);

    for (int i = 0; i < v.size(); i++)
        vp[i].update(v[i]);

    while (window.isOpen()) {
        Event event{};

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                x = y = z = alpha = beta = gamma = 0;

                if (event.key.code == sf::Keyboard::S) y += -50;
                if (event.key.code == sf::Keyboard::W) y += 50;
                if (event.key.code == sf::Keyboard::A) x += -50;
                if (event.key.code == sf::Keyboard::D) x += 50;
                if (event.key.code == sf::Keyboard::L) alpha = -M_PI / 60;
                if (event.key.code == sf::Keyboard::J) alpha = M_PI / 60;
                if (event.key.code == sf::Keyboard::O) beta = -M_PI / 60;
                if (event.key.code == sf::Keyboard::U) beta = M_PI / 60;
                if (event.key.code == sf::Keyboard::I) gamma = -M_PI / 60;
                if (event.key.code == sf::Keyboard::K) gamma = M_PI / 60;

                update(x, y, z, alpha, beta, gamma);
            }
        }

        window.clear();

        std::sort(begin(vp), end(vp), compare);
        for (auto i: vp)
            window.draw(&i.getVer()[0], i.size(), TriangleStrip);

//        for (auto i : white_side)
//            window.draw(&i.getVer()[0], i.size(), TriangleStrip);

        window.display();
    }
}