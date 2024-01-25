int layers[] = { 11, 12, 13 };
int columns[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10 };

void setDiode(int layer, int column, bool state) {
  bool col_state = state;
  bool lay_state = !state;
  digitalWrite(layers[layer], lay_state);
  digitalWrite(columns[column], col_state);
}

void lightDiode(int diode, bool state) {
  int layer = diode % 3;
  int column = diode / 3;
  setDiode(layer, column, state);
}

int lightDiodeSet(int diodes[27], int iteration) {
  if (iteration < 0 || iteration > 26) return 0;

  int previous = iteration - 1;

  if (previous < 0) previous = 26;

  lightDiode(previous, false);

  if (diodes[iteration]) {
    lightDiode(iteration, true);
  }

  return (iteration + 1) % 27;
}

int diodes[27] = {
  1, 0, 0,  // l1, l2, l3 col(1)
  0, 0, 0,  // l1, l2, l3 col(2)
  0, 0, 0,  // l1, l2, l3 col(3)
  0, 0, 0,  // l1, l2, l3 col(4)
  0, 0, 0,  // l1, l2, l3 col(5)
  0, 0, 0,  // l1, l2, l3 col(6)
  0, 0, 0,  // l1, l2, l3 col(7)
  0, 0, 0,  // l1, l2, l3 col(8)
  0, 0, 0,  // l1, l2, l3 col(9)
};



// timing variables
const int dt = 500;
int pt = 0, ct = 0;
int iteration = 0;

void setup() {
  for (int i = 2; i <= 13; i++) { pinMode(i, OUTPUT); }
  for (int i = 2; i <= 10; i++) { digitalWrite(i, LOW); }
  for (int i = 11; i <= 13; i++) { digitalWrite(i, HIGH); }
}

int layer = 0;
int column = 0;

void loop() {

  iteration = lightDiodeSet(diodes, iteration);
  ct = millis();
  if (ct - pt >= dt) {
    column = (column + 1) % 9;
    if (column == 0) {
      layer = (layer + 1) % 3;
    }
    diodes[column * 3 + layer] = !diodes[column * 3 + layer];
    pt = ct;
  }
}
