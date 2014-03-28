#include "Background.hpp"

Background::Background(sf::Vector2i window_size, unsigned int nb_particules)
{
    _window_size = window_size;
    addParticule(nb_particules);
}

Background::~Background() {}



void Background::addParticule(unsigned int nb_new_particule)
{
    for (unsigned int i=0; i<nb_new_particule; i++)
        particules.push_back(*(new Particule(_window_size)));
}



void Background::update()
{
    for (unsigned int i=0; i<particules.size(); i++)
        particules[i].update();
}




void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i=0; i<particules.size(); i++)
        target.draw(particules[i], states);
}










Particule::Particule(sf::Vector2i window_size) :
    shape(rand_float(0.5, 3), rand_int(3, 5))
{
    _window_size = window_size;
    speed = sf::Vector2f(rand_float(-0.5, 0.5),rand_float(-0.5, 0.1));
    shape.setPosition(sf::Vector2f(rand_float(0.0f, (float) (window_size.x)),rand_float(0.0f, (float) (window_size.y))));
    //shape.setPosition(sf::Vector2f(10,100));
    shape.setFillColor(sf::Color(rand_int(0, 96), rand_int(0, 96), rand_int(0, 96)));
}



void Particule::update()
{
    sf::Vector2f pos = shape.getPosition();
    if (pos.x > _window_size.x) // sors de l'écran par la droite
        pos.x -= _window_size.x + shape.getRadius()*2;
    if (pos.y > _window_size.y) // sors de l'écran par le bas
        pos.y -= _window_size.y + shape.getRadius()*2;
    if (pos.x < -shape.getRadius()*2) // sors de l'écran par la gauche
        pos.x += _window_size.x + shape.getRadius()*2;
    if (pos.y < -shape.getRadius()*2) // sors de l'écran par le haut
        pos.y += _window_size.y + shape.getRadius()*2;

    shape.setPosition(sf::Vector2f(pos.x+speed.x, pos.y+speed.y));

}




void Particule::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(shape, states);
}
