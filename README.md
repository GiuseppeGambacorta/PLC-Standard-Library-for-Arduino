<a name="readme-top"></a>

<div align="center">

  <h1>PLC Standard Library for Arduino</h1>

  <p>
    IEC 61131-3-inspired blocks and I/O helpers for Arduino-compatible boards,
    STM32 Opta, Arduino Uno, ESP32, and native host testing.
  </p>

  <p>
    <a href="https://github.com/GiuseppeGambacorta/PLC-Standard-Library-for-Arduino/blob/main/LICENSE">
      <img src="https://img.shields.io/github/license/GiuseppeGambacorta/PLC-Standard-Library-for-Arduino.svg" alt="MIT License">
    </a>
  </p>
</div>

## About the project

This library provides PLC-style building blocks for Arduino projects. It
includes edge triggers, timers, digital I/O wrappers, analog input filtering,
and analog output scaling.

The library is header-only. Include it in an Arduino sketch with:

```cpp
#include <plc.h>
```

## Features

- `R_trig` rising-edge trigger.
- `F_trig` falling-edge trigger.
- `TON` on-delay timer.
- `TOF` off-delay timer.
- `DigitalInput` with `NormalyOpen` and `NormalyClosed` configuration.
- `DigitalOutput` with `on()`, `off()`, and `isActive()`.
- `AnalogInput` with raw reads, range scaling, callable access, and a moving-average filter.
- `AnalogOutput` with raw writes, range scaling, clamping, and callable access.
- Native PlatformIO tests for the platform-independent logic.

## Requirements

- [PlatformIO Core](https://docs.platformio.org/en/latest/core/index.html)
- Arduino framework for board examples.
- A supported board: STM32 Opta, Arduino Uno, or ESP32.

## Repository layout

```text
src/plc.h                         Library API
examples/                         Arduino IDE .ino examples
platformio/                        PlatformIO board projects
tests/UnitTests                    PlatformIO Unity test project
```

## Examples and API overview

All examples use the same environments:

| Environment | Board | Example-specific notes |
|---|---|---|
| `opta` | Arduino Opta | User button, Opta indicator/output pins |
| `uno` | Arduino Uno | Button on D2 and PWM output on D9 where applicable |
| `esp32` | ESP32 DevKit | Button on GPIO0 and analog output on GPIO25 where applicable |

### 1. Fundamental function blocks

The four fundamental PLC function blocks are available in the standard
method-based form:

```cpp
R_trig risingTrigger;
F_trig fallingTrigger;
TON onDelay;
TOF offDelay;

risingTrigger.update(input);
fallingTrigger.update(input);
onDelay.update(input, 1000);
offDelay.update(input, 1000);

if (risingTrigger.isActive()) {
    // Rising edge detected.
}

if (fallingTrigger.isActive()) {
    // Falling edge detected.
}

if (onDelay.isActive()) {
    // Input has been high for the preset time.
}

if (offDelay.isActive()) {
    // Output remains active during the off-delay.
}
```

The same four blocks also support callable syntax:

```cpp
risingTrigger(input);
fallingTrigger(input);
onDelay(input, 1000);
offDelay(input, 1000);

if (risingTrigger()) {
    // Rising edge detected.
}

if (onDelay()) {
    // TON output is active.
}
```

`examples/FundamentalBlocks/FundamentalBlocks.ino` demonstrates these blocks
using direct Arduino functions. The `TON` turns on one LED after the button
has been held for one second. The `TOF` keeps another LED on for one second
after the button is released.

### 2. Digital input and output

`DigitalInput` supports `NormalyOpen` and `NormalyClosed` inputs. The default
configuration is `NormalyOpen`.

```cpp
DigitalInput button(BUTTON_PIN, NormalyClosed);
DigitalOutput led(LED_PIN);

const bool active = button.isActive();
if (active) {
    led.on();
} else {
    led.off();
}
```

Digital I/O also supports callable syntax:

```cpp
if (button()) {
    led.on();
}

if (led()) {
    // Output is active.
}
```

`examples/DigitalIO/DigitalIO.ino` demonstrates digital input and output
wrappers using the traditional method-based API.

### 3. Analog input and output

`AnalogInput` supports raw reads, range scaling, and an optional moving-average
filter. `AnalogOutput` supports raw writes, range scaling, and clamping.

```cpp
AnalogInput sensor(A0, 0.0f, 100.0f, 1023, 5);
AnalogOutput actuator(9, 0.0f, 100.0f);

const int rawValue = sensor.readRaw();
const float processedValue = sensor.readProcessedValue();
const float filteredValue = sensor.readFilteredValue();

actuator.writeProcessedValue(filteredValue);
```

Analog I/O also supports callable syntax:

```cpp
const float value = sensor();
actuator(value);
```

`examples/AnalogIO/AnalogIO.ino` demonstrates raw analog reads, processed
values, moving averages, and analog output scaling.

### Callable API

Callable syntax is available for every supported input, output, trigger, and
timer object. The method-based API remains available as well, so both styles
can be used depending on project preference.

`examples/CallableAPI/CallableAPI.ino` demonstrates the callable form.

`AnalogInput` requires the ADC maximum to be configured explicitly. Use `1023`
for a 10-bit ADC and `4095` for a 12-bit ADC. `AnalogOutput` uses a default
PWM range of `0..255`; its range can also be overridden explicitly.

## PlatformIO commands

Run these commands from the selected project directory.

### Build PlatformIO examples

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\platformio\StandardLibraryExample
pio run
pio run -e opta
pio run -e uno
pio run -e esp32
```

Build the other examples by changing the directory:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\platformio\WithInputsAndOutputs
pio run -e uno

cd C:\Users\gamba\CLionProjects\untitled1\platformio\CallableExample
pio run -e uno

cd C:\Users\gamba\CLionProjects\untitled1\platformio\AnalogExample
pio run -e uno
```

### Upload examples

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\platformio\StandardLibraryExample
pio run -e opta --target upload
pio run -e uno --target upload
pio run -e esp32 --target upload
```

For another example, run the same command after changing to its directory.
Specify a port when more than one device is connected:

```powershell
pio run -e uno --target upload --upload-port COM3
```

### Read serial output

The examples use `115200` baud:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\platformio\StandardLibraryExample
pio device monitor -e uno --baud 115200
```

Specify the serial port explicitly when required:

```powershell
pio device monitor -p COM3 -b 115200
```

Close the monitor with `Ctrl+C`.

## Testing

The test project is located in `tests\UnitTests`.

### Native host tests

Native tests run without hardware and are the fastest way to validate the
library:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\tests\UnitTests
pio test -e native
```

Run only one test suite:

```powershell
pio test -e native -f test_trig
pio test -e native -f test_analog
```

Enable verbose output:

```powershell
pio test -e native -vvv
```

### Hardware tests

Hardware tests compile, upload, and execute Unity tests on the connected board:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\tests\UnitTests
pio test -e opta
pio test -e uno
pio test -e esp32
```

Provide upload and test ports explicitly:

```powershell
pio test -e opta --upload-port COM3 --test-port COM3
pio test -e uno --upload-port COM4 --test-port COM4
```

Run every configured environment:

```powershell
pio test
```

## Installation as a dependency

Add the repository to a project's `platformio.ini`:

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
lib_deps =
    https://github.com/GiuseppeGambacorta/PLC-Standard-Library-for-Arduino.git
```

Then include the library:

```cpp
#include <plc.h>
```

## Start the Linter on windows
```
.\arduinoLinter.ps1 | Out-Host
```
## Contributing

1. Fork the repository.
2. Create a feature branch.
3. Implement and test the change.
4. Run `pio test -e native`.
5. Open a pull request with a clear description.

## License

Distributed under the MIT License. See `LICENSE` for details.

## Contact

Giuseppe Gambacorta — [project repository](https://github.com/GiuseppeGambacorta/PLC-Standard-Library-for-Arduino)

<p align="right">(<a href="#readme-top">back to top</a>)</p>
