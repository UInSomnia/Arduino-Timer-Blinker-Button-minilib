#ifndef INSOMNIA_BLINKER_H
#define INSOMNIA_BLINKER_H

#include "timer.h"

class Blinker
{
public:
    Blinker() :
        is_active_(false),
        interval_left_(0u),
        interval_right_(0u),
        limit_count_(0u),
        current_count_(0u),
        cycle(false),
        intro(false) {}

    Blinker(
        const uint32_t interval_left,
        const uint32_t interval_right,
        const uint32_t limit_count) :
        is_active_(false),
        interval_left_(interval_left),
        interval_right_(interval_right),
        limit_count_(limit_count),
        current_count_(0u),
        cycle(false),
        intro(false) {}
    
    void operator () (
        bool *signal,
        bool *active_left,
        bool *active_right,
        bool *finish)
    {
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

            this->is_active_ = true;

            this->current_count_ = 0u;
            
            this->left = Timer(this->interval_left_);
            this->right = Timer(this->interval_right_);

            this->cycle = true;
            this->intro = false;

            *signal = false;
        }

        this->left(&(this->cycle), active_left, &(this->intro));
        this->right(&(this->intro), active_right, &(this->cycle));

        if (this->cycle)
        {
            ++(this->current_count_);

            if (this->current_count_ >= this->limit_count_)
            {
                if (finish != nullptr)
                {
                    this->is_active_ = false;
                    this->current_count_ = 0u;
                    
                    *finish = true;
                }

                this->cycle = false;
            }
        }
    }

private:
    bool is_active_;

    uint32_t interval_left_;
    uint32_t interval_right_;
    uint32_t limit_count_;
    uint32_t current_count_;

    Timer left;
    Timer right;

    bool cycle;
    bool intro;
};

#endif
