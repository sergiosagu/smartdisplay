#include <string>

using namespace std;

// CONSTANTS

// From https://www.cplusplus.com/reference/ctime/strftime/
const string TIME1 = "%T";                    // "12:34:56"
const string TIME2 = "%R";                    // "12:34"
const string DATE1 = "%a %d %b %Y";           // "Fri 25 Dec 2020"
const string DATE2 = "%d/%m/%Y";              // "25/12/2020"
const string TIMEDATE1 = "%a %d %b %R";       // "Thu 24 Jun 17:30"
const string TIMEDATE2 = TIME2 + " " + DATE2; // "17:30 24/06/2021"

const string EXCHANGE_URL = "https://api.cryptonator.com/api/ticker/";
const string USD = "btc-usd";
const string EUR = "btc-eur";

class Provider
{
public:
    Provider();
    ~Provider();

    static string getIp();
    static string getTimeInfo(string format);
    static string getBtcExchangeRate(string currency);
    static string getTemperature(string city);
    static string getQuoteOfTheDay();
    static string getStocks();
};
