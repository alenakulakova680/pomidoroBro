#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Button.hpp"
#include "TimerLogic.hpp"

std::string getHistoryFilename()
{

    std::cout << "Enter history file name (default: history.txt): ";
    std::string input;
    std::getline(std::cin, input);
    input = TimerLogic::formatFilenameLogic(input);

    std::cout << "History will be saved to: " << input << "\n";
    return input;
}

int main()
{
    try
    {
        std::string historyFile = getHistoryFilename();

        std::string currentScreen{"menu"};
        int customWork = 25;
        int customBreak = 5;

        sf::RenderWindow window(sf::VideoMode({800, 600}), "Pomodoro bro", sf::Style::Close);

        TimerLogic timer;

        // загрузка ресурсов
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("assets/bell.mp3"))
        {
            throw std::runtime_error("assets/bell.mp3 not found!");
        }
        sf::Sound bellSound(buffer);

        sf::Font font;
        if (!font.openFromFile("assets/font.ttf"))
        {
            throw std::runtime_error("assets/font.ttf not found!");
        }

        try
        {
            timer.loadHistory(font, historyFile);
        }
        catch (const std::exception &e)
        {
            std::cerr << " Could not load history file on startup: " << e.what() << "\n";
        }

        sf::Texture pomidoroTexture1;
        if (!pomidoroTexture1.loadFromFile("assets/pomidoro.png"))
        {
            throw std::runtime_error("assets/pomidoro.png not found!");
        }
        sf::Sprite pomidoromenu(pomidoroTexture1);
        pomidoromenu.setPosition({400, 150});

        sf::Texture pomidoroTexture2;
        if (!pomidoroTexture2.loadFromFile("assets/pomstudy.png"))
        {
            throw std::runtime_error("assets/pomstudy.png not found!");
        }

        sf::Texture pomidoroTexture3;
        if (!pomidoroTexture3.loadFromFile("assets/pomrest.png"))
        {
            throw std::runtime_error("assets/pomrest.png not found!");
        }

        sf::Sprite pomidoroTimer(pomidoroTexture2);
        pomidoroTimer.setPosition({380, 150});

        Button backBtn({200, 40}, {10, 10}, sf::Color(221, 85, 65), "back", font, 30);

        // Экран: Главное меню
        sf::Text menuTitletxt(font, "Timer Pomodoro bro", 60);
        menuTitletxt.setFillColor(sf::Color(225, 94, 55));
        menuTitletxt.setPosition({100, 50});
        Button startBtn({260, 60}, {270, 150}, sf::Color(255, 205, 48), "start", font, 50);
        Button historyBtn({160, 40}, {320, 230}, sf::Color(141, 160, 71), "history", font, 30);

        // Экран: Выбор режима
        sf::Text chooseTitletxt(font, "Choose your timer!", 48);
        chooseTitletxt.setFillColor(sf::Color(142, 161, 72));
        chooseTitletxt.setPosition({150, 50});
        Button btn25({700, 100}, {50, 120}, sf::Color(221, 85, 65), "study 25/5", font, 50);
        Button btn50({700, 100}, {50, 260}, sf::Color(221, 85, 65), "study 50/10", font, 50);
        Button customBtn({700, 100}, {50, 400}, sf::Color(221, 85, 65), "custom your own time", font, 50);

        // Экран: Настройка Custom
        sf::Text workSetuptxt(font, "Work: 25 min", 40);
        workSetuptxt.setFillColor(sf::Color::Black);
        workSetuptxt.setPosition({150, 150});
        sf::Text breakSetuptxt(font, "Break: 5 min", 40);
        breakSetuptxt.setFillColor(sf::Color::Black);
        breakSetuptxt.setPosition({150, 270});

        Button workMinusBtn({60, 50}, {500, 150}, sf::Color(221, 85, 65), "-", font, 35);
        Button workPlusBtn({60, 50}, {580, 150}, sf::Color(142, 161, 72), "+", font, 35);
        Button breakMinusBtn({60, 50}, {500, 270}, sf::Color(221, 85, 65), "-", font, 35);
        Button breakPlusBtn({60, 50}, {580, 270}, sf::Color(142, 161, 72), "+", font, 35);
        Button customStartBtn({300, 70}, {250, 420}, sf::Color(255, 205, 48), "LET'S GO!", font, 40);

        // Экран: Таймер
        sf::Text timerTitletxt(font, "TIMER", 100);
        timerTitletxt.setFillColor(sf::Color(255, 205, 48));
        timerTitletxt.setPosition({250, 50});
        sf::Text timeDisplay(font, "25:00", 100);
        timeDisplay.setFillColor(sf::Color(142, 161, 72));
        timeDisplay.setPosition({280, 150});

        // Экран: История
        sf::Text historyTitle(font, "Your Pomodoro History", 45);
        historyTitle.setFillColor(sf::Color(255, 205, 48));
        historyTitle.setPosition({140, 50});

        Button stopBtn({200, 50}, {100, 300}, sf::Color(221, 85, 65), "stop", font, 35);
        Button nextBtn({200, 50}, {100, 375}, sf::Color(221, 85, 65), "next", font, 35);
        Button restartBtn({200, 50}, {100, 450}, sf::Color(221, 85, 65), "restart", font, 35);

        while (window.isOpen())
        {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }

                if (currentScreen == "menu")
                {
                    startBtn.updateHover(mousePos);
                    historyBtn.updateHover(mousePos);
                }
                else if (currentScreen == "choose")
                {
                    backBtn.updateHover(mousePos);
                    btn25.updateHover(mousePos);
                    btn50.updateHover(mousePos);
                    customBtn.updateHover(mousePos);
                }
                else if (currentScreen == "custom")
                {
                    backBtn.updateHover(mousePos);
                    workMinusBtn.updateHover(mousePos);
                    workPlusBtn.updateHover(mousePos);
                    breakMinusBtn.updateHover(mousePos);
                    breakPlusBtn.updateHover(mousePos);
                    customStartBtn.updateHover(mousePos);
                }
                else if (currentScreen == "timer")
                {
                    backBtn.updateHover(mousePos);
                    stopBtn.updateHover(mousePos);
                    nextBtn.updateHover(mousePos);
                    restartBtn.updateHover(mousePos);
                }
                else if (currentScreen == "history")
                {
                    backBtn.updateHover(mousePos);
                }

                if (event->is<sf::Event::MouseButtonPressed>())
                {
                    auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
                    bool isLeftClick = (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left);

                    if (currentScreen == "menu")
                    {
                        if (startBtn.isClicked(mousePos, isLeftClick))
                        {
                            currentScreen = "choose";
                        }
                        else if (historyBtn.isClicked(mousePos, isLeftClick))
                        {
                            currentScreen = "history";

                            try
                            {
                                timer.loadHistory(font, historyFile);
                            }
                            catch (const std::runtime_error &fileError)
                            {
                                std::cerr << "FILE ERROR: " << fileError.what();
                            }
                        }
                    }
                    else if (currentScreen == "choose")
                    {
                        if (backBtn.isClicked(mousePos, isLeftClick))
                        {
                            currentScreen = "menu";
                        }
                        else if (btn25.isClicked(mousePos, isLeftClick))
                        {
                            timer.launch(25, 5, timeDisplay, pomidoroTimer, pomidoroTexture2);
                            currentScreen = "timer";
                        }
                        else if (btn50.isClicked(mousePos, isLeftClick))
                        {
                            timer.launch(50, 10, timeDisplay, pomidoroTimer, pomidoroTexture2);
                            currentScreen = "timer";
                        }
                        else if (customBtn.isClicked(mousePos, isLeftClick))
                        {
                            currentScreen = "custom";
                        }
                    }
                    else if (currentScreen == "custom")
                    {
                        if (backBtn.isClicked(mousePos, isLeftClick))
                        {
                            currentScreen = "choose";
                        }
                        else if (workMinusBtn.isClicked(mousePos, isLeftClick) && customWork > 1)
                        {
                            customWork--;
                            workSetuptxt.setString("Work: " + std::to_string(customWork) + " min");
                        }
                        else if (workPlusBtn.isClicked(mousePos, isLeftClick))
                        {
                            customWork++;
                            workSetuptxt.setString("Work: " + std::to_string(customWork) + " min");
                        }
                        else if (breakMinusBtn.isClicked(mousePos, isLeftClick) && customBreak > 1)
                        {
                            customBreak--;
                            breakSetuptxt.setString("Break: " + std::to_string(customBreak) + " min");
                        }
                        else if (breakPlusBtn.isClicked(mousePos, isLeftClick))
                        {
                            customBreak++;
                            breakSetuptxt.setString("Break: " + std::to_string(customBreak) + " min");
                        }
                        else if (customStartBtn.isClicked(mousePos, isLeftClick))
                        {
                            timer.launch(customWork, customBreak, timeDisplay, pomidoroTimer, pomidoroTexture2);
                            currentScreen = "timer";
                        }
                    }
                    else if (currentScreen == "timer")
                    {
                        if (backBtn.isClicked(mousePos, isLeftClick))
                        {
                            currentScreen = "choose";
                        }
                        else if (stopBtn.isClicked(mousePos, isLeftClick))
                        {
                            timer.togglePause(stopBtn);
                        }
                        else if (restartBtn.isClicked(mousePos, isLeftClick))
                        {
                            timer.restart(timeDisplay);
                        }
                        else if (nextBtn.isClicked(mousePos, isLeftClick))
                        {
                            timer.forceNext(timeDisplay, pomidoroTimer, pomidoroTexture2, pomidoroTexture3, bellSound);
                        }
                    }
                    else if (currentScreen == "history")
                    {
                        if (backBtn.isClicked(mousePos, isLeftClick))
                        {
                            currentScreen = "menu";
                        }
                    }
                }
            }

            if (currentScreen == "timer")
            {
                timer.update(timeDisplay, pomidoroTimer, pomidoroTexture2, pomidoroTexture3, bellSound, historyFile);
            }

            // отрисовка
            window.clear(sf::Color(255, 253, 240));

            if (currentScreen == "menu")
            {
                window.draw(menuTitletxt);
                window.draw(pomidoromenu);
                startBtn.draw(window);
                historyBtn.draw(window);
            }
            else if (currentScreen == "choose")
            {
                window.draw(chooseTitletxt);
                btn25.draw(window);
                btn50.draw(window);
                customBtn.draw(window);
                backBtn.draw(window);
            }
            else if (currentScreen == "custom")
            {
                window.draw(workSetuptxt);
                window.draw(breakSetuptxt);
                workMinusBtn.draw(window);
                workPlusBtn.draw(window);
                breakMinusBtn.draw(window);
                breakPlusBtn.draw(window);
                customStartBtn.draw(window);
                backBtn.draw(window);
            }
            else if (currentScreen == "timer")
            {
                window.draw(timerTitletxt);
                window.draw(pomidoroTimer);
                window.draw(timeDisplay);
                stopBtn.draw(window);
                nextBtn.draw(window);
                restartBtn.draw(window);
                backBtn.draw(window);
            }
            else if (currentScreen == "history")
            {
                backBtn.draw(window);
                window.draw(historyTitle);
                timer.drawHistory(window);
            }
            window.display();
        }
    }

    catch (const std::runtime_error &e)
    {
        std::cerr << "CRITICAL ERROR: " << e.what();
        std::cerr << "Application will be closed.\n";
        return -1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Fatal Exception caught: " << e.what() << std::endl;
        return -2;
    }
    catch (...)
    {
        std::cerr << "Unknown critical error occurred!" << std::endl;
        return -3;
    }
    return 0;
}