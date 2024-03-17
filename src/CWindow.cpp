
#include<methods.h>
#include <iostream>
#include <sstream>
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
	strVectorOfInitialApproximations(4, "1")
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
		window.clear();

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	ImPlot::DestroyContext();
}

void CWindow::renderGUI()
{
	static std::vector<table> res;
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

	static bool rbtnJacobi = false;
	static bool rbtnSimpleIterations = false;
	static bool rbtnGaussSeidel = false;
	static bool toler_e2 = false;
	static bool toler_e3 = false;
	static bool toler_e4 = false;
	static std::string convergenceCriteriaS;
	static std::string convergenceCriteriaJ;
	static std::string convergenceCriteriaG;

	ImGui::Checkbox("Simple iterations method", &rbtnSimpleIterations);
	ImGui::SameLine();
	ImGui::Checkbox("Jacobi method", &rbtnJacobi);
	ImGui::SameLine();
	ImGui::Checkbox("Gauss-Seidel method", &rbtnGaussSeidel);

	ImGui::Checkbox("1e-2", &toler_e2);
	ImGui::SameLine();
	ImGui::Checkbox("1e-3", &toler_e3);
	ImGui::SameLine();
	ImGui::Checkbox("1e-4", &toler_e4);
	if (ImGui::Button("Get Result"))
	{
		convergenceCriteriaS.clear();
		convergenceCriteriaJ.clear();
		convergenceCriteriaG.clear();
		res.clear();
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
		std::stringstream ss;
		std::vector<double> tolerations;
		if (toler_e2)
			tolerations.push_back(1e-2);
		if (toler_e3)
			tolerations.push_back(1e-3);
		if (toler_e4)
			tolerations.push_back(1e-4);

		ss << "Condition numbers of this matrix is: " << A.getConditionNumber(1) << "; " << A.getConditionNumber(2) << "; " << A.getConditionNumber(3) << std::endl;

		if (rbtnSimpleIterations) {

			CustomMatrix tempE(A.getDim());						//
			tempE.EFill();										//некоторые временные величины
			tempE = tempE - (A * (A.getTau()));					//для проверки условий и критериев
			vector<double> lam = tempE.getLambda();				//
			double max = 0;										//
			for (int i = 0; i < lam.size(); i++) {				//
				double temp = (lam[i] > 0) ? lam[i] : -lam[i];	//
				max = (temp > max) ? temp : max;				//
			}
			ss << "Sufficient condition of simple iterations method ";
			ss << ((tempE.getNorm1() < 1) ?"is performed":"is not performed") << ", since the ||E-tb|| = " << tempE.getNorm1() << std::endl
				<< "Convergence criterion "<<((max < 1) ?"is performed": "is not performed")
				<< ", since the eigenvalues of E-tb: ";
			for (int i = 0; i < lam.size(); i++) { ss << lam[i] << " "; }
			ss <<  std::endl;
			convergenceCriteriaS = ss.str();
			for (size_t i = 0; i < tolerations.size(); i++)
			{
				if (convergenceSimpleCheck(A)) {
					table tab;
					SimpleIterations(A, freeMembersVector, vecApproximations, tolerations[i], tab);
					res.push_back(tab);
				}
			}

		}
		if (rbtnJacobi) {
			vector<CustomMatrix> LUD = A.getLUD();
			vector<double> lam = ((LUD[2].getReverse() * (LUD[0] + LUD[1])) * (-1)).getLambda();

			ss << "Sufficient condition of Jacobi method ";
			ss << ((sufficientJacobiCheck(A)) ? "is performed" : "is not performed") << std::endl
			<< "Convergence criterion " << ((convergenceJacobiCheck(A)) ? "is performed" : "is not performed")
				<< ", since the eigenvalues of -D^(-1) * (L + U): ";
			for (int i = 0; i < lam.size(); i++) { 
				ss << lam[i] << " "; 
			}
			ss << std::endl;
			convergenceCriteriaS = ss.str();

			for (size_t i = 0; i < tolerations.size(); i++)
			{
				if (convergenceJacobiCheck(A)) {
					table tab;
					Jacobi(A, freeMembersVector, vecApproximations, tolerations[i], tab);
					res.push_back(tab);
				}
			}
		}
		if (rbtnGaussSeidel) {
			vector<CustomMatrix> LUD = A.getLUD();
			vector<double> lam = (((LUD[0] + LUD[2]).getReverse() * LUD[1]) * (-1)).getLambda();

			ss << "Sufficient condition of Gauss-Seidel method ";
			ss << ((sufficientGaussSeidelCheck(A)) ? "is performed" : "is not performed") << std::endl
				<< "Convergence criterion " << ((convergenceGaussSeidelCheck(A)) ? "is performed" : "is not performed")
				<< ", since the eigenvalues of -(L + D)^(-1) * U: ";
			for (int i = 0; i < lam.size(); i++) { ss << lam[i] << " "; }
			ss << std::endl;
			convergenceCriteriaS = ss.str();

			for (size_t i = 0; i < tolerations.size(); i++)
			{
				if (convergenceGaussSeidelCheck(A)) {
					table tab;
					GaussSeidel(A, freeMembersVector, vecApproximations, tolerations[i], tab);
					res.push_back(tab);
				}
			}
		}
		
		isTheResultReady = true;
	}
	if (isTheResultReady)
	{
		ImGui::BeginChild("result", ImVec2(0, 1280), true);
		{
			ImGui::LabelText("##lable", "Result:");
			if (!convergenceCriteriaS.empty())
			{
				ImGui::LabelText("##lable", convergenceCriteriaS.c_str());
			}

			ImGui::LabelText("##lable", "Graphics:");
			for (size_t i = 0; i < res.size(); i++)
			{
				ImGui::LabelText("##lable", res[i].methodName.c_str());
				std::string roots = "Roots:";
				for (size_t j = 0; j < res[i].roots.size(); j++)
				{
					roots += std::to_string(res[i].roots[j]) + ' ';
				}
				ImGui::LabelText("##lable", roots.c_str());
				std::string epsil = "eps = ";
				epsil += std::to_string(res[i].eps);
				epsil += "  Iterations:";
				epsil += std::to_string(res[i].num.size());

				if (ImPlot::BeginPlot(epsil.c_str())) {
					ImPlot::SetupAxes("Iterations", "Norm");
					ImPlot::PlotLine("##plot", res[i].num.data(), res[i].diffNorm.data(), res[i].diffNorm.size());
					ImPlot::EndPlot();
				}
			}
			


			ImGui::LabelText("##lable", ":");
		}
		ImGui::EndChild();
	}
	ImGui::End();
}

