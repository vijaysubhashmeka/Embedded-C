#include <stdio.h>
#include <stdint.h>

/*
 * Simulated GPIO Output Data Register (8-bit)
 * In real hardware, this would be a fixed memory address.
 */
volatile uint8_t GPIO_ODR = 0x00;

/*
 * Pointer to the register
 * IMPORTANT:
 * - 'volatile' ensures compiler does not optimize access
 * - Pointer allows indirect (hardware-like) access
 */
volatile uint8_t *ptr = &GPIO_ODR;

/*
 * Function: isValidBit
 * Purpose : Validate bit position (0–7 for 8-bit register)
 */
int isValidBit(uint8_t bit) {
    return (bit <= 7);
}

/*
 * Function: setBit
 * Purpose : Set a specific bit (make it HIGH)
 * Operation:
 *   - (1 << bit) creates mask
 *   - OR operation sets only that bit
 */
void setBit(uint8_t bit) {
    if (!isValidBit(bit)) return;

    *ptr |= (1 << bit);   // Modify register via pointer

    printf("After setBit(%d): GPIO_ODR = 0x%02X\n", bit, *ptr);
}

/*
 * Function: clearBit
 * Purpose : Clear a specific bit (make it LOW)
 * Operation:
 *   - ~(1 << bit) creates mask with target bit = 0
 *   - AND operation clears only that bit
 */
void clearBit(uint8_t bit) {
    if (!isValidBit(bit)) return;

    *ptr &= ~(1 << bit);

    printf("After clearBit(%d): GPIO_ODR = 0x%02X\n", bit, *ptr);
}

/*
 * Function: toggleBit
 * Purpose : Toggle a specific bit (flip state)
 * Operation:
 *   - XOR flips the targeted bit
 */
void toggleBit(uint8_t bit) {
    if (!isValidBit(bit)) return;

    *ptr ^= (1 << bit);

    printf("After toggleBit(%d): GPIO_ODR = 0x%02X\n", bit, *ptr);
}

/*
 * MAIN FUNCTION
 * Demonstrates:
 * - Pointer-based register manipulation
 * - Bit-level control
 */
int main() {

    setBit(2);      // Expect: 0x04
    clearBit(2);    // Expect: 0x00
    toggleBit(3);   // Expect: 0x08

    return 0;
}
