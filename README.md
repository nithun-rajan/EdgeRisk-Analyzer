# 🛡️ EdgeRisk Analyzer – Real-Time Credit Card Fraud Detection on ESP32

## 🎥 Demo Videos

🔗 [Watch Full-Length Demo (ESP32 Fraud Detection)](https://youtu.be/W8rHCju79kY)
                            Or
🔗 [Watch Short Demo ( YouTube Short)](https://www.youtube.com/shorts/TrEbAUzd5hQ)


---

## 🚀 Project Overview  
**EdgeRisk Analyzer** is a real-time, edge-deployed fraud detection system powered by a quantized deep neural network. Built for ultra-low-power environments, the system runs entirely on an **ESP32 microcontroller (240MHz, 128KB RAM)** using **TensorFlow Lite for Microcontrollers**, without any cloud dependence.

This project highlights my ability to **optimize machine learning models for embedded hardware** and deploy intelligent systems in constrained environments.

---

## 🔍 Key Metrics & Highlights

| Feature              | Value                           |
|----------------------|---------------------------------|
| **Dataset**          | 284,807 real-world transactions |
| **Features Used**    | 30+ engineered input variables  |
| **Model Accuracy**   | 94% (training)                  |
| **Quantization**     | int8 via TFLite Micro           |
| **Inference Time**   | ⚡ 0.06 ms per transaction       |
| **MCU Used**         | ESP32 Dev Module @ 240MHz (128KB RAM) |

### 📟 OLED Display Shows:
- 💵 **Transaction Amount**  
- 🔁 **Transaction ID**  
- ✅❌ **Transaction Status** (Safe / Fraudulent)  
- ⏱️ **Inference Time (ms)**  

### 🔴🟢 LED Indicators:
- **Red LED** → Fraudulent Transaction (Blocked)  
- **Green LED** → Safe Transaction (Approved)

### 📡 Future-Ready:
- Built-in **WiFi & Bluetooth** for AWS/mobile alert integration

---

## 📊 Visual Insights

### ⚖️ Class Distribution – Normal vs Fraudulent
![Class Distribution](./Figure_1.png)

> Note: This shows the extreme class imbalance in the dataset — a real-world challenge that makes fraud detection harder and more meaningful.

### 🕵️ Transaction Scatter by Time & Amount
![Transaction Time vs Amount](./Figure_2.png)

---
## 📸 Project Snapshots

### 🖥️ OLED Output  
![OLED 1](./1.png)  
![OLED 2](./4.png)

### 🔌 Full Hardware Setup  
![Setup 1](./2.png)  
![Setup 2](./3.png)

---

## ⚙️ Tech Stack

- **Languages:** Python, C++  
- **Frameworks:** TensorFlow, TensorFlow Lite Micro  
- **Hardware:** ESP32 Dev Module, SSD1306 OLED Display  

---
# 📥 How to Use This Project

## 🔁 Clone the Repository
-git clone https://github.com/nithun-rajan/EdgeRisk-Analyzer.git
-cd EdgeRisk-Analyzer

## 🧪 Training (Python)
-Use the main.py script to train and evaluate the model on your local machine.

This file:
-Loads the credit card dataset
-Trains a dense neural network
-Saves a .tflite model for quantization

## 📦 Microcontroller Deployment (Arduino)
Use the following files for ESP32 deployment:
-final.ino – Main firmware logic for ESP32 (handles OLED display, LED alerts, and model inference)
-fraud_model.h – Quantized model in C header format (converted using xxd)
-model.h, fraud_model.tflite – Intermediate files used for model conversion

Upload final.ino using Arduino IDE with the following libraries:
-TensorFlowLite_ESP32
-Adafruit_GFX
-Adafruit_SSD1306

## 🧠 System Architecture

1. **Data Pipeline:** Preprocessed 284,807 credit card transactions with 30+ features.
2. **Model Training:** Trained a dense neural network using TensorFlow; quantized to int8.
3. **Model Deployment:** Deployed using TensorFlow Lite Micro on ESP32 (128KB RAM).
4. **On-Device Execution:** Real-time inference + OLED visualization + LED alerts.
5. **Hardware I/O:** Inputs simulated via serial; output shown via OLED & LEDs.
6. **Connectivity Layer:** WiFi/Bluetooth stack initialized for future cloud/phone alerts.

---

## 🛠️ Build & Deployment Pipeline

1. Train fraud detection model in Python with TensorFlow  
2. Quantize model using post-training int8 quantization  
3. Convert `.h` model file using `xxd` for microcontroller use  
4. Integrate model into Arduino IDE via `TensorFlowLite.h` and `fraud_model.h`  
5. Program OLED and GPIO feedback via C++  
6. Upload firmware to ESP32 and test real-time predictions  

---

## 📦 Real-World Applications

- Offline credit card scanners for remote/rural ATMs  
- Smart POS terminals with built-in fraud filtering  
- Embedded risk engines for edge IoT finance devices  
- Educational demo for ML + Embedded Systems + Security  



