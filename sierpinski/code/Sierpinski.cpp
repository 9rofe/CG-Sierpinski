#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game

	RenderWindow window(vm, "Sierpinski Triangle!!", Style::Default);
	CircleShape vert(1);

	vector<Vector2f> vertices;   ///push_back stuff into us!
	vector<Vector2f> points;

	Vector2f clicked;

	float midpoint_x, midpoint_y;

	//set the prompt
	Text prompt;
	Text prompt2;
	Text prompt3;
	Font font;
	font.loadFromFile("fonts/TitilliumWeb-Regular.ttf");
	if (!font.loadFromFile("fonts/TitilliumWeb-Regular.ttf"))
	{
		// error
	}
	prompt.setFont(font);
	prompt.setString("Click 3 vertices of a triangle");
	prompt.setCharacterSize(30);
	prompt.setFillColor(Color::White);

	prompt2.setFont(font);
	prompt2.setString("Click a random point to begin");
	prompt2.setCharacterSize(25);
	prompt2.setFillColor(Color::White);

	prompt3.setFont(font);
	prompt3.setString("Click to reveal new points...");
	prompt3.setCharacterSize(20);
	prompt3.setFillColor(Color::Red);

	//position the prompt
	FloatRect textRect = prompt.getLocalBounds();
	prompt.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	prompt.setPosition(1920 / 2.0f, 1080 / 20.0f);
	
	FloatRect textRect2 = prompt2.getLocalBounds();
	prompt2.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	prompt2.setPosition(1920 / 2.0f + 20.0f, 1080 / 11.0f);

	FloatRect textRect3 = prompt3.getLocalBounds();
	prompt3.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	prompt3.setPosition(1920 / 2.0f + 55.0f, 1080 / 8.0f);

	int lastVertex;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					clicked.x = event.mouseButton.x;
					clicked.y = event.mouseButton.y;

					//triangle:
					if (vertices.size() < 3) 
					//square:
					//if (vertices.size() < 4)
					{
						vertices.push_back(Vector2f(clicked.x, clicked.y));
						//cout << "vertices: " << vertices[vertices.size() - 1].x << " " << vertices[vertices.size() - 1].y << endl;
					}
					else if (points.size() == 0)
					{
						points.push_back(Vector2f(clicked.x, clicked.y));
						//cout << "points: " << points[points.size() - 1].x << " " << points[points.size() - 1].y << endl;
					}

					//ONE DOT PER CLICK:
					/*
					else
					{
						//triangle:
						int randVertex = (rand() % 3);
						midpoint_x = ((vertices[randVertex].x + points[points.size() - 1].x) / 2);
						midpoint_y = ((vertices[randVertex].y + points[points.size() - 1].y) / 2);
						points.push_back(Vector2f(midpoint_x, midpoint_y));
						//cout << "points.size " << points.size() << endl;
						//cout << "vertex chosen : " << vertices[randVertex].x << " " << vertices[randVertex].y << endl;
						//cout << "points: " << points[points.size() - 1].x << " " << points[points.size() - 1].y << endl;

						//square:
						int randVertex = (rand() % 4);
						if (randVertex != lastVertex)
						{
							lastVertex = randVertex;
							midpoint_x = ((vertices[randVertex].x + points[points.size() - 1].x) / 2);
							midpoint_y = ((vertices[randVertex].y + points[points.size() - 1].y) / 2);
							points.push_back(Vector2f(midpoint_x, midpoint_y));
						}			
					}
					*/
				}
			}

		}
					
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}	
		
		window.clear();
		
		// Draw our game scene here
		for (int i = 0; i < vertices.size(); i++)
		{
			vert.setPosition(vertices[i].x, vertices[i].y);
			window.draw(vert);
		}
		
		for (int i = 0; i < points.size(); i++)
		{
			vert.setPosition(points[i].x, points[i].y);
			window.draw(vert);
		}

		//quick draw
		
		int count = 0;
		
		while(points.size() > 0 && count < 100)
		{
			//triangle:
			
			int randVertex = (rand() % 3);
			midpoint_x = ((vertices[randVertex].x + points[points.size() - 1].x) / 2);
			midpoint_y = ((vertices[randVertex].y + points[points.size() - 1].y) / 2);
			points.push_back(Vector2f(midpoint_x, midpoint_y));
			vert.setPosition(points[count].x, points[count].y);
			

			//square:
			/*
			int randVertex = (rand() % 4);
			if (randVertex != lastVertex)
			{
				lastVertex = randVertex;
				midpoint_x = ((vertices[randVertex].x + points[points.size() - 1].x) / 2);
				midpoint_y = ((vertices[randVertex].y + points[points.size() - 1].y) / 2);
				points.push_back(Vector2f(midpoint_x, midpoint_y));
			}
			*/
			window.draw(vert);
			count++;
		}
		
		
		window.draw(prompt);
		
		if (vertices.size() == 3 && points.size() >= 0)
		{
			window.draw(prompt2);
		}

		if (vertices.size() == 3 && points.size() >= 1)
		{
			window.draw(prompt3);
		}

		window.display();
		
    }
    return 0;
}