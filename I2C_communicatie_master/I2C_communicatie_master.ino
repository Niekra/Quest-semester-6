#include <Wire.h>
#include <SoftwareSerial.h>


#define ARDUINO_TANSMIT_PIN 6  //should connect to RX of the Serial MP3 Player module
#define ARDUINO_RECEIVE_PIN 7  //connect to TX of the module

SoftwareSerial mp3(ARDUINO_RECEIVE_PIN, ARDUINO_TANSMIT_PIN);
//#define mp3 Serial3    // Connect the MP3 Serial Player to the Arduino MEGA Serial3 (14 TX3 -> RX, 15 RX3 -> TX)

static int8_t Send_buf[8] = {0}; // Buffer for Send commands.  // BETTER LOCALLY
static uint8_t ansbuf[10] = {0}; // Buffer for the answers.    // BETTER LOCALLY

String mp3Answer;           // Answer from the MP3.

/************ Command byte **************************/
#define CMD_NEXT_SONG     0X01  // Play next song.
#define CMD_PREV_SONG     0X02  // Play previous song.
#define CMD_PLAY_W_INDEX  0X03
#define CMD_VOLUME_UP     0X04
#define CMD_VOLUME_DOWN   0X05
#define CMD_SET_VOLUME    0X06

#define CMD_SNG_CYCL_PLAY 0X08  // Single Cycle Play.
#define CMD_SEL_DEV       0X09
#define CMD_SLEEP_MODE    0X0A
#define CMD_WAKE_UP       0X0B
#define CMD_RESET         0X0C
#define CMD_PLAY          0X0D
#define CMD_PAUSE         0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F

#define CMD_STOP_PLAY     0X16
#define CMD_FOLDER_CYCLE  0X17
#define CMD_SHUFFLE_PLAY  0x18 //
#define CMD_SET_SNGL_CYCL 0X19 // Set single cycle.

#define CMD_SET_DAC 0X1A
#define DAC_ON  0X00
#define DAC_OFF 0X01

#define CMD_PLAY_W_VOL    0X22
#define CMD_PLAYING_N     0x4C
#define CMD_QUERY_STATUS      0x42
#define CMD_QUERY_VOLUME      0x43
#define CMD_QUERY_FLDR_TRACKS 0x4e
#define CMD_QUERY_TOT_TRACKS  0x48
#define CMD_QUERY_FLDR_COUNT  0x4f

/************ Opitons **************************/
#define DEV_TF            0X02


void setup(){
  Serial.begin(9600);
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.println("master");

  mp3.begin(9600);
  delay(500);

  sendCommand(CMD_SEL_DEV, DEV_TF);
  delay(500);

  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);
  sendCommand(CMD_VOLUME_DOWN, 0);



  
  
}


void stand(byte stand){
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("S");        // sends one bytes
  Wire.write(stand); // sends one byte

  Wire.endTransmission();    // stop transmitting
  Serial.print("transmitted");
  return;
}

void intensiteit(byte intensiteit){
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("I");        // sends one bytes
  Wire.write(intensiteit); // sends one byte

  Wire.endTransmission();    // stop transmitting
}


void loop(){
  char c = ' ';

  // If there a char on Serial call sendMP3Command to sendCommand
  if ( Serial.available() )
  {
    c = Serial.read();
    sendMP3Command(c);
  }

  // Check for the answer.
  if (mp3.available())
  {
    Serial.println(decodeMP3Answer());
  }
  delay(100);

//  ledstrip(1);
//  delay(3000);
//  ledstrip(2);
//  delay(3000);
//  ledstrip(3);
//  delay(3000);
}


