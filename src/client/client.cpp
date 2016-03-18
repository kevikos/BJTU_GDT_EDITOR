#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "../lib/SocketAPI/SocketTCPClient.hpp"
#include "../lib/SocketAPI/Select/FDSet/FDSet.hpp"
#include "../lib/SocketAPI/Select/Select.hpp"
#include <SFML/Graphics.hpp>

int main(int ac, char **av) {
    SocketTCPClient client;

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML color game");
    sf::CircleShape shape(400.f);
    sf::CircleShape shape2(300.f);
    sf::CircleShape shape3(200.f);

    sf::Color color;
    sf::Color color2;
    sf::Color color3;

    if (ac != 4)
    {
	std::cout << "./client host port name" << std::endl;
	return (0);
    }
    client.start();
    client.connectToServer(av[1], atoi(av[2]));
    color = sf::Color::Red;
    color2 = sf::Color::Yellow;
    color3 = sf::Color::Green;
    shape.setFillColor(color);
    shape2.setFillColor(color2);
    shape3.setFillColor(color3);

    FDSet fdSet;
    char buff[1024];
    std::string entry;
    int nbRead;

    while (window.isOpen())
    {
	fdSet.zero();
	fdSet.set(&client);
	fdSet.set(0);
	Select::call(&fdSet, NULL);
	if (fdSet.isset(&client))
	{
	    if ((nbRead = client.receive(buff, 1024)) == 0)
	    {
		client.close();
		std::cout << "Server left" << std::endl;
		return 0;
	    }
	    if (std::string(buff) == "BIENVENU")
	    {
		client.send(("player|" + std::string(av[3])).c_str(), 7 + std::string(av[3]).length());
	    }
	    else if (std::string(buff) == "kick")
	    {
		std::cout << "You are kicked by server" << std::endl;
		return (0);
	    }
	    else if (std::string(buff) == "1")
	    {
		color = sf::Color::Blue;
		color2 = sf::Color::Red;
		color3 = sf::Color::Yellow;

		shape.setFillColor(color);
		shape2.setFillColor(color2);
		shape3.setFillColor(color3);

	    }
	    else if (std::string(buff) == "2")
	    {
		color = sf::Color::Black;
		color2 = sf::Color::White;
		color3 = sf::Color::Blue;

		shape.setFillColor(color);
		shape2.setFillColor(color2);
		shape3.setFillColor(color3);

	    }
	    else if (std::string(buff) == "3")
	    {
		color = sf::Color::Red;
		color2 = sf::Color::Yellow;
		color3 = sf::Color::Green;
		shape.setFillColor(color);
		shape2.setFillColor(color2);
		shape3.setFillColor(color3);

	    }
	    std::cout << "msg : " << buff << std::endl;
	    memset(buff, 0, 1024);
	}
	if (fdSet.isset(0))
	{
	    std::getline(std::cin, entry);
	    client.send(entry.c_str(), entry.length());
	}
	sf::Event event;
	while (window.pollEvent(event))
	{
	    if (event.type == sf::Event::Closed)
		window.close();
	}
	window.clear();
	window.draw(shape);
	window.draw(shape2);
	window.draw(shape3);
	window.display();
    }
}
