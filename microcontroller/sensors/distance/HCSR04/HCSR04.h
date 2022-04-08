
class HCSR04
{
    public:
        HCSR04(int trigPin, int echoPin);
        int calculate_distance();

    private:
        int _trigPin;
        int _echoPin;
};