int readval, writeval;

void setup() {
pinMode(A0,INPUT);// put your setup code here, to run once:
Serial.begin(9600);
pinMode(10,OUTPUT);
pinMode(9,INPUT);
}

void loop() {
  if(digitalRead(9)==1){
readval=analogRead(A0);
Serial.println(readval);
while(Serial.available()==0);
writeval=Serial.parseInt();
analogWrite(10,writeval);
}
else if(digitalRead(9)==0)digitalWrite(10,LOW);
}
