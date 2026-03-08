Power Supply]

5V → ESP8266/Arduino VCC

GND → ESP8266/Arduino GND



\[Water Sensor Probes]

Probe1 → 5V

Probe2 → Voltage Divider → Analog Pin A0

Voltage Divider → GND



\[Microcontroller Pins]

A0 → Sensor Output

PIN 4 → Buzzer Control (via NPN transistor)

PIN 5 \& 2→ LED (via 220Ω resistor)



\[Buzzer Circuit]

PIN 4→  → To positive of buzzer

Buzzer GND to microcontroller GND 









\[LED Circuit]

PIN 5 \& 2  → 220Ω resistor → LED Anode

LED Cathode → GND



