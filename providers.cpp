#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>
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

string Provider::getTimeInfo(string format)
{
    time_t rawtime;
    time(&rawtime);

    tm *timeinfo;
    timeinfo = localtime(&rawtime);

    char buffer[16];
    strftime(buffer, sizeof(buffer), format.c_str(), timeinfo);
    string s(buffer);
    return s;
}

string Provider::getBtcExchangeRate(string currency)
{
    return "404";
}

string Provider::getTemperature(string city)
{
    return "404";
}

string Provider::getQuoteOfTheDay()
{
    return "404";
}

string Provider::getStocks()
{
    return "404";
}