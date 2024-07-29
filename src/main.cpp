#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

using namespace sf;

const int WIDTH = 1280;
const int HEIGHT = 720;
const int POINTS = 10;
const int GRID = 3;

// calculate distance between two points
float distance(float x1, float y1, float x2, float y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

int main() {
    srand(time(0));
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Window");

    // image for pixel by pixels 
    Image img;
    img.create(WIDTH, HEIGHT, Color::White);

    std::vector<CircleShape> points;

    for(int i = 0; i < POINTS; i++) {
        int x = rand() % WIDTH + 0;
        int y = rand() % HEIGHT + 0;
        CircleShape point(8);
        point.setPosition(x, y);
        point.setFillColor(Color::Green);
        points.push_back(point);
    }

    for (size_t x = 0; x < WIDTH; x += GRID) {
        for (size_t y = 0; y < HEIGHT; y += GRID) {
            float distances[POINTS];
            for(int i = 0; i < POINTS; i++) {
                float d = distance(x, y, points[i].getPosition().x, points[i].getPosition().y);
                distances[i] = d;
            }
            std::sort(distances, distances + POINTS);
            float d = distances[0];
            float c = (d / 700) * 255.0;
            
            for (size_t xx = 0; xx < GRID; xx++) {
            for (size_t yy = 0; yy < GRID; yy++) {
                img.setPixel(x + xx, y + yy, Color(c, c, c));
            }}
        }
    }
    
    sf::Texture t;
    t.loadFromImage(img);
    Sprite s;
    s.setTexture(t);
    
    while(window.isOpen()) {
        Event event;
        
        while(window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::Black);
        window.draw(s);
        for(int i = 0; i < POINTS; i++) {
            window.draw(points[i]);
        }    

        window.display();
    }  
}
