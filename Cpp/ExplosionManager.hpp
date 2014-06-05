#ifndef EXPLOSIONMANAGER_H
#define EXPLOSIONMANAGER_H


#include "headers.hpp"

#include "fn_random.hpp"


using namespace std;
using namespace sf;

class RectangleExplosion;

class ExplosionManager : public sf::Drawable
{
    private:

        sf::Vector2i * _window_size;



        vector<RectangleExplosion> explosions;


        void deleteExplosion(unsigned int i);

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        ExplosionManager(sf::Vector2i * window_size);
        virtual ~ExplosionManager();

        void update();


        void addExplosion(RectangleExplosion explosion);


        static int _nbParticules;
};


class ExplosionParticle;

class RectangleExplosion : public sf::Drawable
{

    private:
        sf::Vector2i * _window_size;
        vector<ExplosionParticle> particules;


        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    public:
        RectangleExplosion(sf::Vector2i * window_size,
                           sf::FloatRect init_surface,
                           unsigned int nb_particules,
                           float max_size_particules,
                           sf::Color couleur);
        virtual ~RectangleExplosion();

        bool update();

        void deleteParticle(unsigned int i);


};


class ExplosionParticle : public sf::Drawable
{
    private:
        sf::Vector2f _speed;
        sf::Vector2f _gravity;
        sf::Vector2i * _window_size;

        sf::CircleShape _shape;

        sf::Clock _cl;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;




    public:
        ExplosionParticle(sf::Vector2i * window_size,
                          sf::Vector2f init_pos,
                          sf::Vector2f init_speed,
                          sf::Vector2f gravity,
                          float init_size,
                          sf::Color couleur);
        virtual ~ExplosionParticle();

        bool update();
};

#endif // EXPLOSIONMANAGER_H
