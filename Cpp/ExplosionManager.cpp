#include "ExplosionManager.hpp"



int ExplosionManager::_nbParticules = 0;

ExplosionManager::ExplosionManager(sf::Vector2i * window_size) :
    _window_size(window_size),
    explosions()
{

}

ExplosionManager::~ExplosionManager()
{

}



void ExplosionManager::update()
{
    unsigned int i=0;
    _nbParticules = 0;
    while (i<explosions.size())
    {
        if (!explosions[i].update())
            deleteExplosion(i);
        else
            i++;
    }
}



void ExplosionManager::deleteExplosion(unsigned int i)
{
    if (i >= explosions.size())
        return;

    swap(explosions[i], explosions[explosions.size()-1]);
    explosions.pop_back();
}







void ExplosionManager::addExplosion(RectangleExplosion explosion)
{
    explosions.push_back(explosion);
}


void ExplosionManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (unsigned int i=0; i<explosions.size(); i++)
        target.draw(explosions[i], states);
}








RectangleExplosion::RectangleExplosion(sf::Vector2i * window_size,
                           sf::FloatRect init_surface,
                           unsigned int nb_particules,
                           float max_size_particules,
                           sf::Color couleur) :
    _window_size(window_size),
    particules()
{

    for (unsigned int i=0; i<nb_particules; i++)
    {
        couleur *= sf::Color(255, 230, 230);
        ExplosionParticle p(window_size,
                            sf::Vector2f(rand_float(init_surface.left, init_surface.left + init_surface.width),
                                         rand_float(init_surface.top, init_surface.top + init_surface.height)),
                            sf::Vector2f(rand_float(-200, 200),
                                         rand_float(-200, 50)),
                            sf::Vector2f(0,200),
                            rand_float(1, max_size_particules),
                            couleur);
        particules.push_back(p);
    }


}


RectangleExplosion::~RectangleExplosion() {}


bool RectangleExplosion::update()
{
    unsigned int i=0;
    while (i<particules.size())
    {
        if (!particules[i].update())
            deleteParticle(i);
        else
            i++;
    }
    return (particules.size() > 0);
}


void RectangleExplosion::deleteParticle(unsigned int i)
{

    if (i >= particules.size())
        return;

    swap(particules[i], particules[particules.size()-1]);
    particules.pop_back();
}




void RectangleExplosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    for (unsigned int i=0; i<particules.size(); i++)
        target.draw(particules[i], states);
}






ExplosionParticle::ExplosionParticle(sf::Vector2i * window_size,
                          sf::Vector2f init_pos,
                          sf::Vector2f init_speed,
                          sf::Vector2f gravity,
                          float init_size,
                          sf::Color couleur) :
    _speed(init_speed),
    _gravity(gravity),
    _window_size(window_size),
    _shape(init_size)
{
    _shape.setPointCount(rand_int(3, 6));
    _shape.setFillColor(couleur);
    _shape.setPosition(init_pos);

}


ExplosionParticle::~ExplosionParticle() {}


bool ExplosionParticle::update()
{
    sf::FloatRect win_rect(sf::Vector2f(0, 0), sf::Vector2f(*_window_size));
    sf::Time elapsed = _cl.restart();
    _speed.x += _gravity.x * (1.0/FPS_MAX);
    _speed.y += _gravity.y * (1.0/FPS_MAX); // je sais que les opérateurs * et += sont surchargés pour les Vector2f, mais ça marche pas ici
    _shape.setPosition(_shape.getPosition() + sf::Vector2f(_speed.x*(1.0/FPS_MAX), _speed.y*(1.0/FPS_MAX)));
    _shape.setRadius(_shape.getRadius() - elapsed.asSeconds());
    if (_shape.getRadius() <= 0 ||
        !win_rect.contains(_shape.getPosition()))
        return false;

    ExplosionManager::_nbParticules++;
    return true;
}





void ExplosionParticle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_shape, states);
}




