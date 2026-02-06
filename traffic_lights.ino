#include "timer.h"
#include "blinker.h"
#include "button.h"

constexpr uint8_t led_car_r = 13u;
constexpr uint8_t led_car_y = 12u;
constexpr uint8_t led_car_g = 11u;

constexpr uint8_t led_human_r = 10u;
constexpr uint8_t led_human_g = 9u;

constexpr uint8_t pin_button = 8u;

void setup()
{
    Serial.begin(115200);

    pinMode(led_car_r, OUTPUT);
    pinMode(led_car_y, OUTPUT);
    pinMode(led_car_g, OUTPUT);

    pinMode(led_human_r, OUTPUT);
    pinMode(led_human_g, OUTPUT);

    pinMode(pin_button, INPUT);

    // Serial.print(sizeof(test));
}

void loop()
{
    // LEDs

    // Car

    static bool car_is_red = false;

    static bool car_is_yellow = false;

    static bool car_is_green = true;

    if (car_is_red)
    {
        digitalWrite(led_car_r, 1);
    }
    else
    {
        digitalWrite(led_car_r, 0);
    }

    if (car_is_yellow)
    {
        digitalWrite(led_car_y, 1);
    }
    else
    {
        digitalWrite(led_car_y, 0);
    }

    if (car_is_green)
    {
        digitalWrite(led_car_g, 1);
    }
    else
    {
        digitalWrite(led_car_g, 0);
    }

    // Human

    static bool human_is_red = true;

    static bool human_is_green = false;

    if (human_is_red)
    {
        digitalWrite(led_human_r, 1);
    }
    else
    {
        digitalWrite(led_human_r, 0);
    }

    if (human_is_green)
    {
        digitalWrite(led_human_g, 1);
    }
    else
    {
        digitalWrite(led_human_g, 0);
    }

    // Button

    static Button button(pin_button);

    static bool signal_to_unlock_button = false;
    static bool signal_click_button = false;
    
    button.check_click(
        &signal_to_unlock_button,
        &signal_click_button);
      
    // Car

    // Blinker Green

    static constexpr uint32_t interval_left = 1000u;
    static constexpr uint32_t interval_right = 1000u;
    static constexpr uint32_t limit_count = 3u;

    static Blinker blinker(
        interval_left,
        interval_right,
        limit_count);

    static bool blinker_finished = false;

    blinker(
        &signal_click_button,
        &car_is_green,
        nullptr,
        &blinker_finished);


    // Yellow

    static constexpr uint32_t duration_yellow = 3000u;

    static Timer timer_yellow(duration_yellow);

    static bool yellow_finished = false;

    timer_yellow(&blinker_finished, &car_is_yellow, &yellow_finished);

    // Red

    static constexpr uint32_t duration_red = 10000u;

    static Timer timer_red(duration_red);

    static bool red_finished = false;

    timer_red(&yellow_finished, &car_is_red, &red_finished);

    const bool reset = red_finished;
    
    // timer_red(&yellow_finished, &car_is_red, &signal_to_unlock_button);

    // Sleep

    static constexpr uint32_t duration_sleep = 5000u;

    static Timer timer_sleep(duration_sleep);

    timer_sleep(&red_finished, nullptr, &signal_to_unlock_button);

    // Reset state
    if (reset)
    {
        // Serial.println("In reset");
        
        car_is_red = false;
        car_is_yellow = false;
        car_is_green = true;

        // reset = false;
    }
    
    // Human

    if (car_is_red || car_is_red)
    {
        human_is_red = false;
        human_is_green = true;
    }

    if (car_is_green)
    {
        human_is_red = true;
        human_is_green = false;
    }

}
