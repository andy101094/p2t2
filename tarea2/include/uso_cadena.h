/*
  Módulo de definición de `uso_cadena_s'.

  Se definen funciones sobre cadenas.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _USO_CADENA_H
#define _USO_CADENA_H

#include "info.h"
#include "cadena.h"

/*
  Devuelve `true' si y sólo si en `cad' hay un elemento cuyo dato numérico es
  `i'.
 */
bool pertenece(int i, cadena_t cad);

/*  Devuelve la cantidad de elementos de `cad'. */
nat longitud(cadena_t cad);

/*
  Devuelve `true' si y sólo si `c1' y `c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si es_vacia_cadenat(c1) y es_vacia_cadena(c2) devuelve `true'.
 */
bool son_iguales(cadena_t c1, cadena_t c2);

/*
  Devuelve el resultado de concatenar `c2' después de `c1'.
  La cadena_t resultado no comparte memoria ni con `c1' ni con `c2'.
 */
cadena_t concatenar(cadena_t c1, cadena_t c2);

/*
  Se ordena `cad' de manera creciente según los datos numéricos de sus
  elementos.
  No se debe obtener ni devolver memoria de manera dinámica.
  Si es_vacia_cadena (cad) no hace nada.
 */
void ordenar(cadena_t &cad);

/*
  Cambia todas las ocurrencias de `original' por `nuevo' en los elementos
   de `cad'. No debe quedar memoria inaccesible.
 */
void cambiar_todos(int original, int nuevo, cadena_t &cad);

/*
  Devuelve la cadena_t de elementos de `cad' que cumplen
  "menor <= numero_info (elemento) <= mayor".
  El orden relativo de los elementos en la cadena_t resultado debe ser el mismo
  que en `cad'.
  La cadena_t resultado no comparte memoria con `cad'.
  Precondición: esta_ordenada (cad), `menor' <= `mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
 */
cadena_t subcadena(int menor, int mayor, cadena_t cad);

#endif
