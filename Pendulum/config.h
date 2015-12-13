#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

struct Config {
	Config() {};
	sf::RenderWindow window;
	sf::ContextSettings settings;
	float lastRotate;
	bool isMoveGears;
	float startPosX;
	float startPosY;
	float speed;
	float speed0;
	float deltaTime;
	float g;
	float accelerationError; // погрешность
	float isBoost;
	float isClockwiseMotion;
	float deltaFi;
	sf::ConvexShape pendulPast1;
	sf::ConvexShape pendulPast2;
	sf::CircleShape pendulPast3;
	sf::ConvexShape gear1;
	sf::ConvexShape gear2;
};