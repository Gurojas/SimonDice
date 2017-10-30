int pinBotonRojo = 2;
int pinLedRojo = 3;

int pinBotonVerde = 4;
int pinLedVerde = 5;

int pinBotonAmarillo = 6;
int pinLedAmarillo = 7;

int numLeds = 3;
int numPulsos = 3;

int secuencia[] = {0,0,0,0,0,0,0,0,0,0};
int secuenciaPulsos[] = {0,0,0,0,0,0,0,0,0,0};

int numAciertos = 0;

// contador global
int i = -1;

int rojo = 0;
int verde = 1;
int amarillo = 2;

/*
 - 0 -> led rojo
 - 1 -> led verde
 - 2 -> led amarillo
*/


void setup() {
  // put your setup code here, to run once:

   // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  
  pinMode(pinBotonRojo,INPUT);
  pinMode(pinLedRojo,OUTPUT);

  pinMode(pinBotonVerde,INPUT);
  pinMode(pinLedVerde,OUTPUT);

  pinMode(pinBotonAmarillo,INPUT);
  pinMode(pinLedAmarillo,OUTPUT);

  Serial.begin(9600);

 
  
}

void loop() {
  // put your main code here, to run repeatedly:

  
  if (i == -1){
    llenarSecuencia();
    encenderSecuencia();
    i++;
  }
  

  int botonRojo = digitalRead(pinBotonRojo);
  if (botonRojo == HIGH){
    secuenciaPulsos[i] = rojo;
    i++;
    digitalWrite(pinLedRojo,HIGH);
    delay(500);
    digitalWrite(pinLedRojo,LOW);
    delay(500); 
  }

  int botonVerde = digitalRead(pinBotonVerde);
  if (botonVerde == HIGH){
      secuenciaPulsos[i] = verde;
      i++;
      digitalWrite(pinLedVerde,HIGH);
      delay(500);
      digitalWrite(pinLedVerde,LOW);
      delay(500);
  }

  int botonAmarillo = digitalRead(pinBotonAmarillo);
  if (botonAmarillo == HIGH){
      secuenciaPulsos[i] = amarillo;
      i++;
      digitalWrite(pinLedAmarillo,HIGH);
      delay(500);
      digitalWrite(pinLedAmarillo,LOW);
      delay(500);
  }

  if (i == numPulsos){
    boolean correcto = esSecuenciaCorrecta();
    if (correcto){
      numAciertos++;
      secuenciaCorrecta(500);
      aumentarNivel(); 
    }
    else{
        secuenciaIncorrecta(500);
        numAciertos = 0;
        numPulsos = 3;      
    }
    i = -1;
    reiniciarSecuencia();
    Serial.print("pulsos: ");
    Serial.println(numPulsos);
    delay(500);  
  }

}

void aumentarNivel(){
  if (numAciertos % 3 == 0){
    numPulsos++;  
  }
}

void reiniciarSecuencia(){
    for (int i = 0; i < 10; i++){
      secuenciaPulsos[i] = 0;  
      secuencia[i] = 0;
    }
}

void secuenciaCorrecta(int tiempo){

  digitalWrite(pinLedRojo,HIGH);
  digitalWrite(pinLedVerde,HIGH);
  digitalWrite(pinLedAmarillo,HIGH);
  delay(tiempo);
  digitalWrite(pinLedRojo,LOW);
  digitalWrite(pinLedVerde,LOW);
  digitalWrite(pinLedAmarillo,LOW);
  delay(tiempo);
  digitalWrite(pinLedRojo,HIGH);
  digitalWrite(pinLedVerde,HIGH);
  digitalWrite(pinLedAmarillo,HIGH);
  delay(tiempo);
  digitalWrite(pinLedRojo,LOW);
  digitalWrite(pinLedVerde,LOW);
  digitalWrite(pinLedAmarillo,LOW);
    
}

void secuenciaIncorrecta(int tiempo){
  
  digitalWrite(pinLedRojo,HIGH);
  digitalWrite(pinLedVerde,HIGH);
  digitalWrite(pinLedAmarillo,HIGH);
  delay(tiempo);
  digitalWrite(pinLedRojo,LOW);
  digitalWrite(pinLedVerde,LOW);
  digitalWrite(pinLedAmarillo,LOW);

}

boolean esSecuenciaCorrecta(){
    for (int i = 0; i < numPulsos; i++){
      if (secuencia[i] != secuenciaPulsos[i]){
         return false;
      }  
    }
    return true;
}


void encenderSecuencia(){
  for (int i = 0; i < numPulsos; i++){
    if (secuencia[i] == rojo){
      digitalWrite(pinLedRojo,HIGH);
      delay(500);
      digitalWrite(pinLedRojo,LOW);
      delay(500); 
    }
    else if (secuencia[i] == verde){
      digitalWrite(pinLedVerde,HIGH);
      delay(500);
      digitalWrite(pinLedVerde,LOW);
      delay(500);
    }
    else if (secuencia[i] == amarillo){
      digitalWrite(pinLedAmarillo,HIGH);
      delay(500);
      digitalWrite(pinLedAmarillo,LOW);
      delay(500);
    }
  }  
}

void llenarSecuencia(){
  for (int i = 0; i < numPulsos; i++){
    secuencia[i] = random(0,numLeds); 
  }  
}