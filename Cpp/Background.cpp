#include "Background.hpp"

Background::Background(sf::Vector2i window_size, GameConfiguration * gameConfig, AudioConfiguration * audio):
    bordure(sf::Vector2f(window_size))
{
    _window_size = window_size;
    _gameConfig = gameConfig;
    _audio = audio;
    bordure.setPosition(0, 0);
    bordure.setFillColor(sf::Color::Transparent);
    bordure.setOutlineColor(sf::Color::Black);
    bordure.setOutlineThickness(50);
}

Background::~Background() {}


/*
void Background::addParticule(unsigned int nb_new_particule)
{
    for (unsigned int i=0; i<nb_new_particule; i++)
        particules.push_back(*(new Particule(_window_size)));
}*/



void Background::update()
{
    // ajout/suppression des particules
    while (_gameConfig->getBGParticules() > particules.size())
        particules.push_back(Particule(_window_size, _gameConfig, _audio));

    while (_gameConfig->getBGParticules() < particules.size())
        particules.pop_back();


    float speed_coeff = _audio->getAudioLevel();

    for (unsigned int i=0; i<particules.size(); i++)
        particules[i].update(speed_coeff);
}




void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i=0; i<particules.size(); i++)
        target.draw(particules[i], states);
    target.draw(bordure, states);
}










Particule::Particule(sf::Vector2i window_size, GameConfiguration * gameConfig, AudioConfiguration * audio) :
    shape(1, rand_int(3, 5))
{
    _radius_base = rand_float(0.05, 0.3);
    _window_size = window_size;
    _gameConfig = gameConfig;
    _audio = audio;
    speed = sf::Vector2f(rand_float(-0.5, 0.5),rand_float(-0.5, 0.1));
    shape.setPosition(sf::Vector2f(rand_float(0.0f, (float) (window_size.x)),rand_float(0.0f, (float) (window_size.y))));
    //shape.setPosition(sf::Vector2f(10,100));
    shape.setFillColor(sf::Color(rand_int(0, 96), rand_int(0, 96), rand_int(0, 96)));
}



void Particule::update(float speed_coeff)
{
    float elapsed = _cl.restart().asSeconds();
    shape.setRadius(_radius_base * _gameConfig->getBGPartSize() * (speed_coeff));
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    sf::Vector2f pos = shape.getPosition() + speed * (elapsed * _gameConfig->getBGSpeed());

    if (pos.x > _window_size.x) // sors de l'écran par la droite
        pos.x -= _window_size.x + shape.getRadius()*2;
    if (pos.y > _window_size.y) // sors de l'écran par le bas
        pos.y -= _window_size.y + shape.getRadius()*2;
    if (pos.x < -shape.getRadius()*2) // sors de l'écran par la gauche
        pos.x += _window_size.x + shape.getRadius()*2;
    if (pos.y < -shape.getRadius()*2) // sors de l'écran par le haut
        pos.y += _window_size.y + shape.getRadius()*2;

    shape.setPosition(pos);

}




void Particule::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(shape, states);
}
