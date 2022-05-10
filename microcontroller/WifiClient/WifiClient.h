#include <Arduino.h>

class WifiClient
{
public:
    WifiClient(String ssid, String pass);
    void connect();
private:
    String _ssid;
    String _pass;
};