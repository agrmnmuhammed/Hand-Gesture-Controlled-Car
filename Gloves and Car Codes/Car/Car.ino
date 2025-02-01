#include <esp_now.h>
#include <WiFi.h>

#define ENA 5
#define IN1 18
#define IN2 19
#define ENB 16
#define IN3 23
#define IN4 22

enum Command {
  MOVE_RIGHT,
  MOVE_LEFT,
  MOVE_FORWARD,
  MOVE_BACKWARD,
  STOP
};

typedef struct {
  Command command;
  float ax;
  float ay;
  float az;
} Payload;

Payload receivedData;

void onReceive(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  if (len == sizeof(Payload)) {
    memcpy(&receivedData, incomingData, sizeof(receivedData));
    Serial.print("Komut: ");
    Serial.println(receivedData.command);

    switch (receivedData.command) {
      case MOVE_FORWARD:
        moveForward();
        break;
      case MOVE_BACKWARD:
        moveBackward();
        break;
      case MOVE_LEFT:
        moveLeft();
        break;
      case MOVE_RIGHT:
        moveRight();
        break;
      case STOP:
        stopMotors();
        break;
    }
  } else {
    Serial.println("Gelen veri boyutu hatalı!");
  }
}

void moveForward() {
  Serial.println("İleri gidiliyor");
  analogWrite(ENA, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, 200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveBackward() {
  Serial.println("Geri gidiliyor");
  analogWrite(ENA, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENB, 200);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void moveRight() {
  Serial.println("Sağa dönülüyor");
  analogWrite(ENA, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, 100);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveLeft() {
  Serial.println("Sola dönülüyor");
  analogWrite(ENA, 100);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENB, 200);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors() {
  Serial.println("Motorlar durduruldu");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup() {
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı!");
    return;
  }
  esp_now_register_recv_cb(onReceive);
}

void loop() {

}
