# EspEepromManager

Simple utilities functions to manage ESP EEPROM class. It uses debounce concept to write into the EEPROM to prevent multple write cycles.


### Setup

### Installation

1.  Open  [platformio.ini](https://docs.platformio.org/en/latest/projectconf/index.html), a project configuration file located in the root of PlatformIO project.
2.  Add the following line to the  [lib_deps](https://docs.platformio.org/en/latest/projectconf/sections/env/options/library/lib_deps.html)  option of  `[env:]`  section:
    
    ```cpp
    lib_deps=
      siglibs/EspEepromManager@^1.0.0
    ```
    
3.  Build a project, PlatformIO will automatically install dependencies.

### Include it

1.  Add the following line to your source code:
    
    ```cpp
    #include <EspEepromManager.h>
    ```
    
2.  Check  [Examples](https://registry.platformio.org/libraries/siglibs/EspEepromManager/examples)  on how to use the  **EspEepromManager**  library.

### Command Line Interface

1.  Open  [PlatformIO Core CLI](https://docs.platformio.org/en/latest/core/index.html)
2.  Change directory (`cd`) to the PlatformIO project where  [platformio.ini](https://docs.platformio.org/en/latest/projectconf/index.html)  is located.
3.  Copy the following  [pio pkg install](https://docs.platformio.org/en/latest/core/userguide/pkg/cmd_install.html)  command and paste into the CLI shell, press  Enter:
    
    ```cpp
    pio pkg install --library "siglibs/EspEepromManager@^1.0.0"
    ```


### Usage

```cpp
#include <EspEepromManager.h>


EspEepromManager eepromManager;

void setup() {
    // your setup code here

    eepromManager.begin(256); // Initialize EEPROM with size 256 bytes
}

void loop() {
    // your loop code here

    eepromManager.checkAndCommit(); // Must keep this inside loop to check if there are pending writes to commit
}
```

### All Functions

```cpp
// Initialise the eeprom manager
EspEepromManager eepromManager;

// Setup
eepromManager.begin(128); // param: size
// or
eepromManager.begin(); // default rom size = 256

// Write single byte. 
// write(int address, byte value)
eepromManager.write(0, 42);

// Read single byte. 
// read(int address)
uint8_t value = eepromManager.read(0);

// Write String
// writeString(int address, char *str, size_t maxLen)
eepromManager.writeString(10, "Hello EEPROM", 20);

// Read String
// readString(int address, char *buffer, size_t bufSize)
char buf[20];
eepromManager.readString(10, buf, sizeof(buf));

// Write struct/complex data
// put(int address, T &data)
struct MyData {
    int id;
    float value;
};
MyData data = {123, 45.67f};
eepromManager.put(50, data);

// Read struct/complex data
// get(int address, T &data)
MyData readData;
eepromManager.get(50, readData);

// Reset whole EEPROM
eepromManager.reset();

// Must called inside loop().
// Check pending commit and commit them
eepromManager.checkAndCommit();

// commit instantly
eepromManager.forceCommit();
```


---

#### Design & Developed by

> Alauddin Ansari

