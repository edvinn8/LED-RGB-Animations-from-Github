// ***************************************************************************
// Request handlers
// ***************************************************************************

char* string2char(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
    return nullptr;
}


unsigned int hexToDec(String hexString) {
    unsigned int decValue = 0;
    int nextInt;
    for (unsigned int i = 0; i < hexString.length(); i++) {
        nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
        nextInt = constrain(nextInt, 0, 15);
        decValue = (decValue * 16) + nextInt;
      }
    return decValue;
}




void getArgsof(String message){

   // validate form, massage is in format [00:0000FA00:3D:31]
            if (!(message.length() == 19 && (message.startsWith("["))&&(message.endsWith("]")))){
                  Serial.println("[ERROR]: Form Validation failed!");
                  // gradually slow down animations, to allow message parsing
                  ws2812fx_speed += 100;
                  // notify the app that the last command wasn't applied and ask for a resend
                  SerialBT.write("X");
                  return;
            }
            Serial.println(message);
            
            String msg = message;
            // remove Frame
            msg = msg.substring(1,message.indexOf("]"));

                  ws2812fx_mode  =  hexToDec(msg.substring(0,2));

                  String wrgb = msg.substring(3,11);
                
                  main_color.white  = hexToDec(wrgb.substring(0,2));
                  main_color.red  = hexToDec(wrgb.substring(2,4));
                  main_color.green  = hexToDec(wrgb.substring(4,6));
                  main_color.blue = hexToDec(wrgb.substring(6));
                
                  brightness  = hexToDec(msg.substring(12,14)); 
                  ws2812fx_speed  = hexToDec(msg.substring(15)); 
                  
                  ws2812fx_speed = constrain(ws2812fx_speed, 1, 255);
                  main_color.white = constrain(main_color.white, 0, 255);
                  main_color.red   = constrain(main_color.red,   0, 255);
                  main_color.green = constrain(main_color.green, 0, 255);
                  main_color.blue  = constrain(main_color.blue,  0, 255);
            
              Serial.print("Mode: ");
              Serial.print(ws2812fx_mode);
              Serial.print(", Color: ");
              Serial.print(main_color.white);
              Serial.print(", ");
              Serial.print(main_color.red);
              Serial.print(", ");
              Serial.print(main_color.green);
              Serial.print(", ");
              Serial.print(main_color.blue);
              Serial.print(", Speed:");
              Serial.print(ws2812fx_speed);
              Serial.print(", Brightness:");
              Serial.println(brightness);

              mode = SET_MODE;
            }


uint16_t convertSpeed(uint8_t mcl_speed) {
  //long ws2812_speed = mcl_speed * 256;
  uint16_t ws2812_speed = 61760 * (exp(0.0002336 * mcl_speed) - exp(-0.03181 * mcl_speed));
  ws2812_speed = SPEED_MAX - ws2812_speed;
  if (ws2812_speed < SPEED_MIN) {
    ws2812_speed = SPEED_MIN;
  }
  if (ws2812_speed > SPEED_MAX) {
    ws2812_speed = SPEED_MAX;
  }
  return ws2812_speed;
}









 
