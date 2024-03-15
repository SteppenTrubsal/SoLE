#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <implot.h>

class CWindow
{
public:
	CWindow();
	~CWindow();


	void start();
	void stop();
private:
	void mainLoop();

	sf::RenderWindow window;

	bool isStarted = false;

};

