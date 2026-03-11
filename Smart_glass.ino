const int trigPin = 9;
const int echoPin = 10;
const int buzzer = 8;
const int led = 7;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 50) {
    digitalWrite(led, HIGH);
    int beepDelay = map(distance, 0, 50, 50, 500);
    digitalWrite(buzzer, HIGH);
    delay(beepDelay);
    digitalWrite(buzzer, LOW);
    delay(beepDelay);
  } else {
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }

  delay(50);
}
