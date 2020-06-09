#include <fstream>
#include <sstream>

#include "Sidebar.h"
#include "Constants.h"

Sidebar::Sidebar(GraphInformation &info)
	: _left(0), _width(0), info(info), historyButton(nullptr)
{

}

Sidebar::Sidebar(GraphInformation &info, float left, float width)
	: _left(left), _width(width), info(info), historyButton(nullptr)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
		exit(-1);
	}

	rect.setFillColor(sf::Color(35, 35, 165));
	rect.setPosition(sf::Vector2f(left, 0));
	rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
	
	title.Load(font);
	title.SetCharacterSize(20);
	title.SetPosition(SCREEN_WIDTH - SIDE_BAR, 0);
	title.SetSize(SIDE_BAR, SCREEN_HEIGHT / 9);
	title.SetString("History");
	title.SetFillColor(sf::Color(100, 93, 140));
	title.SetStyle(sf::Text::Bold);

	Load();

	if (!items.empty())
		items[0]->OnClick();
}

Sidebar::~Sidebar()
{
	Save();

	for (auto& i : items)
		delete i;
}

void Sidebar::Save()
{
	std::ofstream ofs("history.txt", std::ios::out | std::ios::trunc);

	if (!ofs.is_open())
	{
		std::cout << "Failed to open history.txt" << std::endl;
		exit(-1);
	}

	for (auto& i : items)
		ofs << std::string(i->GetText() + "\n");
}

void Sidebar::Load()
{
	std::ifstream ifs("history.txt");

	if (!ifs.is_open())
	{
		std::cout << "Failed to open history.txt" << std::endl;
		std::ofstream ofs("history.txt");
	}

	std::string line;
	std::vector<std::string> temp;

	while (std::getline(ifs, line))
		temp.push_back(line);

	for (int i = temp.size() - 1; i >= 0; --i)
		AddFunction(temp[i]);
}

void Sidebar::Clear()
{
	while (!items.empty())
	{
		delete items.back();
		items.pop_back();
	}
}

void Sidebar::Draw(sf::RenderWindow &window) 
{
	window.draw(rect);
	title.Render(window);

	for (auto &i : items)
		i->Render(window);
}

void Sidebar::Update()
{
	for (auto &i : items)
		i->Update();

	title.Update();
}

void Sidebar::AddFunction(const std::string& name)
{
	float y = 0;
	
	if (items.empty())
		y = title.GetSize().y + ((SCREEN_HEIGHT / NUM_SIDEBAR_ITEMS) - 
								 (SCREEN_HEIGHT / (NUM_SIDEBAR_ITEMS + 1)));
	else
	{
		Button* prevButton = items[items.size() - 1];

		y += prevButton->GetPosition().y + prevButton->GetSize().y + 
			((SCREEN_HEIGHT / NUM_SIDEBAR_ITEMS) - prevButton->GetSize().y);
	}

	historyButton = new Button();
	historyButton->SetSize(sf::Vector2f(SIDE_BAR - BUTTON_X_PADDING,
										(SCREEN_HEIGHT / (NUM_SIDEBAR_ITEMS + 1))));
	historyButton->SetNormalColor(sf::Color(80, 50, 140));
	historyButton->SetHighlightedColor(sf::Color(135, 135, 57));
	historyButton->SetPressedColor(sf::Color(52, 55, 39));
	historyButton->Load(nullptr, font);
	historyButton->SetTextCharacterSize(20);
	historyButton->SetTextFillColor(sf::Color(30, 30, 55));
	historyButton->SetTextStyle(sf::Text::Bold);
	historyButton->SetPosition(SCREEN_WIDTH - SIDE_BAR + (BUTTON_X_PADDING / 2), y);
	historyButton->AddEvent(new ButtonOnClickEvent(info, historyButton));
	items.push_back(historyButton);

	if (items.size() > 1)
		for (unsigned int i = items.size() - 1; i > 0; --i)
			items[i]->SetText(items[i - 1]->GetText());

	items[0]->SetText(name);
}
