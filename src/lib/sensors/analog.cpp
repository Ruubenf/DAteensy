#include "analog.h"

namespace ANALOG
{
    // given a int readed by analog read, get voltage
    float int2voltage(int value)
    {
        return (value * (3.3 / 1023.0)) * 2;
    }

    // For adc read
    float int2voltageADC(int value)
    {
        return (value * (3.3 / 4095.0)) * 2;
    }

    float int2pressurefuel(int value)
    {
        float voltage = int2voltage(value);
        const float minVoltage = 0.5;
        const float maxVoltage = 4.5;
        const float minPressure = 0.0;
        const float maxPressure = 10.0;

        Serial.println(int(maxVoltage * 100));

        // Map the voltage to the pressure range using the map() function
        float pressure = map(int(voltage * 100), minVoltage * 100, maxVoltage * 100, minPressure * 100, maxPressure * 100) / 100.0;

        return pressure;
    }

    // all 4 analog suspension linear potentiometers
    float readSuspension(int pin)
    {
        int value = analogRead(pin);
        float voltage = int2voltage(value);
        const float minVoltage = 0;
        const float maxVoltage = 5;
        // min max cm of movment
        const float minSuspension = 0;
        const float maxSuspension = 7;

        // Map the voltage to the pressure range using the map() function
        float suspension = map(int(voltage * 100), minVoltage * 100, maxVoltage * 100, minSuspension * 100, maxSuspension * 100) / 100.0;

        return suspension;
    }

    float sensorToBars(int pin, int minSensorValue, int maxSensorValue, float minBarValue, float maxBarValue)
    {

        // Read the sensor value
        int sensorValue = analogRead(pin);

        // Ensure the sensor value is within the valid range
        sensorValue = constrain(sensorValue, minSensorValue, maxSensorValue);

        // Map the sensor value to the corresponding bar value
        float barValue = map(sensorValue, minSensorValue, maxSensorValue, minBarValue, maxBarValue);

        // Return the bar value
        return barValue;
    }

}