/**
 * LED controller
 */
#include "leds.h"

#define LEDS_MASK_RED   (1<<LEDS_PIN_RED)
#define LEDS_MASK_GREEN (1<<LEDS_PIN_GREEN)
#define LEDS_MASK_BLUE  (1<<LEDS_PIN_BLUE)

static uint8_t red_value = 0x80;
static uint8_t green_value = 0xcc;
static uint8_t blue_value = 0x00;
static uint16_t off_timer = 0;

void leds_init(void)
{
    LEDS_DDR |= LEDS_MASK_RED | LEDS_MASK_GREEN | LEDS_MASK_BLUE;
    LEDS_PORT |= LEDS_MASK_RED | LEDS_MASK_GREEN | LEDS_MASK_BLUE;
}

void leds_set_color(uint8_t red, uint8_t green, uint8_t blue)
{
    red_value = red;
    green_value = green;
    blue_value = blue;
}

void leds_begin_off(uint16_t period)
{
    off_timer = period;
}

void leds_tick(void)
{
    static uint8_t count = 0;

    if (off_timer > 0)
    {
        LEDS_PORT |= LEDS_MASK_RED | LEDS_MASK_GREEN | LEDS_MASK_BLUE;
    }
    else
    {
        if (count < red_value)
            LEDS_PORT &= ~LEDS_MASK_RED;
        else
            LEDS_PORT |= LEDS_MASK_RED;

        if (count < green_value)
            LEDS_PORT &= ~LEDS_MASK_GREEN;
        else
            LEDS_PORT |= LEDS_MASK_GREEN;

        if (count < blue_value)
            LEDS_PORT &= ~LEDS_MASK_BLUE;
        else
            LEDS_PORT |= LEDS_MASK_BLUE;
    }

    count++;
    if (off_timer > 0)
        off_timer--;
}
