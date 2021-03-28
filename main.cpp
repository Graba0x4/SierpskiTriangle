#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <windows.h>

#define SIZE 800 // size of window
#define AA 8 // antialiasing level
#define POINT_SIZE 1.f
#define SLEEP 10 // thread sleep time in ms

//get random point inside triangle ABC
sf::Vector2f getRandomPoint(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C)
{

	double r1 = rand() / (double)RAND_MAX;
	double r2 = rand() / (double)RAND_MAX;

	double sqrtR1 = sqrt(r1);

	double x = (1 - sqrtR1) * A.x + (sqrtR1 * (1 - r2)) * B.x + (sqrtR1 * r2) * C.x;
	double y = (1 - sqrtR1) * A.y + (sqrtR1 * (1 - r2)) * B.y + (sqrtR1 * r2) * C.y;

	return sf::Vector2f(x, y);
}
//return half distance point on a line between points p1 and p2
sf::Vector2f getHalfLinePoint(sf::Vector2f p1, sf::Vector2f p2)
{
	int x, y;

	x = round(0.5f * p1.x + 0.5f * p2.x);
	y = round(0.5f * p1.y + 0.5f * p2.y);

	return sf::Vector2f(x, y);
}

int main()
{


	sf::ContextSettings settings;
	settings.antialiasingLevel = AA;


	sf::RenderWindow window(sf::VideoMode(SIZE, SIZE), "Sierpski Triangle!", sf::Style::Default, settings);
	sf::CircleShape triangle(SIZE / 2, 3);
	triangle.move(sf::Vector2(0.f, SIZE * 0.1f));
	sf::FloatRect fr = triangle.getGlobalBounds();
	float top = fr.top;
	float left = fr.left;
	float bottom = floor(top + fr.height);
	float right = floor(left + fr.width);

	sf::Vector2f A(left, bottom);
	sf::Vector2f B(right, bottom);
	sf::Vector2f C(SIZE / 2, top);

	sf::CircleShape point(POINT_SIZE, 100);
	point.setFillColor(sf::Color::White);
	

	//window.draw(triangle);
	srand(static_cast<int>(time(NULL)));
	sf::Vector2f half;
	sf::Vector2f p = getRandomPoint(A, B, C);
	int r;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		

		r = (int)(rand() % 3);
		//pick random vertex
		switch (r)
		{
		case 0: //a
			half = getHalfLinePoint(p, A);
			break;

		case 1: //b
			half = getHalfLinePoint(p, B);
			break;

		case 2: //c
			half = getHalfLinePoint(p, C);
			break;
		}

		p = half;

		point.setPosition(half.x, half.y);
		window.draw(point);

		//window.draw(line, 2, sf::PrimitiveType::Lines);
		window.display();
		Sleep(SLEEP);
	}

	return 0;
}