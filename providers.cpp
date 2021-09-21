#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

#include <netdb.h>
#include <ifaddrs.h>

#include "providers.hpp"

Provider::Provider()
{
}

Provider::~Provider()
{
}

string Provider::getIp()
{
    struct ifaddrs *ifaddr, *ifa;
    int family, s, n;
    char host[NI_MAXHOST];

    string eth_addr;
    string wlan_addr;

    if (getifaddrs(&ifaddr) == -1)
    {
        return "GET IP ERROR";
    }

    for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++)
    {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        if (family == AF_INET)
        {
            s = getnameinfo(ifa->ifa_addr,
                            (family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
                            host, NI_MAXHOST,
                            NULL, 0, NI_NUMERICHOST);
            if (s != 0)
            {
                continue;
            }

            string ifa_name(ifa->ifa_name);
            string tmp_addr(host);

            if (ETH0.compare(ifa_name))
            {
                eth_addr = tmp_addr;
            }
            else if (WLAN0.compare(ifa_name))
            {
                wlan_addr = tmp_addr;
            }
        }
    }

    freeifaddrs(ifaddr);

    return !wlan_addr.empty() ? wlan_addr : (!eth_addr.empty() ? eth_addr : "IP NOT FOUND");
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