// =====================================================
//  LERRO-JARRAITZAILEA · 1. fasea: abiadura kontrolik gabe
//  dbBots · dbSariak
//  Sentsoreak: beltza = 0, zuria = 1
//  S1 = ezkerrekoena ... S3 = erdikoa ... S5 = eskuinekoena
//  (robota atzetik begiratuta, aurrera doala)
//  L298N: ENA eta ENB jumperrak JARRITA
// =====================================================

// Sentsoreak (sarrerak)
#define sen1 2
#define sen2 3
#define sen3 4
#define sen4 5
#define sen5 6

// Eskuineko motorra (L298N IN3, IN4 -> OUT3, OUT4)
#define eskIn1 8
#define eskIn2 9
// Ezkerreko motorra (L298N IN1, IN2 -> OUT1, OUT2)
#define ezkIn1 10
#define ezkIn2 11

int eg_sen1 = 0;
int eg_sen2 = 0;
int eg_sen3 = 0;
int eg_sen4 = 0;
int eg_sen5 = 0;

void setup() {
  // Behin bakarrik egiten diren atazak
  pinMode(sen1, INPUT);
  pinMode(sen2, INPUT);
  pinMode(sen3, INPUT);
  pinMode(sen4, INPUT);
  pinMode(sen5, INPUT);
  pinMode(eskIn1, OUTPUT);
  pinMode(eskIn2, OUTPUT);
  pinMode(ezkIn1, OUTPUT);
  pinMode(ezkIn2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Behin eta berriz egiten diren atazak
  eg_sen1 = digitalRead(sen1);
  eg_sen2 = digitalRead(sen2);
  eg_sen3 = digitalRead(sen3);
  eg_sen4 = digitalRead(sen4);
  eg_sen5 = digitalRead(sen5);
  serialetik_idatzi();

  // Erdiko sentsorea beltza -> bi motorrak aurrera
  if (eg_sen1 == 1 && eg_sen2 == 1 && eg_sen3 == 0 && eg_sen4 == 1 && eg_sen5 == 1) {
    Serial.println("Aurrera");
    digitalWrite(eskIn1, HIGH);
    digitalWrite(eskIn2, LOW);
    digitalWrite(ezkIn1, HIGH);
    digitalWrite(ezkIn2, LOW);
  }

  // Eskuineko lehen sentsorea beltza -> eskuineko motorra geldi, ezkerrekoa aurrera
  if (eg_sen1 == 1 && eg_sen2 == 1 && eg_sen3 == 1 && eg_sen4 == 0 && eg_sen5 == 1) {
    Serial.println("Eskuinera");
    digitalWrite(eskIn1, LOW);
    digitalWrite(eskIn2, LOW);
    digitalWrite(ezkIn1, HIGH);
    digitalWrite(ezkIn2, LOW);
  }

  // Ezkerreko lehen sentsorea beltza -> ezkerreko motorra geldi, eskuinekoa aurrera
  if (eg_sen1 == 1 && eg_sen2 == 0 && eg_sen3 == 1 && eg_sen4 == 1 && eg_sen5 == 1) {
    Serial.println("Ezkerrera");
    digitalWrite(eskIn1, HIGH);
    digitalWrite(eskIn2, LOW);
    digitalWrite(ezkIn1, LOW);
    digitalWrite(ezkIn2, LOW);
  }

  // Eskuineko bigarren sentsorea beltza -> eskuineko motorra geldi, ezkerrekoa aurrera
  if (eg_sen1 == 1 && eg_sen2 == 1 && eg_sen3 == 1 && eg_sen4 == 1 && eg_sen5 == 0) {
    Serial.println("Eskuinera (gogor)");
    digitalWrite(eskIn1, LOW);
    digitalWrite(eskIn2, LOW);
    digitalWrite(ezkIn1, HIGH);
    digitalWrite(ezkIn2, LOW);
  }

  // Ezkerreko bigarren sentsorea beltza -> ezkerreko motorra geldi, eskuinekoa aurrera
  if (eg_sen1 == 0 && eg_sen2 == 1 && eg_sen3 == 1 && eg_sen4 == 1 && eg_sen5 == 1) {
    Serial.println("Ezkerrera (gogor)");
    digitalWrite(eskIn1, HIGH);
    digitalWrite(eskIn2, LOW);
    digitalWrite(ezkIn1, LOW);
    digitalWrite(ezkIn2, LOW);
  }
}

// Sentsoreen egoera serie-monitorean idatzi (9600 baud)
void serialetik_idatzi() {
  Serial.print(eg_sen1); Serial.print("   ");
  Serial.print(eg_sen2); Serial.print("   ");
  Serial.print(eg_sen3); Serial.print("   ");
  Serial.print(eg_sen4); Serial.print("   ");
  Serial.println(eg_sen5);
}
