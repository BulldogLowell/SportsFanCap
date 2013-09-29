//void setup() {
  // initialize serial communication:
  //Serial.begin(9600); 
   // initialize the LED pins:
    //  for (int thisPin = 2; thisPin < 7; thisPin++) {
      //  pinMode(thisPin, OUTPUT);


const int showlights = 5;
int LED[ showlights ] = { A4, A3, A2, 11, 10 };
int start_time;
#define RED 5
#define GREEN 9
#define BLUE 6
#define DELAY 1000.0
int select = 0;
char health=' ';

double shift;

void setup() {
  Serial.begin(9600); 
  for( int i=0; i<= showlights; i++ ){
    pinMode( LED[i], OUTPUT );
      }
  shift = DELAY/(3 * DELAY);
  pinMode( RED, OUTPUT );
  pinMode( GREEN, OUTPUT );
  pinMode( BLUE, OUTPUT );
  win_flash_on ();
  turn_off ();
}

void switch_on( int pin, double theta ) {
  analogWrite( pin, 128.0 + 128 * sin( theta * 2.0 * PI  ) ); 
}

void turn_off() {
      digitalWrite(A3, LOW);
      digitalWrite(A4, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(6, HIGH);
}

void win_flash_off() {
      digitalWrite(A3, LOW);
      digitalWrite(A4, LOW);
      digitalWrite(A2, LOW);
      digitalWrite(11, LOW);
      digitalWrite(10, LOW);
      delay ( 100 );
}
void win_flash_on() {
      digitalWrite(A3, HIGH);
      digitalWrite(A4, HIGH);
      digitalWrite(A2, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(10, HIGH);
      delay ( 100 );
}

void rgb_win() {
      double theta = millis()/DELAY;     
      switch_on( RED, theta );
      switch_on( GREEN, theta + 1*shift );
      switch_on( BLUE, theta + 2*shift );
}  

void loop() {
  // read the sensor:
  if (Serial.available() > 0) {
    health = Serial.read();
    // do something different depending on the character received.  
    // The switch statement expects single number values for each case;
    // in this exmaple, though, you're using single quotes to tell
    // the controller to get the ASCII value for the character.  For 
    // example 'a' = 97, 'b' = 98, and so forth:
  }
    switch (health) {
    case 'a':   
      digitalWrite(A4, HIGH);
      delay( 5000 );
      turn_off ();
      break;
    case 'b':    
      digitalWrite(A4, HIGH);
      delay( 500 );
      digitalWrite(A3, HIGH);
      delay( 5000 );
      turn_off ();
      break;
    case 'c':    
      digitalWrite(A4, HIGH);
      delay( 500 );
      digitalWrite(A3, HIGH);
      delay( 500 );
      digitalWrite(A2, HIGH);
      delay( 5000 );
      turn_off ();
      break;
    case 'd':   
      digitalWrite(A4, HIGH);
      delay( 500 );
      digitalWrite(A3, HIGH);
      delay( 500 );
      digitalWrite(A2, HIGH);
      delay( 500 );
      digitalWrite(11, HIGH);
      delay( 5000);
      turn_off ();
      break;
    case 'e':    
      digitalWrite(A4, HIGH);
      delay( 500 );
      digitalWrite(A3, HIGH);
      delay( 500 );
      digitalWrite(A2, HIGH);
      delay( 500 );
      digitalWrite(11, HIGH);
      delay( 500 );
      digitalWrite(10, HIGH);
      delay( 5000 );
      turn_off();
      break;
    case 'w':
      
      start_time=millis();
      while ( millis() - start_time < 1000 ) {
          win_flash_off ();
          rgb_win ();
          rgb_win ();
          delay ( 100 );
          win_flash_on ();
          rgb_win ();
          rgb_win ();
          delay ( 100 );
         }
      start_time=millis();
      while ( millis() - start_time < 4000 ) {
          rgb_win ();
         }
         turn_off();
      break;
    case 'l':
      start_time=millis();
      while ( millis() - start_time < 3000 ) {
          digitalWrite (A4, HIGH);
          digitalWrite (5, LOW);
          delay ( 500 );
          digitalWrite (A4, LOW);
          digitalWrite (5, HIGH);
          delay ( 500 );
      }
      turn_off ();
      break;  
    default:
      turn_off();
      // turn all the LEDs off:
     // for (int showlights = 2; thisPin < 5; showlights++) {
      //  digitalWrite(showlights, LOW);
      }
    health = ' ';
    } 
//  }
//}

