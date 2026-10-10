# Arduino-Nano-Heart-Rate-Monitor
Arduino Nano Heart Rate Monitor
A workshop-built heart-rate monitoring prototype using an Arduino Nano and a MAX30102 optical pulse sensor. The Arduino reads an infrared (IR) signal, detects pulse events, calculates beats per minute (BPM), and displays instantaneous and averaged heart-rate estimates in the Arduino Serial Monitor.
Educational prototype only: This project is not a medical device and its readings are not intended for diagnosis or health decisions.

Project demonstration


Hardware assembly

Serial Monitor output

[Watch the workshop demonstration](

https://github.com/user-attachments/assets/31dcec74-ce05-49d6-a566-138e55bffa22


Hardware and tools
- Arduino Nano microcontroller
- MAX30102 optical pulse sensor module
- Breadboard and jumper wires
- USB cable and computer
- Arduino IDE
- SparkFun MAX3010x Sensor Library (MAX30105.h and heartRate.h)
- Arduino Wire library for I²C communication
Note: The library uses the header MAX30105.h even when communicating with a MAX30102 module.
How it works
1. Starts serial communication at 115200 baud and initializes the I²C bus.
2. Attempts to connect to the sensor, displaying a troubleshooting message if the sensor is not found.
3. Reads the IR value from the sensor.
4. If the IR value is below 50,000, displays a No finger detected message. This is a configurable heuristic, not a guaranteed finger-detection method.
5. Uses checkForBeat() from the sensor library's heart-rate helper to identify a pulse event.
6. Measures the time between detected beats using millis() and calculates BPM:
   BPM = 60000 / milliseconds_between_beats
7. Accepts calculated values between 20 and 255 BPM and computes an average of up to four recent accepted readings.
8. Prints IR, BPM, and average BPM when it accepts a detected beat.
Code
The workshop sketch is preserved in [`src/HeartRateMonitor.ino`](src/HeartRateMonitor.ino).
Running the prototype
1. Install Arduino IDE and the SparkFun MAX3010x Sensor Library through the Library Manager.
2. Connect the MAX30102 module to the Arduino Nano using appropriate power, ground, SDA, and SCL connections. Verify the pinout and voltage compatibility of your specific sensor breakout before powering it. (The photograph is not sufficient to document exact pin assignments.)
3. Open src/HeartRateMonitor.ino in Arduino IDE.
4. Select the correct Arduino Nano board variant and serial port.
5. Upload the sketch.
6. Open Serial Monitor and set the baud rate to 115200.
7. Place a finger gently and steadily over the optical sensor, and observe the output.
Example output
Starting MAX30102...
MAX30102 detected!
Place your finger flat over the sensor.

IR: 132447 | Beat! | BPM: 90.4 | Average BPM: 72
Output is illustrative of the photographed workshop session; readings will vary with use and setup.
Engineering concepts explored
- Breadboard circuit assembly and microcontroller interfacing
- I²C sensor communication
- Optical pulse detection
- Time-based BPM calculation
- Small rolling sample buffers for averaging
- Real-time serial monitoring and troubleshooting
Limitations and potential improvements
- A four-sample moving average can smooth readings but does not guarantee accuracy.
- When a finger is removed, the current sketch doesn't clear the prior BPM history or reset lastBeat; reacquiring a signal may initially produce misleading output.
- Sensor motion, finger placement, and ambient conditions can affect readings.
- A future version could reset stale readings, add an OLED readout, and compare readings against a reference pulse-measuring device.
- This sketch does not compute blood oxygen saturation (SpO₂), despite the sensor hardware being used in applications that support it.
Workshop and attribution
Assembled and tested during a hands-on heartbeat sensor workshop in October 2026.
