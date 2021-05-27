#pragma once
#include "Stage.h"
#include "Resources.h"
#include "OpeningScreen.h"
#include "StagesMenu.h"
#include <vector>
#include <string>
#include <fstream>
using std::ifstream;
using std::string;
using std::vector;


class Controller
{
public:
	Controller();
	void run();
private:
	vector<string> readStageFromFile(int num);
	vector<vector<string>> m_stages;
	OpeningScreen m_openingScreen;
	RenderWindow m_window;
	Resources m_resources;
	Sprite m_background;
};

