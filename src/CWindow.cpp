#if  _MSVC_TRADITIONAL
#include <CWindow.h>
#else
#include "include/CWindow.h"
#endif

CWindow::CWindow() : 
	window(sf::VideoMode(1024,728),L"LAB 2"),
strMatrix(4,std::vector<std::string>(4,"0")),
strFreeMembersVector(4,"0"),
strVectorOfInitialApproximations(4,"0"),
toleration(1e-2)
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
	static int sizeMatrix = 4;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin("Main Window", nullptr,
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoBringToFrontOnFocus);


	ImGui::LabelText("##lable","Matrix systems of linear algebraic equations:");

	ImGui::SliderInt("SLAE size", &sizeMatrix, 2, 10);
	if (sizeMatrix != strMatrix.size())
	{
		std::vector<std::vector<std::string>> temp(strMatrix);
		std::vector<std::string> temp2(strFreeMembersVector);
		std::vector<std::string> temp3(strVectorOfInitialApproximations);
		
		int newSize = std::min((int)strMatrix.size(), sizeMatrix);
		strMatrix.clear();
		strFreeMembersVector.clear();
		strVectorOfInitialApproximations.clear();
		for (size_t i = 0; i < sizeMatrix; i++)
		{
			strMatrix.push_back(std::vector<std::string>(sizeMatrix,"0"));
			strFreeMembersVector.push_back("0");
			strVectorOfInitialApproximations.push_back("0");
		}
		for (size_t i = 0; i < newSize; i++)
		{
			for (size_t j = 0; j < newSize; j++)
			{
				strMatrix[i][j] = temp[i][j];
			}
		}
		for (size_t i = 0; i < newSize; i++)
		{
			strFreeMembersVector[i] = temp2[i];
			strVectorOfInitialApproximations[i] = temp3[i];
		}

	}
	static ImGuiTableFlags flags2 =
		ImGuiTableFlags_Borders |
		ImGuiTableFlags_RowBg |
		ImGuiTableFlags_BordersH |
		ImGuiTableFlags_BordersV |
		ImGuiTableFlags_BordersInner |
		ImGuiTableFlags_BordersOuter |
		ImGuiTableFlags_Resizable;

	if (ImGui::BeginTable("SLAE", strMatrix.size() + 1, flags2))
	{
		for (size_t row = 0; row < strMatrix.size(); row++)
		{
			for (size_t column = 0; column < strMatrix.size() + 1; column++)
			{
				if (strMatrix.size() == column)
				{
					ImGui::TableNextColumn();
					ImGui::SetNextItemWidth(-FLT_MIN);
					ImGui::PushID(row * (strMatrix.size() + 1) + column);
					ImGui::InputText("##cell", &strFreeMembersVector[row]);
					ImGui::PopID();
					ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.5f, 0.5f, 0.5f, 1.0f)));
				}
				else
				{
					ImGui::TableNextColumn();
					ImGui::SetNextItemWidth(-FLT_MIN);
					ImGui::PushID(row * (strMatrix.size() + 1) + column);
					ImGui::InputText("##cell", &strMatrix[row][column]);
					ImGui::PopID();
				}
			}
		}
		ImGui::EndTable();
	}
	ImGui::InputDouble("delta 1e-n", &toleration, 1e-2, 1e-2);
	ImGui::LabelText("##lable", "Vector of initial approximations:");
	if (ImGui::BeginTable("VectorOfInitialApproximations", strMatrix.size(), flags2))
	{

		for (size_t column = 0; column < strMatrix.size(); column++)
		{
			ImGui::TableNextColumn();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::PushID((strMatrix.size()+1) * (strMatrix.size() + 1) + column);
			ImGui::InputText("##cell", &strVectorOfInitialApproximations[column]);
			ImGui::PopID();
			ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.2f, 0.5f, 0.7f, 1.0f)));
			
		}
		ImGui::EndTable();
	}
	if (ImGui::Button("Get Result"))
	{
		std::vector<std::vector<double>> slae(strMatrix.size(),std::vector<double>(strMatrix.size(),0));
		for (size_t i = 0; i < strMatrix.size(); i++)
		{
			for (size_t j = 0; j < strMatrix.size(); j++)
			{
				slae[i][j] = std::stod(strMatrix[i][j]);
			}
		}
		std::vector<double> vecApproximations(strMatrix.size());
		std::vector<double> freeMembersVector(strMatrix.size());
		
		for (size_t i = 0; i < strMatrix.size(); i++)
		{
			vecApproximations[i] = std::stod(strVectorOfInitialApproximations[i]);
			freeMembersVector[i] = std::stod(strFreeMembersVector[i]);
		}

		matrix A(slae);
		table temp;
		result.simpleIterTable.clear();
		result.JacobiTable.clear();
		result.GaussSeidelTable.clear();
		SimpleIterations(A, freeMembersVector, vecApproximations, 1e-2, temp);
		result.simpleIterTable.push_back(temp);
		SimpleIterations(A, freeMembersVector, vecApproximations, 1e-3, temp);
		result.simpleIterTable.push_back(temp);
		SimpleIterations(A, freeMembersVector, vecApproximations, 1e-4, temp);
		result.simpleIterTable.push_back(temp);
		Jacobi(A, freeMembersVector, vecApproximations, 1e-2, temp);
		result.JacobiTable.push_back(temp);
		Jacobi(A, freeMembersVector, vecApproximations, 1e-3, temp);
		result.JacobiTable.push_back(temp);
		Jacobi(A, freeMembersVector, vecApproximations, 1e-4, temp);
		result.JacobiTable.push_back(temp);
		GaussSeidel(A, freeMembersVector, vecApproximations, 1e-2, temp);
		result.GaussSeidelTable.push_back(temp);
		GaussSeidel(A, freeMembersVector, vecApproximations, 1e-3, temp);
		result.GaussSeidelTable.push_back(temp);
		GaussSeidel(A, freeMembersVector, vecApproximations, 1e-4, temp);
		result.GaussSeidelTable.push_back(temp);

		isTheResultReady = true;
	}
	if (!isTheResultReady)
	{
		ImGui::BeginChild("result", ImVec2(0, 1000), true);
		ImGui::LabelText("##lable", "Result:");
		ImGui::EndChild();
	}
	ImGui::End();
}

