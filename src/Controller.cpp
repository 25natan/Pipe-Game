#include "Controller.h"
Controller::Controller()
	:m_openingScreen(m_window,m_background)
{
	m_window.create(sf::VideoMode::getDesktopMode(), "Pipe Game");
	m_background.setTexture(m_resources.background);

	//loading all stages' files content one by one until there is no more
	int num = 1;
	while (1)
	{
		vector<string> stage = readStageFromFile(num++);
		if (stage == vector<string>())
			break;
		m_stages.push_back(stage);
	}
	if (!m_stages.size())
		throw string("There are no stages at all!");
}

vector<string> Controller::readStageFromFile(int num)
{
	//try to read stage with the given number from file
	string fileName = "stage" + std::to_string(num) + ".txt";
	ifstream input(fileName);

	//if there is no such a file then return empty stage
	if (!input.is_open())
		return vector<string>();

	//read stage line by line using std::getline function
	vector<string> stage;
	while (!input.eof())
	{
		stage.push_back(string());
		std::getline(input, stage.back());
	}
	return stage;
}

void Controller::run()
{
	StagesMenu stagesMenu(m_window,m_background,m_stages.size());
	m_openingScreen.show();
	while (1)
	{
		int stageNum = stagesMenu.show();
		if (stageNum == -1)
			break;
		Stage stage(m_stages[stageNum], m_resources, m_window, m_background);
		stage.play();
	}
}