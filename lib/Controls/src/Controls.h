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

        void begin();
        

    private:  

        struct thumbstick{
            byte x_pin;
            byte y_pin;
            uint16_t x_val;
            uint16_t y_val;
            int16_t x_offset;
            int16_t y_offset;
        };

        thumbstick left_stick;
        thumbstick right_stick;

        uint16_t _max_volt = 3295;
        uint16_t _min_volt = 800;
        
        byte _L_up_pin = 43;
        byte _L_left_pin = 44;
        byte _L_down_pin = 42;
        byte _L_right_pin = 41;

        byte _R_up_pin = 15;
        byte _R_left_pin = 17;
        byte _R_down_pin = 18;
        byte _R_right_pin = 16;

        byte _L_button_pin = 2;
        byte _R_button_pin = 5;

        byte _pair_pin = 40;
     
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

        //void read_analog_thumb( byte pin, uint16_t &pin_val, int16_t offset = 0);
        void read_analog_thumb( thumbstick &stick);
        bool read_LR_buttons();
        void read_buttons();
        void read_offset(thumbstick &stick);

        unsigned long last_read_time;
        u_int16_t read_freq = 200; //100 ms between reads
        
};


#endif