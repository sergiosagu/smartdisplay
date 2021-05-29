#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "providers.hpp"

Provider::Provider()
{
}

Provider::~Provider()
{
}

string Provider::getIp()
{
    return "172.16.0.1";
}

struct tm *getLocaltime()
{
    time_t rawtime;
    time(&rawtime);
    return localtime(&rawtime);
}

string Provider::getTime()
{
    tm *timeinfo;
    timeinfo = getLocaltime();
    char buffer[32];
    strftime(buffer, sizeof(buffer), "%T", timeinfo);
    string s(buffer);
    return s;
}

string Provider::getDate()
{
    tm *timeinfo;
    timeinfo = getLocaltime();
    char buffer[32];
    strftime(buffer, sizeof(buffer), "%F", timeinfo);
    string s(buffer);
    return s;
}

string Provider::getDateTime()
{
    tm *timeinfo;
    timeinfo = getLocaltime();
    char buffer[32];
    strftime(buffer, sizeof(buffer), "%a %b %e %R", timeinfo);
    string s(buffer);
    return s;
}