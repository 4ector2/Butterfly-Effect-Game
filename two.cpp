//#include <SFML/Graphics.hpp>
//#include <cmath>
//#include <ctime>
//#include <cstdlib>
//#include <vector>
//
//constexpr int WINDOW_WIDTH = 800;
//constexpr int WINDOW_HEIGHT = 600;
//
//struct Butterfly {
//    sf::ConvexShape leftWing;
//    sf::ConvexShape rightWing;
//    sf::CircleShape body;
//    sf::Vector2f position;
//    sf::Vector2f velocity;
//    float wingAngle;
//    float wingSpeed;
//    bool wingDirection;
//};
//
//int main() {
//    // Инициализация генератора случайных чисел
//    srand(static_cast<unsigned>(time(nullptr)));
//
//    // Создание окна
//    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Butterfly Flight Simulation");
//    window.setFramerateLimit(60);
//
//    // ====================== ЗАГРУЗКА РЕСУРСОВ ======================
//
//    // 1. Загрузка фонового изображения
//    sf::Texture backgroundTexture;
//    if (!backgroundTexture.loadFromFile("background.jpg")) {
//        // Если не удалось загрузить изображение, создаем градиентный фон программно
//        backgroundTexture.create(WINDOW_WIDTH, WINDOW_HEIGHT);
//        sf::Uint8* pixels = new sf::Uint8[WINDOW_WIDTH * WINDOW_HEIGHT * 4];
//
//        for (int y = 0; y < WINDOW_HEIGHT; ++y) {
//            // Создаем градиент от голубого (верх) к светло-голубому (низ)
//            sf::Color color(100, 149 + y * 0.1, 237 - y * 0.1);
//
//            for (int x = 0; x < WINDOW_WIDTH; ++x) {
//                pixels[(y * WINDOW_WIDTH + x) * 4] = color.r;
//                pixels[(y * WINDOW_WIDTH + x) * 4 + 1] = color.g;
//                pixels[(y * WINDOW_WIDTH + x) * 4 + 2] = color.b;
//                pixels[(y * WINDOW_WIDTH + x) * 4 + 3] = 255;
//            }
//        }
//
//        backgroundTexture.update(pixels);
//        delete[] pixels;
//        std::cout << "Created gradient background (background.jpg not found)" << std::endl;
//    }
//
//    sf::Sprite background(backgroundTexture);
//
//    // ====================== СОЗДАНИЕ БАБОЧКИ ======================
//
//    Butterfly butterfly;
//
//    // Начальная позиция (центр экрана)
//    butterfly.position = sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
//
//    // Начальная скорость
//    butterfly.velocity = sf::Vector2f(1.f, 0.5f);
//
//    // Параметры анимации крыльев
//    butterfly.wingAngle = 0.f;
//    butterfly.wingSpeed = 5.f;
//    butterfly.wingDirection = true;
//
//    // Тело бабочки
//    butterfly.body.setRadius(10.f);
//    butterfly.body.setFillColor(sf::Color(139, 69, 19)); // Коричневый
//    butterfly.body.setOrigin(10.f, 10.f); // Центрирование
//
//    // Левое крыло
//    butterfly.leftWing.setPointCount(4);
//    butterfly.leftWing.setPoint(0, sf::Vector2f(0.f, 0.f));
//    butterfly.leftWing.setPoint(1, sf::Vector2f(-30.f, -20.f));
//    butterfly.leftWing.setPoint(2, sf::Vector2f(-50.f, 0.f));
//    butterfly.leftWing.setPoint(3, sf::Vector2f(-30.f, 20.f));
//    butterfly.leftWing.setFillColor(sf::Color(255, 165, 0)); // Оранжевый
//
//    // Правое крыло
//    butterfly.rightWing.setPointCount(4);
//    butterfly.rightWing.setPoint(0, sf::Vector2f(0.f, 0.f));
//    butterfly.rightWing.setPoint(1, sf::Vector2f(30.f, -20.f));
//    butterfly.rightWing.setPoint(2, sf::Vector2f(50.f, 0.f));
//    butterfly.rightWing.setPoint(3, sf::Vector2f(30.f, 20.f));
//    butterfly.rightWing.setFillColor(sf::Color(255, 165, 0)); // Оранжевый
//
//    // ====================== УПРАВЛЕНИЕ ======================
//
//    bool animationPaused = false;
//    float animationSpeed = 1.0f;
//
//    // Инструкция для пользователя
//    std::cout << "Controls:\n";
//    std::cout << "  ESC - Exit\n";
//    std::cout << "  SPACE - Pause/Resume\n";
//    std::cout << "  +/- - Speed up/down\n";
//
//    // ====================== ГЛАВНЫЙ ЦИКЛ ======================
//
//    while (window.isOpen()) {
//        // Обработка событий
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            if (event.type == sf::Event::KeyPressed) {
//                if (event.key.code == sf::Keyboard::Escape)
//                    window.close();
//                else if (event.key.code == sf::Keyboard::Space)
//                    animationPaused = !animationPaused;
//                else if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal)
//                    animationSpeed *= 1.1f;
//                else if (event.key.code == sf::Keyboard::Subtract || event.key.code == sf::Keyboard::Dash)
//                    animationSpeed /= 1.1f;
//            }
//        }
//
//        // ====================== ОБНОВЛЕНИЕ СОСТОЯНИЯ ======================
//
//        if (!animationPaused) {
//            // 1. Обновление позиции (хаотичное движение)
//            butterfly.velocity.x += (rand() % 100 - 50) / 100.f * animationSpeed;
//            butterfly.velocity.y += (rand() % 100 - 50) / 100.f * animationSpeed;
//
//            // Ограничение максимальной скорости
//            float speed = sqrt(butterfly.velocity.x * butterfly.velocity.x +
//                butterfly.velocity.y * butterfly.velocity.y);
//            if (speed > 5.f * animationSpeed) {
//                butterfly.velocity = (butterfly.velocity / speed) * 5.f * animationSpeed;
//            }
//
//            butterfly.position += butterfly.velocity;
//
//            // Проверка границ окна
//            if (butterfly.position.x < 0) {
//                butterfly.position.x = 0;
//                butterfly.velocity.x = -butterfly.velocity.x * 0.5f;
//            }
//            else if (butterfly.position.x > WINDOW_WIDTH) {
//                butterfly.position.x = WINDOW_WIDTH;
//                butterfly.velocity.x = -butterfly.velocity.x * 0.5f;
//            }
//
//            if (butterfly.position.y < 0) {
//                butterfly.position.y = 0;
//                butterfly.velocity.y = -butterfly.velocity.y * 0.5f;
//            }
//            else if (butterfly.position.y > WINDOW_HEIGHT) {
//                butterfly.position.y = WINDOW_HEIGHT;
//                butterfly.velocity.y = -butterfly.velocity.y * 0.5f;
//            }
//
//            // 2. Анимация крыльев
//            if (butterfly.wingDirection) {
//                butterfly.wingAngle += butterfly.wingSpeed * animationSpeed;
//                if (butterfly.wingAngle > 30.f) butterfly.wingDirection = false;
//            }
//            else {
//                butterfly.wingAngle -= butterfly.wingSpeed * animationSpeed;
//                if (butterfly.wingAngle < -30.f) butterfly.wingDirection = true;
//            }
//        }
//
//        // ====================== ОТРИСОВКА ======================
//
//        window.clear();
//
//        // 1. Рисуем фон
//        window.draw(background);
//
//        // 2. Рисуем бабочку
//        butterfly.body.setPosition(butterfly.position);
//
//        butterfly.leftWing.setPosition(butterfly.position);
//        butterfly.leftWing.setRotation(butterfly.wingAngle);
//
//        butterfly.rightWing.setPosition(butterfly.position);
//        butterfly.rightWing.setRotation(-butterfly.wingAngle);
//
//        window.draw(butterfly.leftWing);
//        window.draw(butterfly.rightWing);
//        window.draw(butterfly.body);
//
//        window.display();
//    }
//
//    return 0;
//}