
/* Alien eyes blinker

 Animates alien eyes and a glowing finger (ala ET)

 First draft coming form BlinkWithoutDelay Arduino exemple:
 Turns on and off a light emitting diode(LED) connected to a digital
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.

 */


typedef struct {
  unsigned int pin1;
  unsigned int pin2;
  unsigned int val1;
  unsigned int val2;
  bool up: true;
}pulser_t;

// WARNING: debug mode mess up the led timing!
const int DEBUG = 0;
const int BUMP = 5;
const int MAX = 255;
const int MIN = 50;
const int HL = 0; // HeadLeft
const int HR = 1; // HeadRight
const int FL = 2; // FingerRight
const int TOTAL_GIZMOS = 3; // How many gizmos we have?

int pindbg = 12;
// our gizmos
pulser_t Gizmos[TOTAL_GIZMOS];

// Variables will change:
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long interval = 50;           // interval at which to blink (milliseconds)

void setup() {
  if (DEBUG){
    Serial.begin(9600);
  }

  Gizmos[HL].pin1 = 6;
  Gizmos[HL].pin2 = 9;

  Gizmos[HR].pin1 = 10;
  Gizmos[HR].pin2 = 11;

  Gizmos[FL].pin1 = 3;
  Gizmos[FL].pin2 = 5;

  for (int i = 0; i < TOTAL_GIZMOS; i++){
    if (DEBUG){
      Serial.print("set value for ");
      Serial.print(i);
    }
    if (i % 2){
      Gizmos[i].val1 = MIN;
      Gizmos[i].val2 = MAX;
      Gizmos[i].up = true;
    } else {
      Gizmos[i].val1 = MAX;
      Gizmos[i].val2 = MIN;
      Gizmos[i].up = false;
    }
  }
}

void loop()
{
  // check to see if it's time to animate the gizmos
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    if (DEBUG)
      Serial.print("new loop\n------\n\n");
    previousMillis = currentMillis;
    // set new state for each gizmos
    for (int gizmo = 0; gizmo < TOTAL_GIZMOS; gizmo++){
      animateGizmo(gizmo);
    }
    if (Gizmos[0].up){
      if (DEBUG){
        Serial.print("debug up\n");
        analogWrite(pindbg, 225);
      }
    } else {
      if (DEBUG){
        Serial.print("debug down\n");
        analogWrite(pindbg, 0);
      }
    }
  }
}

void animateGizmo(int gizmo){
  /*Serial.print("in gizmo no :");
  Serial.print(gizmo);
  Serial.print("\n");
*/
  if (Gizmos[gizmo].up){
    if (Gizmos[gizmo].val1 < MAX){
      if (DEBUG){ Serial.print("go up\n"); }
      gizmoUp(gizmo);
    } else {
      // Change direction
      if (DEBUG){ Serial.print("up toggle to down\n");}
      gizmoToggle(gizmo);
    }
  } else {
    if (Gizmos[gizmo].val1 > MIN){
      if (DEBUG) { Serial.print("go down\n");}
      gizmoDown(gizmo);
    } else {
      if (DEBUG) { Serial.print("down toggle to up\n");}
      gizmoToggle(gizmo);
    }
  }
  gizmoShow(gizmo);
}

void gizmoUp(int gizmo){
  if (DEBUG){
    Serial.print("up\n");
    Serial.print("val1= ");
    Serial.print( Gizmos[gizmo].val1) ;
    Serial.print(" val2= ");
    Serial.print( Gizmos[gizmo].val2) ;
    Serial.print("\n");
  }
  if(Gizmos[gizmo].val1 < MAX){
    Gizmos[gizmo].val1 += BUMP;
  }
  if(Gizmos[gizmo].val2 > MIN){
    Gizmos[gizmo].val2 -= BUMP;
  }
}

void gizmoToggle(int gizmo){
  if (Gizmos[gizmo].up){
    if (DEBUG) { Serial.print("Toggle DOWN\n");}
    Gizmos[gizmo].up = false;
  } else {
    if (DEBUG) { Serial.print("Toggle UP\n");}
    Gizmos[gizmo].up = true;
  }
}

void gizmoDown(int gizmo){
  if (DEBUG) {
    Serial.print("down\n");
    Serial.print("val1= ");
    Serial.print( Gizmos[gizmo].val1) ;
    Serial.print(" val2= ");
    Serial.print( Gizmos[gizmo].val2) ;
    Serial.print("\n");
  }
  if(Gizmos[gizmo].val1 > MIN){
    Gizmos[gizmo].val1 -= BUMP;
  }
  if(Gizmos[gizmo].val2 < MAX){
    Gizmos[gizmo].val2 += BUMP;
  }
}

void gizmoShow(int gizmo){
  if (DEBUG) {
    Serial.print("show\n");
    Serial.print("1 : ");
    Serial.print(Gizmos[gizmo].pin1);
    Serial.print(" - ");
    Serial.print( Gizmos[gizmo].val1);
    Serial.print("\n");

    Serial.print("2 : ");
    Serial.print(Gizmos[gizmo].pin2);
    Serial.print(" - ");
    Serial.print( Gizmos[gizmo].val2);
    Serial.print("\n");
  }
  analogWrite(Gizmos[gizmo].pin1, Gizmos[gizmo].val1);
  analogWrite(Gizmos[gizmo].pin2, Gizmos[gizmo].val2);
}
