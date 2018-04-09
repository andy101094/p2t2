/*
  Módulo principal de la tarea 2.

Intérprete de comandos para probar los módulos.

Están creados una cadena_t `cad' y un localizador `loc'.

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

Si un parámetro debe ser de tipo info_t su formato cumple con lo descrito en
`info_a_texto' del módulo `info', con el agregado de que no puede incluir el
 símbolo ')'.

Si un parámetro es una secuencia de elementos de algún tipo termina con un
espacio en blanco y un punto.


El comando
Fin
termina el programa

El comando
# comentario
imprime comentario.

El comando
reiniciar
libera la memoria asignada a `cad' y la vuelve a crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/info.h"
#include "include/cadena.h"
#include "include/uso_cadena.h"

#include <stdio.h>
#include <string.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256

/*
  Lee una cadena_t de info_t desde la entrada estándar. Después de cada elemento
  hay un espacio en blanco. Termina con un punto.
 */
cadena_t leer_cadena() {
  cadena_t res = crear_cadena();
  info_t info = leer_info(MAX_PALABRA);
  while (es_valida_info(info)) {
    insertar_al_final(info, res);
    info = leer_info(MAX_PALABRA);
  }
  liberar_info(info);
  return res;
} // leer_cadena

// programa principal
int main() {
  cadena_t cad = crear_cadena();
  localizador_t loc = inicio_cadena(cad); // no válido porque cad es vacía

  char resto_linea[MAX_LINEA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    char nom_comando[MAX_PALABRA];
    scanf("%s", nom_comando);

    // procesar el comando
    if (!strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (!strcmp(nom_comando, "#")) {
      scanf("%[^\n]", resto_linea);
      printf("# %s.\n", resto_linea);

      // operaciones de cadena

    } else if (!strcmp(nom_comando, "insertar_al_final")) {
      info_t info = leer_info(MAX_LINEA);
      insertar_al_final(info, cad);
      printf("Insertado al final.\n");

    } else if (!strcmp(nom_comando, "insertar_antes")) {
      info_t info = leer_info(MAX_LINEA);
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        insertar_antes(info, loc, cad);
        printf("Insertado antes de loc.\n");
      }

    } else if (!strcmp(nom_comando, "insertar_segmento_despues")) {
      if (!es_vacia_cadena(cad) && !localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        cadena_t sgm = leer_cadena();
        insertar_segmento_despues(sgm, loc, cad);
        liberar_cadena(sgm);
        printf("Segmento insertado después de loc.\n");
      }

    } else if (!strcmp(nom_comando, "segmento_cadena")) {
      nat k1, k2;
      scanf("%u %u", &k1, &k2);
      nat cantidad = longitud(cad);
      if (!es_vacia_cadena(cad) && ((k1 < 1) || (k2 < k1) || (k2 > cantidad)))
        printf("Posiciones fuera de rango.\n");
      else {
        localizador_t loc_desde = kesimo(k1, cad);
        localizador_t loc_hasta = kesimo(k2, cad);
        cadena_t sgm = segmento_cadena(loc_desde, loc_hasta, cad);
        imprimir_cadena(sgm);
        liberar_cadena(sgm);
      }

    } else if (!strcmp(nom_comando, "separar_segmento")) {
      nat k1, k2;
      scanf("%u %u", &k1, &k2);
      nat cantidad = longitud(cad);
      if (!es_vacia_cadena(cad) && ((k1 < 1) || (k2 < k1) || (k2 > cantidad)))
        printf("Posiciones fuera de rango.\n");
      else {
        localizador_t loc_desde = kesimo(k1, cad);
        localizador_t loc_hasta = kesimo(k2, cad);
        cadena_t sgm = separar_segmento(loc_desde, loc_hasta, cad);
        imprimir_cadena(sgm);
        liberar_cadena(sgm);
      }

    } else if (!strcmp(nom_comando, "mezcla")) {
      cadena_t otra = leer_cadena();
      if (!esta_ordenada(cad) || !esta_ordenada(otra))
        printf("Cadena no ordenada.\n");
      else {
        cadena_t mzc = mezcla(cad, otra);
        imprimir_cadena(mzc);
        liberar_cadena(mzc);
      }
      liberar_cadena(otra);

    } else if (!strcmp(nom_comando, "remover_de_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        remover_de_cadena(loc, cad);
        printf("Removido.\n");
      }

    } else if (!strcmp(nom_comando, "es_localizador")) {
      printf("loc%s válido.\n", es_localizador(loc) ? "" : " no");

    } else if (!strcmp(nom_comando, "es_vacia_cadena")) {
      printf("cad%s.\n", es_vacia_cadena(cad) ? " vacia" : " no vacia");

    } else if (!strcmp(nom_comando, "esta_ordenada")) {
      printf("cad%s.\n", esta_ordenada(cad) ? " ordenada" : " no ordenada");

    } else if (!strcmp(nom_comando, "es_final_cadena")) {
      printf("loc%s es final de cad.\n",
             es_final_cadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "es_inicio_cadena")) {
      printf("loc%s es incio de cad.\n",
             es_inicio_cadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "localizador_en_cadena")) {
      printf("loc%s pertenece a cad.\n",
             localizador_en_cadena(loc, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "precede_en_cadena")) {
      nat k1;
      scanf("%u", &k1);
      nat cantidad = longitud(cad);
      if ((k1 < 1) || (k1 > cantidad))
        printf("Posición fuera de rango.\n");
      else if (!localizador_en_cadena(loc, cad))
        printf("loc no pertenece a cad.\n");
      else {
        localizador_t loc1 = kesimo(k1, cad);
        printf("loc1%s precede a loc.\n",
               precede_en_cadena(loc1, loc, cad) ? "" : " no");
      }

    } else if (!strcmp(nom_comando, "inicio_cadena")) {
      loc = inicio_cadena(cad);
      printf("loc al inicio.\n");

    } else if (!strcmp(nom_comando, "final_cadena")) {
      loc = final_cadena(cad);
      printf("loc al final.\n");

    } else if (!strcmp(nom_comando, "kesimo")) {
      unsigned int k;
      scanf("%u", &k);
      loc = kesimo(k, cad);
      printf("loc en la posición %u.\n", k);

    } else if (!strcmp(nom_comando, "siguiente")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        loc = siguiente(loc, cad);
        printf("loc al siguiente.\n");
      }

    } else if (!strcmp(nom_comando, "anterior")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        loc = anterior(loc, cad);
        printf("loc al anterior.\n");
      }

    } else if (!strcmp(nom_comando, "menor_en_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        loc = menor_en_cadena(loc, cad);
        printf("loc avanzó hasta el menor.\n");
      }

    } else if (!strcmp(nom_comando, "siguiente_clave")) {
      if (!es_vacia_cadena(cad) && !localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        int clave;
        scanf("%d", &clave);
        loc = siguiente_clave(clave, loc, cad);
        printf("loc avanzó buscando %d.\n", clave);
      }

    } else if (!strcmp(nom_comando, "anterior_clave")) {
      if (!es_vacia_cadena(cad) && !localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        int clave;
        scanf("%d", &clave);
        loc = anterior_clave(clave, loc, cad);
        printf("loc retrocedió buscando %d.\n", clave);
      }

    } else if (!strcmp(nom_comando, "info_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        char *txt_info = info_a_texto(info_cadena(loc, cad));
        printf("%s\n", txt_info);
        delete[] txt_info;
      }

    } else if (!strcmp(nom_comando, "cambiar_en_cadena")) {
      if (!localizador_en_cadena(loc, cad))
        printf("Localizador no válido.\n");
      else {
        info_t nueva_info = leer_info(MAX_PALABRA);
        info_t anterior_info = info_cadena(loc, cad);
        cambiar_en_cadena(nueva_info, loc, cad);
        liberar_info(anterior_info);
        printf("Cambio.\n");
      }

    } else if (!strcmp(nom_comando, "intercambiar")) {
      nat k1, k2;
      scanf("%u %u", &k1, &k2);
      nat cantidad = longitud(cad);
      if ((k1 < 1) || (k1 > cantidad) || (k2 < 1) || (k2 > cantidad))
        printf("Posición fuera de rango.\n");
      else {
        localizador_t loc1 = kesimo(k1, cad);
        localizador_t loc2 = kesimo(k2, cad);
        intercambiar(loc1, loc2, cad);
        printf("Intercambio.\n");
      }

    } else if (!strcmp(nom_comando, "imprimir_cadena")) {
      imprimir_cadena(cad);

      // operaciones de uso_cadena

    } else if (!strcmp(nom_comando, "pertenece")) {
      int i;
      scanf("%d", &i);
      printf("%d%s pertenece a cad.\n", i, pertenece(i, cad) ? "" : " no");

    } else if (!strcmp(nom_comando, "longitud")) {
      printf("Longitud: %u\n", longitud(cad));

    } else if (!strcmp(nom_comando, "son_iguales")) {
      cadena_t otra = leer_cadena();
      printf("%s.\n",
             son_iguales(cad, otra) ? "Son iguales" : "No son iguales");
      liberar_cadena(otra);

    } else if (!strcmp(nom_comando, "concatenar")) {
      cadena_t otra = leer_cadena();
      cadena_t conc = concatenar(cad, otra);
      imprimir_cadena(conc);
      liberar_cadena(conc);
      liberar_cadena(otra);

    } else if (!strcmp(nom_comando, "ordenar")) {
      ordenar(cad);
      printf("Ordenada.\n");

    } else if (!strcmp(nom_comando, "cambiar_todos")) {
      int original, nuevo;
      scanf("%d %d", &original, &nuevo);
      cambiar_todos(original, nuevo, cad);
      printf("Cambiados.\n");

    } else if (!strcmp(nom_comando, "subcadena")) {
      int menor, mayor;
      scanf("%d %d", &menor, &mayor);
      if (!esta_ordenada(cad) || (mayor < menor) || !pertenece(menor, cad) ||
          !pertenece(mayor, cad))
        printf("No se cumplen las precondiciones.\n");
      else {
        cadena_t sub = subcadena(menor, mayor, cad);
        imprimir_cadena(sub);
        liberar_cadena(sub);
      }

    } else if (!strcmp(nom_comando, "reiniciar")) {
      liberar_cadena(cad);
      cad = crear_cadena();
      loc = inicio_cadena(cad);
      printf("Estructuras reiniciadas.\n");

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(resto_linea, MAX_LINEA + 1, stdin);
  } // while

  liberar_cadena(cad);

  return 0;
}
