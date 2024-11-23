#include "ComplexPlane.h"
ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight) : m_vArray(Points, 1)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = static_cast<float>(pixelHeight)/pixelWidth;
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::CALCULATING;
	m_vArray.resize(pixelWidth * pixelHeight);
}
void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}
void ComplexPlane::zoomIn()
{
	++m_zoomCount;
	float x = static_cast<float>(BASE_WIDTH) * pow(BASE_ZOOM, m_zoomCount);
	float y = static_cast<float>(BASE_HEIGHT) * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x, y };
	m_state = State::CALCULATING;
}
void ComplexPlane::zoomOut()
{
	--m_zoomCount;
	float x = static_cast<float>(BASE_WIDTH) * pow(BASE_ZOOM, m_zoomCount);
	float y = static_cast<float>(BASE_HEIGHT) * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_plane_size = { x, y };
	m_state = State::CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}
void ComplexPlane::loadText(Text& text)
{
	stringstream ss;
	text.setCharacterSize(16);
	text.setColor(Color::Yellow);
	ss << "Mandelbrot set" << endl;
	ss << "Center: (" << m_plane_center.x << "," << m_plane_center.y << ")" << endl;
	ss << "Cursor: (" << m_mouseLocation.x << "," << m_mouseLocation.y << ")" << endl;
	ss << "Left-click to Zoom in" << endl;
	ss << "Right-click to Zoom out" << endl;
	text.setString(ss.str());
}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for (int i = 0; i < m_pixel_size.y; i++)
		{
			for (int j = 0; j < m_pixel_size.x; j++)
			{
				int index = j + i * m_pixel_size.x;

				m_vArray[index].position = {(float)j, (float)i};
				
				Vector2i pixelCoord(j, i);
				
				Vector2f coords = mapPixelToCoords(pixelCoord);

				size_t iterations = countIterations(coords);

				Uint8 r, g, b;

				iterationsToRGB(iterations, r, g, b);

				m_vArray[index].color = Color(r, g, b);
			}
		}
		m_state = State::DISPLAYING;
	}
}

int ComplexPlane::countIterations(Vector2f coord)
{
	float x = 0.0f;
	float y = 0.0f;

	int iterations = 0;

	while(x*x + y*y <= 4.0f && iterations < MAX_ITER)
	{
		float tempX = x * x - y * y + coord.x;
		y = 2.0f * x * y + coord.y;
		x = tempX;
		++iterations;
	}
	return iterations;
}
void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
	if (count == MAX_ITER)
	{
		r = g = b = 0;
	}
	else
	{
		/*r = static_cast<Uint8>((count * 20 )% 256);             
		g = static_cast<Uint8>((count  ) % 256);        
		b = static_cast<Uint8>((count * 1) % 256);  */    
		r = static_cast<Uint8>((count * 10) % 256);   
		g = static_cast<Uint8>((count * 5) % 64);    
		b = static_cast<Uint8>((count * 5) % 64);
	}
}
Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	float x = ((mousePixel.x - 0) / static_cast<float>(1920 - 0)) * m_plane_size.x + (m_plane_center.x - m_plane_size.x / 2.0f);

	float y = ((mousePixel.y - 1080) / static_cast<float>(0 - 1080)) * m_plane_size.y + (m_plane_center.y - m_plane_size.y / 2.0f);

	return Vector2f(x, y);
}