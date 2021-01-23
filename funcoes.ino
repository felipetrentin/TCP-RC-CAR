void receiveData() {
   
   //Serial.println(cl.available());
   if (cl.available() < nob) {
     // error
     return;
   }
   //Serial.println("got data");
   for (byte n = 0; n < nob; n++) {
      pcData[n] = cl.read();
   }
   for (byte n = 0; n < nob; n++) {
     inputData.pcLine[n] = pcData[n];
   }
   newData = true;
}

void setall(){
  if (newData == false) {
     return;
  }
  Serial.print("<steering: ");
  Serial.print(inputData.moveData.steering);
  Serial.print("speed: ");
  Serial.print(inputData.moveData.motorspeed);
  Serial.println('>');
  steer(inputData.moveData.steering);
  drive(inputData.moveData.motorspeed);
  newData = false;
}

void steer(int steer){
  if(steer < 0){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enb, (steer * -1));
  }else if(steer > 0){
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enb, steer);
  }else{
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enb, 0);
  }
}
void drive(int spd){
  if(spd < 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(ena, (spd * -1));
  }else if(spd > 0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(ena, spd);
  }else{
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(ena, 0);
  }
}
