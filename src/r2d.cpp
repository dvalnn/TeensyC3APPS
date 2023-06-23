#include "r2d.h"
#include <Arduino.h>
#include <FlexCAN_T4.h>


FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can1;

int check_bamocar() {
    CAN_message_t msg;
    if(can1.read(msg)) {
        if(msg.buf[0] == 0x8F) {
            uint32_t data = msg.buf[1] + msg.buf[2];
            switch (data) { //all possible errors. O que fazer quando são detetados??
                case 1:
                    //Parameter damaged 
                    break;
                case 2:
                    //Hardware error
                    break;
                case 4:
                    //Safety circuit faulty (only active with RUN)
                    break;
                case 8:
                    //CAN TimeOut Time exceeded 
                    break;
                case 16:
                    //Bad or wrong encoder signal
                    break;
                case 32:
                    //Power voltage missing
                    break;
                case 64:
                    //Engine temperature too high 
                    break;
                case 128:
                    //Unit temperature too high
                    break;
                case 256:
                    //Overvoltage > 1.8 x UN reached
                    break;
                case 512:
                    //Overcurrent or strong oscillating current detected 
                    break;
                case 1024:
                    //Spinning (without setpoint, wrong direction)
                    break;
                case 2048:
                    //User - Error selection
                    break;
                case 16384:
                    //Current - Measurement error
                    break;
                case 32768:
                    //Ballast circuit overloaded 
                    break;
            }
        }
    }
    return 0;
}

void can_setup() {
    can1.begin();
    can1.setBaudRate(500000);
}

int send_to_bamocar(int value_bamo) {
    uint8_t byte1 = (value_bamo >> 8) & 0xFF;  // MSB
    uint8_t byte2 = value_bamo & 0xFF;         // LSB

    // Serial.print("byte1: ");
    // Serial.print(byte1, HEX);
    // Serial.print("\n byte2: ");
    // Serial.print(byte2, HEX);
    // definir a mensagem de acordo com o que o BAMOCAR pede
    // speed command value

    // Serial.printf("\n Value sent: %d", value_bamo);

    CAN_message_t msg;
    msg.id = 0x201;
    msg.len = 3;
    msg.buf[0] = 0x31;
    msg.buf[1] = byte2;
    msg.buf[2] = byte1;

    // Serial.print("Sent message with ID 0x");
    // Serial.print(msg.id, HEX);
    // Serial.print(": ");
    // for (int i = 0; i < msg.len; i++) {
    //     Serial.print(msg.buf[i]);
    // }

    can1.write(msg);

    // Serial.println("\n Message sent!");
    return 0;
}

int check_BMS() {
    return 0;
}

int play_r2d_sound() {
    return 0;
}

void r2d_state_update(r2d_mode* state) {
    return;
}

r2d_mode r2d_state_machine(r2d_mode cur_state) {
    r2d_mode next_state = cur_state;
    switch (cur_state) {
        case R2D_MODE_STARTUP:
            // delay(POWER_ON_DELAY_MS);
            next_state = R2D_MODE_IDLE;
            break;
        case R2D_MODE_IDLE:
            // check bamo
            // check bms
            // check apps
            // check modo dash
            // check modo volante
            // check fim precharge
            // check r2d button
            // check brake
            // update display
            break;
        case R2D_MODE_DRIVE:

            break;
        case R2D_MODE_ERROR:
            break;

        default:
            next_state = R2D_MODE_ERROR;
            break;
    }
    return next_state;
}
