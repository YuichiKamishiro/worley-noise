#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

using namespace sf;

const int WIDTH = 500;
const int HEIGHT = 500;
const int POINTS = 20;

// calculate distance between two points
float distance(float x1, float y1, float x2, float y2)
{
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

int main()
{
    srand(time(0));
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Window");

    // image for pixel by pixels
    Image img;
    img.create(WIDTH, HEIGHT, Color::White);

    CircleShape points[POINTS];

    for (int i = 0; i < POINTS; i++)
    {
        int x = rand() % WIDTH + 0;
        int y = rand() % HEIGHT + 0;
        CircleShape point(8);
        point.setPosition(x, y);
        point.setFillColor(Color::Green);
        points[i] = point;
    }

    for (size_t x = 1; x < WIDTH; x += 3)
    {
        for (size_t y = 1; y < HEIGHT; y += 3)
        {
            float distances[POINTS];
            for (int i = 0; i < POINTS; i++)
            {
                float d = distance(x, y, points[i].getPosition().x, points[i].getPosition().y);
                distances[i] = d;
            }
            std::sort(distances, distances + POINTS);
            float d = distances[0];
            float c = (d / 700) * 255.0;

            for (int xx = -1; xx <= 1; xx++)
            {
                for (int yy = -1; yy <= 1; yy++)
                {
                    img.setPixel(x + xx, y + yy, Color(c, c, c));
                }
            }
        }
    }

    sf::Texture t;
    t.loadFromImage(img);
    Sprite s;
    s.setTexture(t);

    Clock clock;
    float elapsedTime = 0.f;
    while (window.isOpen())
    {

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        elapsedTime += clock.getElapsedTime().asSeconds();
        clock.restart();
        std::cout << elapsedTime << std::endl;

        if (elapsedTime >= 0.01)
        {
            for (int i = 0; i < POINTS; i++)
            {
                elapsedTime = 0;
                float x = rand() % 20 + (-10);
                float y = rand() % 20 + (-10);
                points[i].move(x, y);
            }
        }

        for (size_t x = 1; x < WIDTH; x += 3)
        {
            for (size_t y = 1; y < HEIGHT; y += 3)
            {
                float distances[POINTS];
                for (int i = 0; i < POINTS; i++)
                {
                    float d = distance(x, y, points[i].getPosition().x, points[i].getPosition().y);
                    distances[i] = d;
                }
                std::sort(distances, distances + POINTS);
                float d = distances[0];
                float c = (d / 700) * 255.0;

                for (int xx = -1; xx <= 1; xx++)
                {
                    for (int yy = -1; yy <= 1; yy++)
                    {
                        img.setPixel(x + xx, y + yy, Color(c, c, c));
                    }
                }
            }
        }
        sf::Texture t;
        t.loadFromImage(img);
        Sprite s;
        s.setTexture(t);

        window.clear(Color::Black);
        window.draw(s);

        window.display();
    }
}
