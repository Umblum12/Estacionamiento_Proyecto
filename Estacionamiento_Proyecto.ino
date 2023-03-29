//Inportar las librerias necesarias para que los sensores y/o actuadores funcionen
#include <Servo.h>
//Declaracion de variables para los pines de entrada y salida analogos y digitales
//Areglo de pines digitales para el display 7 segmentos ánodo común
const int pins[7] = { 2, 3, 4, 5, 6, 7, 8 };
const int Pinfoto1 = A0;
const int Pinfoto2 = A1;
int Pinservo1 = 9;
int Pinservo2 = 10;
//Declarar e igualar variables a un valor deseado
int fotoValor1 = 0; //Establecer valor 0 para que el fotorresistor1 inicie en este valor
int fotoValor2 = 0; //Establecer valor 0 para que el fotorresistor2 inicie en este valor
int NoCarrosEst;
//Esto es un objeto de clase servo para utilizar las acciones del servomotor conectado al pin especifico
Servo servomotor1;
Servo servomotor2;
//                 a  b  c  d  e  f  g
//Declarar un array o areglo de 6 espacios con los numeros para que se muestre en el display 7 segmentos ánodo común
const byte numbersDisplayAnode[6] = {
                          0b1000000,     //0
                          0b1111001,          //1
                          0b0100100,          //2
                          0b0110000,          //3
                          0b0011001,          //4
                          0b0010010};         //5
//Es una función en Arduino que se ejecuta una vez al inicio del programa
void setup() {
  pinMode(Pinfoto1, INPUT);
  pinMode(Pinfoto2, INPUT);
  servomotor1.attach(Pinservo1);
  servomotor2.attach(Pinservo2);
  Serial.begin(9600);
  for(int i = 0; i < 7; i++) {
    pinMode(pins[i], OUTPUT);  
  }
  //Establecer el numero 0 en el display 7 segmentos ánodo común
  lightSegments(0);
}
void loop() {
  //Escribir Valor de fotorresistor 1
  fotoValor1 = analogRead(Pinfoto1);
  //sentencia if para saber si esta un carro delante de la pluma
  if (fotoValor1 < 3 ) {
     NoCarrosEst += 1;
    //Escribir Numero de display 7 segmentos ánodo común
    lightSegments(NoCarrosEst);
    //Escribir Valor de grados de servo motor 1  
    servomotor1.write(0);
  }
  //sentencia if para saber si no esta un carro delante de la pluma
  if (fotoValor1 > 4 ) {
    //Escribir Numero de display 7 segmentos ánodo común
    lightSegments(NoCarrosEst);
    //Escribir Valor de grados de servo motor 1  
    servomotor1.write(80);
  }
    //Esperar
    delay(200);
}
//Método para asignar codigo dependiendo el numero del array
void lightSegments(int number) {
  byte numberBit = numbersDisplayAnode[number];
  for (int i = 0; i < 7; i++)  {
    int bit = bitRead(numberBit, i);
    digitalWrite(pins[i], bit);
  }
}