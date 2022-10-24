#include "IQS5xx.h"

IQS5xx trackpad; // Creat an IQS5xx instance for the trackpad.

void setup() {

	uint8_t ui8DataBuffer[15];  // defaut size : 6

	Serial.begin(115200);

	trackpad.begin(0x74, 2);

	trackpad.AcknowledgeReset();

	trackpad.CheckVersion(ui8DataBuffer);

	Serial.print("Product "); Serial.print( (ui8DataBuffer[0]<<8) + ui8DataBuffer[1] );
	Serial.print(" Project "); Serial.print( (ui8DataBuffer[2]<<8) + ui8DataBuffer[3]);
	Serial.print(" Version "); Serial.print( ui8DataBuffer[4]);Serial.print(".");Serial.println( ui8DataBuffer[4]);

}

void loop() {

	if(digitalRead(trackpad._readyPin) == HIGH) {

		uint16_t ui8DataBuffer2[20];

		uint8_t nbrsFingers = trackpad.Process_XY(ui8DataBuffer2);

		if(nbrsFingers) {
			Serial.print("nbrs fingers: "); Serial.print( nbrsFingers );

			for(uint8_t i=0; i < nbrsFingers; i++) {
				Serial.print(" |  x");Serial.print(1+i); Serial.print(": "); Serial.print( ui8DataBuffer2[0+i*4] );
				Serial.print(" |  y");Serial.print(1+i); Serial.print(": "); Serial.print( ui8DataBuffer2[1+i*4] );
				Serial.print(" strenght: "); Serial.print( ui8DataBuffer2[2+i*4] );
				Serial.print(" area: "); Serial.print( ui8DataBuffer2[3+i*4] );
			}
			Serial.println("");
		}
	}
}