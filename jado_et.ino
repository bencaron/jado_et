
/* Alien eyes blinker

 Animates alien eyes and a glowing finger (ala ET)

 First draft coming form BlinkWithoutDelay Arduino exemple:
 Turns on and off a light emitting diode(LED) connected to a digital
 pin, without using the delay() function.  This means that other code
 can run at the same time without being interrupted by the LED code.

 */


typedef struct {
  int pin1;
  int pin2;
  int val1;
  int val2;
  bool up: true;
}pulser_t;

const int MAX = MAX;
const int MIN = 0;
const int HL = 0; // HeadLeft
const int HR = 1; // HeadRight
const int FL = 2; // FingerRight
const int TOTAL_GIZMOS = 3; // How many gizmos we have?

// our gizmos
pulser_t Gizmos[TOTAL_GIZMOS];

// Variables will change:
long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long interval = 100;           // interval at which to blink (milliseconds)

void setup() {
  Serial.begin(9600);

  Gizmos[HL].pin1 = 3;
  Gizmos[HL].pin2 = 5;

  Gizmos[HR].pin1 = 10;
  Gizmos[HR].pin2 = 11;

  Gizmos[FL].pin1 = 6;
  Gizmos[FL].pin2 = 9;

  for (int i = 0; i <= TOTAL_GIZMOS; i++){
    Gizmos[i].val1 = 0;
    Gizmos[i].val2 = MAX;
  }
}

void loop()
{
  // check to see if it's time to animate the gizmos
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    // set new state for each gizmos
    for (int gizmo = 0; gizmo <= TOTAL_GIZMOS; gizmo++){
      animateGizmo(gizmo);
    }
  }
}

void animateGizmo(int gizmo){
  Serial.write("in gizmo no ");
  Serial.write(gizmo);
  Serial.write("\n");

  if (Gizmos[gizmo].up){
    if (Gizmos[gizmo].val1 < MAX){
      gizmoUp(gizmo);
    } else {
      // Change direction
      gizmoToggle(gizmo);
    }
  } else {
    if (Gizmos[gizmo].val1 > MIN){
      gizmoDown(gizmo);
    } else {
      gizmoToggle(gizmo);
    }
  }
  gizmoShow(gizmo);
}

void gizmoUp(int gizmo){
  if(Gizmos[gizmo].val1 < MAX){
    Gizmos[gizmo].val1++;
  }
  if(Gizmos[gizmo].val2 > MIN){
    Gizmos[gizmo].val2--;
  }
}

void gizmoToggle(int gizmo){
  if (Gizmos[gizmo].up){
    Serial.write("Toggle DOWN\n");
    Gizmos[gizmo].up = false;
  } else {
    Serial.write("Toggle UP\n");
    Gizmos[gizmo].up = true;
  }
}

void gizmoDown(int gizmo){
  if(Gizmos[gizmo].val1 > MIN){
    Gizmos[gizmo].val1--;
  }
  if(Gizmos[gizmo].val2 < MAX){
    Gizmos[gizmo].val2++;
  }
}

void gizmoShow(int gizmo){
  analogWrite(Gizmos[gizmo].pin1, Gizmos[gizmo].val1);
  analogWrite(Gizmos[gizmo].pin2, Gizmos[gizmo].val2);
}
