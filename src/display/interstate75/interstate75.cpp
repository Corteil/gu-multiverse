#include "display.hpp"
#include "drivers/hub75/hub75.hpp"
#include "common/pimoroni_common.hpp"
#include "pico/stdlib.h"

using namespace pimoroni;

// Set how many LEDs you have
const uint NUM_LEDS = 4096;

//Hub75 hub75(64, 64, nullptr, PANEL_FM6126A, false);
Hub75 hub75(64, 64, nullptr, PANEL_GENERIC, false);

PicoGraphics_PenRGB888 graphics(hub75.width, hub75.height, nullptr);

// Callback for the dma interrupt (required)
void __isr dma_complete() {
  hub75.dma_complete();
}

namespace display {
    uint8_t buffer[BUFFER_SIZE];
    PicoGraphics_PenRGB888 graphics(WIDTH, HEIGHT, &buffer);

    


    void init() {
        
         hub75.start(dma_complete);
    }

    void info(std::string_view text) {
        graphics.set_pen(0, 0, 0);
        graphics.clear();
        graphics.set_pen(255, 255, 255);
        graphics.set_font("bitmap5");
        graphics.text(text, Point(0, 0), WIDTH, 1);
        update();
    }


    /*
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
                    
                    
                    uint8_t blue = buffer[buffer_index] * 0.4; // Scale down the blue value
                    uint8_t green = buffer[buffer_index + 1] * 0.4; // Scale down the green value
                    uint8_t red = buffer[buffer_index + 2] * 0.4; // Scale down the red value
                    
                    led_strip[hat_x_offset].set_rgb(unicorn_pixel_address[strip_index], red, green, blue);
                    
                };
        update_all();

  //cout << "-------------------\n";
        }
    }

*/
        void update() {
        // display update
        
        hub75.update(&graphics);
    }



    void play_note(uint8_t channel, uint16_t freq, uint8_t waveform, uint16_t a, uint16_t d, uint16_t s, uint16_t r, uint8_t phase) {
        // not supported on the Gigantic Unicorn
    }

    void play_audio(uint8_t *audio_buffer, size_t len) {
        // not supported on the Gigantic Unicorn
    } 
}