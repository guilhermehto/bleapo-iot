#include <iostream>
#include "BleapoBpm.h"
#include <Arduino.h>

using namespace std;

void BleapoBpm::Initialize(int interval, int sample, int delay, int pin) {
    loopDelay = delay;
    sampleSize = sample;
    intervalBetweenReads = interval;
    calculatedBpms = new float[sampleSize];
    signalPin = pin;
    pinMode(signalPin, INPUT);
}

BleapoBpm::~BleapoBpm() {
    delete[] calculatedBpms;
}

/*
** Called in every loop cycle
*/
void BleapoBpm::Tick() {
    currentInterval += loopDelay;

    if (currentInterval < intervalBetweenReads) {
        return;
    }

    int beatSignal = analogRead(signalPin);

    if (!beatStarted) {
        if (beatSignal >= BEAT_THRESHOLD) {
            if (!isCalculatingBeat) {
                isCalculatingBeat = true;
            } else {
                isCalculatingBeat = false;
                float bpm = 60000 / msInterval;
                bpm = bpm * 2; //don't ask me
                calculatedBpms[calculatedBpmIndex] = bpm;
                calculatedBpmIndex += 1;
                if (calculatedBpmIndex == sampleSize) {
                    calculatedBpmIndex = 0;
                    currentInterval = 0;
                    float currentBpm = calculateBpmMean();
                    Serial.println("Mean [BPM-MEAN]: " + String(currentBpm));
                }
                Serial.println("Current [BPM]: " + String(bpm));
                Serial.println("Interval: " + String(msInterval));
                msInterval = 0;
            }
            beatStarted = true;
            beatEnded = false;
        }
    } else if (beatSignal < BEAT_THRESHOLD) {
        beatStarted = false;
        beatEnded = true;
    }

    msInterval += 20;
}


float BleapoBpm::calculateBpmMean() {
    float bpmSum = 0;
    for (int c = 0; c < sampleSize; c++) {
        bpmSum += calculatedBpms[c];
    }
    return bpmSum / sampleSize;
}