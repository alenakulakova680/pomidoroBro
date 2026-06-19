/**
 * @file TimerLogic.hpp
 * @brief Определение класса TimerLogic для управления логикой Помодоро-таймера.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "Button.hpp"

/**
 * @class TimerLogic
 * @brief Класс, отвечающий за отсчет времени, переключение режимов работы/отдыха и ведение истории сессий.
 */
class TimerLogic {
public:
    /**
     * @brief Конструктор по умолчанию. Инициализирует начальное состояние таймера.
     */
    TimerLogic();

    /**
     * @brief Запускает таймер с заданными интервалами работы и отдыха.
     * @param workMin Количество минут для рабочей сессии.
     * @param breakMin Количество минут для перерыва.
     * @param display Текстовый объект SFML для вывода оставшегося времени.
     * @param timerSprite Спрайт таймера для визуального изменения фона.
     * @param workTexture Текстура, устанавливаемая для режима работы.
     */
    void launch(int workMin, int breakMin, sf::Text& display, sf::Sprite& timerSprite, const sf::Texture& workTexture);

    /**
     * @brief Переключает состояние таймера (пауза / возобновление).
     * @param stopBtn Ссылка на кнопку управления паузой для возможного изменения её состояния или текста.
     */
    void togglePause(Button& stopBtn);

    /**
     * @brief Сбрасывает текущую сессию к её начальному временному значению.
     * @param display Текстовый объект SFML для обновления отображаемого времени.
     */
    void restart(sf::Text& display);

    /**
     * @brief Принудительно завершает текущий промежуток и переводит таймер на следующий (работа / отдых).
     * @param display Текстовый объект SFML для обновления времени.
     * @param timerSprite Спрайт фона, меняющий текстуру в зависимости от нового режима.
     * @param workTexture Текстура для режима работы.
     * @param breakTexture Текстура для режима отдыха.
     * @param bell Звуковой эффект, воспроизводимый при переключении.
     */
    void forceNext(sf::Text& display, sf::Sprite& timerSprite, const sf::Texture& workTexture, const sf::Texture& breakTexture, sf::Sound& bell);
    
    /**
     * @brief Обновляет состояние таймера в каждом кадра (уменьшает оставшееся время).
     * @param display Текстовый объект SFML для вывода текущего времени в формате ММ:СС.
     * @param timerSprite Спрайт фона таймера.
     * @param workTexture Текстура для режима работы.
     * @param breakTexture Текстура для режима отдыха.
     * @param bell Звуковой эффект при автоматическом завершении сессии.
     */
    void update(sf::Text& display, sf::Sprite& timerSprite, const sf::Texture& workTexture, const sf::Texture& breakTexture, sf::Sound& bell, const std::string& filename);    
    
    /**
     * @brief Загружает последние записи истории из указанного файла и форматирует их в объекты sf::Text.
     * @param font Шрифт, используемый для создания графического текста истории.
     * @param filename Имя файла (введённое пользователем), откуда считывается история.
     */
    void loadHistory(const sf::Font& font, const std::string& filename);
    
    /**
     * @brief Форматирует общее количество секунд в строку вида ММ:СС.
     * @details Используется для отображения времени на экране таймера. 
     * Защищена от отрицательных значений (в случае сбоя вернет "00:00").
     * * @param totalSeconds Общее количество секунд для форматирования.
     * @return std::string Отформатированная строка времени в формате "Минуты:Секунды".
     */
    static std::string formatTimeLogic(int totalSeconds);

    /**
     * @brief Валидирует имя файла истории и автоматически добавляет расширение .txt.
     * @details Если переданная строка пустая, возвращает дефолтное имя "history.txt".
     * Если в строке отсутствует подстрока ".txt", она принудительно добавляется в конец.
     * * @param input Исходное имя файла, введенное пользователем или переданное системой.
     * @return std::string Корректное имя файла с расширением .txt.
     */
    static std::string formatFilenameLogic(std::string input);

    /**
     * @brief Переключает логический режим текущей сессии (Работа / Отдых).
     * @details Инвертирует текущее состояние флага сессии на противоположное.
     * * @param currentIsWork Текущий статус сессии (true — если идет работа, false — если отдых).
     * @return true Если следующая сессия должна быть рабочей.
     * @return false Если следующая сессия должна быть временем отдыха.
     */
    static bool switchSessionLogic(bool currentIsWork);

    /**
     * @brief Отрисовывает загруженные строки истории в текущее графическое окно.
     * @param window Ссылка на окно рендеринга SFML.
     */
    void drawHistory(sf::RenderWindow& window);

private:
    bool isRunning;          ///< Флаг, указывающий, запущен ли отсчет времени прямо сейчас.
    bool isWorkSession;      ///< Режим сессии: true — работа, false — перерыв.
    int workDuration;        ///< Установленная длительность работы в минутах.
    int breakDuration;       ///< Установленная длительность отдыха в минутах.
    sf::Time timeLeft;       ///< Оставшееся время до конца текущего промежутка.
    std::vector<sf::Text> historyTexts; ///< Вектор графических текстовых объектов для вывода истории на экран.
};