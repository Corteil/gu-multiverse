#include "display.hpp"
#include "drivers\plasma\ws2812.hpp"
#include "common/pimoroni_common.hpp"
#include "pico/stdlib.h"

using namespace pimoroni;
using namespace plasma;

// Set how many LEDs you have
const uint NUM_LEDS = 64;

// Set how many Unicorn Hats you have

const uint NUM_PICOS = 8; // 8x8 grid of Unicorn Hats =  8, 3x3 grid of Unicorn Hats = 3

// Unicorns Hats setup, for 8x8, int? 

WS2812 led_strip[8] = {
    WS2812(NUM_LEDS, pio0, 0, 21, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB),
    WS2812(NUM_LEDS, pio0, 1, 20, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB),
    WS2812(NUM_LEDS, pio0, 2, 19, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB),
    WS2812(NUM_LEDS, pio0, 3, 18, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB),
    WS2812(NUM_LEDS, pio1, 0, 17, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB),
    WS2812(NUM_LEDS, pio1, 1, 16, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB),
    WS2812(NUM_LEDS, pio1, 2, 15, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB),
    WS2812(NUM_LEDS, pio1, 3, 14, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB)
};
/*

WS2812 led_strip[3] = {
    WS2812(NUM_LEDS, pio0, 0, 19, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB),
    WS2812(NUM_LEDS, pio0, 1, 20, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB),
    WS2812(NUM_LEDS, pio0, 2, 21, WS2812::DEFAULT_SERIAL_FREQ, false, WS2812::COLOR_ORDER::GRB)
};

int unicorn_pixel_address[64] = {7 , 6 , 5 , 4 , 3 , 2 , 1 , 0,
                                8 , 9 , 10, 11, 12, 13, 14, 15,
                                23, 22, 21, 20, 19, 18, 17, 16,
                                24, 25, 26, 27, 28, 29, 30, 31,
                                39, 38, 37, 36, 35, 34, 33, 32,
                                40, 41, 42, 43, 44, 45, 46, 47,
                                55, 54, 53, 52, 51, 50, 49, 48,
                                56, 57, 58, 59, 60, 61, 62, 63};
*/
int unicorn_pixel_address[64] = {0, 15, 16, 31, 32, 47, 48, 63,
                                1, 14, 17, 30, 33, 46, 49, 62,
                                2, 13, 18, 29, 34, 45, 50, 61,
                                3, 12, 19, 28, 35, 44, 51, 60,
                                4, 11, 20, 27, 36, 43, 52, 59,
                                5, 10, 21, 26, 37, 42, 53, 58,
                                6, 9, 22, 25, 38, 41, 54, 57,
                                7, 8, 23, 24, 39, 40, 55, 56};


namespace display {
    uint8_t buffer[BUFFER_SIZE];
    PicoGraphics_PenRGB888 graphics(WIDTH, HEIGHT, &buffer);

    


    void init() {
        // Initialize the Unicorn Hats

        for (int i = 0; i < NUM_PICOS; i++) {
        led_strip[i].start(60);
        //led_strip[i].set_brightness(0.001); // not required
        led_strip[i].clear(); // Clear the strip
        led_strip[i].update(); // Update the strip to show the changes
    }

        //info("rdy");
    }

    void info(std::string_view text) {
        graphics.set_pen(0, 0, 0);
        graphics.clear();
        graphics.set_pen(255, 255, 255);
        graphics.set_font("bitmap5");
        graphics.text(text, Point(0, 0), WIDTH, 1);
        update();
    }

    void set_rgb_all(uint8_t r, uint8_t g, uint8_t b, uint8_t w=0) {
        for (int unicorn = 0; unicorn < NUM_PICOS; unicorn++) {
            for (int index = 0; index < NUM_LEDS; index++) {
                led_strip[unicorn].set_rgb(index, r, g, b, w);

            }
        }
    }

    void update_all() {
        for (int i = 0; i < NUM_PICOS; i++) {
            led_strip[i].update();
        }
    }

    void clear_all() {
        for (int i = 0; i < NUM_PICOS; i++) {
            led_strip[i].clear();
    }
}
/*
    void update() {
        // display update
        for (int x=0; x < WIDTH; x++) {
                int hat_x_offset = x / floor(8); 
                int unicorn_x = x % 8; 
                //cout << "Hat x off: " << hat_x_offset << " ## ";
                for (int y=0; y < HEIGHT; y++) {
                	int hat_y_offset = y / floor(8); 
                	int unicorn_y = y % 8;
                	
                    int buffer_index = (x + y * WIDTH) * 4; // Calculate the index in the buffer
                    int strip_index = unicorn_y * 8 + unicorn_x; // Calculate the index in the strip
                    
                    
                    uint8_t blue = buffer[buffer_index] * 0.5; // Scale down the blue value
                    uint8_t green = buffer[buffer_index + 1] * 0.5; // Scale down the green value
                    uint8_t red = buffer[buffer_index + 2] * 0.5; // Scale down the red value
                    
                    led_strip[hat_x_offset].set_rgb(unicorn_pixel_address[strip_index], red, green, blue);
                    
                };
        update_all();

  //cout << "-------------------\n";
        }
    }
*/

        void update() {
        // display update
        for (int y=0; y < HEIGHT; y++) {
                int hat_y_offset = y / floor(8); 
                int unicorn_y = y % 8; 
                //cout << "Hat x off: " << hat_x_offset << " ## ";
                for (int x=0; x < WIDTH; x++) {
                	int hat_x_offset = x / floor(8); 
                	int unicorn_x = x % 8;
                	
                    int buffer_index = (x + y * WIDTH) * 4; // Calculate the index in the buffer
                    int strip_index = unicorn_x * 8 + unicorn_y; // Calculate the index in the strip
                    
                    
                    uint8_t blue = buffer[buffer_index] * 0.5; // Scale down the blue value
                    uint8_t green = buffer[buffer_index + 1] * 0.5; // Scale down the green value
                    uint8_t red = buffer[buffer_index + 2] * 0.5; // Scale down the red value
                    
                    led_strip[hat_x_offset].set_rgb(unicorn_pixel_address[strip_index], red, green, blue);
                    
                };
        update_all();

  //cout << "-------------------\n";
        }
    }


    void play_note(uint8_t channel, uint16_t freq, uint8_t waveform, uint16_t a, uint16_t d, uint16_t s, uint16_t r, uint8_t phase) {
        // not supported on the Gigantic Unicorn
    }

    void play_audio(uint8_t *audio_buffer, size_t len) {
        // not supported on the Gigantic Unicorn
    } 
}