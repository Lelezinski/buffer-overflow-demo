#include <stdio.h>
#include <string.h>
#include <bcm2835.h>
#include <unistd.h>

// Define the GPIO pin for the LED
#define LED_PIN RPI_V2_GPIO_P1_11 // GPIO pin 11 on the Raspberry Pi

// Define Morse code representations for each letter
const char *morseCode[] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--.."  // Z
};

// Function to convert a single character to Morse code and blink the LED accordingly
void convertAndBlink(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
    {
        int index = ch - 'A';
        const char *morse = morseCode[index];

        while (*morse != '\0')
        {
            bcm2835_gpio_write(LED_PIN, HIGH);

            if (*morse == '.')
            {
                usleep(200000); // Sleep for 200 ms (adjust this value based on your preference)
                printf("A");
            }
            else if (*morse == '-')
            {
                usleep(400000); // Sleep for 200 ms (adjust this value based on your preference)
            }

            bcm2835_gpio_write(LED_PIN, LOW);
            usleep(700000); // Sleep for 100 ms (adjust this value based on your preference)

            morse++;
        }
    }
    else if (ch == ' ')
    {
        // If the character is a space, add a longer delay to represent word gap
        usleep(3000000); // Sleep for 600 ms (adjust this value based on your preference)
    }
}

int main()
{
    // Initialize bcm2835 library
    if (!bcm2835_init())
    {
        fprintf(stderr, "Unable to initialize bcm2835 library\n");
        return 1;
    }

    // Set the pin as output
    bcm2835_gpio_fsel(LED_PIN, BCM2835_GPIO_FSEL_OUTP);

    // Take input message
    char message[80];
    printf("%p\n", message); // address of the message array

    printf("Enter a message: ");
    gets(message);
    printf("Received Message: %s\n", message); // for debugging

    // Convert each character in the message to Morse code and blink the LED
    for (int i = 0; i < strlen(message); i++)
    {
        convertAndBlink(message[i]);
    }

    // Close bcm2835 library
    bcm2835_close();

    return 0;
}