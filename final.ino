#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "fraud_model.h" 
#include <wire.h> // <<-- Use your model header
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#define GREEN_LED_PIN 19
#define RED_LED_PIN 18

#define TFLITE_SCHEMA_VERSION 3  // <<-- Add if missing and correct as needed

#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
// DO NOT include version.h

// OLED config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// TFLite globals
constexpr int kTensorArenaSize = 10 * 1024;
uint8_t tensor_arena[kTensorArenaSize];

const tflite::Model* model;
tflite::MicroInterpreter* interpreter;
TfLiteTensor* input;
TfLiteTensor* output;

// Replace with all 30 values — here's a partial snippet based on your dataset
float featureMins[30] = {
  0.0,        -56.4075, -72.7157, -48.3256, -5.6832,   // Time, V1–V4
  -26.1605,   -43.5572, -33.8478,  -0.5556, -13.4341,  // V5–V9
  -24.5883,   -4.7977,  -15.1240, -5.7919,  -4.4989,   // V10–V14
  -4.2891,    -14.4070, -26.1605, -2.3032,  -5.7919,   // V15–V19
  -54.4977,   -34.8303, -10.9331, -44.8077, -2.5542,   // V20–V24
  -10.5977,   -22.5657, -11.3589, -0.3077,   0.0       // V25–Amount
};

float featureMaxs[30] = {
  172792.0,    2.4549,  22.0577,   9.3826,  16.8753,
  34.8017,     20.7121, 39.4209,   12.0189, 15.5950,
  23.7451,      7.5936,  7.1269,   5.3977,  2.3844,
  4.5845,       2.0542,  7.5196,   2.3644,  3.2081,
  39.4209,     0.4085,  22.5284,   5.5919,  10.0000,
  7.5196,       1.6483,  3.5173,   0.7589,  25691.16
};


void setup() {
  Serial.begin(115200);
  pinMode(GREEN_LED_PIN , OUTPUT);
  pinMode(RED_LED_PIN , OUTPUT);
  digitalWrite(GREEN_LED_PIN , LOW);
  digitalWrite(RED_LED_PIN, LOW);

  // OLED Init
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("EdgeRisk Analyzer");
  display.display();
  delay(2000);

  // Load model
  model = tflite::GetModel(fraud_model_tflite);   // <<-- Use array name from your header
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch");
    while (1);
  }

  // Op Resolver (ensure you have the ops your model needs)
  static tflite::MicroMutableOpResolver<6> resolver;
  resolver.AddFullyConnected();
  resolver.AddRelu();
  resolver.AddSoftmax();
  resolver.AddQuantize();
  resolver.AddDequantize();
  resolver.AddLogistic();

  static tflite::MicroInterpreter static_interpreter(model, resolver, tensor_arena, kTensorArenaSize);
  interpreter = &static_interpreter;

  if (interpreter->AllocateTensors() != kTfLiteOk) {
    Serial.println("Tensor allocation failed");
    while (1);
  }

  input = interpreter->input(0);
  output = interpreter->output(0);
  Serial.print("Output type: ");
 Serial.println(output->type);

}

void loop() {
  // Simulate dummy input data for all 30 features
for (int i = 0; i < 30; i++) {
  float minVal = featureMins[i];
  float maxVal = featureMaxs[i];
  float randVal = minVal + ((float)random(0, 10001) / 10000.0) * (maxVal - minVal);
  input->data.f[i] = randVal;
}    // Simulated Amount

  float amount = input->data.f[29];          // For display only

  // 💡 Start timing
  unsigned long start_time = micros();

  // Run inference
  if (interpreter->Invoke() != kTfLiteOk) {
    Serial.println("Invoke failed");
    return;
  }
  float riskScore;

 if (output->type == 1) {  // float
  riskScore = output->data.f[0] * 100.0;
 } else if (output->type == 4) {  // uint8 quantized
  riskScore = (output->data.uint8[0] - output->params.zero_point) * output->params.scale * 100.0;
 } else {
  riskScore = 0.0;
 }

 
  unsigned long end_time = micros();
  unsigned long inference_time = end_time - start_time;  // Time in microseconds

 // float riskScore = output->data.f[0] * 100.0;  // 0.0 to 100.0
  String status = (riskScore > 75.0) ? "BLOCKED" : "SAFE";

  char txnId[10];
sprintf(txnId, "%c%c%c%c-%c%c%c%c",
        random('A', 'Z'), random('A', 'Z'),
        random('0', '9'), random('0', '9'),
        random('A', 'Z'), random('0', '9'),
        random('A', 'Z'), random('0', '9'));

 
  // Serial Output
  Serial.println("===========");
  Serial.printf("Amount: $%.2f\n", amount);
  Serial.printf("Status: %s\n", status.c_str());
  Serial.print("TXN ID: ");
  Serial.println(txnId);
  Serial.printf("Inference Time: %lu microseconds (%.2f ms)\n", inference_time, inference_time / 1000.0);
  
  // OLED Output
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("EdgeRisk Analyzer");
  display.println("------------------");
  display.print("Amt: $");
  display.println(amount, 2);
  display.print("Status: ");
  display.println(status);
  display.print("TXN ID: ");
  display.println(txnId);  
  display.print("Infrce Time: ");
  display.print(inference_time / 1000.0);
  display.println(" ms");
  display.display();

  if (status == "SAFE") {
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
  } else {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
  }

  delay(3000);  // Wait 3s before next inference
}

