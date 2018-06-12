#include <iostream>

class BleapoBpm {
    public:
        void Initialize(int interval, int sample, int delay, int pin);
        ~BleapoBpm();
        void Tick();

    
    private:
        const int BEAT_THRESHOLD = 2000;

        int intervalBetweenReads;
        int sampleSize;
        int loopDelay;
        int currentInterval = 0;
        int calculatedBpmIndex = 0;
        int signalPin;

        float *calculatedBpms;
        float msInterval;

        bool beatEnded;
        bool beatStarted;
        bool isCalculatingBeat;


        float calculateBpmMean();
};