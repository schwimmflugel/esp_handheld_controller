
#include <Constants.h>
#include <Arduino.h>
#include <Controls.h>

Controls::Controls(){

    analogReadResolution(12);

    left_stick.y_pin = 1;
    left_stick.x_pin = 4;
    right_stick.y_pin = 6;
    right_stick.x_pin = 7;

    pinMode(_L_up_pin, INPUT);
    pinMode(_L_left_pin, INPUT);
    pinMode(_L_down_pin, INPUT);
    pinMode(_L_right_pin, INPUT);

    pinMode(_R_up_pin, INPUT);
    pinMode(_R_left_pin, INPUT);
    pinMode(_R_down_pin, INPUT);
    pinMode(_R_right_pin, INPUT);

    pinMode(_pair_pin, INPUT);

}

void Controls::begin(){
    delay(500);
    read_offset(left_stick);
    read_offset(right_stick);
}


void Controls::read_analog_thumb( thumbstick &stick){
    int16_t x_val = analogRead(stick.x_pin);
    int16_t y_val = analogRead(stick.y_pin);

    x_val -= stick.x_offset;
    y_val -= stick.y_offset;

    x_val = constrain(x_val, _min_volt, _max_volt);
    y_val = constrain(y_val, _min_volt, _max_volt);

    /*Serial.print("X Val:");
    Serial.println(x_val);   
    Serial.print("Y Val:");
    Serial.println(y_val);*/

    stick.x_val = map(x_val, _min_volt, _max_volt, 0, 255);
    stick.y_val = map(y_val, _min_volt, _max_volt, 0, 255);
}

void Controls::read_offset(thumbstick &stick){
    int16_t x_val = analogRead(stick.x_pin);
    int16_t y_val = analogRead(stick.y_pin);

    stick.x_offset = x_val - 2048;
    stick.y_offset = y_val - 2048;
}


bool Controls::read_LR_buttons(){
    /*Read and assign vals to L & R Buttons*/ 
    uint16_t val_L = analogRead(_L_button_pin);
    uint16_t val_R = analogRead(_R_button_pin);
    byte map_L_val = map(val_L, 0, 4095, 0, 100);
    byte map_R_val = map(val_R, 0, 4095, 0, 100);
    /*Serial.print("Left Val:");
    Serial.println(map_L_val);
    Serial.print("Right Val:");
    Serial.println(map_R_val); */
    
    if( map_L_val < 30){
        L_button_val = 0;
    }
    else if ( map_L_val >= 30 && map_L_val < 50){
        L_button_val = RIGHT;
    }
    else if ( map_L_val >= 50 && map_L_val < 70){
        L_button_val = CENTER;
    }
     else if ( map_L_val >= 70){
        L_button_val = LEFT;
    }
    else{
        L_button_val = 0;
        return false;
    }


    if( map_R_val < 30){
        R_button_val = 0;
    }
    if ( map_R_val >= 30 && map_R_val < 50){
        R_button_val = RIGHT;
    }
    else if ( map_R_val >= 50 && map_R_val < 70){
        R_button_val = CENTER;
    }
     else if ( map_R_val >= 70){
        R_button_val = LEFT;
    }
    else{
        R_button_val = 0;
        return false;
    }

    return true;
}

void Controls::read_buttons(){
    read_analog_thumb(left_stick);
    read_analog_thumb(right_stick);
    read_LR_buttons();

    L_up_val = digitalRead(_L_up_pin);
    L_left_val = digitalRead(_L_left_pin);
    L_down_val = digitalRead(_L_down_pin);
    L_right_val = digitalRead(_L_right_pin);

    R_up_val = digitalRead(_R_up_pin);
    R_left_val = digitalRead(_R_left_pin);
    R_down_val = digitalRead(_R_down_pin);
    R_right_val = digitalRead(_R_right_pin);

    pair_val = digitalRead(_pair_pin);
}

void Controls::get_button_data(byte* packet){
    packet[0] = 255 - left_stick.x_val; //Flip thumbstick direction
    packet[1] = left_stick.y_val;
    packet[2] = 255 - right_stick.x_val;
    packet[3] = 255 - right_stick.y_val;
    
    byte val = L_up_val;
    val <<= 1;
    val |= L_left_val;
    val <<= 1;
    val |= L_down_val;
    val <<= 1;
    val |= L_right_val;
    val <<= 1;
    val |= R_up_val;
    val <<= 1;
    val |= R_left_val;
    val <<= 1;
    val |= R_down_val;
    val <<= 1;
    val |= R_right_val;

    packet[4] = ~val;

    val = L_button_val;
    val <<= 2;
    val |= R_button_val;
    val <<= 1;
    val |= !pair_val;

    packet[5] = val;
}

bool Controls::run(){
    /*Return true if buttons are read, false if no read*/
    long present_time = millis();
    if ( present_time - last_read_time  >= read_freq ){
        read_buttons();
        last_read_time = present_time;
        return true;
    }
    return false;


}

/*
void Controls::button_state_change(){
    byte val = read_direction();
    if( val != _prev_direction){
        _prev_direction = val;
        return val; //Return the direction value only if its different
    }
    
    return -1; //Return -1 if no state change
}
*/


