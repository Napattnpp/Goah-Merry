void getDistance() {
  distance = sonar.ping_cm();
}

bool isObsFound() {
  getDistance();
  return (distance <= obstacleRange) ? 1 : 0;
}

void checkObs180D() {
  for (int i = 0; i <= 180; i++) {
    servoFront.write(i);
    delay(10);
  }
  for (int i = 180; i >= 0; i--) {
    servoFront.write(i);
    delay(10);
  }
}