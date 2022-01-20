#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

using namespace sf;
using namespace std;
extern int status;
//������ ����
const int Width = 1200; //������ ����
const int Height = 800; //������ ����

//�onfig-����������
struct {
	Keyboard::Key Up;
	Keyboard::Key Down;
	Keyboard::Key Left;
	Keyboard::Key Right;
} MyKeyboard = { Keyboard::W, Keyboard::S, Keyboard::A, Keyboard::D }; //���������
string Name = "Player"; //��� ������
string Name2 = "Player2"; //��� ������� ������
Color NameColor = Color::Black; //���� ����� ������� ������
Color NameColor2 = Color::Black; //���� ����� ������� ������
int CountOfCellsX = 25; //���������� ������ �� �  ...25(40px) � 40(25px)
int CountOfCellsY = 20; //���������� ������ �� y  ...20(40px) � 32(25px)
int CellSize = 40; //������ ������(px)
int CountOfRounds = 1; //���������� �������
int CountOfBots = 0; //���������� �����
Texture GameOverTexture, ExitGameTexture;
Sprite GameOver, ExitGame;

//���� ������:
const string MapBackgroundB("Pictures\\MapBackgroundB.png"); //������� �����
const string MapBackgroundL("Pictures\\MapBackgroundL.png"); //��������� �����
const string MapBackgroundMul("Pictures\\MapBackgroundMul.png"); //����� ��������������������� ����
const string TextureB("Pictures\\TextureB.png"); //T������� ������� �����
const string TextureL("Pictures\\TextureL.png"); //�������� ��������� �����
const string ConfigPath("config.txt");
const string ConfigMulPath("config_Mul.txt");
const string FontPath("font\\ComicSans.ttf");

//������� ���������
Texture SnakeTexture, MapTexture;
Sprite HeadSprite, HeadSprite2, HeadSpriteBot, BodySprite, AppleSprite, MapBackgroundSprite; //�������
int AppleX = 0;
int AppleY = 0;
const int StartSpeed = 500; //��������� ��������
int SpeedCoeff = 15; //��� ��������� �����
int PlayerScore = 0; //���� ������� ������
int PlayerScore2 = 0; //���� ������� ������
int GameScore = 0; //C��� � ����� � ������� ��� ���������� ���������
bool Game = true; //�������� �����������

void setTexture(string MapBackgroundPath, string TexturePath, int NameColorCode) {
	//�������� ����
	SnakeTexture.loadFromFile(TexturePath);
	//�������� �����
	MapTexture.loadFromFile(MapBackgroundPath);

	//��������� ��������
	//������ ������
	AppleSprite.setTexture(SnakeTexture);
	AppleSprite.setTextureRect(IntRect(0, 0, CellSize, CellSize));
	//������ ����
	BodySprite.setTexture(SnakeTexture);
	BodySprite.setTextureRect(IntRect(CellSize, 0, CellSize, CellSize));
	//������ ������ ����
	HeadSpriteBot.setTexture(SnakeTexture);
	HeadSpriteBot.setTextureRect(IntRect(CellSize * 2, 0, CellSize, CellSize));
	//������ ������ ������
	HeadSprite.setTexture(SnakeTexture);
	HeadSprite.setTextureRect(IntRect(CellSize * NameColorCode, 0, CellSize, CellSize));
	//������ �����
	MapBackgroundSprite.setTexture(MapTexture);
}

void setConfig() {
	ifstream ConfigFile(ConfigPath, ios::in);
	//���� ���� �� ������ - ��������� �� ���������
	if (!ConfigFile.is_open()) {
		setTexture(MapBackgroundL, TextureL, 3);
		return;
	}

	string Line; //������ ��������� ��������� �� Config.txt

	//���������
	getline(ConfigFile, Line);
	if (Line == "1") {
		MyKeyboard.Up = Keyboard::Up;
		MyKeyboard.Down = Keyboard::Down;
		MyKeyboard.Left = Keyboard::Left;
		MyKeyboard.Right = Keyboard::Right;
	}

	//���
	getline(ConfigFile, Name);

	//����
	int NameColorCode = 0;
	getline(ConfigFile, Line);
	switch (atoi(Line.c_str()))
	{
	case 1:
		NameColor = Color::Black;
		NameColorCode = 3;
		break;
	case 2:
		NameColor = Color::Red;
		NameColorCode = 4;
		break;
	case 3:
		NameColor = Color::Blue;
		NameColorCode = 5;
		break;
	}

	//������ �����
	getline(ConfigFile, Line);
	if (Line == "1") {
		CountOfCellsX = 40;
		CountOfCellsY = 32;
		CellSize = 25;
		SpeedCoeff = 20;
		setTexture(MapBackgroundB, TextureB, NameColorCode);
	}
	else {
		setTexture(MapBackgroundL, TextureL, NameColorCode);
	}

	//���������� �������
	getline(ConfigFile, Line);
	CountOfRounds = atoi(Line.c_str());

	//���������� �����
	getline(ConfigFile, Line);
	CountOfBots = atoi(Line.c_str());

	ConfigFile.close();
}

void setConfigMul() {

	//������ �����
	CountOfCellsX = 40;
	CountOfCellsY = 32;
	CellSize = 25;
	SpeedCoeff = 20;

	//��������
	SnakeTexture.loadFromFile(TextureB);
	MapTexture.loadFromFile(MapBackgroundMul);

	//��������� ��������
	//������ ������
	AppleSprite.setTexture(SnakeTexture);
	AppleSprite.setTextureRect(IntRect(0, 0, CellSize, CellSize));
	//������ ����
	BodySprite.setTexture(SnakeTexture);
	BodySprite.setTextureRect(IntRect(CellSize, 0, CellSize, CellSize));
	//������ ������ ������� ������
	HeadSprite.setTexture(SnakeTexture);
	//������ ������ ������� ������
	HeadSprite2.setTexture(SnakeTexture);
	//������ �����
	MapBackgroundSprite.setTexture(MapTexture);

	//-----------------------------------------------------------------
	//������ �����

	ifstream ConfigFile(ConfigPath, ios::in);
	//���� ���� �� ������ - ��������� �� ���������
	if (!ConfigFile.is_open()) {
		HeadSprite.setTextureRect(IntRect(CellSize * 3, 0, CellSize, CellSize));
		return;
	}

	string Line; //������ ��������� ���������

	//���������
	getline(ConfigFile, Line);
	MyKeyboard.Up = Keyboard::Up;
	MyKeyboard.Down = Keyboard::Down;
	MyKeyboard.Left = Keyboard::Left;
	MyKeyboard.Right = Keyboard::Right;

	//���
	getline(ConfigFile, Name);

	//����
	getline(ConfigFile, Line);
	switch (atoi(Line.c_str()))
	{
	case 1:
		NameColor = Color::Black;
		HeadSprite.setTextureRect(IntRect(CellSize * 3, 0, CellSize, CellSize));
		break;
	case 2:
		NameColor = Color::Red;
		HeadSprite.setTextureRect(IntRect(CellSize * 4, 0, CellSize, CellSize));
		break;
	case 3:
		NameColor = Color::Blue;
		HeadSprite.setTextureRect(IntRect(CellSize * 5, 0, CellSize, CellSize));
		break;
	}

	//������ �����
	getline(ConfigFile, Line);

	//���������� �������
	getline(ConfigFile, Line);
	CountOfRounds = atoi(Line.c_str());

	ConfigFile.close();
	//-----------------------------------------------------------------

	//-----------------------------------------------------------------
	//������ �����

	ifstream ConfigFile2(ConfigMulPath, ios::in);
	//���� ���� �� ������ - ��������� �� ���������
	if (!ConfigFile2.is_open()) {
		HeadSprite2.setTextureRect(IntRect(CellSize * 3, 0, CellSize, CellSize));
		return;
	}

	//���
	getline(ConfigFile2, Name2);

	//����
	getline(ConfigFile2, Line);
	switch (atoi(Line.c_str()))
	{
	case 1:
		NameColor2 = Color::Black;
		HeadSprite2.setTextureRect(IntRect(CellSize * 3, 0, CellSize, CellSize));
		break;
	case 2:
		NameColor2 = Color::Red;
		HeadSprite2.setTextureRect(IntRect(CellSize * 4, 0, CellSize, CellSize));
		break;
	case 3:
		NameColor2 = Color::Blue;
		HeadSprite2.setTextureRect(IntRect(CellSize * 5, 0, CellSize, CellSize));
		break;
	}

	ConfigFile2.close();
	//-----------------------------------------------------------------
}

bool pause(RenderWindow& Window) { //true - �����

	enum class Pause {
		Empty,
		Resume,
		Restart,
		Exit,
	};
	Pause Status = Pause::Empty;

	while (Window.isOpen()) {

		Event event;
		while (Window.pollEvent(event)) {
			if (event.type == Event::Closed)
				Window.close();
		}

		//��������
		Texture PauseBackgroundTexture, ResumeButtonTexture, RestartButtonTexture, ExitButtonTexture;
		PauseBackgroundTexture.loadFromFile("Pictures\\PauseBackground.png");
		ResumeButtonTexture.loadFromFile("Pictures\\ResumeButton.png");
		RestartButtonTexture.loadFromFile("Pictures\\RestartButton.png");
		ExitButtonTexture.loadFromFile("Pictures\\ExitButton.png");

		//�������
		Sprite PauseBackground, ResumeButton, RestartButton, ExitButton;
		PauseBackground.setTexture(PauseBackgroundTexture);
		ResumeButton.setTexture(ResumeButtonTexture);
		RestartButton.setTexture(RestartButtonTexture);
		ExitButton.setTexture(ExitButtonTexture);

		//��������� �������� �� �����
		PauseBackground.setPosition(450, 100);
		ResumeButton.setPosition(542, 290);
		RestartButton.setPosition(542, 410);
		ExitButton.setPosition(542, 530);

		if (IntRect(542, 290, 280, 96).contains(Mouse::getPosition(Window))) { ResumeButton.setColor(Color(105, 101, 101, 160)); Status = Pause::Resume; }
		if (IntRect(542, 410, 280, 96).contains(Mouse::getPosition(Window))) { RestartButton.setColor(Color(105, 101, 101, 160)); Status = Pause::Restart; }
		if (IntRect(542, 530, 280, 96).contains(Mouse::getPosition(Window))) { ExitButton.setColor(Color(105, 101, 101, 160)); Status = Pause::Exit; }
		if (!IntRect(542, 290, 280, 96).contains(Mouse::getPosition(Window)) && !IntRect(542, 410, 280, 96).contains(Mouse::getPosition(Window)) && !IntRect(542, 530, 280, 96).contains(Mouse::getPosition(Window))) { Status = Pause::Empty; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			switch (Status) {
			case Pause::Empty:
				break;
			case Pause::Resume:
				return false;
			case Pause::Restart:
				PlayerScore = PlayerScore2 = GameScore = 0;
				Game = true;
				return true;
			case Pause::Exit:
				PlayerScore = PlayerScore2 = GameScore = 0;
				status = 0;
				return true;
			}
		}

		//���������
		Window.draw(PauseBackground);
		Window.draw(ResumeButton);
		Window.draw(RestartButton);
		Window.draw(ExitButton);
		Window.display();
	}
}

//���� ������ �� ����
void game_over(RenderWindow& Window, int score) {
	Event event;
	sf::Text Winner;
	sf::Text Score;
	bool status_ps = 0;

	//������� �������
	GameOverTexture.loadFromFile("Pictures/GameOver.png");
	GameOver.setTexture(GameOverTexture);
	ExitGameTexture.loadFromFile("Pictures/ExitGame.png");
	ExitGame.setTexture(ExitGameTexture);
	ExitGame.setScale(0.8, 0.8);
	while (Window.isOpen() && status != 0) {
		while (Window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// ����� ��������� ���
				Window.close();
		}

		Font FonT;
		FonT.loadFromFile(FontPath);

		//����������
		Winner.setString(Name);
		Winner.setFont(FonT);
		Winner.setFillColor(sf::Color::Black);
		Winner.setPosition(660, 400);

		//����
		Score.setFont(FonT);
		Score.setString(to_string(PlayerScore * 10));
		Score.setFillColor(sf::Color::Black);
		Score.setPosition(680, 535);

		ExitGame.setPosition(570, 585);
		GameOver.setPosition(450, 100);

		if (IntRect(570, 585, 240, 80).contains(Mouse::getPosition(Window))) { ExitGame.setColor(Color(255, 255, 255, 160)); status_ps = true; }
		if (!IntRect(570, 585, 240, 80).contains(Mouse::getPosition(Window))) { ExitGame.setColor(Color(255, 255, 255, 250)); status_ps = false; }

		if (Mouse::isButtonPressed(Mouse::Left) && status_ps) {
			status = 0;
		}
		Window.draw(GameOver);
		Window.draw(Score);
		Window.draw(Winner);
		Window.draw(ExitGame);
		Window.display();
	}
}



//������� ���������� game_over
void Round_over(RenderWindow& Window, int score) {
	Event event;
	sf::Text Winner;
	sf::Text Score;
	bool status_ps = 0;


	GameOverTexture.loadFromFile("Pictures/RoundOver.png");
	GameOver.setTexture(GameOverTexture);
	ExitGameTexture.loadFromFile("Pictures/Resume_pause.png");
	ExitGame.setTexture(ExitGameTexture);
	ExitGame.setScale(0.8, 0.8);
	while (Window.isOpen() && status != 0) {
		while (Window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// ����� ��������� ���
				Window.close();
		}

		Font FonT;
		FonT.loadFromFile(FontPath);

		//���������� �������
		Winner.setString(to_string(PlayerScore));
		Winner.setFont(FonT);
		Winner.setFillColor(sf::Color::Black);
		Winner.setPosition(680, 400);

		//����
		Score.setFont(FonT);
		Score.setString(to_string(PlayerScore * 10));
		Score.setFillColor(sf::Color::Black);
		Score.setPosition(680, 535);

		ExitGame.setPosition(570, 585);
		GameOver.setPosition(450, 100);

		if (IntRect(570, 585, 240, 80).contains(Mouse::getPosition(Window))) { ExitGame.setColor(Color(255, 255, 255, 160)); status_ps = true; }
		if (!IntRect(570, 585, 240, 80).contains(Mouse::getPosition(Window))) { ExitGame.setColor(Color(255, 255, 255, 250)); status_ps = false; }

		if (Mouse::isButtonPressed(Mouse::Left) && status_ps) {
			return;
		}
		Window.draw(GameOver);
		Window.draw(Score);
		Window.draw(Winner);
		Window.draw(ExitGame);
		Window.display();
	}
}

//��������� ���� � ������������
void game_over_multy(RenderWindow& Window, int score1, int score2) {
	Event event;
	sf::Text Winner;
	sf::Text Score;
	bool status_ps = 0;
	int max_score;
	//������ ��������� ������������� ����������
	bool win = 1;
	if (score1 < score2) win = 0;

	max_score = max(score1, score2);

	GameOverTexture.loadFromFile("Pictures/GameOver.png");
	GameOver.setTexture(GameOverTexture);
	ExitGameTexture.loadFromFile("Pictures/ExitGame.png");
	ExitGame.setTexture(ExitGameTexture);
	ExitGame.setScale(0.8, 0.8);
	while (Window.isOpen() && status != 0) {
		while (Window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// ����� ��������� ���
				Window.close();
		}

		Font FonT;
		FonT.loadFromFile(FontPath);
		if (win) Winner.setString(Name);
		else Winner.setString(Name2);

		Winner.setFont(FonT);
		Winner.setFillColor(sf::Color::Black);
		Winner.setPosition(660, 400);

		Score.setFont(FonT);
		Score.setString(to_string(max_score * 10));
		Score.setFillColor(sf::Color::Black);
		Score.setPosition(680, 535);

		ExitGame.setPosition(570, 585);
		GameOver.setPosition(450, 100);

		if (IntRect(570, 585, 240, 80).contains(Mouse::getPosition(Window))) { ExitGame.setColor(Color(255, 255, 255, 160)); status_ps = true; }
		if (!IntRect(570, 585, 240, 80).contains(Mouse::getPosition(Window))) { ExitGame.setColor(Color(255, 255, 255, 250)); status_ps = false; }

		if (Mouse::isButtonPressed(Mouse::Left) && status_ps) {
			status = 0;
		}
		Window.draw(GameOver);
		Window.draw(Score);
		Window.draw(Winner);
		Window.draw(ExitGame);
		Window.display();
	}
}

enum class PlaneCondition {
	Empty,
	Head,
	Body,
	Apple,
};

enum class Direction {
	Up,
	Down,
	Left,
	Right,
};

struct Cell
{
	int CoordinateX;
	int CoordinateY;
	PlaneCondition Condition;
};

struct Coordinate
{
	unsigned X;
	unsigned Y;
};

class Snake {

protected:
	Cell** plane;
	Direction direction;
	Direction newDirection;
	Sprite BodySprite, HeadSprite, AppleSprite;
	vector<Coordinate> snake;
	int Apples; //���� �� �����

public:

	void grow() {
		unsigned newX(snake[0].X), newY(snake[0].Y);
		plane[newY][newX].Condition = PlaneCondition::Body;
		switch (newDirection)
		{
		case Direction::Up:
			newY--;
			break;
		case Direction::Down:
			newY++;
			break;
		case Direction::Left:
			newX--;
			break;
		case Direction::Right:
			newX++;
			break;
		}
		snake.insert(snake.begin(), { newX, newY });
		plane[newY][newX].Condition = PlaneCondition::Head;
	}

	Snake(Cell** plane, const unsigned startY, const unsigned startX, Direction direction, Sprite HeadSprite, Sprite BodySprite, Sprite AppleSprite) {
		//������� ���������
		this->plane = plane;

		//����������� ��������
		this->direction = this->newDirection = direction;

		//��������� �������
		snake.push_back({ startX , startY });
		this->plane[startY][startX].Condition = PlaneCondition::Head;

		//C����� ���� ����
		this->BodySprite = BodySprite;
		//C����� ������ ����

		this->HeadSprite = HeadSprite;

		//C����� ������
		this->AppleSprite = AppleSprite;

		//������� ����
		Apples = 0;
	}

	int getApples() {
		return Apples;
	}

	void appleSpawn() {

		while (plane[AppleY][AppleX].Condition != PlaneCondition::Empty) {
			AppleX = rand() % CountOfCellsX;
			AppleY = rand() % CountOfCellsY;
		}
		plane[AppleY][AppleX].Condition = PlaneCondition::Apple;
	}

	void control() {
		//���������� �������
		if (direction == Direction::Up || direction == Direction::Down) {
			if (Keyboard::isKeyPressed(MyKeyboard.Left))
				newDirection = Direction::Left;
			if (Keyboard::isKeyPressed(MyKeyboard.Right))
				newDirection = Direction::Right;
		}

		if (direction == Direction::Right || direction == Direction::Left) {
			if (Keyboard::isKeyPressed(MyKeyboard.Up))
				newDirection = Direction::Up;
			if (Keyboard::isKeyPressed(MyKeyboard.Down))
				newDirection = Direction::Down;
		}
	}

	void draw(RenderWindow& Window) {
		AppleSprite.setPosition(plane[AppleY][AppleX].CoordinateX, plane[AppleY][AppleX].CoordinateY);
		Window.draw(AppleSprite);
		HeadSprite.setPosition(plane[snake[0].Y][snake[0].X].CoordinateX, plane[snake[0].Y][snake[0].X].CoordinateY);
		Window.draw(HeadSprite);
		for (unsigned i = 1; i < snake.size(); i++) {
			BodySprite.setPosition(plane[snake[i].Y][snake[i].X].CoordinateX, plane[snake[i].Y][snake[i].X].CoordinateY);
			Window.draw(BodySprite);
		}
	}

	virtual void playerScore() {
		PlayerScore++;
	}

	bool move() {
		const unsigned Last = snake.size() - 1;
		unsigned newX(snake[0].X), newY(snake[0].Y);

		switch (newDirection)
		{
		case Direction::Right:
			newX++;
			break;
		case Direction::Left:
			newX--;
			break;
		case Direction::Down:
			newY++;
			break;
		case Direction::Up:
			newY--;
			break;
		}

		//������ ������������:
		PlaneCondition newHead = plane[newY][newX].Condition;
		if (newHead == PlaneCondition::Body || newHead == PlaneCondition::Head) return false;
		if (newHead == PlaneCondition::Apple) {
			Apples++;
			GameScore++;
			playerScore();
			grow();
			appleSpawn();
			return true;
		}

		//���� ������ �� �������� ��������� ������
		plane[snake[Last].Y][snake[Last].X].Condition = PlaneCondition::Empty;
		//������ ������ ���������� �����
		plane[snake[0].Y][snake[0].X].Condition = PlaneCondition::Body;

		for (int i = Last; i > 0; i--) {
			snake[i].X = snake[i - 1].X;
			snake[i].Y = snake[i - 1].Y;
		}

		snake[0].X = newX;
		snake[0].Y = newY;

		plane[snake[0].Y][snake[0].X].Condition = PlaneCondition::Head;
		direction = newDirection;
		return true;
	}
};

class SnakeBot : public Snake {
	unsigned Recursion = 0;
public:
	SnakeBot(Cell** plane, const unsigned startY, const unsigned startX, Direction direction, Sprite HeadSprite, Sprite BodySprite, Sprite AppleSprite) : Snake(plane, startY, startX, direction, HeadSprite, BodySprite, AppleSprite) {};

	void playerScore() {
		return; //������ ���������������
	}

	void draw(RenderWindow& Window) {
		HeadSprite.setPosition(plane[snake[0].Y][snake[0].X].CoordinateX, plane[snake[0].Y][snake[0].X].CoordinateY);
		Window.draw(HeadSprite);
		for (unsigned i = 1; i < snake.size(); i++) {
			BodySprite.setPosition(plane[snake[i].Y][snake[i].X].CoordinateX, plane[snake[i].Y][snake[i].X].CoordinateY);
			Window.draw(BodySprite);
		}
	}

	void death() {
		for (unsigned i = 0; i < snake.size(); i++) {
			plane[snake[i].Y][snake[i].X].Condition = PlaneCondition::Empty;
		}
	}


	//Dangerous by Erik71Pensian. ������� ����������� ������ ������ ������� ��������
	void Dangerous(int newX, int newY, Direction assumption) {
		PlaneCondition MayBeIGoTo;
		//������������
		if (Recursion == 4) {
			Recursion = 0;
			newDirection = Direction::Up;
			return;
		}
		//������� ��������:
		//� ����� ������ ���� ��������� ��������, ����� ���������� ���� � ������, �� ������� ����������. ������ ������� ������� ������ ������ ������ ����������� � �� ���� ��� �������� ��� ������.
		//���� � �������������� ����������� �������� (����������� ��������� ������� ��� ��������) ������� ���, �� ������� ����� ������� �����������
		//�� ����, �� �������-������
		//� ������ ������� ���������� ������� ���������� ������, �� �������� ��������������� ����������� �������� �� �������� �� ������� �������
		//��� ������ ����� ������������ ������ ������� Recursion ����������. ��� �������� 4 ������ �������, �.�. �� ������ ������
		switch (assumption) {
		case (Direction::Up):
			//�������� ����������� ������ �� ����������� ����� ��������������� ��������
			MayBeIGoTo = this->plane[newY - 1][newX].Condition;

			//� ������ ������ ������ ��� �� �.�.
			if (MayBeIGoTo != PlaneCondition::Body && MayBeIGoTo != PlaneCondition::Head) { Recursion = 0; newDirection = Direction::Up; }
			//����� ����� �������� �������� �����������
			else { Recursion++; (Dangerous(newX, newY, Direction::Right)); }
			break;
		//����� ��� ������ ����������
		case (Direction::Right):
			MayBeIGoTo = this->plane[newY][newX + 1].Condition;
			if (MayBeIGoTo != PlaneCondition::Body && MayBeIGoTo != PlaneCondition::Head) { Recursion = 0; newDirection = Direction::Right; }
			else { Recursion++; (Dangerous(newX, newY, Direction::Down)); }
			break;

		case (Direction::Down):
			MayBeIGoTo = this->plane[newY + 1][newX].Condition;
			if (MayBeIGoTo != PlaneCondition::Body && MayBeIGoTo != PlaneCondition::Head) { Recursion = 0; newDirection = Direction::Down; }
			else { Recursion++; (Dangerous(newX, newY, Direction::Left)); }
			break;

		case (Direction::Left):
			MayBeIGoTo = this->plane[newY][newX - 1].Condition;
			if (MayBeIGoTo != PlaneCondition::Body && MayBeIGoTo != PlaneCondition::Head) { Recursion = 0; newDirection = Direction::Left; }
			else { Recursion++; (Dangerous(newX, newY, Direction::Up)); }
			break;

		}
	}
	
	//�������� ����� � ����� ������ ����������� ����� � ������
	bool control() {
		unsigned newX(snake[0].X);
		unsigned newY(snake[0].Y);
		//��������� �������� ����� ������������ ������ � ������.
		int deltaY = newY - AppleY;
		int deltaX = newX - AppleX;
		if (deltaX == 0) {
			if (deltaY >= 0)
				Dangerous(newX, newY, Direction::Up);
			else
				Dangerous(newX, newY, Direction::Down);
		}
		else {
			if (deltaX > 0) {
				Dangerous(newX, newY, Direction::Left);
			}
			else {
				Dangerous(newX, newY, Direction::Right);
			}
		}
		return true;
	}
};

class Snake2 : public Snake {
public:
	Snake2(Cell** plane, const unsigned startY, const unsigned startX, Direction direction, Sprite HeadSprite, Sprite BodySprite, Sprite AppleSprite) : Snake(plane, startY, startX, direction, HeadSprite, BodySprite, AppleSprite) {};

	void control() {
		//���������� �������
		if (direction == Direction::Up || direction == Direction::Down) {
			if (Keyboard::isKeyPressed(Keyboard::A))
				newDirection = Direction::Left;
			if (Keyboard::isKeyPressed(Keyboard::D))
				newDirection = Direction::Right;
		}

		if (direction == Direction::Right || direction == Direction::Left) {
			if (Keyboard::isKeyPressed(Keyboard::W))
				newDirection = Direction::Up;
			if (Keyboard::isKeyPressed(Keyboard::S))
				newDirection = Direction::Down;
		}
	}

	void playerScore() {
		PlayerScore2++;
	}

	void draw(RenderWindow& Window) {
		HeadSprite.setPosition(plane[snake[0].Y][snake[0].X].CoordinateX, plane[snake[0].Y][snake[0].X].CoordinateY);
		Window.draw(HeadSprite);
		for (unsigned i = 1; i < snake.size(); i++) {
			BodySprite.setPosition(plane[snake[i].Y][snake[i].X].CoordinateX, plane[snake[i].Y][snake[i].X].CoordinateY);
			Window.draw(BodySprite);
		}
	}
};

struct Bot {
	SnakeBot bot;
	bool alive;
};

void singlePlayer(RenderWindow& Window) {

	//��������� ������
	Font font;
	font.loadFromFile(FontPath);
	//����� ����
	Text NameText, AppleText, ScoreText, RoundText;
	//���
	NameText.setFont(font);
	NameText.setFillColor(Color::Black);
	NameText.setCharacterSize(43);
	NameText.setPosition(30, 50);

	//������
	AppleText.setFont(font);
	AppleText.setFillColor(Color::Black);
	AppleText.setPosition(85, 320);
	AppleText.setCharacterSize(43);
	AppleText.setString("0");

	//����
	ScoreText.setFont(font);
	ScoreText.setFillColor(Color::Black);
	ScoreText.setPosition(70, 550);
	ScoreText.setCharacterSize(43);
	ScoreText.setString("0");

	//�����
	RoundText.setFont(font);
	RoundText.setFillColor(Color::Black);
	RoundText.setPosition(120, 705);
	RoundText.setCharacterSize(28);

	srand(time(NULL)); //������������� ��������� ��������� �����
	Clock clock;

	setConfig(); //������������� ���������
	NameText.setString(Name); //������������� ���

	for (int Round = 1; Round <= CountOfRounds; Round++) {

		RoundText.setString(to_string(Round));
		int Speed = StartSpeed; //�������� ������
		float GameTimer = 0; //������ ����

		//C������� ��������� ����
		Cell** Plane = new Cell * [CountOfCellsY];
		for (int i = 0; i < CountOfCellsY; i++) {
			Plane[i] = new Cell[CountOfCellsX];
		}
		//���������� ���������
		for (int i = 0; i < CountOfCellsY; i++) {
			for (int j = 0; j < CountOfCellsX; j++) {
				//���������� ��������� ������
				if ((i == 0) || (i == CountOfCellsY - 1) || (j == 0) || (j == CountOfCellsX - 1))
					Plane[i][j].Condition = PlaneCondition::Body;
				else Plane[i][j].Condition = PlaneCondition::Empty;
				//���������� ���������
				Plane[i][j].CoordinateX = 200 + CellSize * j;
				Plane[i][j].CoordinateY = CellSize * i;
			}
		}

		Snake Player(Plane, 1, CountOfCellsX - 2, Direction::Left, HeadSprite, BodySprite, AppleSprite);
		//��������� �����
		vector<Bot> Bots;
		switch (CountOfBots)
		{
		case 3:
			Bots.push_back({ SnakeBot(Plane, CountOfCellsY - 2, 1, Direction::Right, HeadSpriteBot, BodySprite, AppleSprite), true });
		case 2:
			Bots.push_back({ SnakeBot(Plane, CountOfCellsY - 2, CountOfCellsX - 2, Direction::Left, HeadSpriteBot, BodySprite, AppleSprite), true });
		case 1:
			Bots.push_back({ SnakeBot(Plane, 1, 1, Direction::Right, HeadSpriteBot, BodySprite, AppleSprite), true });
		}

		for (int i = 0; i < 5; i++) { //��������� ���� ����
			Player.grow();
			for (unsigned j = 0; j < Bots.size(); j++) {
				Bots[j].bot.grow();
			}
		}
		AppleX = AppleY = 0;
		Player.appleSpawn();

		while (Window.isOpen()) {

			//���������� �������
			Player.control();
			for (unsigned i = 0; i < Bots.size(); i++) {
				if (Bots[i].alive) {
					Bots[i].bot.control();
				}
			}

			float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
			clock.restart(); //������������� �����
			time = time / 800; //�������� ����
			GameTimer += time;

			Speed = StartSpeed - SpeedCoeff * GameScore;
			if (Speed < 100) Speed = 100;
			if (GameTimer > Speed) {
				if (!Player.move()) { //�������� ������������
					delete[] Plane;
					//������� ������
					if (Round != CountOfRounds) Round_over(Window, PlayerScore);
					GameScore = 0;
					break;
				}

				//�������� �����
				for (unsigned i = 0; i < Bots.size(); i++) {
					if (Bots[i].alive) {
						if (!Bots[i].bot.move()) {
							Bots[i].alive = false;
							Bots[i].bot.death();
						}
					}
				}

				AppleText.setString(to_string(Player.getApples()));
				ScoreText.setString(to_string(PlayerScore * 10));
				GameTimer = 0; //�������� ������
			}

			//�����
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {
				if (pause(Window)) return;
			}

			//���������
			Window.clear();
			Window.draw(MapBackgroundSprite);
			Player.draw(Window);
			for (unsigned i = 0; i < Bots.size(); i++) {
				if (Bots[i].alive) {
					Bots[i].bot.draw(Window);
				}
			}
			Window.draw(NameText);
			Window.draw(AppleText);
			Window.draw(ScoreText);
			Window.draw(RoundText);
			Window.display();
			Event event;

			while (Window.pollEvent(event)) {
				if (event.type == Event::Closed)
					Window.close();
			}
		}
	}
	game_over(Window, PlayerScore);
	PlayerScore = 0;
}

class Obstacle {
	Cell** Plane;
	int Count;
	vector<Coordinate> Obstacles;
public:

	Obstacle(Cell** Plane, int Count) {
		this->Plane = Plane;
		this->Count = Count;
		unsigned X(0), Y(0);
		for (unsigned i = 0; i < Count; i++) {
			while (Plane[Y][X].Condition != PlaneCondition::Empty || Y == 1 || Y == (CountOfCellsY - 2)) {
				X = rand() % CountOfCellsX;
				Y = rand() % CountOfCellsY;
			}
			Plane[Y][X].Condition = PlaneCondition::Body;
			Obstacles.push_back({ X, Y });
		}
	}

	void drow(RenderWindow& Window) {
		for (unsigned i = 0; i < Count; i++) {
			BodySprite.setPosition(Plane[Obstacles[i].Y][Obstacles[i].X].CoordinateX, Plane[Obstacles[i].Y][Obstacles[i].X].CoordinateY);
			Window.draw(BodySprite);
		}
	}
};

void multyPlayer(RenderWindow& Window) {

	//��������� ������
	Font font;
	font.loadFromFile(FontPath);

	//����� ����
	Text NameText, NameText2, ScoreText, ScoreText2;

	//���
	NameText.setFont(font);
	NameText.setFillColor(Color::Black);
	NameText.setCharacterSize(43);
	NameText.setPosition(30, 117);

	//���2
	NameText2.setFont(font);
	NameText2.setFillColor(Color::Black);
	NameText2.setCharacterSize(43);
	NameText2.setPosition(30, 402);

	//����
	ScoreText.setFont(font);
	ScoreText.setFillColor(Color::Black);
	ScoreText.setPosition(70, 238);
	ScoreText.setCharacterSize(43);
	ScoreText.setString("0");

	//����2
	ScoreText2.setFont(font);
	ScoreText2.setFillColor(Color::Black);
	ScoreText2.setPosition(70, 522);
	ScoreText2.setCharacterSize(43);
	ScoreText2.setString("0");

	srand(time(NULL)); //������������� ��������� ��������� �����
	Clock clock;

	setConfigMul(); //������������� ���������
	NameText.setString(Name); //������������� ���
	NameText2.setString(Name2); //������������� ���

	int Speed = StartSpeed; //�������� ������
	float GameTimer = 0; //������ ����

	//C������� ��������� ����
	Cell** Plane = new Cell * [CountOfCellsY];
	for (int i = 0; i < CountOfCellsY; i++) {
		Plane[i] = new Cell[CountOfCellsX];
	}
	//���������� ���������
	for (int i = 0; i < CountOfCellsY; i++) {
		for (int j = 0; j < CountOfCellsX; j++) {
			//���������� ��������� ������
			if ((i == 0) || (i == CountOfCellsY - 1) || (j == 0) || (j == CountOfCellsX - 1))
				Plane[i][j].Condition = PlaneCondition::Body;
			else Plane[i][j].Condition = PlaneCondition::Empty;
			//���������� ���������
			Plane[i][j].CoordinateX = 200 + CellSize * j;
			Plane[i][j].CoordinateY = CellSize * i;
		}
	}

	Snake Player(Plane, 1, CountOfCellsX - 2, Direction::Left, HeadSprite, BodySprite, AppleSprite);
	Snake2 Player2(Plane, CountOfCellsY - 2, 1, Direction::Right, HeadSprite2, BodySprite, AppleSprite);
	Obstacle GameObstacle(Plane, 25); //�����������

	for (int i = 0; i < 5; i++) { //��������� ���� ����
		Player.grow();
		Player2.grow();
	}
	AppleX = AppleY = 0;
	Player.appleSpawn();

	while (Window.isOpen()) {

		//���������� �������
		Player.control();
		Player2.control();

		float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		clock.restart(); //������������� �����
		time = time / 800; //�������� ����
		GameTimer += time;

		Speed = StartSpeed - SpeedCoeff * GameScore;
		if (Speed < 100) Speed = 100;
		if (GameTimer > Speed) {

			//�������� �������
			if (!Player.move()) { //�������� ������������
				delete[] Plane; //������� ������
				GameScore = 0;
				break;
			}

			if (!Player2.move()) { //�������� ������������
				delete[] Plane; //������� ������
				GameScore = 0;
				break;
			}

			ScoreText.setString(to_string(PlayerScore * 10));
			ScoreText2.setString(to_string(PlayerScore2 * 10));
			GameTimer = 0; //�������� ������
		}

		//�����
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			if (pause(Window)) return;
		}

		//���������
		Window.clear();
		Window.draw(MapBackgroundSprite);
		Player.draw(Window);
		Player2.draw(Window);
		GameObstacle.drow(Window);
		Window.draw(NameText);
		Window.draw(NameText2);
		Window.draw(ScoreText);
		Window.draw(ScoreText2);
		Window.display();

		Event event;
		while (Window.pollEvent(event)) {
			if (event.type == Event::Closed)
				Window.close();
		}
	}
	game_over_multy(Window, PlayerScore, PlayerScore2);
	PlayerScore = PlayerScore2 = 0;
}

void singlePlayerGame(RenderWindow& Window) {
	while (Game) {
		Game = false;
		singlePlayer(Window);
	}
	Game = true;
}

void multyPlayerGame(RenderWindow& Window) {
	while (Game) {
		Game = false;
		multyPlayer(Window);
	}
	Game = true;
}