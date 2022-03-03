#include "NixieController.hpp"

// SN74141 : True Table
//D C B A #
//L,L,L,L 0
//L,L,L,H 1
//L,L,H,L 2
//L,L,H,H 3
//L,H,L,L 4
//L,H,L,H 5
//L,H,H,L 6
//L,H,H,H 7
//H,L,L,L 8
//H,L,L,H 9

#define SN74141_A 19
#define SN74141_B 18
#define SN74141_C 5
#define SN74141_D 17

#define ANODE_1 32
#define ANODE_2 33
#define ANODE_3 25
#define ANODE_4 26
#define ANODE_5 27
#define ANODE_6 14

#define POWER_PIN 22
#define DELIMITER_PIN 23

const int anodes[] = {ANODE_1, ANODE_2, ANODE_3, ANODE_4, ANODE_5, ANODE_6};

void NixieController::initialize() {
    Log.noticeln("Initializing nixies");
    powerStatus = OFF;
    pinMode(SN74141_A, OUTPUT);
    pinMode(SN74141_B, OUTPUT);
    pinMode(SN74141_C, OUTPUT);
    pinMode(SN74141_D, OUTPUT);

    pinMode(ANODE_1, OUTPUT);
    pinMode(ANODE_2, OUTPUT);
    pinMode(ANODE_3, OUTPUT);
    pinMode(ANODE_4, OUTPUT);
    pinMode(ANODE_5, OUTPUT);
    pinMode(ANODE_6, OUTPUT);

    pinMode(POWER_PIN, OUTPUT);

}

BinaryCodedDecimal_t decimalTo4BitBinary(int decimal_number) {
    BinaryCodedDecimal_t binaryCodedDecimal;
    if (decimal_number > 9) {
        Log.warningln("error in decimal conversion: number too big");
        binaryCodedDecimal.a = true;
        binaryCodedDecimal.b = true;
        binaryCodedDecimal.c = true;
        binaryCodedDecimal.d = true;
        return binaryCodedDecimal;
    }
    int binaryNumber[4];
    binaryNumber[0] = 0;
    binaryNumber[1] = 0;
    binaryNumber[2] = 0;
    binaryNumber[3] = 0;
    int i = 0;
    while (decimal_number > 0) {
        binaryNumber[i] = decimal_number % 2;
        decimal_number = decimal_number / 2;
        i++;
    }
    binaryCodedDecimal.a = binaryNumber[0];
    binaryCodedDecimal.b = binaryNumber[1];
    binaryCodedDecimal.c = binaryNumber[2];
    binaryCodedDecimal.d = binaryNumber[3];
    return binaryCodedDecimal;
}

void turnAnodesOff() {
    for (auto anode: anodes) {
        digitalWrite(anode, LOW);
    }
}

void NixieController::displayBCD(int anode, BinaryCodedDecimal_t binaryCodedDecimal) {
    int anodePin = anodes[anode];

    digitalWrite(SN74141_D, binaryCodedDecimal.d);
    digitalWrite(SN74141_C, binaryCodedDecimal.c);
    digitalWrite(SN74141_B, binaryCodedDecimal.b);
    digitalWrite(SN74141_A, binaryCodedDecimal.a);

    digitalWrite(anodePin, HIGH);
    delay(2);
    digitalWrite(anodePin, LOW);
}

void NixieController::displayValues() {
    for (int i = 0; i < 6; i++) {
        turnAnodesOff();
        delayMicroseconds(15);
        displayBCD(i, this->bcdValues[i]);
    }
}

void NixieController::togglePowerSupply() {
    powerStatus = (powerStatus == ON) ? OFF : ON;
    Log.noticeln(("Setting power pin to " + std::string(powerStatus == ON ? "ON" : "OFF")).c_str());
    digitalWrite(POWER_PIN, powerStatus);
}

void NixieController::setNixieValues(NixieValues_t nixieValues) {
    bcdValues[0] = decimalTo4BitBinary(nixieValues.nixie1);
    bcdValues[1] = decimalTo4BitBinary(nixieValues.nixie2);
    bcdValues[2] = decimalTo4BitBinary(nixieValues.nixie3);
    bcdValues[3] = decimalTo4BitBinary(nixieValues.nixie4);
    bcdValues[4] = decimalTo4BitBinary(nixieValues.nixie5);
    bcdValues[5] = decimalTo4BitBinary(nixieValues.nixie6);
}

#if USE_DELIMITERS
void NixieController::toggleDelimiters() {
    delimiterStatus = (delimiterStatus == ON) ? OFF : ON;
    Log.noticeln(("Setting delimiter pin to " + String(this->delimiterStatus)).c_str());
    digitalWrite(DELIMITER_PIN, this->delimiterStatus);
}
#endif
