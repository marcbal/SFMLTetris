#ifndef BACKGROUND_H
#define BACKGROUND_H


#include "headers.hpp"

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


        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    public:
        Background(sf::Vector2i window_size, unsigned int nb_particules);
        virtual ~Background();

        void addParticule(unsigned int nb_new_particule);

        void update();

    protected:
};



class Particule : public sf::Drawable
{
    private:
        sf::CircleShape shape;
        sf::Vector2f speed;
        sf::Vector2i _window_size;

        // sf::Drawable
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    public:
        Particule(sf::Vector2i window_size);

        void update();



};

#endif // BACKGROUND_H
