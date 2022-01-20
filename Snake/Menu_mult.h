using namespace sf;

int active_color_m = 0;
bool IsMultiplayerMenu = 1;									//Почти все функции данного файла аналогичны функциям в Options.h .
int MultiState = 0;											//_m - это принадлежность переменной к настройкам мультиплеера.
bool isNameInp_m = 0;
bool isPlayButton = 0;

extern bool IsFirstSettingMultiplayer;
std::string PlayerNameDynamic_m = "";						//Строка для сохранения вводимых символов
std::string PlayerName_m = "";								//Имя игрока для вывода в настройки, которое фиусируеися при нажатии клавиши Enter
sf::Font font_m;
sf::Text PlayerNameInput_m("", font);						//Имя вывода в строке ввода, меняется при вводе символов
sf::Text PlayerNameOutScreen_m("", font);					//Вывод имени в окно текущей настройки
ConvexShape InputFill_m;
ofstream Settings_m;


extern int status;
#include"Settings.h"
Texture MultiplayerSaveTexture, Background_mTExture;
void MultiPlayer_menu(RenderWindow& window) {
	if (!IntRect(470, 260, 200, 30).contains(Mouse::getPosition(window))) { isNameInp_m = false; }


	InputFill_m.setPointCount(4);
	InputFill_m.setPoint(0, Vector2f(470.f, 260.f));
	InputFill_m.setPoint(1, Vector2f(670.f, 260.f));
	InputFill_m.setPoint(2, Vector2f(670.f, 290.f));
	InputFill_m.setPoint(3, Vector2f(470.f, 290.f));
	InputFill_m.setFillColor(sf::Color(255, 255, 255, 60));

	font.loadFromFile("font/ComicSans.ttf");

	PlayerNameInput_m.setPosition(470.f, 260);
	PlayerNameInput_m.setFont(font);
	PlayerNameInput_m.setFillColor(sf::Color::Black);


	MultiplayerSaveTexture.loadFromFile("Pictures/Play.png");
	Background_mTExture.loadFromFile("Pictures/MultM.png");
	Sprite Play_M(MultiplayerSaveTexture), Background_m(Background_mTExture);

	Check_in.loadFromFile("Pictures/vacancy_cell.jpg");
	Check_out.loadFromFile("Pictures/active_cell.jpg");

	Background_m.setPosition(0, 0);
	
	
	PlayerNameOutScreen_m.setPosition(470, 200);
	PlayerNameOutScreen_m.setFont(font);
	PlayerNameOutScreen_m.setFillColor(sf::Color::Black);
	
	Play_M.setPosition(830, 640);
	if (IntRect(850, 665, 320, 120).contains(Mouse::getPosition(window))) { Play_M.setColor(Color(105, 101, 101, 160)); MultiState = true; }
	else MultiState = false;


	But_Color_menu menu;
	if (IsFirstSettingMultiplayer == 0) {
		set_config_m();
		IsFirstSettingMultiplayer = 1;
	}
	if (IntRect(470, 260, 250, 30).contains(Mouse::getPosition(window))) { InputFill_m.setFillColor(Color(255, 255, 255, 250)); isNameInp_m = true; }


	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(555, 415, 40, 40).contains(Mouse::getPosition(window))) {
		menu.switch_color(0);
	}

	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(705, 415, 40, 40).contains(Mouse::getPosition(window))) {
		menu.switch_color(1);
	}
	if (Mouse::isButtonPressed(Mouse::Left) && IntRect(855, 415, 40, 40).contains(Mouse::getPosition(window))) {
		menu.switch_color(2);
	}

	if (IntRect(850, 665, 320, 120).contains(Mouse::getPosition(window))) { Play_M.setColor(Color(105, 101, 101, 160)); isPlayButton = true; }
	else {
		SaveIs = false;
		isPlayButton = false;
	}

	if (IntRect(850, 665, 320, 120).contains(Mouse::getPosition(window))) { InputFill.setFillColor(Color(255, 255, 255, 250)); isPlayButton = true; }


	if (Mouse::isButtonPressed(Mouse::Left) && isPlayButton) {
		status = 0;
		Settings_m.close();
		Settings_m.open("config_Mult.txt", ios_base::out);
		if (PlayerNameDynamic_m.length() != 0) {
			PlayerName_m = PlayerNameDynamic_m;
			PlayerNameInput_m.setString(PlayerNameDynamic_m);
			PlayerNameOutScreen_m.setString(PlayerNameDynamic_m);
		}
		else {
			PlayerName_m = PlayerNameOutScreen_m.getString();
			PlayerNameInput_m.setString(PlayerNameOutScreen_m.getString());
			//PlayerNameOutScreen.setString("Player");
		}
		Settings_m << PlayerName_m << endl;
		Settings_m << active_color_m + 1 << endl;
		status = 5;
	}


		window.draw(Background_m);
		window.draw(Play_M);
		window.draw(PlayerNameOutScreen_m);
		window.draw(InputFill_m);
		window.draw(PlayerNameInput_m);
		menu.show_all(window);
		window.display();

}