#include <DHT.h>
#include <vector>

#define DHT0PIN 6
#define DHT1PIN 7
#define DHTTYPE DHT11

struct Reading
{
    float temp;
    float humd;

    Reading(float t, float h) : temp(t), humd(h) {}
};

class DHTSensor
{
public:
    DHTSensor(bool isFahrenheit = false);
    ~DHTSensor(){};

    float readTemperature();
    int readHumidity();

private:
    Reading readOneSensor(int sensorIndex);
    void safeRead();
    int humidity;
    float temperature;
    bool isFahrenheit;
    std::vector<DHT> dhtSensors;
};