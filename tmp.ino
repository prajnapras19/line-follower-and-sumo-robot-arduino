void setup(){
    pinMode(3,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
}

void loop(){
    analogWrite(3,HIGH);
    analogWrite(5,HIGH);
    analogWrite(6,HIGH);
    analogWrite(9,HIGH);
    analogWrite(10,HIGH);
    analogWrite(11,HIGH);
    
    delay(2000);
    
    analogWrite(3,LOW);
    analogWrite(5,LOW);
    analogWrite(6,LOW);
    analogWrite(9,LOW);
    analogWrite(10,LOW);
    analogWrite(11,LOW);
    
    delay(2000);
}
