#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N]= {};

int figures[7][4]= 
{
	1,3,5,7,
	2,4,5,7,
	3,5,4,6,
	3,5,4,7,
	2,3,5,7,
	3,5,7,6,
	2,3,4,5
};


struct Point {
	int x,y;
}a[4],b[4];

bool check()
{
   for (int i=0;i<4;i++)
      if (a[i].x<0 || a[i].x>=N || a[i].y>=M) return 0;
      else if (field[a[i].y][a[i].x]) return 0;

   return 1;
};

int main(){
	
	srand(time(0));
	RenderWindow window(VideoMode(320,360), "Tetris");
	RectangleShape rec, rec2, rec3;
	
	
	Texture t, t2, t3, t4,t5,t6;
	t.loadFromFile("./src/tiles.png");
	t2.loadFromFile("./src/background.png");
	if (t4.loadFromFile("./src/back4.jpg")){
		
	std::cout <<"Error";
	};
	
		if (t5.loadFromFile("./src/tet.jpg")){
		
	std::cout <<"Error";
	};
	
    Sprite s(t), background(t2);
    

    background.setPosition(Vector2f(-600.f, -300.f));
    rec.setPosition(Vector2f(202.f, 50.f));
    rec.setSize(Vector2f(100.f, 40.f));
    rec.setTexture(&t5);
    
    rec2.setPosition(Vector2f(180.f, 0.f));
    rec2.setSize(Vector2f(300.f, 400.f));
    rec2.setTexture(&t4);
    

    

	Event e;
	
	float timer = 0, delay = 0.3;
	
	int dx = 0; bool rotate = false; int colorNum = 1;
	
	Clock  clock;
	
	while(window.isOpen()){
		
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		

		
				
		while(window.pollEvent(e)){
			
			switch(e.type){
				case Event::Closed:
					window.close();
					break;
				case Event::KeyPressed:
					
					if (e.key.code == Keyboard::Up){
					 rotate = true ;
					}
					else if (e.key.code == Keyboard::Left) dx = -1 ;
					else if (e.key.code == Keyboard::Right) dx = 1 ;
					break;
			}
			
			if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
			
		}
		
    for (int i=0;i<4;i++)  { b[i]=a[i]; a[i].x+=dx; }
    if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
		
    if (rotate)
      {
        Point p = a[1]; 
        
        for (int i=0;i<4;i++)
          {
            int x = a[i].y-p.y;
            int y = a[i].x-p.x;
            a[i].x = p.x - x;
            a[i].y = p.y + y;
           }
           if (!check()) for (int i=0;i<4;i++) a[i]=b[i];
      }

		
    if (timer>delay)
      {
        for (int i=0;i<4;i++) { b[i]=a[i]; a[i].y+=1; }

        if (!check())
        {
         for (int i=0;i<4;i++) field[b[i].y][b[i].x]=colorNum;

         colorNum=1+rand()%7;
         int n=rand()%7;
         for (int i=0;i<4;i++)
           {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;
           }
        }

         timer=0;
      }

		int k = M-1;
		
		for(int i = M -1; i>0; i--){
			int count = 0;
			for (int j =0 ; j<N; j++){
				if (field[i][j]) count++;
				
				field[k][j] = field[i][j];
				
			}
			if (count <N) k--;
		}
		
		
		dx = 0; rotate = false; delay = 0.3;
		
		window.clear(Color::White);
	window.draw(background);
	window.draw(rec2);
	window.draw(rec);
    
    for (int i=0;i<M;i++)    
     for (int j=0;j<N;j++)
       {
         if (field[i][j]==0) continue;
         s.setTextureRect(IntRect(field[i][j] * 18,0,18,18));
         s.setPosition(j*18,i*18);
        
         window.draw(s);
       }
		
		for (int i = 0; i<4 ; i++){
		    s.setTextureRect(IntRect(colorNum * 18,0,18,18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
				window.draw(s);
		}

		window.display();
	}
	
	
	return 0;
}
