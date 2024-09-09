#include "FLASH.h"

/* Function to write data to Flash memory */
void Flash_write(volatile uint32_t address_start, volatile uint16_t *data, volatile uint32_t size)
{
    // Check if Flash programming mode is already enabled, disable if so
    if (FLASH->CR & (1U << 1))
    {
        FLASH->CR &= ~(1U << 1);
    }

    // Ensure size is an even number, since Flash operates in half-words
    if (size % 2 != 0U)
    {
        size += 1U;
    }

    // Calculate the number of half-words to write
    uint32_t length = (uint32_t)(size / 2U);

    // Unlock Flash memory if locked
    if (FLASH->CR & (1U << 7))
    {
        FLASH->KEYR = 0x45670123; // First key
        FLASH->KEYR = 0xCDEF89AB; // Second key
    }

    // Enable Flash programming
    FLASH->CR |= (1U << 0);

    // Write data to Flash memory in half-words
    for (uint32_t i = 0U; i < length; i++)
    {
        // Handle unaligned trap if necessary
        if (SCB->CCR & (1U << 3))
        {
            SCB->CCR &= ~(1U << 3); // Clear unaligned trap bit
        }

        // Write half-word to Flash
        *((volatile uint16_t *)address_start + i) = *((volatile uint16_t *)data + i);
    }

    // Wait for Flash write operation to complete (busy flag reset)
    while ((FLASH->SR & (1U << 1)))
    {
        // Busy wait
    }

    // Disable Flash programming
    FLASH->CR &= ~(1U << 0);
}

/* Function to read data from Flash memory (in 32-bit words) */
void Flash_read(volatile uint32_t address_start, volatile uint32_t *data, volatile uint32_t size)
{
    uint32_t length = (uint32_t)(size / 4U); // Calculate number of 32-bit words to read

    // Wait for any previous operations to complete
    while (FLASH->SR & (1U << 1))
    {
        // Busy wait
    }

    // Unlock Flash memory if locked
    if (FLASH->CR & (1U << 7))
    {
        FLASH->KEYR = 0x45670123; // First key
        FLASH->KEYR = 0xCDEF89AB; // Second key
    }

    // Read data from Flash memory
    for (uint32_t i = 0U; i < length; i++)
    {
        *(data + i) = *((volatile uint32_t *)address_start + i);
    }
}

/* Function to read data from Flash memory in half-words (16-bit) */
void Flash_read_half_word(volatile uint32_t address_start, volatile uint16_t *data, volatile uint32_t size)
{
    // Wait for any previous operations to complete
    while (FLASH->SR & (1U << 1))
    {
        // Busy wait
    }

    // Unlock Flash memory if locked
    if (FLASH->CR & (1U << 7))
    {
        FLASH->KEYR = 0x45670123; // First key
        FLASH->KEYR = 0xCDEF89AB; // Second key
    }

    // Read data from Flash memory
    for (uint32_t i = 0U; i < size; i++)
    {
        *((volatile uint16_t *)data + i) = *((volatile uint16_t *)address_start + i);
    }
}

/* Function to erase a Flash memory page */
void Flash_erase(volatile uint32_t address_start)
{
    // Unlock Flash memory if locked
    if (FLASH->CR & (1U << 7))
    {
        FLASH->KEYR = 0x45670123; // First key
        FLASH->KEYR = 0xCDEF89AB; // Second key
    }

    // Enable page erase
    FLASH->CR |= (1U << 1);

    // Set the page address to be erased
    FLASH->AR = address_start;

    // Start erase operation
    FLASH->CR |= (1U << 6);

    // Wait for erase operation to complete (busy flag reset)
    while (FLASH->SR & (1U << 1))
    {
        // Busy wait
    }

    // Disable page erase
    FLASH->CR &= ~(1U << 1);
    FLASH->CR &= ~(1U << 6);
}

