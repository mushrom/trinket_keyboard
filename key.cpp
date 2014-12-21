/*
TrinketKeyboard example
For Trinket by Adafruit Industries
*/
 
#include <TrinketKeyboard.h>
#include <avr/io.h>
 
#define PIN_BUTTON_CAPITAL_A 0
#define PIN_BUTTON_STRING    2

#define LOW  0
#define HIGH 1

#define mode_output( port, pin ) (port |= (1<<pin))
#define mode_input( port, pin )  (port &= ~(1<<pin))
#define set_high( port, pin )    (port |= (1<<pin))
#define set_low( port, pin )     (port &= ~(1<<pin))
#define read_pin( port, pin )    (port & (1<<pin))

void loop();

int main()
{
  // button pins as inputs
  /*
  pinMode(PIN_BUTTON_CAPITAL_A, INPUT);
  pinMode(PIN_BUTTON_STRING, INPUT);
 
  // setting input pins to high means turning on internal pull-up resistors
  digitalWrite(PIN_BUTTON_CAPITAL_A, HIGH);
  digitalWrite(PIN_BUTTON_STRING, HIGH);
  */
  // remember, the buttons are active-low, they read LOW when they are not pressed
  mode_input( DDRB, PIN_BUTTON_CAPITAL_A );
  mode_input( DDRB, PIN_BUTTON_STRING );
  mode_output( DDRB, PB1 );
  set_high( PORTB, PIN_BUTTON_CAPITAL_A );
  set_high( PORTB, PIN_BUTTON_STRING );
  set_high( PORTB, PB1 );
 
  // start USB stuff
  TrinketKeyboard.begin();

  while ( 1 ){
    TrinketKeyboard.poll();
   
    //if (digitalRead(PIN_BUTTON_CAPITAL_A) == LOW)
    if ( read_pin( PINB, PIN_BUTTON_CAPITAL_A ) == LOW )
    {
      // this should type a capital A
      TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_SHIFT, KEYCODE_A);
      // this releases the key (otherwise it is held down!)
      TrinketKeyboard.pressKey(0, 0);
    }
    //if (digitalRead(PIN_BUTTON_STRING) == LOW)
    if ( read_pin( PINB, PIN_BUTTON_STRING ) == LOW)
    {
      // type out a string using the Print class
      TrinketKeyboard.print("Hello World!");
    }
  }
  
  return 0;
}
 
/*
void loop()
{
  // the poll function must be called at least once every 10 ms
  // or cause a keystroke
  // if it is not, then the computer may think that the device
  // has stopped working, and give errors
  TrinketKeyboard.poll();
 
  //if (digitalRead(PIN_BUTTON_CAPITAL_A) == LOW)
  if ( read_pin( PINB, PIN_BUTTON_CAPITAL_A ) == LOW )
  {
    // this should type a capital A
    TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_SHIFT, KEYCODE_A);
    // this releases the key (otherwise it is held down!)
    TrinketKeyboard.pressKey(0, 0);
    set_high( PORTB, PB1 );
  }
 
  //if (digitalRead(PIN_BUTTON_STRING) == LOW)
  if ( read_pin( PINB, PIN_BUTTON_STRING ) == LOW)
  {
    // type out a string using the Print class
    //TrinketKeyboard.print("Hello World!");
  }
}
*/
