
class HCSR04
{
    public:
        HCSR04(int trigPin, int echoPin);
        float calculate_distance();

    private:
        int _trigPin;
        int _echoPin;
};
