/*
  Módulo de implementación de `info_t'.

  Se implementa struct rep_info como un registro con dos campos, uno numérico y
otro de texto.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/info.h"

#include <string.h> // strlen, strcpy, strcmp, strcat
#include <stdio.h>  // sprintf, scanf, ungetc, stdin
#include <limits.h> // INT_MAX

struct rep_info {
  int num;
  char *frase; // arreglo cuyo tamaño se determina en tiempo de ejecución
};

info_t crear_info(int num, char *frase) {
  info_t nueva = new rep_info;
  nueva->num = num;
  nueva->frase = frase; // comparte memoria con el parámetro
  return nueva;
}

info_t copia_info(info_t info) {
  info_t copia = new rep_info;
  copia->num = info->num;
  // NO comparte memoria con info
  copia->frase = new char[strlen(info->frase) + 1];
  strcpy(copia->frase, info->frase);
  return copia;
}

void liberar_info(info_t &info) {
  delete[] info->frase;
  delete info;
}

int numero_info(info_t info) { return info->num; }

char *frase_info(info_t info) { return info->frase; }

bool son_iguales(info_t i1, info_t i2) {
  return (i1->num == i2->num) && (!strcmp(i1->frase, i2->frase));
}

bool es_valida_info(info_t info) { return (info->num != INT_MAX); }

char *info_a_texto(info_t info) {
  char copia_num[11];
  sprintf(copia_num, "%d", info->num);
  char *texto = new char[strlen(copia_num) + strlen(info->frase) + 4];
  strcpy(texto, "(");
  strcat(texto, copia_num);
  strcat(texto, ",");
  strcat(texto, info->frase);
  strcat(texto, ")");
  return texto;
}

info_t leer_info(int max) {
  info_t leido;
  int num;
  char *cadena = new char[max];
  char simbolo;
  bool error = false;
  scanf(" %c", &simbolo);
  if (simbolo != '(')
    error = true;
  else {
    scanf("%d", &num);
    scanf(" %c", &simbolo);
    if (simbolo != ',')
      error = true;
    else {
      int pos = 0;
      int c = getchar();
      while ((c != ')') && (c != '\n')) {
        cadena[pos] = c;
        pos++;
        c = getchar();
      }
      cadena[pos] = '\0';
      if (c == '\n') {
        error = true;
        ungetc('\n', stdin);
      }
    }
  }
  if (error) {
    char *nulo = new char[1];
    nulo[0] = '\0';
    leido = crear_info(INT_MAX, nulo);
  } else {
    char *frase = new char[strlen(cadena) + 1];
    strcpy(frase, cadena);
    leido = crear_info(num, frase);
  }
  delete[] cadena;
  return leido;
}
