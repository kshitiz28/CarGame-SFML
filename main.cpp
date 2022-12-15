#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<sstream>
int windowwidth=225;
int windowheight=225;
using namespace std;
using namespace sf;
class movecar
{
public:
    float xpos;
    float ypos;
    float xvel;
    float yvel;
    bool carstopright;
    bool carstopup;
    movecar()
    {
        bool carstopright=true;
        bool carstopup=true;
        float xpos=0;
        float ypos=0;
        float xvel=0;
        float yvel=0;
    }
    void update(bool playerup,bool playerdown,bool playerright,bool playerleft)
    {
        if(playerright)
        {
            bool carstopright=true;
            xvel=0.3;
        }
        if(playerleft)
        {
            bool carstopright=false;
            xvel=-0.3;
        }
        if(playerup)
        {
            bool carstopup=true;
            yvel=-0.3;
        }
        if(playerdown)
        {
            bool carstopup=false;
            yvel=0.3;
        }
        if(!(playerright || playerleft))
        {
            xvel=0;
        }
        if(!(playerup || playerdown))
        {
            yvel=0;
        }
        xpos+=xvel;
        ypos+=yvel;
        if(xpos>95 || xpos<-95)
        {
            xvel=0;
        }
    }
};
int main()
{   int scoreloop=1;
    int countout=0;
    int score=0;
    int p;
    movecar p1;
    float g=0.2;
    stringstream ss;
    string point;

    bool playerright,playerleft,playerup,playerdown =false;
    RenderWindow window(VideoMode(windowwidth, windowheight), "SCORING CAR!");

    Texture t1,car,coin1,coin2;
    t1.loadFromFile("data/images/background.jpg");
    Sprite backgroundsprite(t1);
    car.loadFromFile("data/images/car.png");
    Sprite carsprite(car);
    carsprite.setPosition(92,160);

    Texture over;
    over.loadFromFile("data/images/gameover.png");
    Sprite gameclose(over);


c:
    srand(time(0));
    int c1=rand()%100;
    int c2=rand()%100;

    coin1.loadFromFile("data/images/coin.png");
    Sprite drop1(coin1);
    drop1.setOrigin(-48,c1);

    coin2.loadFromFile("data/images/coin.png");
    Sprite drop2(coin2);
    drop2.setOrigin(-160,c2);


    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::Right))
            playerright=true;
        if(Keyboard::isKeyPressed(Keyboard::Left))
            playerleft=true;
        if(Keyboard::isKeyPressed(Keyboard::Up))
            playerup=true;
        if(Keyboard::isKeyPressed(Keyboard::Down))
            playerdown=true;
        if(!(Keyboard::isKeyPressed(Keyboard::Down)))
            playerdown=false;
        if(!(Keyboard::isKeyPressed(Keyboard::Up)))
            playerup=false;
        if(!(Keyboard::isKeyPressed(Keyboard::Left)))
            playerleft=false;
        if(!(Keyboard::isKeyPressed(Keyboard::Right)))
            playerright=false;
        p1.update(playerup,playerdown,playerright,playerleft);
        window.clear();

        carsprite.move(Vector2f(p1.xvel,p1.yvel));
        Vector2f position3 =carsprite.getPosition();

        drop1.move(Vector2f(0,g));
        drop2.move(Vector2f(0,g));
        Vector2f position1 = drop1.getPosition();
        Vector2f position2 = drop2.getPosition();
        if((int(position3.x)>14 && int(position3.x)<50)&&(int(position3.y)==int(position1.y)))
        {
            score++;
            goto c;

        }
        if((int(position3.x)>125 && int(position3.x)<165)&&(int(position3.y)==int(position2.y)))
         {
            score++;
            goto c;
        }

        if(position1.y>255 && position2.y>255)
        {
            countout++;
            goto c;
        }
        window.draw(backgroundsprite);
        window.draw(carsprite);
        window.draw(drop1);
        window.draw(drop2);
        if (countout>4)
        {
         ss<<score<<endl;
         ss>>point;
         window.draw(gameclose);
         Font f1;
         f1.loadFromFile("data/fonts/consola.ttf");
         Text scoretext("your score is::",f1,20);
         scoretext.setFillColor(Color::Red);
         scoretext.setOutlineColor(Color::Yellow);
         scoretext.setOutlineThickness(2);
         Text replay("press LEFT MOUSE BUTTON to play again",f1,10);
         replay.setPosition(0,150);
         replay.setFillColor(Color::Magenta);
         Text endgame("press ESCAPE to close the game",f1,12);
         endgame.setPosition(0,160);
         endgame.setFillColor(Color::Green);
         Text pointer(point,f1,20);
         pointer.setFillColor(Color::Red);
         pointer.setPosition(170,0);
         if(Mouse::isButtonPressed(Mouse::Left)){
                window.close();
                main();
         }
         if(Keyboard::isKeyPressed(Keyboard::Escape)){
                window.close();
         }
         window.draw(pointer);
         window.draw(endgame);
         window.draw(replay);
         window.draw(scoretext);
        }
        window.display();
    }

return 0;
}
