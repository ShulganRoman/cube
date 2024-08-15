#ifndef SO_CUBE_POLYGON_H
#define SO_CUBE_POLYGON_H
#include <SFML/Graphics.hpp>

class Polygon {
public:
    explicit Polygon(float d) : depth(d), displacement(0, 0, 0), rotation(0, 0, 0) {
        color = sf::Color::Transparent;
    }

    void move(sf::Vector3f v, float alpha, float beta, float gamma) {
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



    void setUp(std::vector<sf::Vector3f> v, sf::Color c) {
        vec = std::move(v);
        color = c;
        projection();
    }

    int size() {
        return int(vec.size());
    }

    std::vector<sf::Vertex> getVer(float Ox, float Oy) {
        std::vector<sf::Vertex> v;
        for(auto & i : vec)
            v.emplace_back(sf::Vector2f(tx(i.x, Ox), ty(i.y, Oy)), color);
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
    std::vector<sf::Vector3f> vec;
    sf::Vector3f displacement, rotation;
    sf::Color color;
    float depth;

    [[nodiscard]] sf::Vector3f center(const std::vector<sf::Vector3f>& v) const {
        float x(0), y(0), z(0);
        for(auto & i: v) {
            x += i.x;
            y += i.y;
            z += i.z;
        } return sf::Vector3f(x, y, z) / float(vec.size());
    }

    static float v_length (sf::Vector3f v) {
        return float(sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
    }

    static float tx(float x, float Ox) {
        return Ox + x;
    }

    static float ty(float y, float Oy) {
        return Oy - y;
    }

    void projection() {
        for(sf::Vector3f & i : vec) {
            i.x *= depth / i.z;
            i.y *= depth / i.z;
        }
    }

    void unprojection() {
        for(sf::Vector3f & i : vec) {
            i.x /= depth / i.z;
            i.y /= depth / i.z;
        }
    }
};

#endif //SO_CUBE_POLYGON_H
