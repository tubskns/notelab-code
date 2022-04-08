#include "DHT.h" // DHT module library

class DHT11
{
    public:
        DHT11(DHT dht);
        float get_humidity();
        float get_temperature();

    private:
        DHT _dht;
};