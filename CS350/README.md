# CS-350: Emerging Systems Architectures and Technologies

Raspberry Pi embedded-systems coursework: interface software that drives real hardware on a solderless breadboard (LEDs, buttons, a 16x2 LCD, an AHT20 temperature/humidity sensor, and UART serial). Work is organized by module, building from a single GPIO blink up to a multi-device thermostat prototype.

## Featured Artifacts

These two projects best represent the skills this course is meant to demonstrate: writing interface software for hardware, reasoning about architecture choices (GPIO vs. PWM, I2C vs. UART, polling vs. events vs. threads), and assembling those pieces into a system that could support a real product requirement such as remote HVAC monitoring.

### 1. Embedded Thermostat — `Module-7/Thermostat.py`

Capstone prototype of a three-mode thermostat (`off` / `heat` / `cool`).

- **Hardware:** PWM LEDs on GPIO 18 (heat) and GPIO 23 (cool), three buttons (mode, setpoint up, setpoint down), 16x2 character LCD, AHT20 sensor on I2C, UART (`/dev/ttyS0` at 115200 baud).
- **Behavior:** State machine cycles operating mode. In heat or cool, the matching LED pulses while the room is away from the setpoint and stays solid once the target is reached. The LCD shows date/time on line 1 and alternates current temperature with mode + setpoint on line 2. Every 30 seconds the Pi sends a comma-delimited status line (`state,tempF,setpoint`) to a monitoring host. `ThermostatServer-Simulator.py` is the matching serial listener.
- **Why it matters:** This is the full stack from circuit to protocol. It is the piece I would walk an employer through to show that I can connect sensors and actuators, keep UI and control loops concurrent, and expose device state to another system.

### 2. Button-Driven LED State Machine — `Module-5/LightStateMachine.py`

Event-driven GPIO with PWM and an explicit state model.

- **Hardware:** PWM red LED on GPIO 18, PWM blue LED on GPIO 23, green button on GPIO 24.
- **Behavior:** The machine starts in `off`. The first button press fires `begin` and moves to `red`, which fades the red LED in and out with `PWMLED.pulse()`. Later presses fire `cycle` and alternate `red` ↔ `blue`. Enter/exit hooks turn the outgoing LED fully off before the incoming one starts pulsing, so the two colors never overlap. The main loop only sleeps; all real work is the `Button.when_pressed` callback.
- **Why it matters:** This is the cleanest complete example of treating hardware as a software architecture instead of a pile of `if` flags. PWM vs. digital on/off is a real performance/appearance choice, and event callbacks vs. polling the pin in a tight loop is a real responsiveness choice. The thermostat later reuses this same pattern (`off` / `heat` / `cool` instead of `off` / `red` / `blue`).

Supporting work in this repo (GPIO bring-up, PWM fade, UART LED client/server, LCD tests, Morse-code milestone, I2C temperature display) is listed under [Repository layout](#repository-layout).

## Reflection

### Summarize the project and what problem it was solving.

The course problem was to take a Raspberry Pi from a bare GPIO pin to a working embedded controller: software that talks to physical devices, not just other programs. Early modules solved “can I light an LED, dim it with PWM, and drive it from a serial command?” Later modules added a human interface (LCD, buttons) and a real sensor, then combined those into a thermostat that both *acts* (heat/cool indicators and setpoints) and *reports* (UART telemetry to a simulated server). That last piece is the business problem in miniature: a low-cost device that can sense the environment, present status locally, accept user input, and publish state to a larger system.

### What did you do particularly well?

I treated the breadboard as something that had to be brought up incrementally, the same way I would a new board at work. Module 1–2 prove digital GPIO and PWM on one pin. Module 3 proves UART before any extra peripherals. Module 4 proves the LCD in isolation. Module 5 proves buttons and `gpiozero` PWM LEDs, then wraps them in a state machine. Module 6 proves I2C and the AHT20. Module 7 only then composes those proven pieces. That sequence made hardware bugs (wrong BCM pin, floating button, serial port name) obvious because only one new interface was in play at a time. I also got into the habit of catching `KeyboardInterrupt`, calling `GPIO.cleanup()` or `gpiozero` teardown, and de-initing LCD lines so a crashed script did not leave pins or the display in a bad state for the next run.

### Where could you improve?

Shared helpers such as `ManagedDisplay` were copied into several files instead of living in one module; that is easy to maintain in a lab and painful the moment a pin map or LCD size changes. GPIO numbers are documented in comments but still magic numbers in code. The serial payload is a simple comma-separated string with no version field or checksum, which is fine for a lab listener and fragile on a noisy line. This tree also still has unfinished `TODO` sections in later templates (`Milestone3.py`, `Thermostat.py`) because the finished copies lived on the Pi that was wired to the breadboard. If I were packaging this as production firmware, I would extract a hardware-abstraction layer, define pin maps in one place, and add a small protocol (even JSON lines) for the thermostat server.

### What tools and/or resources are you adding to your support network?

- **gpiozero** for buttons and PWM LEDs (event callbacks and `pulse()` instead of hand-rolled duty-cycle loops).
- **RPi.GPIO** for the low-level digital/PWM work in the first milestones — useful when I need to see exactly what the pin is doing.
- **Adafruit CircuitPython** (`board`, `digitalio`, `adafruit_character_lcd`, `adafruit_ahtx0`) for I2C sensors and character LCDs.
- **pyserial** for UART client/server work, including the `/dev/ttyS0` vs `/dev/ttyUSB0` distinction between the Pi UART and a USB–TTL cable.
- **python-statemachine** for explicit `off`/`red`/`blue` and `off`/`heat`/`cool` models instead of ad-hoc flags.
- Raspberry Pi BCM pin maps, the AHT20 datasheet, and the course lab circuits as the hardware reference I will keep next to this repo.

### What skills from this project will be particularly transferable to other projects and/or course work?

Event-driven I/O, state machines, and resource cleanup transfer directly to any system with sensors, actuators, or a UI that cannot freeze. PWM vs. digital output is the same tradeoff as analog-ish control vs. bang-bang control in other domains. I2C vs. UART is a concrete lesson in choosing a bus: I2C for on-board sensors with addresses, UART for a simple point-to-point link to another computer. Threading the display/sensor loop while buttons fire callbacks is the same concurrency pattern as “don’t block the event loop.” Debugging a circuit (continuity, pin numbering, pull-ups, baud rate) is a skill I will use any time software and hardware meet. The larger habit — prove each interface alone, then compose — is how I will approach future embedded, IoT, and even purely software integrations.

### How did you make this project maintainable, readable, and adaptable?

Each script has a header that states the circuit it expects, the GPIO lines it uses, and a short change history. Comments explain *why* BCM numbering is used (it matches the breakout board, not the header silkscreen). A `DEBUG` flag gates console tracing so lab runs are noisy and a demo can be quiet. Hardware concerns are grouped into classes (`ManagedDisplay`, `TemperatureMachine`, `TempMachine`, `LightMachine`) with enter/exit hooks, so a new mode is a new state plus a transition rather than another nested `if`. Serial roles are split into client and server files with the port, baud, parity, and timeout written next to the `Serial()` call, so moving from a USB–TTL cable to the on-board UART is a one-line change. Cleanup is centralized: LCD `deinit()`, GPIO cleanup, and thread-stop flags (`endDisplay`, `endTransmission`) so shutdown is orderly. Pin assignments are consistent across modules (red LED 18, blue LED 23, green button 24), which made the later circuits an extension of the earlier ones instead of a rewrite.

## Repository layout

| Path | What it covers |
| --- | --- |
| `Module-1/` | GPIO 18 on/off and blink (`RPi.GPIO`) |
| `Module-2/Milestone1.py` | PWM fade in/out on GPIO 18 |
| `Module-3/` | UART test plus serial LED client/server (Milestone 2) |
| `Module-4/` | 16x2 LCD bring-up |
| `Module-5/` | Buttons, second LED, `LightStateMachine.py`, Morse-code milestone |
| `Module-6/` | AHT20 I2C test and temperature/humidity LCD with C/F toggle |
| `Module-7/` | Multi-button test, thermostat, serial thermostat server simulator |
| `Resources/` | Course state-machine example |

## Hardware notes

Typical pin map used across the later modules (BCM numbering):

| Function | GPIO |
| --- | --- |
| Red LED (PWM) | 18 |
| Blue LED (PWM) | 23 |
| Green button (mode / toggle) | 24 |
| Red button (setpoint up) | 25 |
| Blue button (setpoint down) | 12 |
| LCD RS / EN / D4–D7 | 17, 27, 5, 6, 13, 26 |
| AHT20 | I2C (`board.I2C()`) |
| Thermostat UART | `/dev/ttyS0`, 115200 8N1 |
| USB–TTL serial | `/dev/ttyUSB0`, 115200 8N1 |

These scripts expect a Raspberry Pi with the matching breadboard circuit. They will not run usefully on a desktop without GPIO, I2C, and the Adafruit / gpiozero stack.

## Course alignment

This repository is a portfolio submission for CS-350. The featured artifacts show:

- **Interface software for hardware** — GPIO, PWM, buttons, LCD, I2C sensor, UART.
- **Hardware architecture vs. application performance** — PWM dimming vs. digital on/off, button callbacks vs. polling a pin in a tight loop, a display thread so the thermostat UI stays responsive, I2C for the on-board sensor and UART for off-board telemetry.
- **Architecture choices against a requirement** — a Raspberry Pi as a low-cost thermostat controller that can present status locally and publish a compact status string to a monitoring service, which is the same pattern used in many small IoT and facilities-monitoring products.
