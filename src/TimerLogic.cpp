#include "TimerLogic.hpp"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

static sf::Clock globalClock;

TimerLogic::TimerLogic()
{
    isRunning = false;
    isWorkSession = true;
    workDuration = 25;
    breakDuration = 5;
    timeLeft = sf::seconds(workDuration * 60);
}

void TimerLogic::launch(int workMin, int breakMin, sf::Text &display, sf::Sprite &timerSprite, const sf::Texture &workTexture)
{
    workDuration = workMin;
    breakDuration = breakMin;
    isWorkSession = true;
    isRunning = true;
    timeLeft = sf::seconds(workDuration * 60);

    timerSprite.setTexture(workTexture);
    globalClock.restart();
}

void TimerLogic::togglePause(Button &stopBtn)
{
    isRunning = !isRunning;
    if (isRunning)
    {
        globalClock.restart();
        stopBtn.setText("stop");
    }
    else
    {
        stopBtn.setText("play");
    }
}

void TimerLogic::restart(sf::Text &display)
{
    if (isWorkSession)
    {
        timeLeft = sf::seconds(workDuration * 60);
    }
    else
    {
        timeLeft = sf::seconds(breakDuration * 60);
    }
    globalClock.restart();
    display.setString(formatTimeLogic(static_cast<int>(timeLeft.asSeconds())));
}

void TimerLogic::forceNext(sf::Text &display, sf::Sprite &timerSprite, const sf::Texture &workTexture, const sf::Texture &breakTexture, sf::Sound &bell)
{
    bell.play();
    isWorkSession = switchSessionLogic(isWorkSession);

    if (isWorkSession)
    {
        timeLeft = sf::seconds(workDuration * 60);
        timerSprite.setTexture(workTexture);
    }
    else
    {
        timeLeft = sf::seconds(breakDuration * 60);
        timerSprite.setTexture(breakTexture);
    }
    globalClock.restart();
}

void saveSessionToHistory(const std::string &filename, int duration, bool wasWorkSession)
{
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open())
    {
        return;
    }

    std::time_t now = std::time(nullptr);
    std::tm *now_tm = std::localtime(&now);

    std::stringstream ss;
    ss << "["
       << (now_tm->tm_year + 1900) << "-"
       << std::setw(2) << std::setfill('0') << (now_tm->tm_mon + 1) << "-"
       << std::setw(2) << std::setfill('0') << now_tm->tm_mday << " "
       << std::setw(2) << std::setfill('0') << now_tm->tm_hour << ":"
       << std::setw(2) << std::setfill('0') << now_tm->tm_min << "]";

    std::string sessionType;
    if (wasWorkSession)
    {
        sessionType = "Completed Work";
    }
    else
    {
        sessionType = "Completed Break";
    }

    file << ss.str() << " " << sessionType << ": " << duration << " min\n";
    file.close();
}

void TimerLogic::update(sf::Text &display, sf::Sprite &timerSprite, const sf::Texture &workTexture, const sf::Texture &breakTexture, sf::Sound &bell, const std::string &filename)
{
    sf::Time elapsed = globalClock.restart();

    if (isRunning)
    {
        timeLeft -= elapsed;

        if (timeLeft <= sf::Time::Zero)
        {
            timeLeft = sf::Time::Zero;
            int currentDuration;

            if (isWorkSession)
            {
                currentDuration = workDuration;
            }
            else
            {
                currentDuration = breakDuration;
            }
            saveSessionToHistory(filename, currentDuration, isWorkSession);

            forceNext(display, timerSprite, workTexture, breakTexture, bell);
        }
    }

    int minutes = std::max(0, static_cast<int>(timeLeft.asSeconds()) / 60);
    int seconds = std::max(0, static_cast<int>(timeLeft.asSeconds()) % 60);

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << minutes << ":"
       << std::setw(2) << std::setfill('0') << seconds;
    display.setString(ss.str());
}

void TimerLogic::loadHistory(const sf::Font &font, const std::string &filename)
{
    historyTexts.clear();

    std::ifstream file(filename);
    if (!file.is_open())
    {
        return;
    }

    std::string line;
    std::vector<std::string> allLines;
    while (std::getline(file, line))
    {
        allLines.push_back(line);
    }
    file.close();

    int startIdx = std::max(0, (int)allLines.size() - 8);
    float yPos = 120.0f;

    for (size_t i = startIdx; i < allLines.size(); ++i)
    {
        sf::Text hText(font, allLines[i], 24);
        hText.setFillColor(sf::Color::Black);
        hText.setPosition({100.0f, yPos});
        historyTexts.push_back(hText);
        yPos += 45.0f;
    }
}

void TimerLogic::drawHistory(sf::RenderWindow &window)
{
    for (const auto &text : historyTexts)
    {
        window.draw(text);
    }
}

std::string TimerLogic::formatTimeLogic(int totalSeconds)
{
    int minutes = std::max(0, totalSeconds / 60);
    int seconds = std::max(0, totalSeconds % 60);

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << minutes << ":"
       << std::setw(2) << std::setfill('0') << seconds;
    return ss.str();
}

std::string TimerLogic::formatFilenameLogic(std::string input)
{
    if (input.empty())
    {
        return "history.txt";
    }
    if (input.find(".txt") == std::string::npos)
    {
        input += ".txt";
    }
    return input;
}

bool TimerLogic::switchSessionLogic(bool currentIsWork)
{
    return !currentIsWork;
}