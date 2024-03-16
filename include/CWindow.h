#pragma once
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>
#include <implot.h>

/*struct vectorArr {
	vector<table> simpleIterTable;
	vector<table> JacobiTable;
	vector<table> GaussSeidelTable;
};*/

class CWindow
{
public:
	CWindow();
	~CWindow();


	void start();
	void stop();
private:
	void mainLoop();
	void renderGUI();
	static void PushStyleCompact()
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(style.FramePadding.x, (float)(int)(style.FramePadding.y * 0.60f)));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x, (float)(int)(style.ItemSpacing.y * 0.60f)));
	}

	static void PopStyleCompact()
	{
		ImGui::PopStyleVar(2);
	}
	sf::RenderWindow window;
	std::vector<std::vector<std::string>> strMatrix;
	std::vector<std::string> strFreeMembersVector;
	std::vector<std::string> strVectorOfInitialApproximations;
	bool isStarted = false;
	bool isTheResultReady = false;
};