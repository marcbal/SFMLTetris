#include "Collision.hpp"


bool pointInRect(AABB rect,sf::Vector2f point){
    return (point.x > rect.x
            && point.x < rect.x2
            && point.y > rect.y
            && point.y < rect.y2);
}

bool pointInRect(sf::Vector2f _pos,sf::Vector2f _size,sf::Vector2f point){
        AABB rect = {_pos.x,_pos.y,_pos.x+_size.x,_pos.y+_size.y};
        return pointInRect(rect,point);
}
