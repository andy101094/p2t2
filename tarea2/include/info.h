/*
  Módulo de definición de `info_t'.

  `info_t' es un puntero a una estructura (que debe definirse en
  info.cpp) cuyo contenido es un dato numérico (entero) y una frase.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _INFO_H
#define _INFO_H

// Declaración del tipo `info_t'
// struct rep_info es la representación de `info_t', definida en info.cpp
typedef struct rep_info *info_t;

/* Operaciones de info_t */

/*
  Devuelve un `info_t' tal que su dato numérico es `num' y su frase
  es `fra'.
 */
info_t crear_info(int num, char *frase);

/*
  Devuelve una copia de `info'.
  El elemento devuelto no comparte memoria con `info'.
 */
info_t copia_info(info_t info);

/* Libera la memoria reservada por `info'. */
void liberar_info(info_t &info);

/* Devuelve el dato numérico de `info'. */
int numero_info(info_t info);

/*  Devuelve la frase de `info'. */
char *frase_info(info_t info);

/*
  Devuelve `true' si y sólo si el dato numérico y la frase de `i1' son iguales a
  los de `i2'.
 */
bool son_iguales(info_t i1, info_t i2);

/*
  Devuelve `true' si y sólo si `info' es válida.
  `info' no es válida cuando su valor numérico es INT_MAX.
 */
bool es_valida_info(info_t info);

/*
  Devuelve un arreglo de caracteres formado por la concatenación del dato
  numérico de `info', el string "," y la frase de `info' encerrados entre
  parentesis.
  El elemento devuelto no comparte memoria con `info'.
   Ejemplos:
   (4,a)
   (9,)
   (56,ja ja)
 */
char *info_a_texto(info_t info);

/*
  Lee texto desde la entrada estándar. Si tiene formato de `info_t' (ver
  info_a_texto) lo devuelve convertido en `info_t'. En otro caso devuelve un
  `info_t' con un  dato numérico = INT_MAX y frase vacía.
  Se asume que hay texto para leer, que no incluye el símbolo `)' y tiene a
  lo sumo `max' caracteres.
 */
info_t leer_info(int max);

#endif
