/*
 * comunication protocol:
 * [command 1 byte] [arg (n)] ...
 * response
 * [response 1 byte]
 * 
 * list of commands:
 * 0 - check connection(keep alive if watchdog)
 * 1 - enable motors
 * 2 - disable motors
 * 3 - drive and steer [int drive, int speed]
 * 
 * list of responses:
 * 0 - sucess
 * 1 - does not exist
 * 2 - forbidden
 * 3 - data error
 */

void receiveData() {
  if (cl.available() < 1) {
    //if has no data, return.
    return;
  }
  byte command = cl.read(); //get first byte
  switch (command){
    case 0:
      sendResponse(0);
      break;
    case 1:
      armed = true;
      sendResponse(0);
      break;
    case 2:
      armed = false;
      sendResponse(0);
      break;
    case 3:
      getmoves();
      if(armed){
        sendResponse(0);
      }else{
        sendResponse(2);
      }
      break;
    default:
      sendResponse(1);
  }
}

void getmoves() {
  if (cl.available() < nob) {
    sendResponse(3);
    return;
  }
  for (byte n = 0; n < nob; n++) {
    inputData.pcLine[n] = cl.read();
  }
  Serial.print("<steering: ");
  Serial.print(inputData.moveData.steering);
  Serial.print("speed: ");
  Serial.print(inputData.moveData.motorspeed);
  Serial.println('>');
  steer(inputData.moveData.steering * 1023);
  drive(inputData.moveData.motorspeed * 1023);
}

void sendResponse(byte response){
  cl.write(response);
}
