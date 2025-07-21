# 🛡️ EdgeRisk Analyzer – Real-Time Credit Card Fraud Detection on ESP32

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

## ⚙️ Tech Stack

- **Languages:** Python, C++  
- **Frameworks:** TensorFlow, TensorFlow Lite Micro  
- **Hardware:** ESP32 Dev Module, SSD1306 OLED Display  

---

## 🌟 Why This Project Stands Out

✅ Optimized deep learning model to run in **128KB RAM**  
✅ Achieved **<1ms inference** without cloud dependency  
✅ Integrated real-time visualization + physical alert system  
✅ Built as a **resume-grade AI + IoT + embedded** project  

---

## 🚧 Next Steps

- 🔗 Integrate with **AWS IoT Core** for cloud-based logging  
- 📲 Add **mobile alerts** via WiFi/Bluetooth  
- 🧠 Retrain using **imbalanced learning techniques** for improved fraud detection  
- 🔒 Add on-device **basic encryption or data masking** features


