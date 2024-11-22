// Include important C++ libraries here
//#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width / 2;
	int pixelHeight = VideoMode::getDesktopMode().height / 2;
	VideoMode vm(pixelWidth, pixelHeight);
	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot set", Style::Default);

	//resize window for different resolutions
	/*View view;
	view.setSize(pixelWidth, pixelHeight);
	view.setCenter(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);
	window.setView(view);*/

	// RainbowScreen rain(pixelWidth, pixelHeight);

	ComplexPlane plane(pixelWidth, pixelHeight);
	Font font;
	if (!font.loadFromFile("timesNewRoman.ttf"))
	{
		cout << "Can not load the file!" << endl;
	}
	bool update = true;

	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					update = true;
				}
			}
			// Handling if moouse moved
			if (event.type == sf::Event::MouseMoved)
			{

			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (update)
		{
			plane.updateRender();
			update = false;
		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		window.clear();
		// displaying text in the corner of the window
		Text text("Mandelbrot set", font);
		text.setCharacterSize(12);
		text.setFillColor(Color::Yellow);
		text.setPosition(10,10);

		window.draw(plane);
		window.display();
	}
}
