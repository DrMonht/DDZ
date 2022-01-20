
#include <SFML/Graphics.hpp>
#include<fstream>
#include"Game.h"
#include"Menu.h"
#include"Settings.h"
#include"Menu_mult.h"

using namespace sf;

bool IsFirstSetting = 0;
bool IsFirstSettingMultiplayer = 0;
extern bool isMenu;
extern int menuNum;
extern bool isNameInp;
extern bool isNameInp_m;
extern sf::Text PlayerNameInput;
extern std::string PlayerNameDynamic;
extern std::string PlayerName;
extern sf::Text PlayerNameOutScreen;
extern sf::Text PlayerNameInput_m;
extern std::string PlayerNameDynamic_m;
int status = 0;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 800), "Snake");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	Image icon;
	icon.loadFromFile("Pictures\\icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	while (window.isOpen())
	{
		if (status == 0) {
			IsFirstSetting = 0;
			IsFirstSettingMultiplayer = 0;
		}
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» 
			if (event.type == Event::Closed)
				//Закрываем окно
				window.close();

			//Два цикла для обработки ввода, когда открыто окно настроек. Каждый цикл отвечает за своё окно в зависимости от выбора  режима игры.
			if (event.type == sf::Event::TextEntered && isNameInp) {
				if (event.text.unicode < 128) {
					if (event.text.unicode == 8) {
						if(PlayerNameDynamic.length() != 0)
							PlayerNameDynamic.pop_back();
					}
					else {
						PlayerNameDynamic += static_cast<char>(event.text.unicode);
					}
					PlayerNameInput.setString(PlayerNameDynamic);
				}	
			}
			if (event.type == sf::Event::TextEntered && isNameInp_m) {
				if (event.text.unicode < 128) {
					if (event.text.unicode == 8) {
						if (PlayerNameDynamic_m.length() != 0)
							PlayerNameDynamic_m.pop_back();
					}
					else {
						PlayerNameDynamic_m += static_cast<char>(event.text.unicode);
					}
					PlayerNameInput_m.setString(PlayerNameDynamic_m);
				}
			}
		}
		switch (status) {
		case(0):
			menu(window);
			break;
		case(1):
			singlePlayer(window);
			break;
		case(2):
			options(window);
			break;
		case(3):
			window.close();
			break;
		case(4):
			MultiPlayer_menu(window);
			break;

		case(5):
			multyPlayer(window);
			break;
		}
	}
	return 0;
}