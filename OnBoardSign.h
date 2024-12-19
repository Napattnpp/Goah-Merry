class OnBoardSign {
  public:
    void ready();
    void skipTask();
}; OnBoardSign onBoardSign;

void OnBoardSign::ready() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_BUILTIN, 1);
    delay(300);
    digitalWrite(LED_BUILTIN, 0);
    delay(300);
  }
}

void OnBoardSign::skipTask() {
  digitalWrite(LED_BUILTIN, 1);
  delay(500);
  for (int i = 0; i < 2; i++) {
    digitalWrite(LED_BUILTIN, 0);
    delay(100);
    digitalWrite(LED_BUILTIN, 1);
    delay(100);
  }
  digitalWrite(LED_BUILTIN, 0);
}