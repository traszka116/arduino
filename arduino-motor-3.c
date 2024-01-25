#define BLUE 8
#define PINK 9
#define YELLOW 10
#define ORANGE 11

#define SW_L 12
#define SW_R 13

typedef enum { Front = 1,
               Back = -1 } direction_t;
typedef enum { Wave,
               FullStep,
               SemiStep } method_t;

int controll[][4] = {
  { 0, 0, 0, 1 },
  { 0, 0, 1, 1 },
  { 0, 0, 1, 0 },
  { 0, 1, 1, 0 },
  { 0, 1, 0, 0 },
  { 1, 1, 0, 0 },
  { 1, 0, 0, 0 },
  { 1, 0, 0, 1 }
};

int nextStep(int current_step, method_t method, direction_t direction) {
  if(current_step < 0)
    current_step = 7;
  if(current_step > 7)
    current_step = 0;
  int next_step = current_step + ((method == SemiStep) ? 1 : 2) * (int)direction;
  digitalWrite(BLUE,controll[current_step][0]);
  digitalWrite(PINK,controll[current_step][1]);
  digitalWrite(YELLOW,controll[current_step][2]);
  digitalWrite(ORANGE,controll[current_step][3]);
  return next_step;
}

// Wave, SemiStep - 0
// FullStep - 1
int step = 0;
int ct = 0, pt = 0, dt = 1000;

void setup() {
  for (int i = BLUE; i <= ORANGE; i++)
    pinMode(i, OUTPUT);
  pinMode(SW_L, INPUT);
  pinMode(SW_R, INPUT);
}

void loop() {

  if(digitalRead(SW_R))
  {
    digitalWrite(BLUE, LOW);
    digitalWrite(PINK, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(ORANGE, LOW);
    return;
  }

  ct = millis();
  if(ct - pt < dt) {
    return;
  }

  direction_t direction = (digitalRead(SW_L)) ? (Back) : Front;
  step = nextStep(step, SemiStep, direction);
  pt = ct;
}
