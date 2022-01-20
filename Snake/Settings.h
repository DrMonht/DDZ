#pragma once
#include <fstream>
#include"windows.h"
#include <string>
#include"Settings_of_buttons.h"

extern bool IsFirstSetting;								//Переменная для однократного применения функции set_config.
extern int status;										//Переменная для опознования типа открытого окна (игра, натсройки и т.д.).
extern Texture Check_in;								//Текустуры квадратиков для выбора определённой настройки.
extern Texture Check_out;		
bool isNameInp = false;									//Индикатор ввода имени.
bool SaveIs = 0;										//Индикатор сохранения.


//Перемнные настроек. По умолчанию всё 0.
int active_rounds = 0;
int active_size = 0;
int active_layout = 0;
int active_color = 0;
int active_Bots = 0;

std::string PlayerNameDynamic="";						//Строка, куда сохраняются вводимые символы.
std::string PlayerName ="";								//Имя игрока для вывода в файл.
sf::Font font;
sf::Text PlayerNameInput("" , font);					//Имя вывода в строке ввода, меняется при вводе символов.
sf::Text PlayerNameOutScreen("" , font);				//Вывод имени в окно текущей настройки.
ofstream Settings;

ConvexShape InputFill;

void options(RenderWindow& window) {
	
	if (!IntRect(350, 570, 350, 30).contains(Mouse::getPosition(window))) { isNameInp = false; }
	//Спрайты.
	Check_in.loadFromFile("Pictures/vacancy_cell.jpg");
	Check_out.loadFromFile("Pictures/active_cell.jpg");
	SaveButtonTexture.loadFromFile("Pictures/save.png");
	Sprite SaveButton(SaveButtonTexture);
	SaveButton.setPosition(830, 640);

	InputFill.setPointCount(4);
	InputFill.setPoint(0, Vector2f(50.f, 190.f));
	InputFill.setPoint(1, Vector2f(250.f, 190.f));
	InputFill.setPoint(2, Vector2f(250.f, 220.f));
	InputFill.setPoint(3, Vector2f(50.f, 220.f));
	InputFill.setFillColor(sf::Color(255, 255, 255, 60));
	font.loadFromFile("font/ComicSans.ttf");

	
	background.loadFromFile("Pictures/OPT.png");
	Sprite options_interface(background);
	window.clear();

	PlayerNameInput.setPosition(50, 190);									  
	PlayerNameInput.setFont(font);
	PlayerNameInput.setFillColor(sf::Color::Black);

	PlayerNameOutScreen.setPosition(230, 120);								
	PlayerNameOutScreen.setFont(font);
	PlayerNameOutScreen.setFillColor(sf::Color::Black);

	options_interface.setPosition(0, 0);

//Объекты для настроек.
	Layout layout;
	But_Color but_color;
	MapSize map_size;
	But_rounds but_rounds;
	But_Bots but_bot;
	if (IsFirstSetting == 0) {
		set_config();  //Единокрвтная инициализация при запуске окна настроек
		IsFirstSetting = 1;
	}
	//Нажатие на настройки кол-ва раундов
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(340, 280, 40, 40).contains(Mouse::getPosition(window))) {
		but_rounds.switch_rounds(0);
	}

	if (Mouse::isButtonPressed(Mouse::Left) &&  IntRect(470, 280, 40, 40).contains(Mouse::getPosition(window))) {
		but_rounds.switch_rounds(1);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(620, 280, 40, 40).contains(Mouse::getPosition(window))) {
		but_rounds.switch_rounds(2);
	}

	//Нажатие на настройки размера карты
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(380, 525, 40, 40).contains(Mouse::getPosition(window))) {
		map_size.switch_layer(0);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(570, 525, 40, 40).contains(Mouse::getPosition(window))) {
		map_size.switch_layer(1);
	}


	//Нажатие на настройки раскладки клавиатуры
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(430, 595, 40, 40).contains(Mouse::getPosition(window))) {
		layout.switch_layer(0);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(700, 595, 40, 40).contains(Mouse::getPosition(window))) {
		layout.switch_layer(1);
	}


	//Нажатие на настройки цвета
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(620, 440, 40, 40).contains(Mouse::getPosition(window))) {
		but_color.switch_color(2);
	}

	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(470, 440, 40, 40).contains(Mouse::getPosition(window))) {
		but_color.switch_color(1);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(340, 440, 40, 40).contains(Mouse::getPosition(window))) {
		but_color.switch_color(0);
	}

	//Нажатие на настройки кол-ва ботов
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(340, 360, 40, 40).contains(Mouse::getPosition(window))) {
		but_bot.switch_bots(0);
	}

	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(470, 360, 40, 40).contains(Mouse::getPosition(window))) {
		but_bot.switch_bots(1);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(620, 360, 40, 40).contains(Mouse::getPosition(window))) {
		but_bot.switch_bots(2);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(760, 360, 40, 40).contains(Mouse::getPosition(window))) {
		but_bot.switch_bots(3);
	}
	

	//Реакция на кнопку сохранения
	if (IntRect(830, 640, 322, 114).contains(Mouse::getPosition(window))) { SaveButton.setColor(Color(105, 101, 101, 160)); SaveIs = true; }
	else SaveIs = false;

	if (IntRect(50, 190, 330, 30).contains(Mouse::getPosition(window))) { InputFill.setFillColor(Color(255, 255, 255, 250)); isNameInp = true; }


	//Логика сохранения
	if (Mouse::isButtonPressed(Mouse::Left) && SaveIs) {
			
			Settings.close();
			
			Settings.open("Config.txt", ios_base::out);
			//Инициализация имени игрока и запись всех параметров в файл
			if(PlayerNameDynamic.length()!=0){
				PlayerName = PlayerNameDynamic;
				PlayerNameInput.setString(PlayerNameDynamic);
				PlayerNameOutScreen.setString(PlayerNameDynamic);
			}
			else {
				PlayerName = PlayerNameOutScreen.getString();
				PlayerNameInput.setString(PlayerNameOutScreen.getString());
			}
			Settings << active_layout << endl;
			Settings << PlayerName << endl;
			Settings << active_color+1 << endl;
			Settings << active_size << endl;
			Settings << active_rounds+1 << endl;
			Settings << active_Bots<< endl;
			Settings.close();
			status = 0;
			Sleep(80);
	}

	//Отрисовка
		window.draw(options_interface);
		window.draw(InputFill);
		window.draw(SaveButton);
		window.draw(PlayerNameInput);
		window.draw(PlayerNameOutScreen);
		but_color.show_all(window);
		layout.show_all(window);
		
		map_size.show_all(window);
		but_rounds.show_all(window);
		but_bot.show_all(window);
		window.display();
}