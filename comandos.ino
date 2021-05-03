void steer(int steer){
  if(!armed){
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(enb, 0);
    return;
  }
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
  if(!armed){
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(ena, 0);
    return;
  }
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
