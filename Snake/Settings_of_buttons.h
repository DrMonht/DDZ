Texture SaveButtonTexture;
Texture background;
Texture Check_in;
Texture Check_out;

//Класс реализации кнопок
//Внешние зависимости
extern int active_rounds;
extern int active_size;
extern int active_layout;
extern int active_color;
extern int active_color_m;
extern int active_Bots;
extern std::string PlayerName;
extern std::string PlayerName_m;
extern sf::Text PlayerNameOutScreen_m;
extern sf::Text PlayerNameOutScreen;
extern sf::Text PlayerNameInput;

//Класс кнопки
class Button_check {
public:
	Sprite cell;
	bool cell_status = 0;
	int ButX;
	int ButY;

	Button_check() {
		cell.setTexture(Check_in);
		cell_status;
		ButX = 0;
		ButY = 0;
	}
	Button_check(int x, int y) {
		cell.setPosition(x, y);
		cell.setTexture(Check_in);
		cell_status = 0;
		ButX = x;
		ButY = y;
	}

	//Смена активности кнопки
	void switch_active() {
		switch (this->cell_status) {
		case 0:
			cell.setTexture(Check_out);
			cell_status = true;
			break;
		case 1:
			cell.setTexture(Check_in);
			cell_status = false;
			break;
		}
	}
	inline bool get_status() {
		return cell_status;
	}
	void set_status(bool st) {
		cell_status = st;
	}
	inline bool get_x() {
		return ButX;
	}
	inline bool get_y() {
		return ButY;
	}
	void show(RenderWindow& window) {
		window.draw(cell);
	}

};

//Классы групп кнопок по функциям
class Layout {
	public:
	Button_check but_lay_wsad{ 430,595 };
	Button_check but_lay_arraw{ 700,595 };
	Button_check* cls[2] = { &but_lay_wsad  ,&but_lay_arraw };

	Layout() {
		cls[active_layout]->switch_active();
		cls[active_layout]->set_status(1);
	}
	void switch_layer(int cl) {
		cls[active_layout]->switch_active();
		cls[cl]->switch_active();
		active_layout = cl;
	}
	bool give_layout() {
		return active_layout;
	}
	void show_all(RenderWindow& window) {
		but_lay_wsad.show(window);
		but_lay_arraw.show(window);
	}
};

class MapSize {
	Button_check but_low{ 380,525 };
	Button_check but_hight{ 570,525 };
	Button_check* cls[2] = { &but_low  ,&but_hight };
public:
	MapSize() {
		cls[active_size]->switch_active();
		cls[active_size]->set_status(1);
	}
	void switch_layer(int cl) {
		cls[active_size]->switch_active();
		cls[cl]->switch_active();
		active_size = cl;
	}
	bool give_layout() {
		return active_size;
	}
	void show_all(RenderWindow& window) {
		but_low.show(window);
		but_hight.show(window);
	}
};


class But_Bots {

	Button_check zero{ 340,360 };
	Button_check one{ 470,360 };
	Button_check two{ 620,360 };
	Button_check three{ 760,360 };
	Button_check* cls[4] = { &zero , &one  ,&two , &three };

public:
	But_Bots() {
		cls[active_Bots]->switch_active();
		cls[active_Bots]->set_status(1);
	}
	void switch_bots(int cl) {
		cls[active_Bots]->switch_active();
		cls[cl]->switch_active();
		active_Bots = cl;
	}
	int give_bots() {
		return active_Bots;
	}
	void show_all(RenderWindow& window) {
		for (int i = 0; i < 4; i++)
			cls[i]->show(window);
	}
};
class But_rounds {

	Button_check one{ 340,280 };
	Button_check two{ 470,280 };
	Button_check three{ 620,280 };
	Button_check* cls[3] = { &one  ,&two , &three };
	
public:
	But_rounds() {
		cls[active_rounds]->switch_active();
		cls[active_rounds]->set_status(1);
	}
	void switch_rounds(int cl) {
		cls[active_rounds]->switch_active();
		cls[cl]->switch_active();
		active_rounds = cl;
	}
	int give_bots() {
		return active_rounds;
	}
	void show_all(RenderWindow& window) {
		for (int i = 0; i < 3; i++)
			cls[i]->show(window);
	}
};
class But_Color {

	Button_check blue_col{ 470,440 };
	Button_check black_col{ 620,440 };
	Button_check red_col{ 340,440 };
	Button_check* cls[3] = {&red_col ,  &blue_col, &black_col};

public:
	But_Color() {
		cls[active_color]->switch_active();
		cls[active_color]->set_status(1);
	}
	void switch_color(int cl) {
		cls[active_color]->switch_active();
		cls[cl]->switch_active();
		active_color = cl;
	}
	int give_color() {
		return active_color;
	}
	void show_all(RenderWindow& window) {
		for (int i = 0; i < 3; i++)
			cls[i]->show(window);
	}
};

class But_Color_menu {

	Button_check blue_col{ 555,415 };
	Button_check red_col{ 705,415 };
	Button_check black_col{ 855,415 };
	Button_check* cls[3] = { &blue_col  ,&red_col , &black_col };

public:
	But_Color_menu() {
		cls[active_color_m]->switch_active();
		cls[active_color_m]->set_status(1);
	}
	void switch_color(int cl) {
		cls[active_color_m]->switch_active();
		cls[cl]->switch_active();
		active_color_m = cl;
	}
	int give_color() {
		return active_color_m;
	}
	void show_all(RenderWindow& window) {
		for (int i = 0; i < 3; i++)
			cls[i]->show(window);
	}
};

ifstream Config_but;
ifstream Config_but_m;

//Функции установки настроек из файла

void set_config() {
	Config_but.open("Config.txt", ios_base::in);
	string  Line;
	getline(Config_but, Line);
	active_layout = atoi(Line.c_str());
	getline(Config_but, Line);
	PlayerNameOutScreen.setString(Line);
	PlayerName = Line;
	getline(Config_but, Line);
	active_color = atoi(Line.c_str())-1;
	getline(Config_but, Line);
	active_size = atoi(Line.c_str());
	getline(Config_but, Line);
	active_rounds = atoi(Line.c_str())-1;
	getline(Config_but, Line);
	active_Bots = atoi(Line.c_str());
	Config_but.close();
}

void set_config_m() {
	Config_but_m.open("config_Mult.txt", ios_base::in);
	string  Line;
	getline(Config_but_m, Line);
	PlayerNameOutScreen_m.setString(Line);
	PlayerName_m = Line;
	getline(Config_but_m, Line);
	active_color_m = atoi(Line.c_str()) - 1;
	Config_but_m.close();
}