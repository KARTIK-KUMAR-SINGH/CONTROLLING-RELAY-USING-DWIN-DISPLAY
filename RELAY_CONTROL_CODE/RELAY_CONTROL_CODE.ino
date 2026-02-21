unsigned char Buffer[8];   // was 9 → now 8 (frame length)

#define Relay1 6
#define Relay2 7
#define Relay3 8
#define Relay4 9

void setup() {
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT); digitalWrite(Relay1, HIGH);
  pinMode(Relay2, OUTPUT); digitalWrite(Relay2, HIGH);
  pinMode(Relay3, OUTPUT); digitalWrite(Relay3, HIGH);
  pinMode(Relay4, OUTPUT); digitalWrite(Relay4, HIGH);
}

void loop()
{
  if (Serial.available())
  {
    for (int i = 0; i < 8; i++)   // was <=8 (9 bytes) → now 8 bytes
    {
      Buffer[i] = Serial.read();
    }

    // was 0x5A → now A9 CB F9 header
    if (Buffer[0] == 0xA9 && Buffer[1] == 0xCB && Buffer[2] == 0xF9)
    {
      switch (Buffer[3])   // was Buffer[4]
      {
        case 0x55:   // Relay 1
          if (Buffer[6] == 0xFD)   // was Buffer[8] == 1
          {
            digitalWrite(Relay1, LOW);
            Serial.println("Relay1 ON");
          }
          else
          {
            digitalWrite(Relay1, HIGH);
            Serial.println("Relay1 OFF");
          }
          break;

        case 0xAA:   // Relay 2
          if (Buffer[6] == 0xFD)
          {
            digitalWrite(Relay2, LOW);
            Serial.println("Relay2 ON");
          }
          else
          {
            digitalWrite(Relay2, HIGH);
            Serial.println("Relay2 OFF");
          }
          break;

        case 0x54:   // Relay 3
          if (Buffer[6] == 0xFD)
          {
            digitalWrite(Relay3, LOW);
            Serial.println("Relay3 ON");
          }
          else
          {
            digitalWrite(Relay3, HIGH);
            Serial.println("Relay3 OFF");
          }
          break;

        case 0xEA:   // Relay 4
          if (Buffer[6] == 0xFD)
          {
            digitalWrite(Relay4, LOW);
            Serial.println("Relay4 ON");
          }
          else
          {
            digitalWrite(Relay4, HIGH);
            Serial.println("Relay4 OFF");
          }
          break;

        default:
          Serial.println("No data..");
      }
    }
  }
  delay(10);
}