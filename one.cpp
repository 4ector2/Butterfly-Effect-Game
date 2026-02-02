//#include <SFML/Graphics.hpp>
//#include <cmath>
//#include <string>
//
//// Глобальные параметры
//float scale = 50.f; // размер единичного отрезка (пиксели)
//sf::Vector2f offset(0.f, 0.f); // смещение координат
//sf::Font font;
//
//// Начальные параметры
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//
//// Функция для рисования оси с стрелками и подписями
//void drawAxis(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end, const std::string& label) {
//    // Основная линия
//    sf::VertexArray line(sf::Lines, 2);
//    line[0].position = start;
//    line[1].position = end;
//    line[0].color = line[1].color = sf::Color::Black;
//    window.draw(line);
//
//    // Стрелка
//    sf::ConvexShape arrow;
//    arrow.setPointCount(3);
//    float arrowSize = 10.f;
//    sf::Vector2f dir = end - start;
//    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
//    sf::Vector2f unitDir = dir / length;
//    sf::Vector2f perp(-unitDir.y, unitDir.x);
//    arrow.setPoint(0, end);
//    arrow.setPoint(1, end - unitDir * arrowSize + perp * (arrowSize / 2));
//    arrow.setPoint(2, end - unitDir * arrowSize - perp * (arrowSize / 2));
//    arrow.setFillColor(sf::Color::Black);
//    window.draw(arrow);
//
//    // Подпись
//    sf::Text labelText(label, font, 14);
//    labelText.setFillColor(sf::Color::Black);
//    labelText.setPosition(end + sf::Vector2f(5, -15));
//    window.draw(labelText);
//}
//
//// Функция для рисования делений и подписей на осях
//void drawMarks(sf::RenderWindow& window, sf::Vector2f origin) {
//    // Определим интервал между делениями в единичных отрезках
//    float step = 1.f; // можно менять в зависимости от масштаба
//    int maxDiv = 20; // количество делений с каждой стороны
//
//    // Метки по X
//    for (int i = -maxDiv; i <= maxDiv; ++i) {
//        float x = origin.x + i * scale;
//        if (i != 0) {
//            // Метки делений
//            sf::RectangleShape tick(sf::Vector2f(2, 10));
//            tick.setFillColor(sf::Color::Black);
//            tick.setPosition(x - 1, origin.y - 5);
//            window.draw(tick);
//
//            // Подписи
//            if (abs(i * scale) > 5) { // чтобы не мешались к началу координат
//                sf::Text label(std::to_string(i), font, 12);
//                label.setFillColor(sf::Color::Black);
//                label.setPosition(x - 5, origin.y + 5);
//                window.draw(label);
//            }
//        }
//    }
//
//    // Метки по Y
//    for (int i = -maxDiv; i <= maxDiv; ++i) {
//        float y = origin.y + i * scale;
//        if (i != 0) {
//            // Метки делений
//            sf::RectangleShape tick(sf::Vector2f(10, 2));
//            tick.setFillColor(sf::Color::Black);
//            tick.setPosition(origin.x - 5, y - 1);
//            window.draw(tick);
//
//            // Подписи
//            if (abs(i * scale) > 5) {
//                sf::Text label(std::to_string(-i), font, 12); // Y увеличивается вниз, поэтому -i
//                label.setFillColor(sf::Color::Black);
//                label.setPosition(origin.x + 5, y - 6);
//                window.draw(label);
//            }
//        }
//    }
//}
//
//// Функция для построения графика функции y = sin(x)
//void drawFunction(sf::RenderWindow& window, sf::Vector2f origin) {
//    sf::VertexArray graph(sf::LineStrip);
//    // задаем диапазон по X в "естественных" единицах
//    float x_start = -(WINDOW_WIDTH / 2) / scale;
//    float x_end = (WINDOW_WIDTH / 2) / scale;
//
//    const float step_x = 0.01f; // шаг по x в "естественных" единицах
//
//    for (float x = x_start; x <= x_end; x += step_x) {
//        float y = std::sin(x); // функция
//        // преобразуем к координатам окна
//        float px = origin.x + x * scale;
//        float py = origin.y - y * scale; // Y вверх - вверх по экрану
//        graph.append(sf::Vertex(sf::Vector2f(px, py), sf::Color::Red));
//    }
//    window.draw(graph);
//}
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "График функции");
//    window.setFramerateLimit(60);
//
//    // Загрузка шрифта
//    if (!font.loadFromFile("arial.ttf")) {
//        // Если шрифт не найден, программа завершится
//        return -1;
//    }
//
//    // Начальная точка начала координат (по центру окна)
//    sf::Vector2f origin(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            // Обработка закрытия окна
//            if (event.type == sf::Event::Closed)
//                window.close();
//
//            // Обработка клавиш для масштабирования и перемещения
//            if (event.type == sf::Event::KeyPressed) {
//                if (event.key.code == sf::Keyboard::Add || event.key.code == sf::Keyboard::Equal) {
//                    // Увеличить масштаб
//                    scale *= 1.1f;
//                }
//                if (event.key.code == sf::Keyboard::Subtract || event.key.code == sf::Keyboard::Hyphen) {
//                    // Уменьшить масштаб
//                    if (scale > 5.f)
//                        scale /= 1.1f;
//                }
//                if (event.key.code == sf::Keyboard::Left) {
//                    offset.x += 10.f;
//                }
//                if (event.key.code == sf::Keyboard::Right) {
//                    offset.x -= 10.f;
//                }
//                if (event.key.code == sf::Keyboard::Up) {
//                    offset.y += 10.f;
//                }
//                if (event.key.code == sf::Keyboard::Down) {
//                    offset.y -= 10.f;
//                }
//            }
//        }
//
//        window.clear(sf::Color::White);
//
//        // Обновляем начало координат с учетом смещения
//        sf::Vector2f currentOrigin = origin + offset;
//
//        // Рисуем оси
//        drawAxis(window, currentOrigin, sf::Vector2f(WINDOW_WIDTH, currentOrigin.y), "X");
//        drawAxis(window, currentOrigin, sf::Vector2f(currentOrigin.x, 0), "Y");
//
//        // Рисуем деления и подписи
//        drawMarks(window, currentOrigin);
//
//        // Рисуем график функции
//        drawFunction(window, currentOrigin);
//
//        window.display();
//    }
//
//    return 0;
//}