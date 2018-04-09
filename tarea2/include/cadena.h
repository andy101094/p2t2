/*
  Módulo de definición de `cadena_t'.

  Lista doblemente enlazada de elementos de tipo `info_t', con cabezal con
  punteros al inicio y al final.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _CADENA_H
#define _CADENA_H

#include "info.h"

typedef unsigned int nat;

/*
  Las variables de tipo localizador_t permiten acceder a los elementos en las
  estructuras que los contienen. En el caso de una cadena enlazada esas
  variables son punteros a los nodos.
 */
// struct nodo es la representación de `localizador', definida en `cadena.cpp'.
typedef struct nodo *localizador_t;

// struct rep_cadena es la representación de `cadena_t', definida en
// `cadena.cpp'.
typedef struct rep_cadena *cadena_t;

/* Constructoras */

/*  Devuelve la cadena_t vacía (sin elementos). */
cadena_t crear_cadena();

/*
  Se inserta `i' como último elemento de `cad'.
  Si es_vacia_cadena (cad) `i' se inserta como único elemento de `cad'.
 */
void insertar_al_final(info_t i, cadena_t &cad);

/*
  Se inserta `i' como un nuevo elemento inmediatamente antes de `loc'.
  Precondición: localizador_en_cadena(loc, cad).
 */
void insertar_antes(info_t i, localizador_t loc, cadena_t &cad);

/*
  Se inserta la cadena_t `sgm' inmediatamente después de `loc' en `cad',
  manteniendo los elementos originales y el orden relativo entre ellos.
  No se debe obtener memoria (los nodos de `sgm' pasan a ser parte de `cad').
  Al terminar, `sgm' queda vacía.
  Si es_vacia_cadena(cad) `loc' es ignorado y el segmento queda insertado.
  Precondición: es_vacia_cadena(cad) o localizador_en_cadena(loc, cad).
 */
void insertar_segmento_despues(cadena_t &sgm, localizador_t loc, cadena_t &cad);

/*
  Devuelve una cadena_t con los elementos de `cad' que se encuentran entre
  `desde' y `hasta', incluidos.
  La cadena_t resultado no comparte memoria con `cad'.
  Si es_vacia_cadena(cad) devuelve la cadena_t vacia.
  Precondición: es_vacia_cadena(cad) o precede_en_cadena(desde, hasta, cad).
 */
cadena_t segmento_cadena(localizador_t desde, localizador_t hasta,
                         cadena_t cad);

/*
  Devuelve una cadena_t con los elementos de `cad' que se encuentran
  entre `desde' y `hasta', incluidos. Además, quita de `cad' dichos elementos,
  manteniendo el orden de los restantes.
  Si es_vacia_cadena(cad) devuelve la cadena_t vacía.
  No se debe obtener ni devolver memoria de nodos ni de elementos.
  La cadena_t resultado no comparte memoria con `cad'.
  Con `desde' y `hasta' se pasa a acceder al inicio y final respectivamente
  de la cadena_t resultado.
  Precondición: es_vacia_cadena(cad) o precede_en_cadena(desde, hasta, cad).
 */
cadena_t separar_segmento(localizador_t desde, localizador_t hasta,
                          cadena_t &cad);

/*
  Devuelve una cadena_t con todos los elementos de `c1' y `c2' ordenada de
  manera
  creciente segun sus datos numéricos.
  Si hay elementos cuyos datos numéricos son iguales los elementos de `c1'
  quedan antes de los de `c2'.
  La cadena_t resultado no comparte memoria ni con `c1' ni con `c2'.
  Precondición: esta_ordenada (c1) y esta_ordenada (c2).
 */
cadena_t mezcla(cadena_t c1, cadena_t c2);

/* Destructoras */

/*
  Se quita el elemento referenciado en `loc' y se libera la memoria asignada
  al mismo y al nodo apuntado por el localizador.
  El valor de `loc' queda indeterminado.
  Precondición: localizador_en_cadena(loc, cad).
 */
void remover_de_cadena(localizador_t &loc, cadena_t &cad);

/*  Libera la memoria asignada a `cad' y la de todos sus elementos. */
void liberar_cadena(cadena_t &cad);

/* Predicados */

/*
  Devuelve `true' si y sólo si `loc' es un localizador_t válido.
  En cadenas enlazadas un localizador_t no es válido si es `NULL'.
*/
bool es_localizador(localizador_t loc);

/* Devuelve `true' si y sólo si `cad' es vacía (no tiene elementos). */
bool es_vacia_cadena(cadena_t cad);

/*
  Devuelve `true' si y sólo si `cad' está ordenada de forma no decreciente
  (= creciente de manera no estricta) según los datos numéricos de sus
  elementos.
  Si es_vacia_cadena (cad) devuelve `true'.
 */
bool esta_ordenada(cadena_t cad);

/*
  Devuelve `true' si y sólo si con `loc' se accede al último elemento de `cad'.
  Si es_vacia_cadena (cad) devuelve `false'.
 */
bool es_final_cadena(localizador_t loc, cadena_t cad);

/*
  Devuelve `true' si y sólo si con `loc' se accede al primer elemento de `cad'.
  Si es_vacia_cadena (cad) devuelve `false'.
 */
bool es_inicio_cadena(localizador_t loc, cadena_t cad);

/*
  Devuelve `true' si y sólo si con `loc' se accede a un elemento de `cad'.
  Si es_vacia_cadena (cad) devuelve `false'.
 */
bool localizador_en_cadena(localizador_t loc, cadena_t cad);

/*
  Devuelve `true' si y sólo si `loc1' es igual o precede a `loc2` en `cad`.
  Si es_vacia_cadena (cad) devuelve `false'.
 */
bool precede_en_cadena(localizador_t loc1, localizador_t loc2, cadena_t cad);

/* Posicionamiento */

/*
  Devuelve el localizador_t con el que se accede al inicio de `cad`.
  Si es_vacia_cadena(cad) devuelve un localizador_t no válido.
 */
localizador_t inicio_cadena(cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al final de `cad'.
  Si es_vacia_cadena(cad) devuelve un localizador_t no válido.
 */
localizador_t final_cadena(cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al k-esimo elemento de `cad'.
  Si `k' es 0 o mayor a la cantidad de elementos de `cad' devuelve un localizdor
  no válido.
 */
localizador_t kesimo(nat k, cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al elemento de `cad'
  inmediatamente  siguiente a `loc'.
  Si es_final_cadena(loc, cad) devuelve un localizador_t no válido.
  Precondición: localizador_en_cadena(loc, cad).
 */
localizador_t siguiente(localizador_t loc, cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al elemento de `cad'
  inmediatamente  anterior a `loc'.
  Si es_inicio_cadena(loc, cad) devuelve un localizador_t no válido.
  Precondición: localizador_en_cadena(loc, cad).
 */
localizador_t anterior(localizador_t loc, cadena_t cad);

/*
  Devuelve el localizador_t con el que se accede al elemento cuyo dato numérico
  es el menor en el segmento que va desde `loc' hasta el final_cadena(cad).
  Si hay más de un elemento cuyo valor es el menor el resultado accede al que
  precede a los otros.
  Precondición: localizador_en_cadena(loc, cad).
 */
localizador_t menor_en_cadena(localizador_t loc, cadena_t cad);

/*
  Devuelve el primer localizador_t con el que se accede a un elemento cuyo dato
  numérico es igual a `clave', buscando desde `loc' (inclusive) hacia el final
  de `cad'.
  Si no se encuentra o `cad' es vacía devuelve un localizador_t no válido.
  Precondición: es_vacia_cadena(cad) o localizador_en_cadena(loc, cad).
 */
localizador_t siguiente_clave(int clave, localizador_t loc, cadena_t cad);

/*
  Devuelve el primer localizador_t con el que se accede a un elemento cuyo dato
  numérico es igual a `clave', buscando desde `loc' (inclusive) hacia el inicio
  de `cad'.
  Si no se encuentra o `cad' es vacia devuelve un localizador_t no válido.
  Precondición: es_vacia_cadena(cad) o localizador_en_cadena(loc, cad).
 */
localizador_t anterior_clave(int clave, localizador_t loc, cadena_t cad);

/* Selectoras */

/*
  Devuelve el elemento de `cad' al que se accede con `loc'.
  Precondición: localizador_en_cadena(loc, cad).
 */
info_t info_cadena(localizador_t loc, cadena_t cad);

/* Modificadoras */

/*
  Sustituye con `i' el elemento de `cad' al que se accede con `loc'.
  No destruye el elemento al que antes se accedía con `loc'.
  Precondición: localizador_en_cadena(loc, cad).
 */
void cambiar_en_cadena(info_t i, localizador_t loc, cadena_t &cad);

/*
  Intercambia los elementos a los que se accede con `loc1' y `loc2'.
  `loc1' y `loc2' mantienen su relación de precedencia.
  Precondición:
    localizador_en_cadena (loc1, cad)
  y localizador_en_cadena (loc2, cad).
 */
void intercambiar(localizador_t loc1, localizador_t loc2, cadena_t &cad);

/* Salida */
/*
  Imprime los elementos de `cad` de la siguiente forma:
  (dn de pos1,fr de pos1)(dn de pos2,fr de pos2) ...
  donce `dn` es el dato numérico y `fr` es la frase.
  Antes de terminar, se debe imprimir un fin de linea.
  Si es_vacia_cadena(cad) sólo se imprime el fin de línea.
 */
void imprimir_cadena(cadena_t cad);

#endif
