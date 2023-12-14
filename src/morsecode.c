#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <bcm2835.h>
#include <unistd.h>
#include <signal.h>

// Define GPIO pins for the LED and loudspeaker
#define LED_START_PIN RPI_V2_GPIO_P1_16 // GPIO pin 16 on the Raspberry Pi (Blue LED)
#define LED_PIN RPI_V2_GPIO_P1_11       // GPIO pin 11 on the Raspberry Pi
#define BUZZER_PIN RPI_V2_GPIO_P1_12    // GPIO pin 18 on the Raspberry Pi (hardware PWM)

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

// Function to handle (SIGINT) signal
void signalHandler(int signum)
{
    bcm2835_gpio_write(LED_PIN, LOW);
    bcm2835_gpio_write(BUZZER_PIN, LOW); // Turn off the LED and buzzer
    bcm2835_close();
    exit(signum);
}

// Function to turn on an LED
void turnOnLED(int ledPin)
{
    bcm2835_gpio_write(ledPin, HIGH);
}

// Function to turn off an LED
void turnOffLED(int ledPin)
{
    bcm2835_gpio_write(ledPin, LOW);
}

// Function to convert a single character to Morse code and blink the LED and sound the speaker accordingly
void convertAndBlinkSound(char ch)
{
    if (isalpha(ch))
    {
        int index = toupper(ch) - 'A';
        const char *morse = morseCode[index];

        while (*morse != '\0')
        {
            if (*morse == '.')
            {
                bcm2835_gpio_write(LED_PIN, HIGH);
                bcm2835_gpio_write(BUZZER_PIN, HIGH);
                usleep(400000); // .
            }
            else if (*morse == '-')
            {
                bcm2835_gpio_write(LED_PIN, HIGH);
                bcm2835_gpio_write(BUZZER_PIN, HIGH);
                usleep(800000); // _
            }

            bcm2835_gpio_write(LED_PIN, LOW);
            bcm2835_gpio_write(BUZZER_PIN, LOW);
            usleep(1000000); // between symbols

            morse++;
        }
    }
    else if (ch == ' ')
    {
        // If the character is a space, add a longer delay to represent word gap
        usleep(1000000); // between words
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

    // Register the signal handler for exit
    signal(SIGINT, signalHandler);

    // Set the pins as output
    bcm2835_gpio_fsel(LED_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(BUZZER_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LED_START_PIN, BCM2835_GPIO_FSEL_OUTP);

    turnOnLED(LED_START_PIN);

    // Loop to wait for multiple messages
    while (1)
    {
        // Take input message
        char message[80];
        printf("%p\n", message); // address of the message array
        printf("Enter a message: ");
        gets(message);

        // Convert each character in the message to Morse code and blink the LED and sound the speaker
        for (int i = 0; i < strlen(message); i++)
        {
            convertAndBlinkSound(message[i]);
            usleep(1200000); // between chars
        }
    }

    return 0;
}
