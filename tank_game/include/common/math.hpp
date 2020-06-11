#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

float dot(const sf::Vector2f& a, const sf::Vector2f& b);

float snorm(const sf::Vector2f& a);

float norm(const sf::Vector2f& a);

float det(const sf::Vector2f& a, const sf::Vector2f& b);

/**
 * Rotates a vector from a given angle
 * \param angle the angle in degrees to consider
 **/
void rotate(sf::Vector2f& a, float angle);