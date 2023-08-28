#include <msp430.h> 

//// Necessary Definitions ////
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define XDIR BIT3    // Based on Motor Driver Connection
#define YDIR BIT1    // Based on Motor Driver Connection
#define XSTEP BIT2   // Based on Motor Driver Connection
#define YSTEP BIT0   // Based on Motor Driver Connection


void penDown();
void penUp();
void penMove(int dir, int steps);

int i=0;

void main(void)
{
     WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //// Set up Timer for Servo ////
    TA0CTL = TASSEL_2 + MC_1 + TAIE +ID_0;
    TA0CCTL1 = OUTMOD_7;
    TA0CCR0 = 20000;
    TA0CCR1 = 900; // Servo start in UP position

    //// Servo Motor on P1.2 ////
    P1DIR |= BIT2;
    P1SEL |= BIT2;  //selection for timer setting

    //// Stepper Motors Setup ////
    P6DIR |= 0b00001111; //YDIR on 6.1, YSTEP on 6.0, XDIR on 6.3, XSTEP on 6.2
    P6OUT = 0; // 0 is forward for X, right for Y

    //// Interrupt Setup ////

    // Set P1.1 and 2.1 as pullup
    P1OUT |= BIT1;
    P2OUT |= BIT1;

    // Enable Pullup resistor on P1.1 and P2.1
    P1REN |= BIT1;
    P2REN |= BIT1;

    // Enable interrupts on P1.1 and P2.1
    P1IE |= BIT1;
    P2IE |= BIT1;

    // Trigger interrupt on Falling Edge for P1.1 and P2.1
    P1IES |= BIT1;
    P2IES |= BIT1;

    // Turn on interrupts and go in to LPM
    _BIS_SR(LPM4b_bits + GIE);


}

void __attribute__((interrupt(PORT1_VECTOR))) PORT1_ISR(void)
{
    //// Draw a House ////

    //// Initial Positioning ////

    penMove(UP, 400);

    penMove(RIGHT, 100);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    //// Main Square of House ////

    penMove(DOWN, 400);

    penMove(RIGHT, 400);

    penMove(UP, 400);

    penMove(LEFT, 500);

    //// Left Side of Roof ////

    for(i=0;i<300,i++)
    {
        penMove(RIGHT, 1);

        if(i%2 == 0)
        {
            penMove(UP, 1);
        }
    }

    //// Right Side of Roof ////

    for(i=0;i<300,i++)
    {
        penMove(RIGHT, 1);

        if(i%2 == 0)
        {
            penMove(DOWN, 1);
        }
    }

    penMove(LEFT, 100);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    //// Door ////

    penMove(LEFT, 150);

    penMove(DOWN, 400);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(UP, 250);

    penMove(LEFT, 100);

    penMove(DOWN, 250);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    //// Window ////

    penMove(LEFT, 50);

    penMove(UP, 300);

    __delay_cycles(500000);
    PenDown();
    __delay_cycles(500000);

    penMove(UP, 76);

    penMove(LEFT, 76);

    penMove(DOWN, 76);

    penMove(RIGHT, 76);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    penMove(LEFT, 38);

    __delay_cycles(500000);
    PenDown();
    __delay_cycles(500000);

    penMove(UP, 76);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    penMove(DOWN, 38);

    penMove(LEFT, 38);

    __delay_cycles(500000);
    PenDown();
    __delay_cycles(500000);

    penMove(RIGHT, 76);

    //// Go back to origin ////

    penMove(LEFT, 276);

    penMove(DOWN, 338);

    P1IFG &= ~BIT1; // Clear interrupt flag
}

void __attribute__((interrupt(PORT2_VECTOR))) PORT2_ISR(void)
{
    //// Draw "PHYS 319" ////

    //// Initial Positioning ////

    penMove(UP, 400);

    ///////// P ////////////

    __delay_cycles(500000);
    penDown();
    __delay_cycles(750000);

    penMove(UP,200);

    penMove(RIGHT, 100);

    penMove(DOWN, 100);

    penMove(LEFT, 100);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    ////////// H ///////////

    penMove(RIGHT, 150);

    penMove(UP, 100);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(DOWN, 200);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    penMove(UP, 100);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(RIGHT, 100);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    penMove(UP, 100);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(DOWN, 200);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    //////// Y ///////////

    penMove(RIGHT, 50);

    penMove(UP, 200);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(DOWN, 75);

    penMove(RIGHT, 100);

    penMove(UP, 75);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    penMove(DOWN, 75);

    penMove(LEFT, 50);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(DOWN, 125);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    //////// S ///////////

    penMove(RIGHT, 100);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(RIGHT, 100);

    penMove(UP, 100);

    penMove(LEFT, 100);

    penMove(UP, 100);

    penMove(RIGHT, 100);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    ////////// 9 ///////////

    penMove(DOWN, 550);

    penMove(LEFT, 150);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(UP, 200);

    penMove(LEFT, 100);

    penMove(DOWN, 100);

    penMove(RIGHT, 100);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    /////// 1 ///////

    penMove(LEFT, 150)

    penMove(DOWN, 100);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(UP, 200);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    //////// 3 /////////

    penMove(RIGHT, 150);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(RIGHT, 100);

    penMove(DOWN, 100);

    penMove(LEFT, 100);

    __delay_cycles(500000);
    penUp();
    __delay_cycles(500000);

    penMove(RIGHT, 100);

    __delay_cycles(500000);
    penDown();
    __delay_cycles(500000);

    penMove(DOWN, 100);

    penMove(LEFT, 100);

    penUp();

    //// Return to origin ////

    penMove(LEFT, 100);
    penMove(DOWN, 50);

    P2IFG &= ~BIT1; // Clear interrupt flag
}


void penUp()
{
    //// Turns the servo motor to set the pen up ////

    TA0CCR1 = 900;
    TA0CCTL1 = OUTMOD_7;  //CCR1 selection reset-set
    TA0CTL = TASSEL_2|MC_1;
}

void penDown()
{
    //// Turns the servo motor to set the pen down ////

    TA0CCR1 = 1400;
    TA0CCTL1 = OUTMOD_7;  //CCR1 selection reset-set
    TA0CTL = TASSEL_2|MC_1;
}

void penMove(int dir, int steps)
{
    //// Moves the pen in the given direction for the given amount of steps ////

    if(dir==UP && ((P6OUT >> XDIR) & 0))
    //// If the pen is supposed to move up and the motor direction is up ////
    {
        for(i=0;i<steps;i++)
        //// Move up by steps amount of steps ////
        {
            P6OUT ^= XSTEP;
            __delay_cycles(1100);
        }
    }

    else if(dir==UP && ((P6OUT >> XDIR) & 1))
    //// If the pen is supposed to move up and the motor direction is not up ////
    {
        P6OUT ^= XDIR; // Change motor direction
        for(i=0;i<steps;i++)
        //// Move up by steps amount of steps ////
        {
            P6OUT ^= XSTEP;
            __delay_cycles(1100);
        }
    }

    if(dir==DOWN && ((P6OUT >> XDIR) & 1))
    //// If the pen is supposed to move down and the motor direction is down ////
    {
        for(i=0;i<steps;i++)
        //// Move down by steps amount of steps ////
        {
            P6OUT ^= XSTEP;
            __delay_cycles(1100);
        }
    }

    else if(dir==DOWN && ((P6OUT >> XDIR) & 0))
    //// If the pen is supposed to move down and the motor direction is not down ////
    {
        P6OUT ^= XDIR; //Change motor direction
        for(i=0;i<steps;i++)
        //// Move down by steps amount of steps
        {
            P6OUT ^= XSTEP;
            __delay_cycles(1100);
        }
    }

    if(dir==RIGHT && ((P6OUT >> XDIR) & 0))
    //// If the pen is supposed to move right and the motor direction is right ////
    {
        for(i=0;i<steps;i++)
        //// Move right by steps amount of steps ////
        {
            P6OUT ^= YSTEP;
            __delay_cycles(1100);
        }
    }

    else if(dir==RIGHT && ((P6OUT >> XDIR) & 1))
    //// If the pen is supposed to move right and the motor direction is not right ////
    {
        P6OUT ^= YDIR; // Change motor direction
        for(i=0;i<steps;i++)
        //// Move right by steps amount of steps ////
        {
            P6OUT ^= YSTEP;
            __delay_cycles(1100);
        }
    }

    if(dir==LEFT && ((P6OUT >> XDIR) & 1))
    //// If the pen is supposed to move left and the motor direction is left ////
    {
        for(i=0;i<steps;i++)
        //// Move left by steps amount of steps
        {
            P6OUT ^= YSTEP;
            __delay_cycles(1100);
        }
    }

    else if(dir==LEFT && ((P6OUT >> XDIR) & 0))
    //// If the pen is supposed to move left and the motor direction is not left ////
    {
        P6OUT ^= YDIR; // Change motor direction
        for(i=0;i<steps;i++)
        //// Move left by steps amount of steps ////
        {
            P6OUT ^= YSTEP;
            __delay_cycles(1100);
        }
    }
}


