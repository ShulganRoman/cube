//
// Created by Роман Шульган on 21.07.2024.
//

#ifndef SO_CUBE_CAMSTREAM_H
#define SO_CUBE_CAMSTREAM_H

#include <SFML/Graphics.hpp>

namespace cam
{
    class Camera {
    private:
        float distance, alpha, beta;
    public:
        Camera(float alpha, float beta, float distance) {
            this->distance = distance;
            this->alpha = alpha;
            this->beta = beta;
        }

        void setObj(sf::RectangleShape &shape) {

        }
    };
}

#endif //SO_CUBE_CAMSTREAM_H