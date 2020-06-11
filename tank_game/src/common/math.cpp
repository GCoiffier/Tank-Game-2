#include "common/math.hpp"

float dot(const sf::Vector2f& a, const sf::Vector2f& b){
    return a.x*b.x + a.y*b.y;
}

float snorm(const sf::Vector2f& a){
    return dot(a,a);
}

float norm(const sf::Vector2f& a) {
    return sqrt(snorm(a));
}

float det(const sf::Vector2f& a, const sf::Vector2f& b){
    return a.x * b.y - a.y * b.x;
}

/**
 * Rotates a vector from a given angle
 * \param angle the angle in degrees to consider
 **/
void rotate(sf::Vector2f& a, float angle){
    float ca = cosf(M_PI * angle / 180.f);
    float sa = sinf(M_PI * angle / 180.f);
    float rx = ca * a.x + sa * a.y;
    float ry = ca * a.y - sa * a.x;
    a.x = float(rx);
    a.y = float(ry);
}