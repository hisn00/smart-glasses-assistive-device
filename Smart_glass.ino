const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 8;

long duration;
int distance;

// For smoothing (reducing noise)
int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long dur = pulseIn(echoPin, HIGH, 30000); // timeout 30ms

  if (dur == 0) return 400; // if no signal, assume far distance

  return dur * 0.034 / 2;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Take multiple readings for accuracy
  int total = 0;
  for (int i = 0; i < 5; i++) {
    total += readDistance();
    delay(10);
  }
  distance = total / 5;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Smarter detection range
  if (distance > 0 && distance <= 100) {

    // Faster and smoother mapping
    int beepDelay = map(distance, 5, 100, 50, 600);
    beepDelay = constrain(beepDelay, 50, 600);

    digitalWrite(buzzer, HIGH);
    delay(beepDelay);
    digitalWrite(buzzer, LOW);
    delay(beepDelay);

  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(30);
}