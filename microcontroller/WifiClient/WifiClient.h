class WifiClient
{
public:
    WifiClient(char *ssid, char *pass);
    void connect();

private:
    char *_ssid;
    char *_pass;
};