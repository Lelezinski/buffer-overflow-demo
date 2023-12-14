#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <bcm2835.h>
#include <unistd.h>
#include <signal.h>

// Define GPIO pins for the LED and loudspeaker
#define LED_START_PIN RPI_V2_GPIO_P1_16 // GPIO pin 16 on the Raspberry Pi (Green LED)
#define LED_PIN RPI_V2_GPIO_P1_11       // GPIO pin 11 on the Raspberry Pi (Red LEDs)
#define BUZZER_PIN RPI_V2_GPIO_P1_18    // GPIO pin 18 on the Raspberry Pi (Buzzer)

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

void parseMessage(char *message)
{
    // Convert each character in the message to Morse code and blink the LED and sound the speaker
    for (int i = 0; i < strlen(message); i++)
    {
        convertAndBlinkSound(message[i]);
        usleep(1200000); // Sleep between characters
    }
}

// Function to handle exit signals
void signalHandler(int signum)
{
    // Turn off the LEDs and buzzer
    bcm2835_gpio_write(LED_START_PIN, LOW);
    bcm2835_gpio_write(LED_PIN, LOW);
    bcm2835_gpio_write(BUZZER_PIN, LOW);
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
    setbuf(stdout, NULL);

    // Initialize bcm2835 library
    if (!bcm2835_init())
    {
        fprintf(stderr, "Unable to initialize bcm2835 library\n");
        return 1;
    }

    // Register the signal handler for exit
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    // Set the pins as output
    bcm2835_gpio_fsel(LED_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(BUZZER_PIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(LED_START_PIN, BCM2835_GPIO_FSEL_OUTP);

    turnOnLED(LED_START_PIN);

    char message[80];
    printf("[DEBUG] %p\n", message); // address of the message array

    // Take input message
    puts("Enter a message. ");
    gets(message);
    printf("Received: %s\n", message);

    parseMessage(message);

    signalHandler(0);
    return 0;
}
