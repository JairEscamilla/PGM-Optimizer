// Incluyo las librerias
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Prototipos de las funciones
void desplegarDatos();
void menu();
void PedirArchivo(char[]);
void ValidarArchivo(char[], int*);
void obtenerDimensiones(char[], int*, int*);
void cargarArchivo(char[], int, int, int*[]);
void guardar(int**, int, int, char[]);
void negativo(int**, int, int);
void NuevoNombre(char[]);
void ecualizar(int**, int, int);
void obtenerEcuacion(int**, int, int , float*, float*);
void reducir(int**, int*, int*, int**);
void ampliar(int**, int*, int*, int**);
void liberarMemoria(int**, int, int);
// Funcion principal
int main(){
  desplegarDatos();
  menu();
  return 0;
}
// Desarrollo de las funciones
void desplegarDatos(){
  system("clear");
  printf("Desarrollador: Allan Jair Escamilla Hernández\nPresione una tecla para continuar...");
  getchar();
  system("clear");
  printf("Objetivo: Procesar digitalmente una imagen PGM dada por el usuario.\n");
}

void menu(){
  int opcion = 0, validacion, Ancho, Alto, **Matriz, **Matriz2, **Matriz3, Ancho2, Alto2;
  char NombreArchivo[200], NuevoNombreA[200];
  PedirArchivo(NombreArchivo);
  ValidarArchivo(NombreArchivo, &validacion);
  if (validacion == 0) {
    obtenerDimensiones(NombreArchivo, &Ancho, &Alto);
    // Generando la matriz
    Matriz = (int**)malloc(Alto*sizeof(int*)); // Columnas
    for(int i = 0; i < Alto; i++)
      Matriz[i] = (int*)malloc(Ancho*sizeof(int)); // Filas
    Matriz2 = (int**)malloc(Alto*sizeof(int*)); // Columnas
    for(int i = 0; i < Alto; i++)
      Matriz2[i] = (int*)malloc(Ancho*sizeof(int)); // Filas
    Ancho2 = Ancho*2;
    Alto2 = Alto*2;
    Matriz3 = (int**)malloc(Alto2*sizeof(int*)); // Columnas
    for(int i = 0; i < Alto2; i++)
      Matriz3[i] = (int*)malloc(Ancho2*sizeof(int)); // Filas
    // Ahora voy a cargar la imagen a la matriz
    cargarArchivo(NombreArchivo, Ancho, Alto, Matriz);
    system("clear");
    printf("\t\t\t\tMENU\n");
    printf("\t1.- Obtener negativo de la imagen.\n");
    printf("\t2.- Ecualizar la imagen.\n");
    printf("\t3.- Reducir la imagen.\n");
    printf("\t4.- Ampliar la imagen.\n\n");
    printf("Elija una opcion-> ");
    scanf("%d", &opcion);
    switch (opcion) {
      case 1:
        negativo(Matriz, Ancho, Alto);
        break;
      case 2:
        ecualizar(Matriz, Ancho, Alto);
        break;
      case 3:
        reducir(Matriz, &Ancho, &Alto, Matriz2);
        break;
      case 4:
        ampliar(Matriz, &Ancho, &Alto, Matriz3);
        break;
      default:
        printf("Ingresa una opcion valida!\n");
    }
    if(opcion >= 1 && opcion<= 4)
      NuevoNombre(NuevoNombreA);
    if(opcion == 1 || opcion == 2)
      guardar(Matriz, Ancho, Alto, NuevoNombreA);
    else{
      if(opcion == 3)
        guardar(Matriz2, Ancho, Alto, NuevoNombreA);
      if(opcion == 4)
        guardar(Matriz3, Ancho, Alto, NuevoNombreA);
    }
      if(opcion == 4){
        liberarMemoria(Matriz, Ancho/2, Alto/2);
        liberarMemoria(Matriz2, Ancho/2, Alto/2);
      }else{
        liberarMemoria(Matriz, Ancho, Alto);
        liberarMemoria(Matriz2, Ancho, Alto);
      }
      liberarMemoria(Matriz3, Ancho2, Alto2);

    printf("El proceso ha terminado\n");
  }else{
    printf("No se ha podido abrir tu archivo, vuelve a intentarlo):\n");
  }
}
void PedirArchivo(char Nombre[]){
  printf("Ingresar nombre del archivo a procesar: ");
  gets(Nombre);
}
void ValidarArchivo(char Nombre[], int* Validacion){
  FILE* Archivo = fopen(Nombre, "rb");
  if(Archivo == NULL)
    *Validacion = 1;
  else{
    *Validacion = 0;
    fclose(Archivo);
  }
}
void obtenerDimensiones(char Nombre[], int* Ancho, int* Alto){
  FILE* Archivo = fopen(Nombre, "rb");
  int Dato1, Dato2;
  char Encabezado;
  fscanf(Archivo, "%c%d %d %d %d", &Encabezado, &Dato1, Ancho, Alto, &Dato2);
  fclose(Archivo);
}
void cargarArchivo(char Nombre[], int Ancho, int Alto, int* Matriz[]){
  FILE* Archivo =  fopen(Nombre, "rb");
  unsigned char prueba;
  fseek(Archivo, 15L, SEEK_SET);
  for(int i = 0; i < Alto; i++){
    for(int j = 0; j < Ancho; j++){
      fread(&prueba, sizeof(unsigned char), 1, Archivo);
      Matriz[i][j] = prueba;
    }
  }
  fclose(Archivo);
}
void guardar(int** Matriz, int Ancho, int Alto, char Nombre[]){
  FILE* Archivo = fopen(Nombre, "wb");
  fprintf(Archivo, "P5 %d %d 255 ", Ancho, Alto);
  for(int i= 0; i < Alto; i++){
    for(int j = 0; j < Ancho; j++){
      fwrite(&(Matriz[i][j]), sizeof(unsigned char), 1, Archivo);
    }
  }

  fclose(Archivo);
}
void negativo(int** Matriz, int Ancho, int Alto){
  for(int i = 0; i < Alto; i++){
    for(int j = 0; j < Ancho; j++){
      Matriz[i][j] = Matriz[i][j]*(-1)+255;
    }
  }
}
void ecualizar(int** Matriz, int Ancho, int Alto){
  float m, b;
  obtenerEcuacion(Matriz, Ancho, Alto, &m, &b);
  for(int i = 0; i < Alto; i++){
    for(int j = 0; j < Ancho; j++){
      Matriz[i][j] = (m)*(Matriz[i][j])+b;
    }
  }
}
void obtenerEcuacion(int** Matriz, int Ancho, int Alto, float* m,float* b){
    int  mayor, menor;
    float mm, bb;
    mayor = Matriz[0][0];
    menor = Matriz[0][0];
    for(int i = 0; i < Alto; i++){
      for(int j = 0; j < Ancho; j++){
        if(Matriz[i][j] > mayor)
          mayor = Matriz[i][j];
        if(Matriz[i][j] < menor)
          menor = Matriz[i][j];
      }
    }
    mm = (255)/(mayor - menor);
    bb = 255 - (mm*mayor);
    *m = mm;
    *b = bb;
}
void reducir(int ** Matriz, int* Ancho, int* Alto, int** Matriz2){
  int x = 0, y = 0;
  for(int i = 0; i < *Alto; i+= 2){
    x = 0;
    for(int j = 0; j < *Ancho; j+= 2){
      Matriz2[y][x] = Matriz[i][j];
      x++;
    }
    y++;
  }
  *Alto = y;
  *Ancho = x;
}
void ampliar(int** Matriz, int* Ancho, int* Alto, int** Matriz3){
  int h = 0, k = 0, i, j;
  for( i = 0; i < *Alto; i++){
    k = 0;
    for( j = 0; j < *Ancho; j++){
      Matriz3[h][k] = Matriz[i][j];
      k++;
      if (k % 2 == 0) {
        Matriz3[h][k] = Matriz[i][j];
        k++;
      }

    }
    h++;
    if(h % 2 == 0){
      for(int l = 0; l < (*Ancho)*2-1; l++){
        Matriz3[h][l] = Matriz3[h-1][l];
      }
      h++;
    }

  }
  *Ancho = k;
  *Alto = h;
}
void NuevoNombre(char Name[]){
  printf("Ingresar nuevo nombre del archivo: ");
  __fpurge(stdin);
  gets(Name);
}
void liberarMemoria(int** Matriz, int Ancho, int Alto){
  for(int i = 0; i < Alto; i++)
    free(Matriz[i]);// Filas
  free(Matriz); // Columnas
}
