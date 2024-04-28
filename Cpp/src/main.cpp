
#include <SFML/Graphics.hpp>
#include "Application.hpp"

using namespace std;
using namespace sf;

int main()
{
    srand(time(NULL));
    Console::initLogFile();
    Application app;
    app.run();

    return 0;
}
