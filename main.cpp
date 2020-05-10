#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <math.h>
#include "menu.h"
#include "Game.h"
#define SFML_NO_DEPRECATED_WARNINGS

int main() {
    enum State {sMenu, Options, Game};
    enum State2 {Decide,DoNothing};
    State saved = sMenu;
    State2 Decision = DoNothing;
    int DealerCards = 0;
    int PlayerCards = 0;
// initalizing window display
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window;
// Display the list of all the video modes available for fullscreen
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::size_t i = 0; i < modes.size(); ++i) {
        sf::VideoMode mode = modes[i];
        std::cout << "Mode #" << i << ": "
                  << mode.width << "x" << mode.height << " - "
                  << mode.bitsPerPixel << " bpp" << std::endl;
    }

// Create a window with the same pixel depth, width and height as the desktop
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "BlackJack", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true); // call it once, after creating the window

//Create Main Menu Class
    Menu MainMenu(window.getSize().x, window.getSize().y,window);
//Create MainDeck Class
    Deck MainDeck;
//Create Play Class
    class Game Play(window);

//General Input Flow
    while(window.isOpen()) {
        sf::Event event;

// while there are pending events...
        while (window.pollEvent(event)) {

            switch (saved) {
                case sMenu:
                    // check the type of the event...
                    switch (event.type) {
                        // window closed
                        case sf::Event::Closed:
                            std::cout << "Window has been closed, program ended" << std::endl;
                            window.close();
                            break;
                        case sf::Event::KeyPressed:
                            switch (event.key.code) {
                                case sf::Keyboard::Up:
                                    MainMenu.MoveUp();
                                    break;

                                case sf::Keyboard::Down:
                                    MainMenu.MoveDown();
                                    break;

                                case sf::Keyboard::Return:
                                    switch (MainMenu.GetSelectedItem()) {
                                        case 0:
                                            std::cout << "Play button has been pressed" << std::endl;
                                            saved = Game;
                                            //Add Code to Change to Play State
                                            break;
                                        case 1:
                                            std::cout << "Option button has been pressed" << std::endl;
                                            //saved = Options;
                                            //Add Code to Change to Option State
                                            break;
                                        case 2:
                                            window.close();
                                            break;
                                    }
                                    break;
                            }
                            break;
                    }
                    break;
                case Options:;
                case Game:
                    switch (Decision) {
                        case DoNothing:
                            break;
                        case Decide:
                            switch (event.type) {
                                case sf::Event::KeyPressed:
                                    switch (event.key.code) {
                                        case sf::Keyboard::Q:
                                            //MAKE IT HIT
                                            break;
                                        case sf::Keyboard::Space:
                                            //MAKE IT NOT HIT
                                            break;
                                    }
                                    break;
                            }
                     break;
                    }
            }
        }
if (saved == sMenu) {
    window.clear(sf::Color::Black);

    MainMenu.draw(window);

    window.display();
}
else if (saved == Options) {

}
else if (saved == Game) {
//IMPLEMENT GAME LOGIC ALL HERE? LOL I GUESS
    if( DealerCards == 0) {
        MainDeck.CheckCard(window,0);
        MainDeck.CheckCard(window,1);
        DealerCards = 2;
    }

    if( PlayerCards == 0) {
        MainDeck.CheckCard(window,5);
        MainDeck.CheckCard(window,6);
        PlayerCards = 2;
    }

//WAIT FOR OPTION
//IMPLEMENT HIT/STAY COMMAND
//going to want to do switch command to determine exactly what to do, enum for hit stay perhaps?
//while(decision == 0) {
//if(hit) {

//}

//if(stay) {



//}

//CALCULATIONS TO DETERMINE THE WINNER

//RESET

    window.clear(sf::Color::Black);
    Play.draw(window); //Draws Background
    //Can Change card location by changing num (We will have dealer location, player locations, etc....)
    window.draw(MainDeck.CardDisplay[0]);
    window.draw(MainDeck.CardDisplay[1]);
    window.draw(MainDeck.CardDisplay[5]);
    window.draw(MainDeck.CardDisplay[6]);
    window.display();

}

    }
    return 0;
}