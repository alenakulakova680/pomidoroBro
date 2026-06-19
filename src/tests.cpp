#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <string>
#include "TimerLogic.hpp"

TEST_CASE("1. Testing Time Formatting Logic") {
    CHECK(TimerLogic::formatTimeLogic(1500) == "25:00"); 
    CHECK(TimerLogic::formatTimeLogic(299) == "04:59");  
    CHECK(TimerLogic::formatTimeLogic(5) == "00:05");    

    CHECK(TimerLogic::formatTimeLogic(0) == "00:00");     
    CHECK(TimerLogic::formatTimeLogic(-1) == "00:00");    
    CHECK(TimerLogic::formatTimeLogic(-3600) == "00:00"); 
}

TEST_CASE("2. Testing Filename Configuration Logic") {
    CHECK(TimerLogic::formatFilenameLogic("my_history") == "my_history.txt"); 
    CHECK(TimerLogic::formatFilenameLogic("session.txt") == "session.txt");   

    CHECK(TimerLogic::formatFilenameLogic("") == "history.txt");             
    CHECK(TimerLogic::formatFilenameLogic(".txt") == ".txt");                 
}

TEST_CASE("3. Testing Session Switching Logic") {
    bool isWork = true;
    isWork = TimerLogic::switchSessionLogic(isWork);
    CHECK(isWork == false); 

    isWork = TimerLogic::switchSessionLogic(isWork);
    CHECK(isWork == true);  
}