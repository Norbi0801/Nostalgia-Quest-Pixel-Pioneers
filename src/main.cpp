#include <SFML/Graphics.hpp>
#include "Game/Game.hpp"


int main(int argc, char *argv[]) {
    Game game;
    while(!game.GetWindow()->IsDone()){
        game.Update();
        game.Render();
        game.Render();
        sf::sleep(sf::seconds(0.2));
        game.RestartClock();
    }
}
