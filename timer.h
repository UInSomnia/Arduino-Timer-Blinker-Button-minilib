#ifndef INSOMNIA_TIMER_H
#define INSOMNIA_TIMER_H

class Timer
{
public:
    Timer() :
        interval_(0u),
        time_start_(0u),
        is_active_(false) {}

    Timer(const uint32_t interval) :
        interval_(interval),
        time_start_(0u),
        is_active_(false) {}

    void operator () (
        bool *signal,
        bool *active,
        bool *finish)
    {
        const uint32_t now = millis();

        if (signal == nullptr)
        {
            Serial.println("Error: Signal is null pointer");
            return;
        }

        if (*signal)
        {
            if (this->is_active_)
            {
                Serial.println("Error: Start active timer");
                return;
            }
            this->time_start_ = now;
            this->is_active_ = true;

            *signal = false;
            if (active != nullptr)
            {
                *active = true;
            }
            if (finish != nullptr)
            {
                *finish = false;
            }

            return;
        }

        if (this->is_active_)
        {
            if (now - this->time_start_ <= this->interval_)
            {
                *signal = false;
                if (active != nullptr)
                {
                    *active = true;
                }
                if (finish != nullptr)
                {
                    *finish = false;
                }
            }
            else
            {
                this->time_start_ = 0u;
                this->is_active_ = false;

                *signal = false;
                if (active != nullptr)
                {
                    *active = false;
                }
                if (finish != nullptr)
                {
                    *finish = true;
                }
            }
        }
    }

private:
    uint32_t interval_;
    uint32_t time_start_;
    bool is_active_;
};

#endif
