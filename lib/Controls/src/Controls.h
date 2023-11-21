#ifndef CONTROLS_H
#define CONTROLS_H

#include <Arduino.h>
#include <Constants.h>
#include <Config.h>


class Controls{
    public:
        Controls();
        void get_button_data(byte* packet);
        /**
         * @brief     Get all button values from the controller
         *
         * @return
         *          None
         */
        bool run();

    private:  
        byte _L_thumb_y_pin = -1;
        byte _L_thumb_x_pin = -1;
        byte _R_thumb_y_pin = -1;
        byte _R_thumb_x_pin = -1;

        byte _L_up_pin = -1;
        byte _L_left_pin = -1;
        byte _L_down_pin = -1;
        byte _L_right_pin = -1;

        byte _R_up_pin = -1;
        byte _R_left_pin = -1;
        byte _R_down_pin = -1;
        byte _R_right_pin = -1;

        byte _L_button_pin = -1;
        byte _R_button_pin = -1;

        byte _pair_pin = -1;
     
        unsigned int L_thumb_x_val, L_thumb_y_val, R_thumb_x_val, R_thumb_y_val;
        byte L_button_val, R_button_val;
        byte L_up_val, L_left_val, L_down_val, L_right_val;
        byte R_up_val, R_left_val, R_down_val, R_right_val;
        byte pair_val;

        byte current_direction = 0;
        byte current_select = 0;
        byte _direction_pin;
        byte _select_pin;
        byte _prev_direction = 0;
        byte _prev_select = 0;

        void read_analog_thumb( byte pin, byte pin_val);
        bool read_LR_buttons();
        void read_buttons();

        unsigned long last_read_time;
        u_int16_t read_freq = 100; //100 ms between reads
        
};


#endif