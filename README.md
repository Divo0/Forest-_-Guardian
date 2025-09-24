# Forest-_-Guardian
esp_32 code to send temp, humidity, light and CO2 data from sensors to webpage
# Fire Guardian 🔥🌲

A smart forest fire detection system that combines **ESP32-based sensor nodes** with a **real-time web dashboard** (`index_test.html`).  
This README is ready to copy — paste into `README.md`.

---

## Project structure
- `index_test.html`  
  Web dashboard: interactive map, node indicators, and real-time charts for Temperature, Humidity, Light, and Gas levels. Connects to ESP32 via the Web Serial API.

- `sensor_V_01_bluetooth_2.0.ino`  
  ESP32 firmware: reads sensors (DHT, LDR, MQ-series gas sensor), outputs serial data (CSV or JSON) compatible with the dashboard.

---

## Features
- Interactive forest map with clickable sensor nodes (Node 3 is default prototype)
- Real-time line charts for Temperature, Humidity, Light, Gas (with threshold lines)
- Per-chart pause/resume (click chart)
- Web Serial connection panel with live serial log
- Fire alert modal when thresholds are exceeded
- Demo mode & keyboard shortcuts:
  - Press `F` to trigger simulated fire alert
  - Press `Escape` to close alert

---

## Hardware requirements (example)
- ESP32 Dev Board
- DHT11 or DHT22 (temperature & humidity)
- LDR (photoresistor) + fixed resistor (voltage divider) for light
- MQ-2 or MQ-135 (gas / smoke)
- Breadboard, jumper wires, 3.3V power (or regulated 5V depending on sensors)

**Example wiring (ESP32):**

| Sensor        | ESP32 pin | Notes                          |
|---------------|-----------|--------------------------------|
| DHT11/DHT22   | GPIO 4    | Data pin → requires DHT library|
| LDR (voltage divider) | GPIO 34 (ADC) | Analog read (use proper divider) |
| MQ gas sensor | GPIO 35 (ADC) | Analog read; may need load resistor |
| VCC           | 3.3V (or 5V per sensor spec) | Match sensor voltage |
| GND           | GND       | Common ground                  |

> ⚠️ Check your sensor datasheets for exact voltage/current needs.

---

## Required Arduino libraries
Install via **Arduino IDE → Tools → Manage Libraries** (or PlatformIO equivalent):
- `DHT sensor library` — Adafruit
- `Adafruit Unified Sensor`
- (Optional) `ArduinoJson` — for JSON output if used

---

## Serial output format (expected by the dashboard)
Either CSV-style key:value pairs (one line per reading):

```
TEMP:25.4,HUMIDITY:60.2,LIGHT:450,GAS:18
```

or JSON:

```json
{"temp":25.4,"humidity":60.2,"light":450,"gas":18}
```

The dashboard parses either format. Ensure numeric values are present for temperature, humidity, light, and gas.

---

## How to upload firmware (ESP32)
1. Open `sensor_V_01_bluetooth_2.0.ino` in Arduino IDE (or PlatformIO).  
2. Select **Tools → Board → ESP32 Dev Module**.  
3. Select correct **Port/COM**.  
4. Set baud rate to **115200** in code and in Serial Monitor.  
5. Upload the sketch.  
6. Open Serial Monitor (115200) — you should see periodic lines like the examples above.

---

## How to run the dashboard (index_test.html)
1. Use **Google Chrome** or **Microsoft Edge** (Web Serial API required).  
2. Open `index_test.html` in the browser (double-click or serve via local web server).  
3. Click **"Connect to ESP32"** in the serial-controls panel. Choose the COM port.  
4. When connected, the dashboard will display live readings and update charts.

> If the browser doesn't support Web Serial API, you will see simulated data only.

---

## Fire detection thresholds (defaults)
A fire alert will trigger if **any** of these conditions is met:

- **Temperature** > **40°C**  
- **Humidity** < **30%**  
- **Light** > **700 Lux**  
- **Gas** > **50 ppm**

When triggered:
- Node 3 becomes red (`fire-alert` state).
- Fire alert modal appears with location "Node 3".
- Charts will show spiked values for visualization.

These thresholds can be adjusted in `index_test.html` (search for `TEMP_THRESHOLD`, `HUMIDITY_THRESHOLD`, `LIGHT_THRESHOLD`, `GAS_THRESHOLD`).

---

## Troubleshooting
- **No serial port visible**: Make sure the ESP32 is connected and drivers are installed. Use Chrome/Edge with the Web Serial API enabled.
- **Serial parsing errors**: Ensure each line ends with `\n` and matches the CSV or JSON formats above.
- **Sensors read strange values**: Check wiring and ADC ranges. MQ sensors may require calibration and a heater warm-up period.
- **Charts not updating**: Verify `updateCharts()` interval and that `useSerialData` is `true` when connected.

---

## Development & customization tips
- To integrate multiple nodes: duplicate the firmware for each ESP32 and modify the dashboard to accept node identifiers (or use MQTT/HTTP backend).
- Add GPS coordinates to the serial output to place nodes on a real map.
- For production, consider a backend (MQTT, Firebase, InfluxDB + Grafana) and alerts via SMS/email.
- Improve gas sensor reliability by calibrating baselines in firmware.

---

## Example Serial Session (sample lines)
```
# CSV style
TEMP:22.5,HUMIDITY:57.3,LIGHT:390,GAS:12
TEMP:22.6,HUMIDITY:57.1,LIGHT:395,GAS:11.8

# JSON style
{"temp":22.5,"humidity":57.3,"light":390,"gas":12}
{"temp":22.6,"humidity":57.1,"light":395,"gas":11.8}
```

---

## License
Include your preferred license here (e.g., MIT). Example:

```
MIT License
Copyright (c) 2025 [Your Name]
```

---

## Contact / Credits
- Project: Fire Guardian  
- Dashboard designed in `index_test.html`.  
- Firmware file: `sensor_V_01_bluetooth_2.0.ino`.  
- Inspired by open-source sensor and visualization projects.

---

### Quick copy checklist
- [ ] Save this content into `README.md`
- [ ] Verify `sensor_V_01_bluetooth_2.0.ino` serial output matches the sample format
- [ ] Install required Arduino libraries
- [ ] Wire sensors to ESP32 as shown
- [ ] Open `index_test.html` in Chrome/Edge and connect
