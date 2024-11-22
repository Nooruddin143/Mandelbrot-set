#include "ComplexPlane.h"
using namespace std;
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
	int x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);  // (BASE_ZOOM to the m_ZoomCount power);
	int y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);//(BASE_ZOOM to the m_ZoomCount
	m_plane_size = { static_cast<float>(x), static_cast<float>(y)};
	m_state = State::CALCULATING;
}
void ComplexPlane::zoomOut()
{
	--m_zoomCount;
	int x = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);  // (BASE_ZOOM to the m_ZoomCount power);
	int y = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);//(BASE_ZOOM to the m_ZoomCount
	m_plane_size = { static_cast<float>(x), static_cast<float>(y) };
	m_state = State::CALCULATING;
}
void ComplexPlane::setCenter(Vector2i mousePixel)
{

}
void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{

}
void ComplexPlane::loadText(Text& text)
{

}
void ComplexPlane::updateRender()
{
	if (m_state == State::CALCULATING)
	{
		for (int i = 0; i < m_pixel_size.y; i++)
		{
			//random color for each row
			Uint8 r, g, b;
			r = rand() % 256;
			g = rand() % 256;
			b = rand() % 256;
			for (int j = 0; j < m_pixel_size.x; j++)
			{
				m_vArray[i * m_pixel_size.x + j].position = { (float)j, (float)i };
				m_vArray[i * m_pixel_size.x + j].color = { r,g,b };
			}
		}
	}
}