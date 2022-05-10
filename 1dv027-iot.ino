// import dependencies
#include <Arduino_MKRIoTCarrier.h>

// Instantiate the carrier-object
MKRIoTCarrier carrier;

float temperature = 0;
float humidity = 0;

void displayTemperature() {
  // Set colors (comes from the Adafruit-ST7735-Library)
  carrier.display.fillScreen(ST77XX_GREEN);
  carrier.display.setTextColor(ST77XX_BLACK);
  
  // Size, position and print text
  carrier.display.setTextSize(6);
  carrier.display.setCursor(30, 70);
  carrier.display.print("Temp: ");
  carrier.display.setTextSize(4);
  carrier.display.setCursor(40, 120);
  carrier.display.print(temperature);
  carrier.display.print(" C");
}

void displayHumidity() {
  // Set colors (comes from the Adafruit-ST7735-Library)
  carrier.display.fillScreen(ST77XX_CYAN); 
  carrier.display.setTextColor(ST77XX_BLUE); 

  // Size, position and print text
  carrier.display.setTextSize(6); 
  carrier.display.setCursor(20, 70);
  carrier.display.println("Humid: ");
  carrier.display.setTextSize(4);
    carrier.display.setCursor(30, 120);
  carrier.display.print(humidity);
  carrier.display.println(" %");
}

void handleTouch() {
  // Read latest state of touch pads
  carrier.Buttons.update();

  // Determine what to display on the carrier's screen
  if (carrier.Buttons.onTouchDown(TOUCH0)) {
    displayTemperature();
  } else if (carrier.Buttons.onTouchDown(TOUCH1)) {
    displayHumidity();
  }
}

void setup() {
  // put your setup code here, to run once:
  
  // Open Serial monitor to wathc details and errors.
  Serial.begin(9600); 
 
  // TODO: Set to true when using the enclosing case!
  CARRIER_CASE = false;

  carrier.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  // Update sensor reading values
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
 
  // Print to serial port
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
 
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  handleTouch();

  // Pause for one second
  delay(1000);  
}
