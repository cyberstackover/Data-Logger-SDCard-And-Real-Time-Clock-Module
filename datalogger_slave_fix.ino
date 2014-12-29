/*
 SD card datalogger	
 created  29 Des 2014
 by Herwin 
 */

#include <SD.h>
#include <Wire.h>
#include <DS1307new.h>

const int chipSelect = 4;
uint16_t TimeIsSet = 0xaa55;

void setup()
{
  Serial.begin(9600);
   //TimeIsSet = 0xffff;  //dicomment biar waktu seting awal tidak kembali kedefault
  if (TimeIsSet != 0xaa55)
  { 
    RTC.fillByYMD(2014,12,29); //tanggal setingan
    RTC.fillByHMS(20,59,00); // jam setingan
    RTC.setTime(); // mengembalikan ke setingan default
    RTC.startClock();  //memulai waktu untuk berjalan
  }
  else
  {
    RTC.getTime();
  }
  RTC.ctrl = 0x00;                                                      
  RTC.setCTRL();
  
   while (!Serial) {
    ; 
  }
  Serial.print("inisialisasi SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card gagal ditampilkan");
    return;
  }
  Serial.println("");
  Serial.println("card terinisialisasi bro!");
}
void loop()
{
  String dataString = "";
   RTC.getTime();
  delay(1000);    
 dataString += "[Tanggal]"; 
 dataString += String (RTC.day, DEC); dataString += "-"; 
 dataString += String (RTC.month, DEC); dataString += "-"; 
 dataString += String (RTC.year, DEC); dataString += " [Jam]"; 
 dataString += String (RTC.hour, DEC); dataString += ":"; 
 dataString += String (RTC.minute, DEC); dataString += ":"; 
 dataString += String (RTC.second, DEC);
 
  File dataFile = SD.open("time.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }  
  else {
    Serial.println("gagal membuka time.txt");
  } 
}
