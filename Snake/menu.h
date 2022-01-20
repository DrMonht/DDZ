#pragma once
#include"Settings.h"

//Функция вызова м=меню
using namespace sf;

//Логические переменные для опознания нужного окна
bool isMenu = 1;
int menuNum = 0;
extern int status;

void menu(RenderWindow& window) {
	Texture SinglePlayerButtonTexture, OptionsButtonTexture, ExitButtonTexture, aboutTexture, menuBackgroundTexture , MultyPlayerButtonTexture;
	//Загрузка текстур
	SinglePlayerButtonTexture.loadFromFile("Pictures/111.png");
	MultyPlayerButtonTexture.loadFromFile("Pictures/multi.png");
	OptionsButtonTexture.loadFromFile("Pictures/222.png");
	ExitButtonTexture.loadFromFile("Pictures/333.png");
	menuBackgroundTexture.loadFromFile("Pictures/background.png");
	Sprite SinglePlayerButton(SinglePlayerButtonTexture), MultyPlayerButton(MultyPlayerButtonTexture), OptionsButton(OptionsButtonTexture), ExitButton(ExitButtonTexture), about(aboutTexture), menuBg(menuBackgroundTexture);

	SinglePlayerButton.setPosition(20, 50);
	MultyPlayerButton.setPosition(20, 170);
	OptionsButton.setPosition(20, 300);
	ExitButton.setPosition(20, 600);
	menuBg.setPosition(0, 0);
	SinglePlayerButton.setColor(Color::White);
	OptionsButton.setColor(Color::White);
	ExitButton.setColor(Color::White);
	
	if (IntRect(20, 50, 320, 110).contains(Mouse::getPosition(window))) { SinglePlayerButton.setColor(Color(105, 101, 101, 160)); menuNum = 1;}
	if (IntRect(20, 170, 320, 110).contains(Mouse::getPosition(window))) { MultyPlayerButton.setColor(Color(105, 101, 101, 160)); menuNum = 4; }
	if (IntRect(20, 300, 320, 110).contains(Mouse::getPosition(window))) { OptionsButton.setColor(Color(105, 101, 101, 160)); menuNum = 2;}
	if (IntRect(20, 600, 320, 110).contains(Mouse::getPosition(window))) { ExitButton.setColor(Color(105, 101, 101, 160)); menuNum = 3;}
	if (!IntRect(20, 50, 320, 110).contains(Mouse::getPosition(window)) && !IntRect(20, 170, 320, 110).contains(Mouse::getPosition(window)) && !IntRect(20, 300, 320, 110).contains(Mouse::getPosition(window)) && (!IntRect(20, 600, 320, 110).contains(Mouse::getPosition(window)))) { menuNum = 0; }
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (menuNum == 1) { status = 1; }
		if (menuNum == 2) { status = 2; }
		if (menuNum == 3) { status = 3; }
		if (menuNum == 4) { status = 4; }
	}

	window.draw(menuBg);
	window.draw(SinglePlayerButton);
	window.draw(MultyPlayerButton);
	window.draw(OptionsButton);
	window.draw(ExitButton);
	window.display();
}