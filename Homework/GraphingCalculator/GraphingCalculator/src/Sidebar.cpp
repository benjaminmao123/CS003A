#include <fstream>
#include <sstream>

#include "Sidebar.h"
#include "Constants.h"

Sidebar::Sidebar(GraphInformation &info)
	: _left(0), _width(0), info(info)
{

}

Sidebar::Sidebar(GraphInformation &info, float left, float width)
	: _left(left), _width(width), info(info)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
		exit(-1);
	}

	rect.setFillColor(sf::Color(105, 105, 105));
	rect.setPosition(sf::Vector2f(left, 0));
	rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
	
	title.Load(font);
	title.SetCharacterSize(20);
	title.SetPosition(SCREEN_WIDTH - SIDE_BAR, 0);
	title.SetSize(SIDE_BAR, SCREEN_HEIGHT / 9);
	title.SetString("History");
	title.SetColor(sf::Color::Yellow);
	title.SetStyle(sf::Text::Bold);

	std::ifstream ifs("history.txt");

	if (!ifs.is_open())
	{
		std::cout << "Failed to open history.txt" << std::endl;
		std::ofstream ofs("history.txt");
	}

	std::string line;

	while (std::getline(ifs, line))
		AddFunction(line);

	if (!items.empty())
		items[0]->OnClick();
}

Sidebar::~Sidebar()
{
	std::ofstream ofs("history.txt", std::ios::out | std::ios::trunc);

	if (!ofs.is_open())
	{
		std::cout << "Failed to open history.txt" << std::endl;
		exit(-1);
	}

	for (auto& i : items)
	{
		ofs << std::string(i->GetLabel() + "\n");
		delete i;
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
	historyButton->SetSize(sf::Vector2f(SIDE_BAR, (SCREEN_HEIGHT / (NUM_SIDEBAR_ITEMS + 1))));
	historyButton->SetHighlightedColor(sf::Color::Blue);
	historyButton->SetPressedColor(sf::Color::Cyan);
	historyButton->Load(nullptr, font);
	historyButton->SetLabelFontSize(20);
	historyButton->SetLabel(name);
	historyButton->SetPosition(SCREEN_WIDTH - SIDE_BAR, y);
	historyButton->SetTextColor(sf::Color::Red);
	historyButton->AddEvent(new ButtonOnClickEvent(info, historyButton));
	items.push_back(historyButton);
}
