#ifndef BACKGROUND_H
#define BACKGROUND_H


#include "headers.hpp"

#include "GameConfiguration.hpp"
#include "fn_random.hpp"

using namespace std;
using namespace sf;

class Particule;

class Background : public sf::Drawable
{
    private:
        vector<Particule> particules;
        sf::Vector2i _window_size;
        sf::RectangleShape bordure;

        GameConfiguration * _gameConfig;


        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    public:
        Background(sf::Vector2i window_size, GameConfiguration * gameConfig);
        virtual ~Background();

        void update();

    protected:
};



class Particule : public sf::Drawable
{
    private:
        sf::CircleShape shape;
        sf::Vector2f speed;
        sf::Vector2i _window_size;
        float _radius_base;

        sf::Clock _cl;

        GameConfiguration * _gameConfig;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        Particule(sf::Vector2i window_size, GameConfiguration * gameConfig);

        void update();



};

#endif // BACKGROUND_H
