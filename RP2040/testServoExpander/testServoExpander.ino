#include <Adafruit_NeoPixel.h>
#define LEDPIN 16
#define SERVOPIN_IN 0
#define SERVOPIN_OUT1 1
#define SERVOPIN_OUT2 2

#define OFFSET_SERVO1 6
#define SCALE_SERVO1 1

#define OFFSET_SERVO2 0
#define SCALE_SERVO2 -1

#include <Servo.h>

Adafruit_NeoPixel rgbLed(1, LEDPIN, NEO_GRB + NEO_KHZ800);

Servo outputServo1;
Servo outputServo2;
unsigned long durationIn;
unsigned long durationOut1;
unsigned long durationOut2;
long angleIn;
float angleOut1;
float angleOut2;

char buffer[100];

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
    rgbLed.begin();

    outputServo1.attach(SERVOPIN_OUT1);
    outputServo2.attach(SERVOPIN_OUT2);
    pinMode(SERVOPIN_IN, INPUT);
} 

void loop() {
	//duration = pulseIn(pin, HIGH);
	
    rgbLed.setPixelColor(0, rgbLed.Color(0, 20, 0));
    rgbLed.show(); 
    durationIn = pulseIn(SERVOPIN_IN, HIGH);
    angleIn = map( durationIn, 1000, 2000, -90, 90 );
    angleOut1 = SCALE_SERVO1 * ( angleIn + OFFSET_SERVO1 );
    angleOut2 = SCALE_SERVO2 * ( angleIn + OFFSET_SERVO2 );


    durationOut1 = map( angleOut1, -90, 90, 1000, 2000 );
    durationOut2 = map( angleOut2, -90, 90, 1000, 2000 );

    outputServo1.writeMicroseconds( durationOut1 );
    outputServo2.writeMicroseconds( durationOut2 );
    /*
    sprintf( buffer, "Angle in: %f, angle 1 out: %f, angle 2 out: %f\n", angleIn, angleOut1, angleOut2  );
    Serial.println(buffer);
    sprintf( buffer, "Angle in: %u, angle 1 out: %u, angle 2 out: %u\n", durationIn, durationOut1, durationOut2  );
    Serial.println(buffer);   
    */ 
}