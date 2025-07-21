import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import confusion_matrix , accuracy_score , classification_report

credit_card_data = pd.read_csv('creditcard.csv')

credit_card_data['Class'].value_counts()
#print(credit_card_data['Class'].value_counts())

normal = credit_card_data[credit_card_data.Class==0]
fraud = credit_card_data[credit_card_data.Class==1]

#print(normal.shape)
#print(fraud.shape)

labels = ["Normal", "Fraud"]
count_classes = credit_card_data.value_counts(credit_card_data['Class'], sort=True)
#print(count_classes)
count_classes.plot(kind="bar", rot=0)

plt.ylabel("Count")

plt.xticks(range(2), labels)

#plt.show()

normal.Amount.describe()
fraud.Amount.describe()

sns.relplot(x='Amount', y= 'Time', hue='Class', data=credit_card_data)

#plt.show()

normal_sample = normal.sample(n=492)

credit_card_new_data=pd.concat([normal_sample,fraud], axis=0)

X = credit_card_new_data.drop('Class', axis=1)
Y = credit_card_new_data['Class']

X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, stratify=Y, random_state=42)
print(X.shape, X_train.shape, X_test.shape)

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
from tensorflow.keras.optimizers import Adam

# Build a simple NN
model = Sequential([
    Dense(16, input_dim=X_train.shape[1], activation='relu'),
    Dropout(0.2),
    Dense(8, activation='relu'),
    Dense(1, activation='sigmoid')
])

model.compile(optimizer=Adam(learning_rate=0.001),
              loss='binary_crossentropy',
              metrics=['accuracy'])

# Train
model.fit(X_train, Y_train, epochs=5, batch_size=64, validation_split=0.2)

model.save("fraud_model.h5")



import tensorflow as tf

# Load the model
model = tf.keras.models.load_model("fraud_model.h5")

# Convert to TFLite
converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]  # Enables quantization
tflite_model = converter.convert()

# Save the .tflite file
with open("fraud_model.tflite", "wb") as f:
    f.write(tflite_model)

print(" TFLite model saved!")

