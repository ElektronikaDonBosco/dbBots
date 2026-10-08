// =====================================================
//  LERRO-JARRAITZAILEA · 2. fasea: abiadura kontrolarekin (PWM)
//  dbBots · dbSariak
//  Sentsoreak: beltza = 0, zuria = 1
//  S1 = ezkerrekoena ... S3 = erdikoa ... S5 = eskuinekoena
//  (robota atzetik begiratuta, aurrera doala)
//  L298N: ENA eta ENB jumperrak KENDU eta PWM pinetara konektatu
// =====================================================

// Sentsoreak (sarrerak)
#define sen1 2
#define sen2 3
#define sen3 4
#define sen4 5
#define sen5 6

// Eskuineko motorra: noranzkoa (IN3, IN4) eta abiadura (ENB)
#define eskIn1 8
#define eskIn2 9
#define eskPWM 10
// Ezkerreko motorra: noranzkoa (IN1, IN2) eta abiadura (ENA)
#define ezkIn1 12
#define ezkIn2 13
#define ezkPWM 11

// Abiadurak (0 = geldi ... 255 = abiadura osoa). Probatu eta doitu!
#define AZKAR 255
#define MOTEL 150
#define GELDI 0

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
  pinMode(eskPWM, OUTPUT);
  pinMode(ezkIn1, OUTPUT);
  pinMode(ezkIn2, OUTPUT);
  pinMode(ezkPWM, OUTPUT);
  Serial.begin(9600);

  // Bi motorrak beti aurrera biratzeko noranzkoa
  digitalWrite(eskIn1, HIGH);
  digitalWrite(eskIn2, LOW);
  digitalWrite(ezkIn1, HIGH);
  digitalWrite(ezkIn2, LOW);
}

void loop() {
  // Behin eta berriz egiten diren atazak
  eg_sen1 = digitalRead(sen1);
  eg_sen2 = digitalRead(sen2);
  eg_sen3 = digitalRead(sen3);
  eg_sen4 = digitalRead(sen4);
  eg_sen5 = digitalRead(sen5);
  serialetik_idatzi();

  // Erdiko sentsorea beltza -> bi motorrak abiadura osoan
  if (eg_sen1 == 1 && eg_sen2 == 1 && eg_sen3 == 0 && eg_sen4 == 1 && eg_sen5 == 1) {
    Serial.println("Aurrera");
    analogWrite(eskPWM, AZKAR);
    analogWrite(ezkPWM, AZKAR);
  }

  // Eskuineko lehen sentsorea beltza -> eskuineko motorra moteldu (bira leuna eskuinera)
  if (eg_sen1 == 1 && eg_sen2 == 1 && eg_sen3 == 1 && eg_sen4 == 0 && eg_sen5 == 1) {
    Serial.println("Eskuinera (leun)");
    analogWrite(eskPWM, MOTEL);
    analogWrite(ezkPWM, AZKAR);
  }

  // Ezkerreko lehen sentsorea beltza -> ezkerreko motorra moteldu (bira leuna ezkerrera)
  if (eg_sen1 == 1 && eg_sen2 == 0 && eg_sen3 == 1 && eg_sen4 == 1 && eg_sen5 == 1) {
    Serial.println("Ezkerrera (leun)");
    analogWrite(eskPWM, AZKAR);
    analogWrite(ezkPWM, MOTEL);
  }

  // Eskuineko bigarren sentsorea beltza -> eskuineko motorra geldi (bira gogorra eskuinera)
  if (eg_sen1 == 1 && eg_sen2 == 1 && eg_sen3 == 1 && eg_sen4 == 1 && eg_sen5 == 0) {
    Serial.println("Eskuinera (gogor)");
    analogWrite(eskPWM, GELDI);
    analogWrite(ezkPWM, AZKAR);
  }

  // Ezkerreko bigarren sentsorea beltza -> ezkerreko motorra geldi (bira gogorra ezkerrera)
  if (eg_sen1 == 0 && eg_sen2 == 1 && eg_sen3 == 1 && eg_sen4 == 1 && eg_sen5 == 1) {
    Serial.println("Ezkerrera (gogor)");
    analogWrite(eskPWM, AZKAR);
    analogWrite(ezkPWM, GELDI);
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
