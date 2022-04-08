
class PIR {

    public:
        PIR(int pin);
        bool detect_motion();
    private:
        int _pin;
};
