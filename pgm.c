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
  int opcion = 0, validacion, Ancho, Alto;
  char NombreArchivo[200];
  PedirArchivo(NombreArchivo);
  ValidarArchivo(NombreArchivo, &validacion);
  if (validacion == 0) {
    obtenerDimensiones(NombreArchivo, *Ancho, *Alto);
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
