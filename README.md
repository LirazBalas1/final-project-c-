##Monopoly Game Project

Overview

This project is a C++ implementation of the classic Monopoly game with a graphical interface (GUI) using the SFML library. The game supports 2 to 8 players and follows the standard rules of Monopoly, including property management, rent payment, and other game mechanics. Players can move around the board, buy properties, build houses and hotels, and collect rent. The winner is the last player standing or the first to reach 4000 in cash.

Features

    Dynamic Board: The board consists of 40 spaces, including properties, railroads, utilities, and special spaces (e.g., Go, Jail, Free Parking).
    Properties: Players can buy, build houses, and hotels. Rent is increased based on the number of houses or hotels.
    Special Squares: Includes Go, Jail, Free Parking, Chance, Community Chest, and Income Tax.
    Chance and Community Chest: Players can draw cards that offer random effects (e.g., receiving money, paying fines, or going to jail).
    Jail Mechanics: Players can be sent to jail and must either roll doubles, use a "Get Out of Jail Free" card, or pay a fine to get out.
    Graphical Interface: The game includes a graphical user interface built with SFML, displaying the board, player statistics, and dice rolls.
    Multi-player Support: Supports 2 to 8 players playing on the same machine.

Requirements

To build and run this project, you need the following dependencies:

    C++11 or later
    SFML 2.5.1 (Simple and Fast Multimedia Library)
    A compiler that supports C++11 (e.g., g++)

Installation

    Clone the repository:

    bash

git clone https://github.com/your-username/monopoly-game.git
cd monopoly-game

Install SFML:

    On Ubuntu:

    bash

    sudo apt-get install libsfml-dev

    On other platforms, refer to SFML's official website for installation instructions.

#Compile the project using: 

make ,for all files


make run,Running the Game

make test,

make test_run

Controls and Gameplay

    Players take turns rolling the dice, moving their token, and interacting with properties.
    Use the graphical interface to view current player statistics, including balance and owned properties.
    Follow the prompts on the screen to buy properties, pay rent, and handle special actions (such as going to jail or drawing chance cards).

Files and Structure

    main.cpp: The entry point of the game, responsible for initializing the game loop.
    
    Player.cpp/Player.hpp: Manages the player, including balance, properties, and movements.
    
    Board.cpp/Board.hpp: Manages the game board and squares.
    
    Square.cpp/Square.hpp: Base class for all squares on the board, including properties and special squares.
    
    StreetSquare.cpp/StreetSquare.hpp: A derived class from Square for property squares (streets).
    
    RailroadSquare.cpp/RailroadSquare.hpp: A derived class from Square for railroad squares.
    
    UtilitySquare.cpp/UtilitySquare.hpp: A derived class from Square for utility squares.
    
    Dice.cpp/Dice.hpp: Manages the dice rolling and rendering.
    
    GameController.cpp/GameController.hpp: Controls the flow of the game, including player turns, rolling dice, and handling game logic.
    
    Card.cpp/Card.hpp: Represents Chance and Community Chest cards.
    
    makefile: Used to compile the project
