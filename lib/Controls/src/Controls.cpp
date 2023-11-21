
#include <Constants.h>
#include <Arduino.h>
#include <Controls.h>

Controls::Controls(){

    analogReadResolution(12);

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


void Controls::read_analog_thumb( byte pin, byte pin_val){
    int val = analogRead(pin);
    pin_val = map(val, 0, 4095, 0, 255);
}


bool Controls::read_LR_buttons(){
    /*Read and assign vals to L & R Buttons*/ 
    uint16_t val_L = analogRead(_L_button_pin);
    uint16_t val_R = analogRead(_R_button_pin);
    byte map_L_val = map(val_L, 0, 4095, 0, 100);
    byte map_R_val = map(val_R, 0, 4095, 0, 100);
    
    
    if( map_L_val < 20){
        L_button_val = 0;
    }
    else if ( map_L_val >= 20 && map_L_val < 45){
        L_button_val = LEFT;
    }
    else if ( map_L_val >= 45 && map_L_val < 55){
        L_button_val = CENTER;
    }
     else if ( map_L_val >= 55){
        L_button_val = RIGHT;
    }
    else{
        L_button_val = 0;
        return false;
    }


    if( map_R_val < 20){
        R_button_val = 0;
    }
    if ( map_R_val >= 20 && map_R_val < 45){
        R_button_val = LEFT;
    }
    else if ( map_R_val >= 45 && map_R_val < 55){
        R_button_val = CENTER;
    }
     else if ( map_R_val >= 55){
        R_button_val = RIGHT;
    }
    else{
        R_button_val = 0;
        return false;
    }

    return true;
}

void Controls::read_buttons(){
    read_analog_thumb(_L_thumb_x_pin, L_thumb_x_val);
    read_analog_thumb(_L_thumb_y_pin, L_thumb_y_val);
    read_analog_thumb(_R_thumb_x_pin, R_thumb_x_val);
    read_analog_thumb(_R_thumb_y_pin, R_thumb_y_val);
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
    packet[0] = L_thumb_x_val;
    packet[1] = L_thumb_y_val;
    packet[2] = R_thumb_x_val;
    packet[3] = R_thumb_y_val;
    
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

    packet[4] = val;

    val = L_button_val;
    val <<= 2;
    val |= R_button_val;
    val <<= 2;
    val |= pair_val;

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


