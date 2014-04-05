#ifndef _COLLISION_HPP_
#define _COLLISION_HPP_
#include <SFML/Graphics.hpp>
struct AABB{
    float x;
    float y;
    float x2;
    float y2;
};

bool pointInRect(AABB rect,sf::Vector2f point);
bool pointInRect(sf::Vector2f _pos,sf::Vector2f _size,sf::Vector2f point);

#endif // _COLLISION_HPP_
