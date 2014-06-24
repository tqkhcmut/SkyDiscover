#include "main.h"

//*****************************************************************************
//
// Define pin to LED color mapping.
//
//*****************************************************************************

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

unsigned long g_ulButtons;

//*****************************************************************************
//
// Main 'C' Language entry point.  Toggle an LED using StellarisWare.
// See www.ti.com/stellaris-launchpad/project0 for more information and 
// tutorial videos.
//
//*****************************************************************************
int main(void)
{
    //
    // Enable stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    MAP_FPUEnable();
    MAP_FPUStackingEnable();

    //
    // Set the system clock to run at 40Mhz off PLL with external crystal as 
    // reference.
    //
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                       SYSCTL_OSC_MAIN);
	
	//
    // Enable and Initialize the UART.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioInit(0);

    UARTprintf("Welcome to the Stellaris LM4F120 LaunchPad!\n");
    UARTprintf("Type 'help' for a list of commands\n");
    UARTprintf("> ");
	
	//
    // Initialize the RGB LED. AppRainbow typically only called from interrupt
    // context. Safe to call here to force initial color update because 
    // interrupts are not yet enabled.
    //
    RGBInit(0);
    RGBIntensitySet(50);
//    AppRainbow(1);
    RGBEnable();
    
    //
    // Initialize the buttons
    //
    ButtonsInit();

    //
    // Initialize the SysTick interrupt to process colors and buttons.
    //
    SysTickPeriodSet(SysCtlClockGet() / 1000); // 1ms
    SysTickEnable();
    SysTickIntEnable();
    IntMasterEnable();
    //
    // Enable and configure the GPIO port for the LED operation.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);

    //
    // Loop Forever
    //
    while(1)
    {
        //
        // Turn on the LED
        //
        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, RED_LED);

        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);

        //
        // Turn on the LED
        //
        GPIOPinWrite(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED, BLUE_LED);

        //
        // Delay for a bit
        //
        SysCtlDelay(2000000);
    }
}


//*****************************************************************************
//
// Handler to manage the button press events and state machine transitions
// that result from those button events.
//
// This function is called by the SysTickIntHandler if a button event is 
// detected. Function will determine which button was pressed and tweak various
// elements of the global state structure accordingly.
//
//*****************************************************************************
void 
AppButtonHandler(void)
{
//    static unsigned long ulTickCounter;
//    
//    ulTickCounter++;

    //
    // Switch statement to adjust the color wheel position based on buttons
    //
    switch(g_ulButtons & ALL_BUTTONS)
    {
    
    case LEFT_BUTTON:

        
        break;

    case RIGHT_BUTTON:

        
        break;

    case ALL_BUTTONS:

        
        break;

    default:
        
        break;
    }
}

//*****************************************************************************
//
// Called by the NVIC as a result of SysTick Timer rollover interrupt flag
//
// Checks buttons and calls AppButtonHandler to manage button events.
// Tracks time and auto mode color stepping.  Calls AppRainbow to implement
// RGB color changes.
//
//*****************************************************************************
void 
SysTickIntHandler(void)
{
    g_ulButtons = ButtonsPoll(0,0);
    AppButtonHandler();
}

