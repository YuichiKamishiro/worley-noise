#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

using namespace sf;

const int WIDTH = 1280;
const int HEIGHT = 720;

int main() {
    srand(time(0));
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Window");

    while(window.isOpen()) {
        Event event;
        
        while(window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear();

        Image img;
        img.create(WIDTH, HEIGHT, Color::Black);

        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                int r = rand() % 2 + 0;
                img.setPixel(j, i, Color(r * 255, r * 255, r * 255));
            }
        }
        Texture texture;
        texture.loadFromImage(img);
        Sprite sprite(texture);


        window.draw(sprite);        

        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }  
}
