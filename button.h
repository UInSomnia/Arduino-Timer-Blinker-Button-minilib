#ifndef INSOMNIA_BUTTON_H
#define INSOMNIA_BUTTON_H

class Button
{
public:
    Button() :
    idx_pin_(-1),
    is_locked_(false) {}

    Button(const uint8_t idx_pin) :
    idx_pin_(idx_pin),
    is_locked_(false) {}

    void check_click(
        bool *signal_to_unlock,
        bool *signal_click)
    {
        if (signal_to_unlock == nullptr)
        {
            Serial.println("Error: Signal_to_unlock is null pointer");
            return;
        }

        if (signal_click == nullptr)
        {
            Serial.println("Error: Signal_click is null pointer");
            return;
        }

        if (*signal_to_unlock)
        {
            this->is_locked_ = false;
            *signal_to_unlock = false;
        }

        const bool is_pressed_button =
            digitalRead(this->idx_pin_);

        if (!(this->is_locked_) && is_pressed_button)
        {
            this->is_locked_ = true;
            *signal_click = true;
        }
    }

private:
    uint8_t idx_pin_;
    bool is_locked_;
};

#endif
