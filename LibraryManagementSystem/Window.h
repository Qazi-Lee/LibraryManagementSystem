#pragma once
struct WindowPros
{
	int Width;
	int Height;
	WindowPros(int width = 1280, int height = 720)
		:Width(width), Height(height) {}
};
class Window
{
public:
	Window(const WindowPros&pros=WindowPros()):
		m_pros(pros) {
	}
public:
	WindowPros m_pros;
};            