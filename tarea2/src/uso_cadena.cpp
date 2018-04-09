#include "../include/uso_cadena.h"
#include "../include/cadena.h"
#include "../include/info.h"

#include <stddef.h>
#include <stdio.h>  // sprintf, scanf, ungetc, stdin
#include <assert.h>

void ordenar(cadena_t &cad)
{
	if ( (!es_vacia_cadena(cad)) && (!esta_ordenada(cad))  )
	{
		localizador_t cursor = inicio_cadena(cad);
		while( es_localizador(cursor))
		{
			localizador_t cursor_menor = menor_en_cadena(cursor,cad);
			intercambiar(cursor_menor,cursor,cad);
			cursor = siguiente(cursor,cad);
		}

	}
}

bool pertenece(int i, cadena_t cad)
{
	bool pertenece = false;
	
	if(!es_vacia_cadena(cad))
	{
		ordenar(cad);

		pertenece = es_localizador(kesimo(i,cad));
	}
	return pertenece;
}

nat longitud(cadena_t cad)
{
	nat l = 0;
	localizador_t cursor = inicio_cadena(cad);
	
	while(es_localizador(cursor))
	{
		l++;
		cursor = siguiente(cursor,cad);
	}
	return l;
}

bool son_iguales(cadena_t c1, cadena_t c2)
{
	bool iguales = true;

	localizador_t it1 = inicio_cadena(c1);
	localizador_t it2 = inicio_cadena(c2);

	while ( iguales && (es_localizador(it1) && es_localizador(it2)) )
	{
		iguales = son_iguales(info_cadena(it1,c1),info_cadena(it2,c2));
		it1 = siguiente(it1,c1);
		it2 = siguiente(it2,c2);
	}

	if ( (es_localizador(it1) && !es_localizador(it2)) || (es_localizador(it2) && !es_localizador(it1)) ) iguales = false;

	return iguales;
}

cadena_t concatenar(cadena_t c1, cadena_t c2)
{
	cadena_t concat  = segmento_cadena(inicio_cadena(c1),final_cadena(c1),c1);
	cadena_t sgm_c2 = segmento_cadena(inicio_cadena(c2),final_cadena(c2),c2);
	insertar_segmento_despues(sgm_c2,final_cadena(concat),concat);
	return concat;
}

void cambiar_todos(int original, int nuevo, cadena_t &cad)
{
	localizador_t cursor = inicio_cadena(cad);

	while(es_localizador(cursor))
	{
		info_t info_cursor = info_cadena(cursor,cad);
		if (numero_info(info_cursor) == original)
		{
			info_t info_nuevo;
			info_t info_aux;
			info_aux = crear_info(nuevo,frase_info(info_cursor));
			info_nuevo = copia_info(info_aux);
			cambiar_en_cadena(info_nuevo,cursor,cad);
			liberar_info(info_cursor);
		}
		cursor = siguiente(cursor,cad);
	}
}

cadena_t subcadena(int menor, int mayor, cadena_t cad)
{
	assert(pertenece (menor, cad) && pertenece (mayor, cad));
	localizador_t loc_menor = anterior_clave(menor,inicio_cadena(cad),cad);
	localizador_t loc_mayor = siguiente_clave(mayor,inicio_cadena(cad),cad);

	cadena_t sub = crear_cadena();

	if ( (es_localizador(loc_menor)) && (es_localizador(loc_mayor)) )
	{
		cadena_t less = segmento_cadena(loc_menor,loc_mayor,cad);
		insertar_segmento_despues(less,inicio_cadena(sub),sub);
	}
	return sub;
}