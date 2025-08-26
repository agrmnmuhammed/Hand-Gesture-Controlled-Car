# ✋🤖 Hand Gesture Controlled Car  

## 📌 Description / Açıklama  

**English:**  
This project is a gesture-controlled 4WD car system developed using two ESP32 boards, an MPU6050 accelerometer/gyroscope sensor, and the ESP-NOW communication protocol.  
- The MPU6050 sensor is mounted on a glove to capture hand gestures (acceleration and orientation data).  
- These values are sent wirelessly via **ESP-NOW** from the glove ESP32 to the car ESP32.  
- The car ESP32 interprets the received motion data and generates PWM signals to drive the motors through an L298N motor driver.  
- Based on the hand tilt direction, the car moves **forward, backward, forward-left, forward-right, backward-left, or backward-right**.  

This project demonstrates wireless communication, motion sensing, and motor control using microcontrollers.  

**Türkçe:**  
Bu proje, iki ESP32 kartı, MPU6050 ivmeölçer/jyroskop sensörü ve ESP-NOW haberleşme protokolü kullanılarak geliştirilmiş bir el hareketiyle kontrol edilen 4 tekerlekli araç sistemidir.  
- MPU6050 sensörü bir eldiven üzerine monte edilerek el hareketleri (ivme ve yönelim verileri) algılanır.  
- Bu veriler **ESP-NOW** protokolü ile eldiven ESP32’den araçtaki ESP32’ye kablosuz olarak iletilir.  
- Araçtaki ESP32, gelen hareket verilerini yorumlayarak PWM sinyalleri üretir ve L298N motor sürücü üzerinden motorları kontrol eder.  
- Elin eğim yönüne göre araç **ileri, geri, ileri-sol, ileri-sağ, geri-sol veya geri-sağ** yönde hareket eder.  

Bu proje ile kablosuz haberleşme, hareket algılama ve mikrodenetleyici tabanlı motor kontrolü konularında yetkinlik kazanılmıştır.  

---

## ⚙️ Features / Özellikler  
- 📡 Wireless communication with **ESP-NOW**  
- ✋ Gesture-based control using **MPU6050 (accelerometer + gyroscope)**  
- ⚡ Real-time motor control with PWM signals  
- 🔄 Support for multiple directions: forward, backward, left, right, diagonal movements  
- 🔌 L298N motor driver integration  
- 🧤 Glove-based intuitive control  

---

## 🛠️ Hardware & Software / Donanım & Yazılım  

**Hardware (Donanım):**  
- 🔹 2 × ESP32 development boards  
- 🔹 1 × MPU6050 accelerometer/gyroscope sensor  
- 🔹 1 × L298N motor driver  
- 🔹 4WD car chassis with DC motors  
- 🔹 Power supply (Li-ion battery / power bank)  
- 🔹 Control glove  

**Software (Yazılım):**  
- 💻 Arduino IDE / PlatformIO (I did with Arduino IDE)  
- 📡 ESP-NOW protocol libraries  
- 🔗 I2C communication for MPU6050  
- ⚙️ PWM motor control  

---

## 📂 Project Structure  
