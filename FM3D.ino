// by Les Hall
// started Mon Nov 17 2014
// 

int controlPin = 2;
int coilPins[] = {0, 1, 4, 3};
int fullStep[][4] = {  // two bit Gray code
    {0, 1, 0, 1},  // - + - +
    {0, 1, 1, 0},  // - + + -
    {1, 0, 1, 0},  // + - + - 
    {1, 0, 0, 1}}; // + - - +
int steps = 0;
long pos = 0;
long command = 0;


void setup()
{
  pinMode(controlPin, INPUT);
  for(int i=0; i<sizeof(coilPins); ++i)
    pinMode(coilPins[i], OUTPUT);
    
  // reset sets pos to zero
  steps = 0;
  pos = 0;
  command = 0;
}


void loop()
{ 
  // read the high and low pulse durations
  unsigned long pulseHigh = pulseIn(controlPin, HIGH, 2000);
  unsigned long pulseLow = pulseIn(controlPin, LOW, 2000);
  
  // set commanded position if the control period matches
  unsigned long T = pulseHigh + pulseLow;
  if ( (T > 900) && (T < 1100) )  // check for frequency
    command = pulseHigh - pulseLow;
  
  // take a step toward the commanded position if not there yet
  if (pos < command  )
  {
    ++steps;
    steps %= 4;
    pos += 1;
  }
  else if (pos > command)
  {
    --steps;
    if (steps < 0) steps = 3;
    pos -= 1;
  }
  
  // execute the next step
  for (int i=0; i<4; ++i)
    if (fullStep[steps][i] == 1)
      digitalWrite(coilPins[i], LOW);
    else
      digitalWrite(coilPins[i], HIGH);
}
