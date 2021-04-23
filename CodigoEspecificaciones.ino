/*
  *primero se elige si quiere comprobar el funcionamiento de las leds ingresando v
  *Ingresando I, se procedara a ingresar el patron a mostrar en la matriz de leds
  *El patron se ingresera fila por fila hasta completar las 8 filas de la matriz de leds 
   Siendo los 1 los leds que quiere encender y 0 los leds que quiere apagados(Para un correcto funcionamiento limitese a ingresar 1 y 0).
  *Solo se podra ingresar un patron a la vez, si se quiere otro se debe reiniciar la simulacion.

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
char digito='0',seleccion='0'; //variables de control digito recibe el patron a ingresar y seleccion recibe del menu lo que se quiere realizar.
unsigned short int potencia=7, columna=0,pinData  = 2,pinLatch = 3, pinClock = 4;// Se inicializa la variable potencia que es la que ayuda a convertir el patron binario recibido a decimal, columna es la posicion del arreglo patron
int patron[8];// arreglo que contendra el patron a mostrar, en cada posicion del arreglo se guarda el decimal equivalente al binario ingresado, el cual corresponde a una fila de la matriz de leds
bool ciclo = true;// auxiliar que permite mostrar constantemente el patron ingresado
void setup() {
  Serial.begin(9600);
  pinMode(pinData, OUTPUT);
  pinMode(pinLatch, OUTPUT);
  pinMode(pinClock, OUTPUT);
  Serial.println("Desea verificar los leds?introduzca v");
  Serial.println("Desea introducir un patron? indtroduzca i");
  for(int i=0;i<8;i++) // se inicializa el arreglo patron a 0 para no tener valores aleatorios en el arreglo y evitar calculos erroneos
      {
        patron[i]=0;
      }
}
void imagen()
{
  if(Serial.available()>0)// Se asegura que unicamente cuando reciba informacion por el puerto serial haga alguna operacion.
	{
         Lectura(patron);
    }
  if(columna==8) // Cuando se llega a la posicion 8 del arreglo patron, se pasa a mostrar el el patron.
  {
    ledWrite(patron);
  }
}
void verificacion()
{
  for(int i=7;i>-1;i--)// un ciclo para enceder todas las leds con el valor estatico 255 que significa 11111111 o todas las leds encendidas.
   {   
      shiftOut(pinData, pinClock, LSBFIRST, 255);
   }
      digitalWrite(pinLatch, HIGH);
      digitalWrite(pinLatch, LOW);
}
void Lectura(int incomingByte[8]) {
    while(Serial.available() > 0)// mientras reciba datos
    {
      digito=Serial.read();//Se guarda el dato ingresado por el serial en esta variable para su posterior evaluacion.
      if(digito=='1')
          {
            incomingByte[columna]+=(pow(2,potencia)+0.5);// si se ingresa un numero 1 hacer la potencia de dos con la posicion del digito evaluado para ir convirtiendo el numero binario ingresado. 
          	potencia--;
          }
      else if(digito=='0')// Se asegura que solamente sean datos validos 0 o 1 haciendo que la posicion de la potencia unicamente disminuya si hay un 1 o 0
      {
        potencia--;
      }
      if(potencia==-1){// Solo cuando se halla evaludo todas las potencia de 7 a 0
        Serial.println(incomingByte[columna]);//Se imprime la conversion del decimal
        potencia=7;//Se vuelve a incializar la potencia en 7 para la siguiente fila
        columna++;// Se aumenta  a la siguiente posicion del arregla que contendra la siguiente fila de la matriz de leds 
      }
    }
}
void ledWrite(int matriz[8]){// Recibe el patron
   for(int i=7;i>-1;i--)
   {   
      shiftOut(pinData, pinClock, LSBFIRST, matriz[i]);//Muestra cada fila del patron empezando en 7 por la posicion de los leds que estan invertidos
   }
      digitalWrite(pinLatch, HIGH);
      digitalWrite(pinLatch, LOW);
}

void loop()
{
  seleccion=Serial.read();// recibe el dato a evaluar del menu
  if(seleccion=='i')
  {
    Serial.println("Introduzca el patron:");
    while(ciclo==true)imagen();// este ciclo hace que siempre corra la funcion imagen para mostrar el patron
  }
  if(seleccion=='v')verificacion();//llama a la funcion verificacion para encender los leds
}