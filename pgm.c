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
void guardar(int**, int, int);
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
  char NombreArchivo[200];
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
    guardar(Matriz, Ancho, Alto);
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
void guardar(int** Matriz, int Ancho, int Alto){
  FILE* Archivo = fopen("prueba.raw", "wb");
  fprintf(Archivo, "P5 %d %d 255 ", Ancho, Alto);
  for(int i= 0; i < Alto; i++){
    for(int j = 0; j < Ancho; j++){
      fwrite(&(Matriz[i][j]), sizeof(unsigned char), 1, Archivo);
    }
  }

  fclose(Archivo);
}
