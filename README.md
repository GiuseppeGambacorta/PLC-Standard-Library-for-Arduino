# Comandi

## Upload degli esempi

Gli esempi disponibili sono:

- `StandardLibraryExample`: utilizzo diretto delle API Arduino e della libreria PLC.
- `WithInputsAndOutputs`: utilizzo dei wrapper `DigitalInput` e `DigitalOutput`.

Opta:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\examples\StandardLibraryExample
pio run --target upload
```

Arduino Uno:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\examples\StandardLibraryExample
pio run -e uno --target upload
```

ESP32:

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\examples\StandardLibraryExample
pio run -e esp32 --target upload
```

Per provare l'esempio con `DigitalInput` e `DigitalOutput`, usare la stessa
configurazione entrando nella directory `WithInputsAndOutputs`.

## Monitor seriale

```powershell
cd C:\Users\gamba\CLionProjects\untitled1\examples\StandardLibraryExample
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

Test su Arduino Uno:

```powershell
pio test -e uno
```

Test su ESP32:

```powershell
pio test -e esp32
```

Per eseguire i test su tutti gli ambienti configurati:

```powershell
pio test
```
