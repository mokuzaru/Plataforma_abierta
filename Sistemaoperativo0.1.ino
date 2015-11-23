int p1 = 9; //input primer motor
int p2 = 4;// input primer motor
int p3 = 5; // input segundo motor
int p4 = 6; // input segundo motor
int E1 = 7; // enable1
int E2 = 8; // enable2
int estado = 'x'; //estado inicial

int pecho = 2;  
int ptrig = 3;
int duracion, distancia;

void parar(void){

  digitalWrite (E1, LOW);
  digitalWrite (E2, LOW);
  
}

void back_off(void){
  digitalWrite(E1,HIGH);
  digitalWrite(p1,LOW);
  digitalWrite(p2, HIGH);
  digitalWrite(E2,HIGH);
  digitalWrite(p3,LOW);
  digitalWrite (p4,HIGH);
}

void left(void){
  digitalWrite(E1,HIGH);
  digitalWrite(p1,LOW);
  digitalWrite(p2, HIGH);
  digitalWrite(E2,HIGH);
  digitalWrite(p3,HIGH);
  digitalWrite (p4,LOW);
}

void right(void){
  digitalWrite(E1,HIGH);
  digitalWrite(p1,HIGH);
  digitalWrite(p2, LOW);
  digitalWrite(E2,HIGH);
  digitalWrite(p3,LOW);
  digitalWrite (p4,HIGH);
}

void forward(void){
  digitalWrite(E1,HIGH);
  digitalWrite(p1,HIGH);
  digitalWrite(p2, LOW);
  digitalWrite(E2,HIGH);
  digitalWrite(p3,HIGH);
  digitalWrite (p4,LOW);
}


void sensar(void){

  digitalWrite(12, HIGH);
  
  digitalWrite(ptrig, HIGH);
  delay(0.01);
  digitalWrite(ptrig,LOW);
  
  duracion = pulseIn(pecho, HIGH);
  distancia = (duracion/2)/29;
  delay(10);
  
  if(distancia <= 20 && distancia >= 2){
   digitalWrite(13, HIGH);
  
   parar();
   delay(200);
  
   right();
   delay(500);
  
   forward();
   delay(1100);
  
   digitalWrite(13, LOW); 
   digitalWrite(12, LOW);
    
  }else
  left();
}

void setup() {
  Serial.begin (9600);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(ptrig, OUTPUT);
  pinMode(pecho, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);

}

void loop() {
  
  if(Serial.available()>0){
    estado = Serial.read();
    if (estado != -1){
     switch(estado) {
       case 'a':
         forward();
         break;
       case 'b':
         back_off();
         break;
       case 'l':
          left();
          break;
       case 'r':
           right();
           break;
       case 's':
           Serial.println ("holi soy autonomo");
           sensar();
           break;
       case 'x':
           parar();
           break;
     }
    }else
    parar();
    }
}

