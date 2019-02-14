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
  int opcion = 0, validacion, Ancho, Alto, **Matriz;
  char NombreArchivo[200], NuevoNombreA[200];
  PedirArchivo(NombreArchivo);
  ValidarArchivo(NombreArchivo, &validacion);
  if (validacion == 0) {
    obtenerDimensiones(NombreArchivo, &Ancho, &Alto);
    // Generando la matriz
    Matriz = (int**)malloc(Alto*sizeof(int*)); // Columnas
    for(int i = 0; i < Alto; i++)
      Matriz[i] = (int*)malloc(Ancho*sizeof(int)); // Filas
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
        printf("Ecualizar\n");
        break;
      case 3:
        printf("Reducir\n");
        break;
      case 4:
        printf("Ampliar\n");
        break;
      default:
        printf("Ingresa una opcion valida!\n");
    }
    NuevoNombre(NuevoNombreA);
    guardar(Matriz, Ancho, Alto, NuevoNombreA);
    printf("El proceso ha sido completado!\n");
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
void NuevoNombre(char Name[]){
  printf("Ingresar nuevo nombre del archivo: ");
  __fpurge(stdin);
  gets(Name);
}
