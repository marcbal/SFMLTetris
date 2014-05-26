#include "OpenGL_Manager.hpp"
using namespace std;
OpenGL_Manager::OpenGL_Manager(GameConfiguration* gameConfig){
    //_tetrisBoard = NULL;

    _gameConfig = gameConfig;
    _tetrisBoard = new int*[BOARD_WIDTH];
    orientation_vitesse = orientation_timeMax = Vector3f(0,0,0);
    orientation_progress = _gameConfig->get3DInclinaison();
    for(int i=0;i<4;i++)
    color[i]=1.0;

}

void OpenGL_Manager::setTetrisBoard(int tetrisBoard[][BOARD_HEIGHT]){
    for(int i=0;i<BOARD_WIDTH;++i)
            _tetrisBoard[i]=tetrisBoard[i];

}

void OpenGL_Manager::preDraw(){

        if(_tetrisBoard == NULL)
            return;

        glClear(GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();


    //glRotatef(10, 0.f, 1.f, 0.f);

    glTranslatef(0,0,-2240);


    glRotatef(orientation_progress.z, 1.f, 0.f, 0.f);
    glRotatef(orientation_progress.x, 0.f, 1.f, 0.f);

    if (_gameConfig->get3DAutorotation())
    {
            glRotatef(orientation_progress.y, 0.f, 0.f, 1.f);
        if(orientation_timer[0].getElapsedTime().asSeconds()>=orientation_timeMax.x){
            orientation_vitesse.x = rand_float(5,50);
            orientation_timeMax.x = rand_float(0.5,3);
            orientation_timer[0].restart();
        }
        if(orientation_timer[1].getElapsedTime().asSeconds()>=orientation_timeMax.y){
            orientation_vitesse.y = rand_float(5,50);
            orientation_timeMax.y = rand_float(0.5,3);
            orientation_timer[1].restart();
        }
        if(orientation_timer[2].getElapsedTime().asSeconds()>=orientation_timeMax.z){
            orientation_vitesse.z = rand_float(5,50);
            orientation_timeMax.z = rand_float(0.5,3);
            orientation_timer[2].restart();
        }
        orientation_progress += orientation_vitesse*timer.getElapsedTime().asSeconds();
    }

    glTranslatef(-100.f*(BOARD_WIDTH/2)-50,100.f*(BOARD_HEIGHT/2)+50,0);

    for(int i=0;i<BOARD_WIDTH;++i){
            glTranslatef(100.f,0.f,0.f);
        for(int j=0;j<BOARD_HEIGHT;++j){
             glTranslatef(0.f,-100.f,0.f);
                    color[0]=0.2;
                    color[1]=0.2;
                    color[2]=0.2;
                    drawArretes();
            if(_tetrisBoard[i][j]>29 && _tetrisBoard[i][j]<37){
                sf::Color c = Tetromino::couleurs[_tetrisBoard[i][j]-30];
                color[0]= c.r/float(255);
                color[1]= c.g/float(255);
                color[2]= c.b/float(255);
                color[3]= 64/float(255);
                drawShapeAlpha(i,j);
                color[3]=1.0;
            }
            else if(_tetrisBoard[i][j]>19 && _tetrisBoard[i][j]<27){
                sf::Color c = Tetromino::couleurs[_tetrisBoard[i][j]-20];
                color[0]= c.r/float(255);
                color[1]= c.g/float(255);
                color[2]= c.b/float(255);
                drawShape();
            }
            else if(_tetrisBoard[i][j]>9 && _tetrisBoard[i][j]<17){
                sf::Color c = Tetromino::couleurs[_tetrisBoard[i][j]-10];
                color[0]= c.r/float(255)-0.2;
                color[1]= c.g/float(255)-0.2;
                color[2]= c.b/float(255)-0.2;
                drawShape();
            }

        }
        glTranslatef(0.f,100.f*BOARD_HEIGHT,0.f);

    }
    timer.restart();
    //drawShape(0,0);
}

void OpenGL_Manager::drawShape(){

        glBegin(GL_QUADS);
            setGLColor(-0.4,-0.4,-0.4);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f( 50.f,  50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            //FACE
            glColor3f(color[0], color[1], color[2]);
            glVertex3f(-50.f, -50.f, 50.f);
            glVertex3f(-50.f,  50.f, 50.f);
            glVertex3f( 50.f,  50.f, 50.f);
            glVertex3f( 50.f, -50.f, 50.f);
            setGLColor(-0.2,-0.2,-0.2);
            //GAUCHE
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f(-50.f,  50.f,  50.f);
            glVertex3f(-50.f, -50.f,  50.f);
            setGLColor(-0.3,-0.3,-0.3);
            //Droite
            glVertex3f(50.f, -50.f, -50.f);
            glVertex3f(50.f,  50.f, -50.f);
            glVertex3f(50.f,  50.f,  50.f);
            glVertex3f(50.f, -50.f,  50.f);

            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f,  50.f);
            //HAUT
            setGLColor(-0.1,-0.1,-0.1);
            glVertex3f(-50.f, 50.f,  50.f);
            glVertex3f(-50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f,  50.f);
        glEnd();

}

void OpenGL_Manager::drawArretes(){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) ;
        glBegin(GL_QUADS);

            setGLColor();
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f( 50.f,  50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);

            glVertex3f(-50.f, -50.f, 50.f);
            glVertex3f(-50.f,  50.f, 50.f);
            glVertex3f( 50.f,  50.f, 50.f);
            glVertex3f( 50.f, -50.f, 50.f);
            //setGLColor(-0.5,-0.5,-0.5);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f(-50.f,  50.f,  50.f);
            glVertex3f(-50.f, -50.f,  50.f);

            glVertex3f(50.f, -50.f, -50.f);
            glVertex3f(50.f,  50.f, -50.f);
            glVertex3f(50.f,  50.f,  50.f);
            glVertex3f(50.f, -50.f,  50.f);

            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f,  50.f);

            glVertex3f(-50.f, 50.f,  50.f);
            glVertex3f(-50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f,  50.f);


        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) ;

}

void OpenGL_Manager::drawShapeAlpha(int x, int y){

        glBegin(GL_QUADS);

            //FOND
            setGLColor(-0.4,-0.4,-0.4);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f( 50.f,  50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            //FACE
            setGLColor();
            glVertex3f(-50.f, -50.f, 50.f);
            glVertex3f(-50.f,  50.f, 50.f);
            glVertex3f( 50.f,  50.f, 50.f);
            glVertex3f( 50.f, -50.f, 50.f);


            setGLColor(-0.2,-0.2,-0.2);
            //GAUCHE
            if(x-1<0||_tetrisBoard[x-1][y]<10){
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f(-50.f,  50.f,  50.f);
            glVertex3f(-50.f, -50.f,  50.f);
            }
            //Droite
            if(x+1>=BOARD_WIDTH||_tetrisBoard[x+1][y]<10){
            glVertex3f(50.f, -50.f, -50.f);
            glVertex3f(50.f,  50.f, -50.f);
            glVertex3f(50.f,  50.f,  50.f);
            glVertex3f(50.f, -50.f,  50.f);
            }//*
            if(y+1>=BOARD_HEIGHT||_tetrisBoard[x][y+1]<10){
            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f,  50.f);
            }
            if(y-1<0||_tetrisBoard[x][y-1]<10){
            //HAUT
            setGLColor(-0.1,-0.1,-0.1);
            glVertex3f(-50.f, 50.f,  50.f);
            glVertex3f(-50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f, -50.f);
            glVertex3f( 50.f, 50.f,  50.f);
            }
            //*/
        glEnd();

}

OpenGL_Manager::~OpenGL_Manager(){
    delete[] _tetrisBoard;
}

void OpenGL_Manager::setGLColor(float r, float g, float b){
    float tmp[3];
    tmp[0]=r;
    tmp[1]=g;
    tmp[2]=b;

    for(int i=0;i<3;++i)
    {
        tmp[i]+=color[i];
        if(tmp[i]<0)
        tmp[i]=0;
        else if(tmp[i]>1)
        tmp[i]=1;
    }
    glColor4f(tmp[0], tmp[1], tmp[2],color[3]);
}
void OpenGL_Manager::setGLColor(){
    setGLColor(0,0,0);
}

void OpenGL_Manager::onEvent(sf::Event & event)
{

    switch(event.type)
    {
        case sf::Event::MouseMoved:

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                Vector2i _movement = sf::Vector2i(event.mouseMove.x,event.mouseMove.y)-lastMousePos;
                orientation_progress += Vector3f(_movement.x,0,_movement.y);
                _gameConfig->set3DInclinaison(orientation_progress);
            }
            lastMousePos = sf::Vector2i(event.mouseMove.x,event.mouseMove.y);
        break;
        default: break;
    }
}
