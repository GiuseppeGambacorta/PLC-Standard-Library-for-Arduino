# Comandi

## Upload dell'esempio TrigExample

Opta:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\examples\TrigExample
pio run --target upload
```

Arduino Uno:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\examples\TrigExample
pio run -e uno --target upload
```

ESP32:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\examples\TrigExample
pio run -e esp32 --target upload
```

## Monitor seriale

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\examples\TrigExample
pio device monitor --baud 115200
```

## Test

Test su Opta:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\tests\UnitTests
pio test -e opta
```

Il comando compila, carica ed esegue i test sulla scheda collegata. Per
specificare manualmente la porta seriale:

```powershell
pio test -e opta --upload-port COM3 --test-port COM3
```

Test host:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\tests\UnitTests
pio test -e native
```
