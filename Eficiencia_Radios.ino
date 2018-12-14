#include "datos_entrenamiento.h"
#include "test.h"
#include "reducida.h"

int on=0;
float result;
float result2;
int i=0;
int j=0;
int a=0;
int b=0;
int total=0;
int etiqueta=0;
float matriz_p [3][5];// datos validos 
float matriz_n [120];// datos validos 
float matriz_np [3];// datos validos 
float matriz_val1[8][5];
int col=0;// varibale de recorrido de columna
int fil=0; // variable recorrido de filas
float promedio; // variable de promedio 
float sumatoria;
float sumatoria2;
float dist_total;
float dist_mayor=0;
int cont=0;
float vector[4]={5.1,3.5,1.4,0.2};

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
knn2(0.22,0.24);
resultado();
}

void loop() {
  
}

float knn2 (float rangomin, float rangomax) // funcion necesita ingrear valor en tipo flotantes
{
  for(;etiqueta<4;etiqueta++){ // como son 3 tipos de etiquetas asta menor de 4
  for(;col<4;col++){ // columnas son 4 por lo que menores de 4 porque empieza desde cero
  for(fil=i;fil<40*etiqueta;fil++) // recorre las filas
  {
  sumatoria=sumatoria + matriz[fil][col]; // suma toda fila que va recorriendo
  }
  promedio=sumatoria/40; // la suma total divide para 40 y saca el promedio
  matriz_p[etiqueta-1][col]=promedio; // se guarda en la matriz promedio el promedio de cada una de las columnas de los tipos de flor 
  fil=0;  // inicializamos de nuevo a cero
  sumatoria=0; // inicializamos de nuevo a cero
  
}
col=0; // inicializamos de nuevo a cero
i=40*etiqueta; // apara q el valor de i tome un nuevo valor
  }
fil=0; // inicializamos de nuevo a cero
col=0; // inicializamos de nuevo a cero
etiqueta=0; // inicializamos de nuevo a cero
i=0; // inicializamos de nuevo a cero

  for(;etiqueta<4;etiqueta++){  
  for(fil=i;fil<40*etiqueta;fil++){
  for(;col<4;col++){
  sumatoria2=sumatoria2 + pow((matriz[fil][col]- matriz_p[etiqueta-1][col]),2); //sacar las distancias de cada columna con su promedio
   }
  dist_total=sqrt(sumatoria2); // sacar raiz cuadrada de la sumatoria
    matriz_n[fil]=dist_total; // guardar ese valor en la matriz normalizada
    if(dist_total>dist_mayor) // vamos a encontrar el valor mayor de la normalizada 
  {
    dist_mayor=dist_total;
    matriz_np[etiqueta-1]=dist_mayor; // guardamos el valor mayor en la normalizada 
    }
  col=0; // inicializamos de nuevo a cero
  dist_total=0; // inicializamos de nuevo a cero
  sumatoria2=0; // inicializamos de nuevo a cero
  
}
dist_mayor=0; // inicializamos de nuevo a cero
fil=0; // inicializamos de nuevo a cero
i=40*etiqueta; // multiplicamos para cambiar valor de i
  }
  col=0;
  fil=0;
  etiqueta=0;
  sumatoria=0;
  for(;etiqueta<4;etiqueta++){
  for(fil=i;fil<40*etiqueta;fil++) // recorre la fila
  {
  sumatoria=matriz_n[fil] / matriz_np[etiqueta-1]; // divide la la matriz normalizada con la matriz del valor maximo de la normalizada dejando todo en funcion de 0 a 1
 //Serial.print(sumatoria);
   if((sumatoria <= rangomax)& (sumatoria >= rangomin)) // ese valor si entra en el rango se almacena en la nueva matriz
   {
    matriz_val1[j][0]=matriz[fil][0]; // se almacena los datos en la nueva matriz que cumplen el rango
   matriz_val1[j][1]=matriz[fil][1]; // se almacena los datos en la nueva matriz que cumplen el rango
   matriz_val1[j][2]=matriz[fil][2]; // se almacena los datos en la nueva matriz que cumplen el rango
   matriz_val1[j][3]=matriz[fil][3]; // se almacena los datos en la nueva matriz que cumplen el rango
   matriz_val1[j][4]=matriz[fil][4]; // se almacena los datos en la nueva matriz que cumplen el rango
    j++; // conocer cuantos datos sera nuestra tabla reducida
    }
   sumatoria=0;
  }
  i=40*etiqueta;
  }
   col=0;
fil=0;
for(;fil<8;fil++)
  {
    for(;col<5;col++)
    {
Serial.print(matriz_val1[fil][col]); // imprimir nuestra tabla reducida
Serial.print(",");
  }
Serial.println("");  
  col=0;
  }
  Serial.print("Numero de datos : ----> ");
  Serial.println(j); // imprimier el numero de datos de la tabla reducida
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

int resultado()
{
 for(int i=0;i<=29;i++)
 {
            result=knn(8,5,3,3,test[i]); // resultado del knn
             Serial.print("Dato : ");
             Serial.println(i+1);
               if(result==test[i][4]){  // si ese resultado es igual al valor de el test en la columna 5 que seleccione correcto
                a++;
                Serial.println("Correcto -> ");}
                else
                {
                b++;
                Serial.println("Incorrecto ->");
                  }              
Serial.print("Aciertos: ");
Serial.println(a); // numero de aciertos
Serial.print("Fallas: ");
Serial.println(b); // numero de fallas
Serial.println("");
}
Serial.println("Porcentage Aciertos: ");
Serial.print((a*100)/30); // porcentaje de eficeincia
Serial.println(" %");
  }
