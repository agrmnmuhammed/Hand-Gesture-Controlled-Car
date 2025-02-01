
#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>
#include <MPU6050.h>


MPU6050 mpu;
int16_t ax_raw, ay_raw, az_raw;
int16_t gx_raw, gy_raw, gz_raw;
float ax, ay, az;
float gx, gy, gz;


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

Payload payload;
uint8_t receiverAddress[] = {0xE4, 0x65, 0xB8, 0xDA, 0x73, 0x74};

void onSent(const uint8_t *macAddr, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Veri başarıyla gönderildi.");
  } else {
    Serial.println("Veri gönderimi başarısız.");
  }
}

void setup() {
  Serial.println("Verici başlatılıyor...");
  Serial.begin(115200);
  Wire.begin(21, 22);

  
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 bağlantısı başarısız!");
    while (1);
  }
  Serial.println("MPU6050 başarıyla başlatıldı.");

  // ESP-NOW başlatma
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı!");
    while (1);
  }
  esp_now_register_send_cb(onSent);

  // Alıcı ESP32'yi ekle
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Alıcı eklenemedi!");
    while (1);
  }
  Serial.println("Alıcı başarıyla eklendi.");
}

void loop() {
  mpu.getMotion6(&ax_raw, &ay_raw, &az_raw, &gx_raw, &gy_raw, &gz_raw);

  ax = ax_raw / 16384.0;
  ay = ay_raw / 16384.0;
  az = az_raw / 16384.0;

  if (ay > 0.6) {
    payload.command = MOVE_FORWARD;
    Serial.println("İleri git");
  } else if (ay < -0.6) {
    payload.command = MOVE_BACKWARD;
    Serial.println("Geri git");
  } else if (ax > 0.6) {
    payload.command = MOVE_RIGHT;
    Serial.println("Sağa dön");
  } else if (ax < -0.6) {
    payload.command = MOVE_LEFT;
    Serial.println("Sola dön");
  } else {
    payload.command = STOP;
    Serial.println("Dur");
  }

  esp_now_send(receiverAddress, (uint8_t *)&payload, sizeof(payload));
delay(200);
}
