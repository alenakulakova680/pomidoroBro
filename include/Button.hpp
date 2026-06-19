/**
 * @file Button.hpp
 * @brief Определение класса Button для создания интерактивных элементов интерфейса.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @class Button
 * @brief Класс Button представляет собой интерактивный элемент графического интерфейса.
 * * Данный класс инкапсулирует в себе прямоугольную форму SFML и текстовую метку,
 * автоматически управляя центрованием текста, обработкой кликов и изменением
 * цвета при наведении курсора мыши.
 */
class Button
{
private:
    sf::RectangleShape m_shape; ///< Геометрическая форма кнопки (рамка).
    sf::Text m_text;            ///< Отображаемый на кнопке текст.
    sf::Color m_baseColor;      ///< Исходный (базовый) цвет кнопки.
    sf::Color m_hoverColor;     ///< Цвет кнопки при наведении курсора мыши.

    /**
     * @brief Внутренний метод для выравнивания текста строго по центру кнопки.
     * * Пересчитывает локальные границы (bounds) текста относительно текущих
     * размеров и позиции прямоугольника кнопки.
     */
    void centerText();

public:
    /**
     * @brief Конструктор для создания и инициализации объекта кнопки.
     * @param size Размеры кнопки (ширина и высота в пикселях).
     * @param position Координаты верхнего левого угла кнопки на экране.
     * @param color Основной цвет заливки кнопки.
     * @param textStr Текст, который будет отображаться на кнопке.
     * @param font Ссылка на загруженный шрифт для текстовой метки.
     * @param characterSize Размер шрифта в пикселях (по умолчанию 30).
     */
    Button(const sf::Vector2f &size, const sf::Vector2f &position,
           const sf::Color &color, const std::string &textStr, const sf::Font &font, unsigned int characterSize = 30);

    /**
     * @brief Отрисовывает кнопку и текст на ней в заданном окне.
     * @param window Ссылка на окно рендеринга SFML, в котором происходит отрисовка.
     */
    void draw(sf::RenderWindow &window) const;

    /**
     * @brief Обновляет состояние подсветки кнопки в зависимости от положения мыши.
     * * Если курсор находится внутри границ кнопки, цвет меняется на m_hoverColor,
     * иначе возвращается m_baseColor.
     * * @param mousePos Текущие координаты курсора мыши в пространстве окна.
     */
    void updateHover(const sf::Vector2f &mousePos);

    /**
     * @brief Проверяет, был ли совершен клик по кнопке.
     * @param mousePos Текущие координаты курсора мыши в момент клика.
     * @param isLeftClick Флаг, указывающий, была ли нажата именно левая кнопка мыши.
     * @return true Если клик совершен, иначе false.
     */
    bool isClicked(const sf::Vector2f &mousePos, bool isLeftClick) const;

    /**
     * @brief Динамически изменяет текст на кнопке.
     * * Метод обновляет строку и автоматически запускает пересчет центрования
     * для нового слова.
     * @param textStr Новая строка текста (например, для смены "START" на "PAUSE").
     */
    void setText(const std::string &textStr);
};