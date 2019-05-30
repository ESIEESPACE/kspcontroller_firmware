#define ANALOG_THRESHOLD 102

int lastval[NUM_DIGITAL_PINS];
bool enable[NUM_DIGITAL_PINS];
String command[NUM_DIGITAL_PINS];

void setup() {
    Serial.begin(9600);

    //Commands declaration
    addCommand(7, "STG");
    addCommand(6, "SAS");
    addCommand(5, "RCS");
    addCommand(4, "ABT");

    addCommand(A0, "THT");
    addCommand(A1, "ROL");
}


void loop() {
    checkcommands();
    delay(10);
}

void addCommand(int pin, String commandName) {
    enable[pin] = true;
    command[pin] = commandName;
    if(pin < A0) {
        pinMode(pin, INPUT_PULLUP);
    }
}

void checkcommands() {
    for(int pin = 0; pin < NUM_DIGITAL_PINS; pin++) {
        if(enable[pin]) {
            //Detect if pin is an analog input
            if(pin < A0) digitalCheck(pin);
            else analogCheck(pin);
        }
    }
}

void digitalCheck(int pin){
    int value = digitalRead(pin);

    //State change detection
    if(value != lastval[pin]) Serial.print(command[pin] + ";" + String(lastval[pin]) + "\n");

    lastval[pin] = value;
}

void analogCheck(int pin){
    int value = analogRead(pin);

    //Less than 30, it is considered as 0
    if(value < 30) value = 0;

    //threshold detection
    if(!(lastval[pin] - ANALOG_THRESHOLD < value && value < lastval[pin] + ANALOG_THRESHOLD)) {
        Serial.print(command[pin] + ";");
        Serial.print((double)value/(double)1023, 7);
        Serial.print("\n");
        lastval[pin] = value;
    }
}