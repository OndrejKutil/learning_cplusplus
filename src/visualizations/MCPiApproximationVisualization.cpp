#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include <array>
#include <limits>
#include <algorithm>
#include <SFML/Graphics.hpp>

/*
In this project we visualize the Monte Carlo method for approximating Pi.
We generate random points in a unit square and determine how many fall within a quarter circle inscribed within that square.
The ratio of points inside the circle to the total number of points, multiplied by 4, approximates Pi.
The visualization animates the point generation process and displays real-time statistics including the current Pi estimate and FPS.
This implementation uses SFML for rendering
*/

struct Pt {
    std::array<double, 2> coords;
    bool inside;
};

// Class to approximate Pi using Monte Carlo method
// For this file we mainly use it to generate points for the animation
class PiApproximation {
    private:

        int samples_;
        std::vector<Pt> points_;

        static double random_double(double lowerBound, double upperBound) {
            // Validate input bounds
            if (lowerBound > upperBound) {
                throw std::invalid_argument("lowerBound must be less than or equal to upperBound");
            }
            if (lowerBound == upperBound) {
                return lowerBound; // closed interval degenerates to a single value
            }
            
            static std::random_device rd;
            static thread_local std::mt19937 eng(rd());

            // normally real distribution is [a, b), thats why we use nextafter to include upperBound
            std::uniform_real_distribution<double> distr(lowerBound, std::nextafter(upperBound, std::numeric_limits<double>::infinity()));

            return distr(eng);
        }

        double calculateDistanceFromOrigin(const std::array<double, 2>& point) {
            // hypot is more numerically stable than manual sqrt(x*x + y*y)
            return std::hypot(point[0], point[1]);
        }

        bool inside(const std::array<double, 2>& point) {
            return calculateDistanceFromOrigin(point) <= 1.0;
        }

        void generatePoints() {
            int lowerBound = 0;
            int upperBound = 1;

            for (int i = 0; i < this->samples_; i++) {
                Pt point;
                point.coords = { random_double(lowerBound, upperBound), random_double(lowerBound, upperBound) };
                point.inside = inside(point.coords);
                this->points_.push_back(point);
            }
        }

    public:

        // Constructor
        PiApproximation(int samples) : samples_(samples) {
            if (samples <= 0) {
                throw std::invalid_argument("Number of samples must be positive");
            }
            generatePoints();
        }

        // Destructor
        ~PiApproximation() = default;

        // -- APIs --
        std::vector<Pt>& getPoints() {
            return this->points_;
        }

        void resetPoints() {
            this->points_.clear();
            generatePoints();
        }
};


int main() {

    // -- Setup simulation parameters --
    const int nSamples = 10000000;
    const int pointsPerPixel = 100; // how many points fit in one pixel
    const float rectangleSize = 500.0f;
    const float pointsPerSecond = 1000.0f; // Speed of animation

    // -- Generate points --
    PiApproximation piApprox(nSamples);
    std::vector<Pt>& points = piApprox.getPoints();

    // -- Setup SFML -- 
    // Create a window (SFML 3.x uses Vector2u for size)
    sf::RenderWindow window(sf::VideoMode({1920u, 1080u}), "SFML Window");

    // Load font for text display
    sf::Font font;
    if (!font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return 1;
    }

    // -- define helper vectors --
    sf::Vector2f WindowMiddle = static_cast<sf::Vector2f>(window.getSize()) / 2.0f;
    sf::Vector2f Origin = WindowMiddle - sf::Vector2f(250.0f, 0.0f) + sf::Vector2f(0.0f, 250.0f); // bottom-left corner of the square
    sf::Vector2f Vx = sf::Vector2f(rectangleSize / (pointsPerPixel * 100), 0.0f); // vector along x-axis
    sf::Vector2f Vy = sf::Vector2f(0.0f, - rectangleSize / (pointsPerPixel * 100)); // vector along y-axis

    // Animation control
    size_t currentPointIndex = 0;
    sf::Clock clock;
    bool isPaused = true;

    // Frame rate tracking
    sf::Clock fpsClock;
    float fps = 0.0f;
    int frameCount = 0;
    float fpsUpdateTime = 0.0f;

    // Button definitions
    sf::RectangleShape pauseButton(sf::Vector2f(120, 40));
    pauseButton.setFillColor(sf::Color(100, 150, 255));
    pauseButton.setPosition(sf::Vector2f(WindowMiddle.x - 250.0f, WindowMiddle.y + 280.0f));

    sf::RectangleShape resetButton(sf::Vector2f(120, 40));
    resetButton.setFillColor(sf::Color(255, 150, 100));
    resetButton.setPosition(sf::Vector2f(WindowMiddle.x - 100.0f, WindowMiddle.y + 280.0f));

    sf::RectangleShape newPointsButton(sf::Vector2f(180, 40));
    newPointsButton.setFillColor(sf::Color(100, 255, 100));
    newPointsButton.setPosition(sf::Vector2f(WindowMiddle.x + 50.0f, WindowMiddle.y + 280.0f));

    // Main loop - runs while the window is open
    while (window.isOpen()) {
        // Process events (SFML 3.x uses std::optional)
        while (auto event = window.pollEvent()) {
            // Close window when close button is clicked
            if (event->is<sf::Event::Closed>())
                window.close();
            
            // Handle mouse clicks
            if (event->is<sf::Event::MouseButtonPressed>()) {
                auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                    sf::Vector2f mousePos(static_cast<float>(mouseEvent->position.x), 
                                         static_cast<float>(mouseEvent->position.y));
                    
                    // Check if pause button was clicked
                    if (pauseButton.getGlobalBounds().contains(mousePos)) {
                        isPaused = !isPaused;
                        if (!isPaused) {
                            clock.restart(); // Reset clock when resuming to avoid jump
                        }
                    }
                    
                    // Check if reset button was clicked
                    if (resetButton.getGlobalBounds().contains(mousePos)) {
                        currentPointIndex = 0;
                        isPaused = false;
                        clock.restart();
                    }

                    // Check if new points button was clicked
                    if (newPointsButton.getGlobalBounds().contains(mousePos)) {
                        currentPointIndex = 0;
                        isPaused = false;
                        piApprox.resetPoints();
                        points = piApprox.getPoints();
                        clock.restart();
                    }
                }
            }

            // Same keyboard handling as mouse buttons
            if (event->is<sf::Event::KeyPressed>()) {
                auto keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent && keyEvent->code == sf::Keyboard::Key::Space) {
                    isPaused = !isPaused;
                    if (!isPaused) {
                        clock.restart();
                    }
                }

                if (keyEvent && keyEvent->code == sf::Keyboard::Key::R) {
                    isPaused = false;
                    currentPointIndex = 0;
                    clock.restart();
                }

                if (keyEvent && keyEvent->code == sf::Keyboard::Key::G) {
                    currentPointIndex = 0;
                    isPaused = false;
                    piApprox.resetPoints();
                    points = piApprox.getPoints();
                    clock.restart();
                }
                
                if (keyEvent && keyEvent->code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            }
        }

        // Clear the window with blue color
        window.clear(sf::Color::White);

        // Calculate FPS
        float frameTime = fpsClock.restart().asSeconds();
        frameCount++;
        fpsUpdateTime += frameTime;
        
        // Update FPS display every 0.5 seconds
        if (fpsUpdateTime >= 0.5f) {
            fps = frameCount / fpsUpdateTime;
            frameCount = 0;
            fpsUpdateTime = 0.0f;
        }

        // Update animation - add more points based on elapsed time (only if not paused)
        if (!isPaused) {
            float elapsed = clock.restart().asSeconds();
            int pointsToAdd = static_cast<int>(elapsed * pointsPerSecond) < points.size() ? static_cast<int>(elapsed * pointsPerSecond) : points.size();
            currentPointIndex = std::min(currentPointIndex + pointsToAdd, points.size());
        } else {
            clock.restart(); // Keep restarting clock while paused to avoid accumulation
        }

        // draw square outline
        sf::RectangleShape square(sf::Vector2f(rectangleSize, rectangleSize));
        square.setFillColor(sf::Color::Transparent);
        square.setOutlineColor(sf::Color::Black);
        square.setOutlineThickness(1);
        square.setPosition(sf::Vector2f(WindowMiddle.x - rectangleSize / 2, WindowMiddle.y - rectangleSize / 2));
        window.draw(square);

        // draw quarter circle arc
        sf::VertexArray arc(sf::PrimitiveType::LineStrip, 1001);
        for (int i = 0; i <= 1000; ++i) {
            float angle = (static_cast<float>(i) / 1000.0f) * 1.57079632679f; // 0 to π/2 radians (90 degrees)
            float x = Origin.x + rectangleSize * std::cos(angle);
            float y = Origin.y - rectangleSize * std::sin(angle);
            arc[i].position = sf::Vector2f(x, y);
            arc[i].color = sf::Color::Black;
        }
        window.draw(arc);

        // statistics for currently displayed points
        int pointsInside = 0;
        int pointsOutside = 0;
        
        // Draw all points up to currentPointIndex
        for (size_t i = 0; i < currentPointIndex; ++i) {
            const Pt& pt = points[i];

            sf::CircleShape pointShape(1); // radius of 1 pixel

            // Set color based on whether point is inside the circle
            // add statistics counting in one loop rather than separate
            if (pt.inside) {
                pointShape.setFillColor(sf::Color::Blue);
                pointsInside++;
            } else {
                pointShape.setFillColor(sf::Color::Red);
                pointsOutside++;
            }
            
            // Calculate position in window coordinates
            sf::Vector2f position = Origin + 
                static_cast<sf::Vector2f>((static_cast<float>(pt.coords[0]) * pointsPerPixel * 100) * Vx + 
                                          (static_cast<float>(pt.coords[1]) * pointsPerPixel * 100) * Vy);
            pointShape.setPosition(position);
            
            window.draw(pointShape);
        }

        // Calculate current pi estimate
        double currentPiEstimate = 0.0;
        if (currentPointIndex > 0) {
            currentPiEstimate = 4.0 * pointsInside / static_cast<double>(currentPointIndex);
        }

        // Display statistics above the rectangle
        std::string statsString = "Samples: " + std::to_string(currentPointIndex) + " / " + std::to_string(nSamples) + 
                                  "\nInside (blue): " + std::to_string(pointsInside) + 
                                  "\nOutside (red): " + std::to_string(pointsOutside) + 
                                  "\nPi estimate: " + std::to_string(currentPiEstimate) +
                                  "\nFPS: " + std::to_string(static_cast<int>(fps));
        
        sf::Text statsText(font, statsString, 20);
        statsText.setFillColor(sf::Color::Black);
        statsText.setPosition(sf::Vector2f(WindowMiddle.x - 250.0f, WindowMiddle.y - 375.0f));
        window.draw(statsText);

        // Draw pause/resume button text
        window.draw(pauseButton);
        std::string pauseButtonText = isPaused ? "Resume" : "Pause";
        sf::Text pauseText(font, pauseButtonText, 18);
        pauseText.setFillColor(sf::Color::White);
        sf::FloatRect pauseTextBounds = pauseText.getLocalBounds();
        pauseText.setPosition(sf::Vector2f(
            pauseButton.getPosition().x + (pauseButton.getSize().x - pauseTextBounds.size.x) / 2 - pauseTextBounds.position.x,
            pauseButton.getPosition().y + (pauseButton.getSize().y - pauseTextBounds.size.y) / 2 - pauseTextBounds.position.y
        ));
        window.draw(pauseText);

        // Draw reset button text
        window.draw(resetButton);
        sf::Text resetText(font, "Reset", 18);
        resetText.setFillColor(sf::Color::White);
        sf::FloatRect resetTextBounds = resetText.getLocalBounds();
        resetText.setPosition(sf::Vector2f(
            resetButton.getPosition().x + (resetButton.getSize().x - resetTextBounds.size.x) / 2 - resetTextBounds.position.x,
            resetButton.getPosition().y + (resetButton.getSize().y - resetTextBounds.size.y) / 2 - resetTextBounds.position.y
        ));
        window.draw(resetText);

        // Draw new points button text
        window.draw(newPointsButton);
        sf::Text newPointsText(font, "Generate new points", 18);
        newPointsText.setFillColor(sf::Color::White);
        sf::FloatRect newPointsTextBounds = newPointsText.getLocalBounds();
        newPointsText.setPosition(sf::Vector2f(
            newPointsButton.getPosition().x + (newPointsButton.getSize().x - newPointsTextBounds.size.x) / 2 - newPointsTextBounds.position.x,
            newPointsButton.getPosition().y + (newPointsButton.getSize().y - newPointsTextBounds.size.y) / 2 - newPointsTextBounds.position.y
        ));
        window.draw(newPointsText);


        // Display what we've drawn
        window.display();
        window.setFramerateLimit(30); // framerate limit also updates window events at a fixed rate
        }

    return 0;
}
