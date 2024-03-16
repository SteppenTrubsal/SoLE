#include<methods.h>
#include <iostream>
#if  _MSVC_TRADITIONAL
#include <CWindow.h>
#else
#include "include/CWindow.h"
#endif
//vector<vector<double>> A = {
//	{18,8,6,1},
//	{4,13,8,1},
//	{0,9,14,5},
//	{6,4,4,12}
//};
//
//vector<double> b = { 17,5,21,0 };
//vector<double> x0 = {1,1,1,1};
CWindow::CWindow() :
	window(sf::VideoMode(1024, 728), L"LAB 2"),
	strMatrix(4, std::vector<std::string>(4, "0")),
	strFreeMembersVector(4, "0"),
	strVectorOfInitialApproximations(4, "1"),
	toleration(1e-2)
{
	strMatrix[0][0] = "18";
	strMatrix[0][1] = "8";
	strMatrix[0][2] = "6";
	strMatrix[0][3] = "1";

	strMatrix[1][0] = "4";
	strMatrix[1][1] = "13";
	strMatrix[1][2] = "8";
	strMatrix[1][3] = "1";

	strMatrix[2][0] = "0";
	strMatrix[2][1] = "9";
	strMatrix[2][2] = "14";
	strMatrix[2][3] = "5";

	strMatrix[3][0] = "6";
	strMatrix[3][1] = "4";
	strMatrix[3][2] = "4";
	strMatrix[3][3] = "12";

	strFreeMembersVector[0] = "17";
	strFreeMembersVector[1] = "5";
	strFreeMembersVector[2] = "21";
	strFreeMembersVector[3] = "0";

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
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
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
		//ImGui::ShowDemoWindow();
		//ImPlot::ShowDemoWindow();
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


	ImGui::LabelText("##lable", "Matrix system of linear algebraic equations:");

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
			strMatrix.push_back(std::vector<std::string>(sizeMatrix, "0"));
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
	ImGui::LabelText("##lable", "Vector of initial approximation:");
	if (ImGui::BeginTable("VectorOfInitialApproximations", strMatrix.size(), flags2))
	{

		for (size_t column = 0; column < strMatrix.size(); column++)
		{
			ImGui::TableNextColumn();
			ImGui::SetNextItemWidth(-FLT_MIN);
			ImGui::PushID((strMatrix.size() + 1) * (strMatrix.size() + 1) + column);
			ImGui::InputText("##cell", &strVectorOfInitialApproximations[column]);
			ImGui::PopID();
			ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.2f, 0.5f, 0.7f, 1.0f)));

		}
		ImGui::EndTable();
	}

	static int selectedMethod = 0;
	ImGui::RadioButton("Simple iterations method", &selectedMethod, 0);
	ImGui::RadioButton("Jacobi method", &selectedMethod, 1);
	ImGui::RadioButton("Gauss-Seidel method", &selectedMethod, 2);

	ImGui::InputDouble("delta 1e-n", &toleration, 1e-2, 1e-2);
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

		CustomMatrix A(slae);
		table res;

		if (selectedMethod == 0) {

			CustomMatrix tempE(A.getDim());						//
			tempE.EFill();										//некоторые временные величины
			tempE = tempE - (A * (A.getTau()));					//для проверки условий и критериев
			vector<double> lam = tempE.getLambda();				//
			double max = 0;										//
			for (int i = 0; i < lam.size(); i++) {				//
				double temp = (lam[i] > 0) ? lam[i] : -lam[i];	//
				max = (temp > max) ? temp : max;				//
			}

			std::cout << "Достаточное условие ";
			if (tempE.getNorm1() < 1) { std::cout << "выполняется"; }
			else { std::cout << "не выполняется"; }
			std::cout << ", так как ||E-tb|| = " << tempE.getNorm1() << std::endl;
			
			std::cout << "Критерий сходимости ";
			if (max < 1) { std::cout << "выполняется"; }
			else { std::cout << "не выполняется"; }
			std::cout << ", так как собственные значения E-tb: ";
			for (int i = 0; i < lam.size(); i++) { std::cout << lam[i] << " "; }
			std::cout <<  std::endl;

			SimpleIterations(A, freeMembersVector, vecApproximations, toleration, res);
		}
		else if (selectedMethod == 1) {
			Jacobi(A, freeMembersVector, vecApproximations, toleration, res);
		}
		else if (selectedMethod == 2) {
			GaussSeidel(A, freeMembersVector, vecApproximations, toleration, res);
		}

		ImGui::BeginChild("result", ImVec2(0, 1280), true);

		ImGui::LabelText("##lable", "Result:");
		std::string roots = "Roots:";
		for (size_t j = 0; j < res.roots.size(); j++)
		{
			roots += std::to_string(res.roots[j]) + ' ';
		}
		ImGui::LabelText("##lable", roots.c_str());
		std::string epsil = "eps = ";
		epsil += std::to_string(res.eps);
		epsil += "  iter:";
		epsil += std::to_string(res.num.back());

		if (ImPlot::BeginPlot(epsil.c_str())) {
			ImPlot::SetupAxes("Iterations", "Norm");
			//ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
			ImPlot::PlotLine("y(x)", res.num.data(), res.diffNorm.data(), res.diffNorm.size());
			ImPlot::EndPlot();
		}
		
		
		ImGui::LabelText("##lable", ":");
		ImGui::EndChild();


		/*result.simpleIterTable.clear();
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
		for (size_t i = 0; i < result.simpleIterTable.size(); i++)
		{
			std::sort(result.simpleIterTable[i].num.begin(), result.simpleIterTable[i].num.end());
			std::sort(result.simpleIterTable[i].diffNorm.begin(), result.simpleIterTable[i].diffNorm.end());
			std::sort(result.JacobiTable[i].num.begin(), result.JacobiTable[i].num.end());
			std::sort(result.JacobiTable[i].diffNorm.begin(), result.JacobiTable[i].diffNorm.end());
			std::sort(result.GaussSeidelTable[i].num.begin(), result.GaussSeidelTable[i].num.end());
			std::sort(result.GaussSeidelTable[i].diffNorm.begin(), result.GaussSeidelTable[i].diffNorm.end());
		}
		printf("Complited");
		isTheResultReady = true;*/
	}
	/*if (isTheResultReady)
	{
		ImGui::BeginChild("result", ImVec2(0, 1280), true);
		ImGui::LabelText("##lable", "Result:");
		ImGui::LabelText("##lable", "SimpleIterations:");

		for (size_t i = 0; i < result.simpleIterTable.size(); i++)
		{
			std::string roots = "Roots:";
			for (size_t j = 0; j < result.simpleIterTable[i].roots.size(); j++)
			{
				roots += std::to_string(result.simpleIterTable[i].roots[j]) + ' ';
			}
			ImGui::LabelText("##lable", roots.c_str());
			std::string epsil = "eps = ";
			epsil += std::to_string(result.simpleIterTable[i].eps);
			epsil += "  iter:";
			epsil += std::to_string(result.simpleIterTable[i].diffNorm.size());
			
			if (ImPlot::BeginPlot(epsil.c_str())) {
				ImPlot::SetupAxes("Iterations", "Norm");
				//ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
				ImPlot::PlotLine("y(x)", result.simpleIterTable[i].num.data(), result.simpleIterTable[i].diffNorm.data(), result.simpleIterTable[i].diffNorm.size());
				ImPlot::EndPlot();
			}

		}
		ImGui::LabelText("##lable", "Jacobi:");

		for (size_t i = 0; i < result.JacobiTable.size(); i++)
		{
			std::string roots = "Roots:";
			for (size_t j = 0; j < result.JacobiTable[i].roots.size(); j++)
			{
				roots += std::to_string(result.JacobiTable[i].roots[j]) + ' ';
			}
			ImGui::LabelText("##lable", roots.c_str());
			std::string epsil = "eps = ";
			epsil += std::to_string(result.JacobiTable[i].eps);
			epsil += "  iter:";
			epsil += std::to_string(result.JacobiTable[i].diffNorm.size());
			if (ImPlot::BeginPlot(epsil.c_str())) {
				ImPlot::SetupAxes("Iterations", "Norm");
				//ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
				ImPlot::PlotLine("y(x)", result.JacobiTable[i].num.data(), result.JacobiTable[i].diffNorm.data(), result.JacobiTable[i].diffNorm.size());
				ImPlot::EndPlot();
			}

		}
		ImGui::LabelText("##lable", "GaussSeidelTable:");

		for (size_t i = 0; i < result.GaussSeidelTable.size(); i++)
		{
			std::string roots = "Roots:";
			for (size_t j = 0; j < result.GaussSeidelTable[i].roots.size(); j++)
			{
				roots += std::to_string(result.GaussSeidelTable[i].roots[j]) + ' ';
			}
			ImGui::LabelText("##lable", roots.c_str());
			std::string epsil = "eps = ";
			epsil += std::to_string(result.GaussSeidelTable[i].eps);
			epsil += "  iter:";
			epsil += std::to_string(result.GaussSeidelTable[i].diffNorm.size());
			if (ImPlot::BeginPlot(epsil.c_str())) {
				ImPlot::SetupAxes("Iterations", "Norm");
				//ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
				ImPlot::PlotLine("y(x)", result.GaussSeidelTable[i].num.data(), result.GaussSeidelTable[i].diffNorm.data(), result.GaussSeidelTable[i].diffNorm.size());
				ImPlot::EndPlot();
			}

		}


		ImGui::LabelText("##lable", ":");
		ImGui::EndChild();
		
	}*/
	ImGui::End();
}

