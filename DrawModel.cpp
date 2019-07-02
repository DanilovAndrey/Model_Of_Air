#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <thread>
#include <chrono>
#include <ctime>
#include <stdlib.h>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

using namespace std;

#define WIDTH 800
#define HEIGHT 800
#define PI 3.14159265
#define MAXSIZE 800
#define STEPS 5
#define TOP 10
#define LEFT 10
int N;

int globalFlagForPrintSpeed = 0;
 #define EPSILON 1
 #define MAXSPEED 7
 
 vector<float> speeds((4*MAXSPEED));

class Atom
{
     public:
         double x;
         double y;
         double z;
         double angle;// in grade
         double speed;
         double massa;
         double radius;

		 void Copy(Atom& a)
		 {
			x = a.x; y = a.y; z = a.z; angle = a.angle;
			speed = a.speed; massa = a.massa; radius = a.radius;
		 }
//		 Atom();
//		~Atom();
};
class Matrix2x2
{
	public:
		double a11; // a11 a12
		double a12; // a21 a22
		double a21;
		double a22;
		
		Matrix2x2(double a11, double a12, double a21, double a22)
		{	
			this->a11 = a11;
			this->a12 = a12;
			this->a21 = a21;
			this->a22 = a22;
		}
		Matrix2x2()
		{
		}
		void Multiply( double& Vx, double& Vy)
		{
			double VinterX = a11 * Vx + a12 * Vy;
			double VinterY = a21 * Vx + a22 * Vy;
			Vx = VinterX;
			Vy = VinterY;
		}

		void Inverse ()
		{
			double a12inter = a12;
			a12 = a21;
			a21 = a12inter;	
		}
		void PRINT()
		{
			cout << a11 << ' ' << a12 <<'\n';
			cout << a21 << ' ' << a22 <<'\n';
		}
};

void Multiply( Matrix2x2 m); 

void init2D(vector<Atom>& atoms);
void DrawBalls(vector<Atom>& atoms);
	void step(vector<Atom>&atoms);
void printValues(vector<Atom>& atoms);
void Accident(vector<Atom>& atoms);
	bool strike(Atom a, Atom b);
	void Proccesing(int i, int j, vector<Atom>& atoms, vector<Atom>& atomsI);
		double findAngle(double BosX, double BosY);
		void createMatrix(Matrix2x2& S, double angleOfreverse);
		void HIT(double& Vx1, double& Vy1, double& Vx2, double& Vy2);
//vector<Atom> atoms(MAXSIZE);
void counterOfSpeed(vector<Atom> atoms);
void writeToFile(vector<Atom> &atoms);
//void printSpeeds();

 


 /* void Multiply( Matrix2x2 m, double& Vx, double& Vy)
  {       
             double VinterX = a11 * Vx + a12 * Vy;
             double VinterY = a21 * Vx + a22 * Vy;
             Vx = VinterX;
             Vy = VinterY;
  }*/



void init2D(vector<Atom>& atoms)
{
	int number;
	cout << "Please enter number of atoms\n";
	cin >> number; N = number;
	srand(time( 0 ) );
	for(int i = 0; i < number; ++i)
	{
		atoms[i].x = double(rand() % WIDTH);
		atoms[i].y = double(rand() % HEIGHT);
		atoms[i].angle = double(rand() % 360); 
	//	atoms[i].speed = double(300 + rand() % 700);
		atoms[i].speed = double(2 + rand() % MAXSPEED);
		atoms[i].radius = 2.5;
	}
}
void printValues(vector<Atom>& atoms)
{
	int w = 20;
	int toch = 4;
	//cout << "x\t\ty\t\tv\t\tang\n";
	cout << fixed << setprecision(toch);
    cout << setfill('.');
	cout << right;

	cout<< setw(w) << "x |" << setw(w) << "y |" << setw(w) << "v |" << setw(w) << " ang" << '\n';
	for(int i = 0; i < N; ++i)
	{
		cout <<setw(w)<< atoms[i].x<<"|" << setw(w) << atoms[i].y<<"|" << setw(w) <<atoms[i].speed<<"|" << setw(w) << atoms[i].angle << "\n";
	}
	cout << "\n\n";
}
void DrawBalls(vector<Atom>& atoms)
{
	sf::RenderWindow window(sf::VideoMode((float)WIDTH, (float)HEIGHT), "authors: Khursik Ekaterina and Danilov Andrey");
	vector<sf::CircleShape> balls(N);
	vector<sf::CircleShape> dots(4*MAXSPEED);
//	sf::RenderWindow window2(sf::VideoMode(600.f, 8000.f), "graphic");
/*double count = 800;
       double here = 10;
       sf::CircleShape shape(20.f);
       shape.setFillColor(sf::Color::Green);
      shape.setPosition(10.f, 10.f);
		int i = 0;*/
int f = 0;
	while(window.isOpen())
	{


		while(true)
		{


// TEST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	/*		i++;
          i%=2;
           window.clear();
              if(here < 750)
              {
                  shape.move(1.f, 1.f);
                  here++;
              }
              else
              {
                  shape.setPosition(0.f, 0.f);
                  here = 0;
              }
	window.draw(shape);
          window.display();*/

// END!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			window.clear();

			step(atoms);
	
			for(int i = 0; i < N; ++i)
			{
				balls[i].setRadius(4.f);
//				balls[i].setPosition(atoms[i].x, atoms[i].y);
				balls[i].setPosition(atoms[i].x, atoms[i].y);
				balls[i].setFillColor(sf::Color::Green);
				window.draw(balls[i]);
			}
			window.display(); 
	//		step(atoms);
		//	if(f < 15)
		//	{
/*			window2.clear();
			for(float j = 0; j < globalFlagForPrintSpeed; ++j)
			{
				dots[j].setRadius(6.f);
    		    dots[j].setFillColor(sf::Color::Green);
	      		dots[j].setPosition(10.f + 5*j, speeds[j]/50);
				window2.draw(dots[j]);
			}
			window2.display();*/
		//	f++;
			//}
		}
	}
}
void step(vector<Atom>& atoms)
{
	for(int i = 0; i < N; ++i)
	{
		atoms[i].x += cos(atoms[i].angle * PI / 180) * atoms[i].speed;
		atoms[i].y += sin(atoms[i].angle * PI / 180) * atoms[i].speed;
//		Accident(atoms);
//printValues(atoms);
//cout << "\n\n\n";
	}
	Accident(atoms);
	counterOfSpeed(atoms);
	writeToFile(atoms);
}
void Accident(vector<Atom>& atoms)
{
	vector<Atom> atomsIntermidiate (MAXSIZE);
	for(int i = 0; i < N; ++i)
	{
		atomsIntermidiate[i].Copy(atoms[i]);
	}
	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j < N; ++j)
		{
			if(i==j) continue;
			else
			{
				if( strike(atoms[i], atoms[j]) == true)
				{
//cout << "YES\n";
//cout << atoms[i].x << ' ' << atoms[j].x << '\n';
//cout << i << ' ' << j << ' ' << sqrt((atoms[i].x - atoms[j].x)*(atoms[i].x-atoms[j].x) + (atoms[i].y - atoms[j].y) * (atoms[i].y - atoms[j].y))<<' '
//<< atoms[i].x-atoms[j].x << ' ' << atoms[i].y - atoms[j].y << ' ' << atoms[i].radius + atoms[j].radius <<'\n';
					Proccesing(i,j,atoms, atomsIntermidiate);
				}
				else
{
//cout <<"NO\n"; 
/*	if(atoms[i].x <= 0 || atoms[i].x >= WIDTH || atoms[i].y <= 0 || atoms[i].y >= HEIGHT)
	{
cout << atomsIntermidiate[i].x << ' ' << atomsIntermidiate[i].y << "\n";
		atoms[i].angle += 180;
		if(atoms[i].angle >= 360) atoms[i].angle -= 360;
	//	atomsIntermidiate[i].speed = 0.1;
	//	atomsIntermidiate[i].x = 0;
	//	atomsIntermidiate[i].y = 0;
	}*/ 
}
			}
		}
	}
	for(int i =0; i < N; ++i)
	{
/*		  if(atoms[i].x <= 10 || atoms[i].x >= WIDTH+10 || atoms[i].y <= 10 || atoms[i].y >= HEIGHT+10)
          {
/*             cout << atomsIntermidiate[i].x << ' ' << atomsIntermidiate[i].y << "\n";
              atomsIntermidiate[i].angle += 180;
              if(atomsIntermidiate[i].angle >= 360) atomsIntermidiate[i].angle -= 360;
//Katya about walls
		if(atoms[i].x <= 0) atoms[i].x = 0;
		if(atoms[i].x >= WIDTH) atoms[i].x = WIDTH;
		if(atoms[i].y <= 0) atoms[i].y  = 0;
		if(atoms[i].y >= HEIGHT) atoms[i].y = HEIGHT;
		if(atoms[i].angle == 0 || atoms[i].angle == 90 || atoms[i].angle == 180 || atoms[i].angle == 270 || atoms[i].angle == 360)
		{
			atomsIntermidiate[i].angle += 180;
		}
		else if(atoms[i].angle < 180) atomsIntermidiate[i].angle = 180 + atomsIntermidiate[i].angle;
		else if(atoms[i].angle < 360)
		{
cout << atoms[i].angle << ' ' << atoms[i].x << '\n';
			atomsIntermidiate[i].angle = 540 - atomsIntermidiate[i].angle;
		}
		if(atomsIntermidiate[i].angle > 360) atomsIntermidiate[i].angle = 360 - atomsIntermidiate[i].angle;
//
          }
		if(atoms[i].angle < 10)
		{
			atomsIntermidiate[i].angle = double(rand() % 360);
		}*/
	if( (atoms[i].x <= LEFT && atoms[i].angle < 180) || (atoms[i].x >= WIDTH-10 && atoms[i].angle < 90))
         {   
             atomsIntermidiate[i].angle = 180 - atomsIntermidiate[i].angle;
         }
         else if((atoms[i].x <= LEFT && atoms[i].angle > 180) || (atoms[i].x >= WIDTH-10 && atoms[i].angle > 90) )// 270?
         {   
             atomsIntermidiate[i].angle = 540 - atomsIntermidiate[i].angle;
         }
         else if(atoms[i].y <= TOP || atoms[i].y >= HEIGHT-10)
         {   
             atomsIntermidiate[i].angle = 360 - atomsIntermidiate[i].angle;
         }
         else  if(atoms[i].angle == 0 || atoms[i].angle == 90 || atoms[i].angle == 180 || atoms[i].angle == 270 || atoms[i].angle == 360) atomsIntermidiate[i].angle += 180;
           
           if(atoms[i].angle < 2)
         {   
             atomsIntermidiate[i].angle = double(rand() % 360);
         }
         if(atomsIntermidiate[i].angle > 360) atomsIntermidiate[i].angle = 360 - atomsIntermidiate[i].angle;


	}
	for(int i = 0; i < N;++i)
	{
		atoms[i].Copy( atomsIntermidiate[i]);
	}
}
bool strike(Atom a, Atom b)
{
	if( sqrt( (a.x - b.x)*(a.x-b.x) + (a.y - b.y) * (a.y - b.y) ) <= a.radius + b.radius)
	{
		return true;
	}
	return false;
}
void Proccesing(int i, int j, vector<Atom>& atoms, vector<Atom>& atomsI)
{
	double BosX = atoms[i].x - atoms[j].x; // resul line
	double BosY = atoms[i].y - atoms[j].y;
	double angleOfreverse = findAngle(BosX, BosY); // reverse of coordinate system
	if(angleOfreverse < 0) angleOfreverse = 360 + angleOfreverse;
//cout<<"angle " << angleOfreverse << '\n';	
	Matrix2x2 S;
	createMatrix(S, angleOfreverse);
//cout << angleOfreverse << "\n";
//S.PRINT();

	double Vx1 = atoms[i].speed * cos(atoms[i].angle * PI / 180);
	double Vy1 = atoms[i].speed * sin(atoms[i].angle * PI / 180);

	double Vx2 = atoms[j].speed * cos(atoms[j].angle * PI / 180);
    double Vy2 = atoms[j].speed * sin(atoms[j].angle * PI / 180);

	S.Inverse();
	S.Multiply(Vx1, Vy1); // vx1 in new coordinate system
	S.Multiply(Vx2, Vy2);

	HIT(Vx1, Vy1, Vx2, Vy2);
	
	S.Inverse();
	S.Multiply(Vx1, Vy1);
	S.Multiply(Vx2, Vy2);
	
	atomsI[i].speed = sqrt(Vx1*Vx1 + Vy1 * Vy1);
	atomsI[j].speed = sqrt(Vx2*Vx2 + Vy2 * Vy2);	

	atomsI[i].angle = atan(Vy1/Vx1);
	atomsI[j].angle = atan(Vy2/Vx2);
}
double findAngle(double BosX, double BosY)
{
//cout << "bosx " << sqrt(BosX*BosX ) <<"\n";
	double COSA = BosX / sqrt( BosX * BosX + BosY * BosY) ; // WIDTH * (BosX) / WIDTH * |BOSX , BOSY|
//	double COSA = BosX / abs(BosX);
//cout << "cosa " << COSA << "\n";
	return acos(COSA) * 180.0 / PI;
}
void createMatrix(Matrix2x2 &S, double angleOfreverse)
{
	S.a11 = cos(angleOfreverse *  PI / 180);
    S.a12 = (-1) * sin( angleOfreverse *  PI / 180);
    S.a21 = sin (angleOfreverse * PI / 180);
    S.a22 = cos(angleOfreverse * PI/ 180);
}
void HIT(double &Vx1, double &Vy1, double &Vx2, double& Vy2)
{
	double Vxinter = Vx1; // Vx1 = Vx2  Vx2 = Vx1
	Vx1 = Vx2;
	Vx2 = Vxinter;
}
void test(vector<Atom>&a)
{
	cout << "\n\n\n Inverse\n";
	Matrix2x2 m1(1,2,3,4);
	m1.PRINT();
	m1.Inverse();
	cout << "\n";
	m1.PRINT();
	cout << "\n";
	cout << "MULTIPLY\n";
	double vx = 1;
	double vy = 2;
	m1.Multiply(vx, vy);
	cout << vx << ' ' << vy <<'\n';
}
 bool cmt(const Atom& l, Atom& r)
 {
     return l.speed < r.speed;
 }
 void counterOfSpeed(vector<Atom> atoms)
 {
     sort( begin(atoms), end(atoms) , cmt);
 
 //for(int i = 0; i < atoms.size(); ++i) cout << atoms[i].speed << ' ';
 //cout <<"\n";
     int flag = 0;
     int j = 0;
     int flag2 = 0;
     speeds.clear();
     for(int i = 0; i <= (2 * MAXSPEED)/EPSILON ; i+= EPSILON)
     {
         for(int z = flag; z < MAXSIZE; z++)
         {
             if(atoms[z].speed <= i)
             {
 //cout<< flag << ' ' << atoms[z].speed << ' ' << i << '\n';
                 speeds[j]++;
                 globalFlagForPrintSpeed = j;
             }
             else
             {
 //cout << flag << '\n';
 //cout<<'!' << speeds[j] << ' ' << i << '\n';
                 j++;
                 flag = z;
                 break;
             }
         }
     }
 }

void writeToFile( vector<Atom> & atoms)
 {
 // (4*pi*N *(m/2pi k T) (^ 3/2) * v(^2) (1/exp)
     ofstream output("File1.txt", ios_base::trunc | ios::out);
 //  ofstream output("File1.txt", ios::app);
 //, ios::app);
 //, ios_base::trunc | ios::out);
     for(int i = 0; i < N; i++)
     {
         output << atoms[i].speed << endl;
    }
     output.close();
}

int main()
{	
	vector<Atom> atoms(MAXSIZE);
	init2D(atoms);
	DrawBalls(atoms);
	return 0;
}
