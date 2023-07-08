#include "display.h"
#include <EasyNextionLibrary.h>
#include <FlexCAN_T4.h>
#include "apps.h"

#define NEXTION_PORT Serial1

EasyNex myNex(NEXTION_PORT);

int speedInt = 0;
int high_tempInt = 0;
int socInt = 1002;
int current_page = 0;
int switchPin = 14;
int sensorValue = 0;
int current = 0;
int pack_voltage = 0;
int low_tempInt = 0;
int power_stage_temp = 0;
int motor_temp = 0;
int rpm = 0;
int ac_current = 0;

extern CAN_message_t request_actual_speed;
extern CAN_message_t request_motor_temp;
extern CAN_message_t request_current;
extern CAN_message_t request_powerStage_temp;
extern CAN_message_t request_rpm;

extern FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;

void setup_display() {
    myNex.begin(9600);
    // Serial.begin(38400);
    pinMode(switchPin, INPUT);

    can1.write(request_current);
    can1.write(request_motor_temp);
    //can1.write(request_powerStage_temp);
    can1.write(request_rpm);
}

void control_display() {
    myNex.NextionListen();

    int sensorValue = analogRead(switchPin);

    // Map the sensor value to the switch position
    int switchPosition = mapSensorValueToSwitchNumber(sensorValue);

    char mode[28];

    sprintf(mode, "MODE %d", switchPosition);

    myNex.writeStr("t3.txt", mode);

    myNex.writeNum("n0.val", speedInt);
    myNex.writeNum("x0.val", socInt * 10);
    myNex.writeNum("x1.val", high_tempInt * 10);
    myNex.writeNum("x2.val", pack_voltage);
    myNex.writeNum("x3.val", current);
    myNex.writeNum("x4.val", motor_temp);
    myNex.writeNum("x5.val", power_stage_temp);
    myNex.writeNum("x7.val", ac_current);
    myNex.writeNum("x8.val", rpm);
    myNex.writeNum("x9.val", high_tempInt);
    myNex.writeNum("x10.val", low_tempInt);
}

int mapSensorValueToSwitchNumber(int sensorValue) {
    int rotswitchNumber = 0;

    float posicao = sensorValue;

    posicao /= 93;

    rotswitchNumber = round(posicao);
    return rotswitchNumber;
}
