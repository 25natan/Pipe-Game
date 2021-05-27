#pragma once
#include <SFML/Graphics.hpp>


struct Resources {
	Resources()
	{
		pipeStreightOn.loadFromFile("pipeStreightOn.png");
		pipeStreightOff.loadFromFile("pipeStreightOff.png");
		pipeCurvedOn.loadFromFile("pipeCurvedOn.png");
		pipeCurvedOff.loadFromFile("pipeCurvedOff.png");
		pipeTon.loadFromFile("pipeTon.png");
		pipeToff.loadFromFile("pipeToff.png");
		pipeCrossOn.loadFromFile("pipeCrossOn.png");
		pipeCrossOff.loadFromFile("pipeCrossOff.png");
		sinkOn.loadFromFile("sinkOn.png");
		sinkOff.loadFromFile("sinkOff.png");
		tap.loadFromFile("tap.png");
		background.loadFromFile("background.png");
	}
	sf::Texture pipeStreightOn, pipeStreightOff, pipeCurvedOn, pipeCurvedOff, pipeTon,
		pipeToff, pipeCrossOn, pipeCrossOff, sinkOn, sinkOff, tap, background;

};