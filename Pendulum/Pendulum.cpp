#include "stdafx.h"
#include "config.h"


sf::ConvexShape createGear(int radius, int pointCount, int deltaRad) {
	sf::ConvexShape gear;
	int delataFi = 360 / pointCount;
	gear.setPointCount(pointCount + 1);
	gear.setPoint(0, sf::Vector2f(0, 0));
	for (int i = 0; i <= pointCount; i++) {
		if (i % 2 == 1) {
			gear.setPoint(i, sf::Vector2f((float)(radius * cos(delataFi * i * M_PI / 180)), (float)(radius * sin(delataFi * i * M_PI / 180))));
		}
		else {
			gear.setPoint(i, sf::Vector2f((float)((radius + deltaRad) * cos(delataFi * i * M_PI / 180)), (float)((radius + deltaRad) * sin(delataFi * i * M_PI / 180))));
		}
	}
	return gear;
}

sf::ConvexShape pendulPast1(Config & conf) {
	sf::ConvexShape pendulPast1;
	pendulPast1.setPointCount(6);
	pendulPast1.setPoint(0, sf::Vector2f(0, 0));
	pendulPast1.setPoint(1, sf::Vector2f(40, 10));
	pendulPast1.setPoint(2, sf::Vector2f(60, 50));
	pendulPast1.setPoint(3, sf::Vector2f(0, 10));
	pendulPast1.setPoint(4, sf::Vector2f(-60, 50));
	pendulPast1.setPoint(5, sf::Vector2f(-40, 10));
	pendulPast1.setPosition(conf.startPosX, conf.startPosY);
	pendulPast1.setFillColor(sf::Color(255, 69, 0));
	return pendulPast1;
}

sf::ConvexShape pendulPast2(Config & conf) {
	sf::ConvexShape pendulPast2;
	pendulPast2.setPointCount(5);
	pendulPast2.setPoint(0, sf::Vector2f(0, 0));
	pendulPast2.setPoint(1, sf::Vector2f(5, 10));
	pendulPast2.setPoint(2, sf::Vector2f(2, 160));
	pendulPast2.setPoint(3, sf::Vector2f(-2, 160));
	pendulPast2.setPoint(4, sf::Vector2f(-5, 10));
	pendulPast2.setPosition(conf.startPosX, conf.startPosY);
	pendulPast2.setFillColor(sf::Color(255, 69, 0));
	return pendulPast2;
}

sf::CircleShape pendulPast3(Config & conf) {
	sf::CircleShape pendulPast3(25);
	pendulPast3.setPosition(conf.startPosX, conf.startPosY);
	pendulPast3.setFillColor(sf::Color(255, 0, 0));
	pendulPast3.setOrigin(25, -150);
	return pendulPast3;
}

void dataInit(Config & conf) {
	conf.accelerationError = 0.000000000005f;
	conf.settings.antialiasingLevel = 12;
	conf.isMoveGears = false;
	conf.lastRotate = 320;
	conf.startPosX = 400;
	conf.startPosY = 200;
	conf.speed = 0;
	conf.speed0 = 0;
	conf.gravity = 9.4f;
	conf.isBoost = 1;
	conf.isClockwiseMotion = -1;
	conf.window.create(sf::VideoMode(800, 600), "Pendulum", sf::Style::Default, conf.settings);
	conf.pendulPast1 = pendulPast1(conf);
	conf.pendulPast2 = pendulPast2(conf);
	conf.pendulPast3 = pendulPast3(conf);
	conf.gear1 = createGear(50, 72, 20);
	conf.gear2 = createGear(30, 90, 10);
}

void movePendulumAndGear(Config & conf) {
	if (conf.speed <= 0) {
		conf.isClockwiseMotion = conf.isClockwiseMotion * -1;
		conf.isBoost = 1;
		conf.speed0 = 0;
	}
	conf.isMoveGears = true;
	if ((conf.pendulPast1.getRotation() < 350) && (conf.pendulPast1.getRotation() > 330))
		conf.isMoveGears = false;
	conf.speed = conf.speed0 + conf.gravity * conf.isBoost *  conf.deltaTime;
	conf.speed0 = conf.speed;
	conf.deltaFi = (float)(2 * M_PI * conf.speed * conf.deltaTime * conf.isClockwiseMotion * conf.accelerationError);
	conf.pendulPast1.rotate(conf.deltaFi);
	conf.pendulPast2.rotate(conf.deltaFi);
	conf.pendulPast3.rotate(conf.deltaFi);
	if (abs(conf.lastRotate - conf.pendulPast1.getRotation()) > 300)
		conf.isBoost = -1;
	if (conf.isMoveGears) {
		conf.gear1.rotate(-0.2f);
		conf.gear2.rotate(0.2f);
	}
	conf.lastRotate = conf.pendulPast1.getRotation();
}

void drawing(Config & conf) {
	conf.window.clear();
	conf.window.draw(conf.pendulPast1);
	conf.window.draw(conf.pendulPast2);
	conf.window.draw(conf.pendulPast3);
	conf.window.draw(conf.gear1);
	conf.window.draw(conf.gear2);
	conf.window.display();
}

void pendulum(Config & conf) {
//---------------------------маятник стартовая позиция-------------------------	
	conf.gear1.setFillColor(sf::Color(0, 255, 0));
	conf.gear1.setPosition(conf.startPosX - 65, conf.startPosY + 130);
	conf.gear2.setFillColor(sf::Color(0, 0, 255));
	conf.gear2.setPosition(conf.startPosX - 165, conf.startPosY + 90);

	conf.pendulPast1.setRotation(-20);
	conf.pendulPast2.setRotation(-20);
	conf.pendulPast3.setRotation(-20);
//-----------------------------------------------------------------------
	sf::Clock clock;
	conf.window.create(sf::VideoMode(800, 600), "Pendulum", sf::Style::Default, conf.settings);
	while (conf.window.isOpen()) {
		conf.deltaTime = (float)clock.getElapsedTime().asMicroseconds();
		clock.restart();
		sf::Event event;
		while (conf.window.pollEvent(event)) {
			if (event.type == sf::Event::Closed ||	(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				conf.window.close();
		}
		movePendulumAndGear(conf);
		drawing(conf);
		sf::sleep(sf::microseconds((sf::Int64)(1000000 / 60.0) - clock.getElapsedTime().asMicroseconds()));
	}	
}

int main()
{
	Config conf;
	dataInit(conf);
	pendulum(conf);
    return 0;
}
