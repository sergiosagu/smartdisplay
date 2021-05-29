#include <string>

using namespace std;

class Provider
{
public:
    Provider();
    ~Provider();

    static string getIp();
    static string getTime();
    static string getDate();
    static string getDateTime();
};
