# Untitled1

Libreria Arduino compatibile con Arduino IDE e PlatformIO.

## Installazione con Arduino IDE

1. Scarica il repository come ZIP.
2. Nell'Arduino IDE seleziona **Sketch > Include Library > Add .ZIP Library...**.
3. Seleziona l'archivio scaricato.

Quando la libreria sarà pubblicata nell'Arduino Library Manager, potrà essere
installata direttamente cercando `Untitled1`.

## Utilizzo

```cpp
#include <Untitled1.h>

Untitled1 library;

void setup() {
    library.begin();
}

void loop() {
    library.update();
}
```

## Esempio PlatformIO

Il progetto PlatformIO di esempio è in `examples/BasicUsage`. Per compilarlo:

```text
cd examples/BasicUsage
pio run
```

## Struttura

```text
src/                         Codice della libreria
examples/BasicUsage/         Progetto PlatformIO di esempio
library.properties           Metadati Arduino Library Manager
library.json                 Metadati PlatformIO
```

## Licenza

MIT
