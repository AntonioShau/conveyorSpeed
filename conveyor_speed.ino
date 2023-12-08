/*
El ejemplo calcula la velocidad de un engrane (podría ser cualquier piñon o incluso alguna rueda)
para el calculo se necesita conocer la circunferencia: diam * π aunque medir con una cinta flexible 
dara mejor resultado. Dependiendo la pieza a tomar la medicion (engrane o rueda) se debe tomar en 
cuenta el numero de dientes para ajustar las rpm. Tambien será necesario conocer la distancia exacta
para tomar la medición, por ejemplo 5m. Por ultimo se necesita conocer el tiempo entre cada "click"
Para este caso se usó un boton de pulso simulando un "limit-switch" asi como una resistencia de 10K.
El algoritmo es el siguiente:

Obtenemos primero el tiempo con la funcion getTime(), esto retorna el tiempo en milisegundos
La condicional es para imprimir en el monitor serial los calculos
La velocidad se obtiene con: distancia entre tiempo, esto retorna la velocidad en cm/s
El tiempo en segundos se obtiene con: distancia / velocidad
*/
const int buttonPin = 8;

int buttonState = 0;
int pressState = 0;

float ms = 0;
float fullDist = 500;
float dist = 15.708; //Resultado de 50cm * PI / n(dientes)
float vel;

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  getTime();
  if (buttonState == HIGH && pressState == 0){
    vel = (dist / (ms/1000));
    Serial.println("Segundos: " + String(ms / 1000));
    Serial.print("cm/s: ");
    Serial.println(vel);
    Serial.print("Tiempo en segundos: ");
    Serial.println(fullDist / vel);
    ms = 0;
    pressState = 1;
  }else if (buttonState == LOW){
    pressState = 0;
  }
}

void getTime(){
  ms += 10;
  delay(10);
}
