#if  _MSVC_TRADITIONAL
#include <CWindow.h>
#else
#include "include/CWindow.h"
#endif

CWindow::CWindow() : window(sf::VideoMode(1024,728),L"LAB 2")
{


}

CWindow::~CWindow() 
{
}

void CWindow::start()
{
	if (isStarted)
	{
		return;
	}
	else
	{
		isStarted = true;
		mainLoop();
	}
	

}

void CWindow::stop()
{
	if (isStarted)
	{
		isStarted = false;
	}
}

void CWindow::mainLoop()
{
	if (!ImGui::SFML::Init(window)) return;
	ImPlot::CreateContext();
	sf::Clock deltaClock;
	while (window.isOpen() && isStarted)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		ImGui::SFML::Update(window, deltaClock.restart());
		renderGUI();
		ImGui::ShowDemoWindow();
		ImPlot::ShowDemoWindow();
		window.clear();

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	ImPlot::DestroyContext();
}

void CWindow::renderGUI()
{

}
