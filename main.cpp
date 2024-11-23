// Include important C++ libraries here
//#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
int main()
{
	// Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width ;
	int pixelHeight = VideoMode::getDesktopMode().height;
	VideoMode vm(pixelWidth, pixelHeight);
	// Create and open a window for the game
	RenderWindow window(vm, "Mandelbrot set", Style::Default);

	//resize window for different resolutions
	/*View view;
	view.setSize(pixelWidth, pixelHeight);
	view.setCenter(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2);
	window.setView(view);*/

	ComplexPlane plane(pixelWidth, pixelHeight);
	Font font;
	if (!font.loadFromFile("timesNewRoman.ttf"))
	{
		cout << "Can not load the file!" << endl;
	}
	else {
		cout << "loaded" << endl;
	}
	bool update = true;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					Vector2i center = { event.mouseButton.x, event.mouseButton.y };
					plane.zoomIn();
					plane.setCenter(center);
					update = true;
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					Vector2i center = { event.mouseButton.x, event.mouseButton.y };
					plane.zoomOut();
					plane.setCenter(center);
					update = true;
				}

			}
			if (event.type == sf::Event::MouseMoved)
			{
				Vector2i location = {event.mouseButton.x, event.mouseButton.y };
				plane.setMouseLocation(location);
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
		Text text("", font);
		plane.loadText(text);
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
		
		window.draw(plane);

		window.draw(text);

		window.display();
	}
}
