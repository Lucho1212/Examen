#include "Arduino_reducida.h"  // archivo Base de datos 
#include <EEPROM.h>// libreria de la EEPROM
#include <TimerOne.h>  // libreria del TIMER

String texto= ""; // palabra original
String str; // variable para obtener  dato
float data; // dato tipo float
float dato; // variable para imprimir el valor de la EEPROM
int f=0; // variable
int c=0; // variable
int i=0; // variable
int j=40; // variable
int k=0; // variable
int l=0; // variable
float vector[5]; // matriz donde se almacena el valor ingresado
int on=0; // controla las etapas del sistema
float result; // resultado obtenido desde el KNN
int a=0; // variables 
int b=0; // variables
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Timer1.initialize(1000000); // inicializa el tiempo del timer
Timer1.attachInterrupt(escritura); // Como se llama el metodo del timer
attachInterrupt(0,iniciar,LOW); // interrupcion 2 
attachInterrupt(1,leer,LOW); // interrupcion 3
Serial.println("Ingrese el primer dato");
for(f=0;f<8;f++)
{
  for(c=0;c<5;c++)
  {
    a++;
 EEPROM.put(a,reducida[f][c]); //Guardar los datos de la tabla reducida e la EEPROM
    }
}
}

void loop() {
    if(Serial.available()>0) // obtiene la cantidad de bytes mayor a 0
      {
str = Serial.readStringUntil('\n'); // obtine el dato
data = str.toFloat(); // lo transforma a tipo float
      }
    }
void leer() // la interrupcion dos
{
  b=1; // variable inicializamos en uno para ver lo guardado en la memoria EEPROM
  }

void iniciar () // la interrupcion uno
{
    on++; // cada que llamemos a la interrupcion se sumara esta variable
   switch(on){  
  case 1:    // si es igual a 1 
  vector[on-1]=data;    // en el vector , en la posicion 0 se guardara el valor ingresado
  Serial.println("");
  Serial.print("EL valor es:");
  Serial.println(data);
  Serial.print("Ingrese el segundo valor");
   str="";
   data=0;
  break;
   case 2:
  vector[on-1]=data; // en el vector , en la posicion 1 se guardara el valor ingresado
    Serial.println("");
  Serial.print("EL valor es:");
  Serial.println(data);
  Serial.print("Ingrese el tercer valor");
  str="";
  data=0;
  break;
  case 3:
  vector[on-1]=data; // en el vector , en la posicion 2 se guardara el valor ingresado
  str="";
  
  Serial.println("");
  Serial.print("EL valor es:");
  Serial.println(data);
  Serial.print("Ingrese el cuarto valor");
    str="";
  data=0;
  break;
   case 4:
  vector[on-1]=data; // en el vector , en la posicion 3 se guardara el valor ingresado
  str="";
    Serial.println("");
  Serial.print("EL valor es:");
  Serial.println(data);
  Serial.print("Ingrese la etiqueta valor");
    str="";
  data=0;
  break;
     case 5:
  vector[on-1]=data; // en el vector , en la posicion 4 se guardara el valor ingresado
  str="";
    Serial.println("");
  Serial.print("La etiqueta es :");
  Serial.println(data);
    str="";
  data=0;
  break;
  case 6: // aqui indicara el vector final ingresado 
    Serial.println("El vector es");
  Serial.println("");
 for(;i<5;i++)
 {
  Serial.print(vector[i]); // imprime el vector concatenado que ingresamos
  Serial.print(" , ");
  }
  break;
    case 7:
         result=knn(8,5,3,3,vector); // llamamos al metodo knn y ver el resultado obtenido
         if(result==vector[4]) // compara el resultado con la etiqueta del vector ingresado
         {
Serial.println("Correcto"); // si es correcto
         }
         else
         {
Serial.println("Incorrecto"); // si es incorrecto
l=1; // si es incorrecto la variable se inicializa en 1
          }
  }
 }
 void escritura() // este es el timer 
  { 
    
 if(l==1) // como la variable es uno 
    {
    if(k<=5)
    {
      k++;
EEPROM.put(40+k,vector[k-1]); // Empoeza almacenar el vector ingresado en la EEPROM
    }
  if(k==5)
  {
  Serial.println ("Guardado en EEPROM"); // al esparar que se almacene en la EEPROM advierte un mensaje q a sido gaurdado en la EEPROM
  k=0;
  l=0;
  }
 }
 if(b==1)
 {
  j++;
EEPROM.get(j,dato);  // obtiene el valor del dato guardado en la EEPROM
Serial.println(dato); // Imprime ese valor obtenido desde la EEPROM 
  }
  }

  
  float knn (int fila2,int col2, int k, int label, float datos[]) // regresa un flotante
{
 int c=0;
 int f=0;
 float k_vecinos_dist[k];//valor que permite q el vector sea flexible vector de almacenamiento k distancias menores 
 float etiquetas [2][label];
 float dist=0; // variable que almacena cada distancia 
 float dist_total=0;
 int k_cont=0;  
 int i=0;
 float clase ;
 float comparacion;
  // llenar el vetor k_vecinos_dist con valores altos
 float eti_menor[k];
  for(;c<k;c++)
  {
    k_vecinos_dist[c]=2000.0+c ;   // valores altos y ordenados 
    }
    c=0;
    //llenar natriz etiquetas
    for(;c<label;c++)
    {
      etiquetas[0][c]=c+1; // lleno con valores de etiquetas
      etiquetas[1][c]=0;
      }
      c=0;

      // distancia muevo punto hacia la matriz
      for(;f<fila2;f++)
      {
        for(;c<col2-1;c++)
        {
         dist=dist+pow((reducida[f][c]- datos[c]),2); // distancia entre dos punts 
         }
          dist_total=sqrt(dist); // raiz de la formula
         // Serial.println(dist_total);

          for(;k_cont<k;k_cont++)   // asta el numero de vecinos que ingresamos
          {
          if(dist_total<k_vecinos_dist[k_cont]) // comparamos si es valor es menor toma esa variable el valor
          {
          k_vecinos_dist[k_cont]=dist_total; // en esa posicion se almcena el numero valor
          eti_menor[k_cont]=reducida[f][col2-1]; 
        }

}
k_cont=0;
dist=0;
dist_total=0;
c=0;
  }

  for(;c<label;c++)
  {
    for(;k_cont<k;k_cont++) // recorro cada posicion de eti_menor y comparo con etiqutas y cuento si son identicas 
    {
      if(etiquetas[0][c]== eti_menor[k_cont]) 
      {
        i++;
        etiquetas [1][c]=i;
        }
      }
      k_cont=0;
      i=0;
    }
    c=1;
    comparacion = etiquetas[1][0];
    clase=etiquetas[0][0];
    for(;c<label;c++)
    {
      if(etiquetas [1][c]> comparacion)// comparaicon entre suma de eiquetas 
      {
        clase=etiquetas[0][c];
        comparacion =etiquetas [1][c];
        }
      }
    comparacion=0;
        c=0;      
    return clase;
 }






