/*
  *primero se elige si quiere comprobar el funcionamiento de las leds ingresando v
  *Ingresando I, se procedara a ingresar el patron a mostrar en la matriz de leds
  * El patron se ingresera fila por fila hasta completar las 8 filas de la matriz de leds 
   Siendo los 1 los leds encendidos y 0 los leds apagados.
  *Solo se podra ingresar un patron a la vez.

Ejemplo matriz apagada:
	00000000 
    00000000
    00000000
    00000000
    00000000
    00000000
    00000000
    00000000
Ejemplo patron 1:
	11111111
	11111111
	11111111
	00011110
	00111100 -> Mostrara una Z en los leds
	01111000
	11111111
	11111111
Ejemplo patron 2:
	11111111
	11100111
	11100111
	11111111-> Mostrara una A en los leds
	11111111
	11100111
	11000011
	10000001
*/
char digito='0',digito1='0';
unsigned short int cont=7,colo=0,columna=0,pinData  = 2,pinLatch = 3, pinClock = 4;
int aux[8];
bool ciclo = true;
void setup() {
  Serial.begin(9600);
  pinMode(pinData, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClock, OUTPUT);
  Serial.println("Desea verificar los leds?introduzca v");
  Serial.println("Desea introducir un patron? indtroduzca i");
  for(int i=0;i<8;i++)
      {
        aux[i]=0;
      }
}
void imagen()
{
  if(Serial.available()>0)
	{
       for(int i=0;i<8;i++)
       {
         colo=Lectura(aux);
       }
    }
  if(colo==8)
  {
    ledWrite(aux);
  }
}
void verificacion()
{
  for(int i=7;i>-1;i--)
   {   
      shiftOut(pinData, pinClock, LSBFIRST, 255);
   }
      digitalWrite(pinLatch, HIGH);
      digitalWrite(pinLatch, LOW);
}
int Lectura(int incomingByte[8]) {
    while(Serial.available() > 0)
    {
      digito=Serial.read();
      if(digito=='1')
          {
            incomingByte[columna]+=(pow(2,cont)+0.5);
          cont--;
          }
      else if(digito=='0')
      {
        cont--;
      }
      if(cont==-1){
        Serial.println(incomingByte[columna]);
        cont=7;
        columna++;
      }
    }
  return columna;
}
void ledWrite(int matriz[8]){
   for(int i=7;i>-1;i--)
   {   
      shiftOut(pinData, pinClock, LSBFIRST, matriz[i]);
   }
      digitalWrite(pinLatch, HIGH);
      digitalWrite(pinLatch, LOW);
}

void loop()
{
  digito1=Serial.read();
  if(digito1=='i')
  {
    Serial.println("Introduzca el patron:");
    while(ciclo==true)imagen();
  }
  if(digito1=='v')verificacion();
}