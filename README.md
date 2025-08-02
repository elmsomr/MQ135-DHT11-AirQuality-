# Arduino Air Quality Monitor using MQ135 and DHT11

This project uses an **MQ-135 gas sensor** and a **DHT11 temperature/humidity sensor** with an **Arduino Nano** to monitor indoor air quality. It calculates the approximate gas concentration in **PPM (parts per million)** and estimates the type of gas based on predefined thresholds. The measured data is printed to the **serial monitor**.

---

##  Hardware Connections

| Component    | Arduino Nano Pin |
|--------------|------------------|
| MQ135 AOUT   | A0               |
| DHT11 DATA   | D3               |
| VCC (Both)   | 5V               |
| GND (Both)   | GND              |

---

##  Dependencies

- [dhrubasaha08/DHT11 Library](https://github.com/dhrubasaha08/DHT11)

---

##  Features

- Calibration of MQ-135 sensor in clean air
- Real-time gas concentration measurement (PPM)
- Basic gas type estimation (CO2, NH3, smoke, alcohol, etc.)
- Temperature and humidity display from DHT11

---

##  Example Output

```
Calibrated Ro value: 9500
Temp: 24°C | Humidity: 41% | Gas (PPM): 78.52 | Gas Type: Smoke / Alcohol / Benzene / NOx
```

---

##  How It Works

- The MQ135 sensor outputs an analog value related to air pollutants.
- This value is converted to a resistance ratio (Rs/Ro), which is then used to estimate gas concentration using a logarithmic formula.
- DHT11 adds ambient temperature and humidity, useful for more accurate calibration.
- Based on the PPM value, a rough gas type is suggested.

---

##  File Structure

```
MQ135_DHT11_AirQuality/
├── mq135_dht11_air_quality.ino
└── README.md
```

---

##  License

MIT License
