#include "IQS5xx.h"

IQS5xx trackpad; // Creat an IQS5xx instance for the trackpad.

void setup() {

  uint8_t ui8DataBuffer[15];  // defaut size : 6
  
  Serial.begin(115200);

  trackpad.begin(0x74, 2);

  trackpad.AcknowledgeReset();

  trackpad.CheckVersion(&ui8DataBuffer[0]);  

  Serial.print("Product "); Serial.print( (ui8DataBuffer[0]<<8) + ui8DataBuffer[1] ); 
  Serial.print(" Project "); Serial.print( (ui8DataBuffer[2]<<8) + ui8DataBuffer[3]);
  Serial.print(" Version "); Serial.print( ui8DataBuffer[4]);Serial.print(".");Serial.println( ui8DataBuffer[4]);

}
 
void loop() {

  if(digitalRead(trackpad._readyPin) == HIGH)
	{
    uint8_t gesture_type = 0x00;

    gesture_type = trackpad.getGesture();

    if(gesture_type) {
      
      switch (gesture_type) {
        case TAP_AND_HOLD   :   Serial.println("Tap & Hold"); 
                                break;
        case SWIPE_X_NEG    :   Serial.println("Swipe X-");
                                break;
        case SWIPE_X_POS    :   Serial.println("Swipe X+"); 
                                break;
        case SWIPE_Y_POS    :   Serial.println("Swipe Y+");
                                break;
        case SWIPE_Y_NEG    :   Serial.println("Swipe Y-");
                                break;
        case SINGLE_TAP     :   Serial.println("One finger tap");
                                break;
        case SCROLL+0x10    :   Serial.println("Horizontal scroll -");
                                break;
        case SCROLL+0x20    :   Serial.println("Horizontal scroll +");
                                break;
        case SCROLL+0x30    :   Serial.println("Vertical scroll -");
                                break;
        case SCROLL+0x40    :   Serial.println("Vertical scroll +");
                                break;
        case ZOOM+0x10      :   Serial.println("Zoom In");
                                break;
        case ZOOM+0x20      :   Serial.println("Zoom Out");
                                break;
        case TWO_FINGER_TAP+0x20  :   Serial.println("Two finger tap");
                                      break;                            
      }
    }
	}  
}