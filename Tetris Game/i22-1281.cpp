/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

//AISHA SIDDIQA 22I-1281 CS-F
#include <SFML/Graphics.hpp>

#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main(){
    srand(time(0));
    RenderWindow window(VideoMode(600, 480), title);
    Texture obj1, obj2, obj3, obj4;
    sf::Font font1;
   
   
   obj1.loadFromFile("img/tiles.png");
   obj2.loadFromFile("img/background.png");
   obj3.loadFromFile("img/frame.png");
   obj4.loadFromFile("img/shadow.png");
   font1.loadFromFile("ghostclanlaser.ttf");  
   
    Sprite sprite(obj1), background(obj2), frame(obj3); 
    Sprite shadow(obj4);
    
    int delta_x=0,delta_y=0, colorNum=1;
    float timer=0, delay=0.3;
    bool rotate=0, space=0;
    bool gameover=false, reset=false;
    int lev=1, score=0;
    
    int n=0, n1=0,n2=0;
   
    
    Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;
	
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e))
        {                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) 
            {            				 //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space)
                  spacebar(n);
                else if (e.key.code == Keyboard::R)
                  reset=true;
            }
        }
        if(n!=7)
        {if (Keyboard::isKeyPressed(Keyboard::Down))        //Just another way to detect key presses without event listener
            delay=0.02;
        }                                    			//If DOWN key is pressed, delay in falling piece decreases from 0 to 0.08
         delay=0.3;   
         if(gameover)
	{
	 gameover= false;
	 
	 break;
	}
	
         //n2 = rand()%7+1;
         



        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        
        
         
         fallingPiece(timer,delay,colorNum,delta_x,n,n2);		
         
           
         move_x( delta_x,n);
       
         rotation(rotate,n);
         
         
         
         GameOver(gameover);
         
         Restart(reset,score);
         
         levelup(score,lev, delay);
         
         bombs_(n);
        // bomb_shadows();
         lineclear(score); 
         shadows(n); 
         bombvacant(n) ;   
         //bombdestruction(n);
         
         
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////



        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                    //SHADOW
                shadow.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                shadow.setPosition(j*18,i*18);
                shadow.move(28,31); //offset
                window.draw(shadow);
                
                //SPRITE
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite); 
                  
                  //next block 1                  
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(400,400); //offset
                
                //NEXT BLOCK 2
                window.draw(sprite);sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(500,400); //offset
                window.draw(sprite);                     
            }
        }
        
        //SHADOWS
        for (int i=0; i<4; i++){
            shadow.setTextureRect(IntRect(colorNum*18,0,18,18));
            shadow.setPosition(point_3[i][0]*18,point_3[i][1]*18);
            shadow.move(28,31);
            window.draw(shadow);
          }
          
          //SPRITE
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
          
          //NEXT BLOCK 1
          for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(bloc_1[i][0]*18,bloc_1[i][1]*18);
            sprite.move(400,400);
            window.draw(sprite);
          }
          
          //NEXT BLOCK 2
          for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(bloc_2[i][0]*18,bloc_2[i][1]*18);
            sprite.move(500,400);
            window.draw(sprite);
          }
          
          
          //TEXT  DISPLAY
          
          		//SCORE
		sf::Text display1;
		display1.setFont(font1);
		display1.setString("SCORE: ");
		display1.setPosition(400,50); 
		window.draw(display1);

			//SCORE VARIABLE
		sf::Text scorecount(std::to_string (score),font1);
		scorecount.setPosition(450,100);
		window.draw(scorecount);
		
		//LEVEL
		sf::Text display2;
		display2.setFont(font1);
		display2.setString("LEVEL: ");
		display2.setPosition(400,150); 
		window.draw(display2);
		
			//VARIABLE
		sf::Text levels(std::to_string (lev),font1);
		levels.setPosition(450,200);
		window.draw(levels);
		
			//NEXT BLOCK
		sf::Text display3;
		display3.setFont(font1);
		display3.setString("NEXT BLOCK: ");
		display3.setPosition(350,250); 
		window.draw(display3);
		
		                
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
        

    }
    


    return 0;
}
