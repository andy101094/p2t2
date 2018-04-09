#include "../include/cadena.h"
#include "../include/info.h"

#include <stddef.h>
#include <stdio.h>  // sprintf, scanf, ungetc, stdin
#include <assert.h>
#include <string.h> // strlen, strcpy, strcmp, strcat

struct nodo
{
	info_t dato;
	nodo *anterior;
	nodo *siguiente;	
};

struct rep_cadena
{
	nodo *inicio;
	nodo *final;
};

cadena_t crear_cadena()
{
 cadena_t cadena = new rep_cadena;
 cadena->inicio = cadena->final = NULL;
 return cadena;
}

void insertar_al_final(info_t i, cadena_t &cad)
{
	nodo *nuevo = new nodo;
	nuevo->dato = i;
	nuevo->siguiente = NULL;
	nuevo->anterior = cad->final;

	if (cad->final == NULL)
	{
		assert(cad->inicio == NULL);
		cad->inicio = nuevo;
	}
	else
	{
		assert(cad->inicio != NULL);
		cad->final->siguiente = nuevo; 
	}
	cad->final = nuevo;
}

void insertar_antes(info_t i, localizador_t loc, cadena_t &cad)
{
	assert(localizador_en_cadena(loc, cad));
	nodo *nuevo = new nodo;
	nuevo->dato = i;

	if (loc == cad->inicio)
	{
		cad->inicio->anterior = nuevo;
		nuevo->anterior = NULL;
		nuevo->siguiente = cad->inicio;
		cad->inicio = nuevo;
	}
	else
	{
		
		loc->anterior->siguiente = nuevo;
		nuevo->anterior = loc->anterior;
		nuevo->siguiente = loc;
		loc->anterior = nuevo;
	}
}																																																																																																																																																																																											

void insertar_segmento_despues(cadena_t &sgm, localizador_t loc, cadena_t &cad)
{
	assert(es_vacia_cadena(cad) || localizador_en_cadena(loc,cad));
	if (es_vacia_cadena(cad))
	{
		cad->inicio = sgm->inicio;
		cad->final = sgm->final;
	}
	else
	{
		if (!es_vacia_cadena(sgm))
		{
			sgm->inicio->anterior = loc;
			sgm->final->siguiente = loc->siguiente;

			if (es_final_cadena(loc,cad)) cad->final =  sgm->final;
			else loc->siguiente->anterior = sgm->final;

			loc->siguiente = sgm->inicio;
		}
	}
	sgm->inicio = sgm->final = NULL;
}

cadena_t segmento_cadena(localizador_t desde, localizador_t hasta,
                         cadena_t cad)
{
	assert(es_vacia_cadena(cad) || precede_en_cadena(desde,hasta,cad));

	cadena_t res = crear_cadena();
	if (!es_vacia_cadena(cad))
	{
		localizador_t loc = desde;
		while(loc != siguiente(hasta,cad))
		{
			info_t info = copia_info(loc->dato);
			insertar_al_final(info,res);
			loc = siguiente(loc,cad);
		}
	}
	return res;
}

cadena_t separar_segmento(localizador_t desde, localizador_t hasta,
                          cadena_t &cad)
{
	assert(es_vacia_cadena(cad) || precede_en_cadena(desde, hasta, cad));

	cadena_t sgm = segmento_cadena(desde,hasta,cad);

	while(desde != siguiente(hasta,cad))
	{
		remover_de_cadena(desde,cad);
		desde = siguiente(desde,cad);
	}
	desde = inicio_cadena(sgm);
	hasta = final_cadena(sgm);
	return sgm;
}

cadena_t mezcla(cadena_t c1,cadena_t c2)
{

	cadena_t marge = crear_cadena();

	if (es_vacia_cadena(c1) || es_vacia_cadena(c2))
	{
		if (es_vacia_cadena(c2))
		{
			cadena_t sgm_c1 = segmento_cadena(inicio_cadena(c1),final_cadena(c1),c1);
			insertar_segmento_despues(sgm_c1,inicio_cadena(marge),marge);
		}
		else
		{
			cadena_t sgm_c2 = segmento_cadena(inicio_cadena(c2),final_cadena(c2),c2);
			insertar_segmento_despues(sgm_c2,inicio_cadena(marge),marge);
		}
	}
	else
	{

		localizador_t loc_c1 = inicio_cadena(c1);
		localizador_t loc_c2 = inicio_cadena(c2);
		while( es_localizador(loc_c1) && es_localizador(loc_c2))
		{
			int clave_c1 = numero_info(loc_c1->dato);
			int clave_c2 = numero_info(loc_c2->dato);
			info_t m_info;
			
			if (clave_c1 <  clave_c2)
			{
				m_info = copia_info(loc_c1-> dato);
				loc_c1 = siguiente(loc_c1,c1);
			}
			else if (clave_c2 < clave_c1)
			{
				m_info = copia_info(loc_c2->dato);
				loc_c2 = siguiente(loc_c2,c2);
			}
			else
			{
				m_info = copia_info(loc_c1->dato);
				loc_c1 = siguiente(loc_c1,c1);
				loc_c2 = siguiente(loc_c2,c2);
			}
			insertar_al_final(m_info,marge);
		}

		if (es_localizador(loc_c1) || es_localizador(loc_c2))
		{
			if(es_localizador(loc_c1)) 
			{	
				cadena_t sgm_c1 = segmento_cadena(loc_c1,final_cadena(c1),c1);
				insertar_segmento_despues(sgm_c1,final_cadena(marge),marge);
			}
			else 
			{
				cadena_t sgm_c2 = segmento_cadena(loc_c2,final_cadena(c2),c2);
				insertar_segmento_despues(sgm_c2,final_cadena(marge),marge);		
			}
		}
	}
	return marge;
}

void remover_de_cadena(localizador_t &loc, cadena_t &cad)
{
	assert(localizador_en_cadena(loc, cad));
	if (es_inicio_cadena(loc,cad))
	{
		localizador_t loc_inicio = siguiente(inicio_cadena(cad), cad);
		loc_inicio->anterior = NULL;
		cad->inicio = loc_inicio;
	}
	else if (es_final_cadena(loc, cad))
	{
		localizador_t loc_fin = anterior(final_cadena(cad),cad);
		loc_fin->siguiente = NULL;
		cad->final = loc_fin;
	}
	else
	{
		localizador_t loc_anterior = anterior(loc,cad);
		localizador_t loc_siguiente = siguiente(loc,cad);
		loc_anterior->siguiente = loc_siguiente;
		loc_siguiente->anterior = loc_anterior; 
	}
	info_t info_loc = info_cadena(loc,cad);
	liberar_info(info_loc);
	delete(loc);
	loc = NULL;
	if (!es_localizador(cad->inicio)) cad->final = NULL;
}


void liberar_cadena(cadena_t &cad)
{
	nodo *a_borrar;
	while(cad->inicio != NULL)
	{
		a_borrar = cad->inicio;
		cad->inicio = cad->inicio->siguiente;
		liberar_info(a_borrar->dato);
		delete(a_borrar);
	}
	delete(cad);
}

bool es_localizador(localizador_t loc)
{
	return (loc != NULL);
}

bool es_vacia_cadena(cadena_t cad)
{
	return (cad->inicio == NULL) && (cad->final == NULL);
}

bool esta_ordenada(cadena_t cad)
{
	bool res = true;
	if (!es_vacia_cadena(cad))
	{
		localizador_t loc = inicio_cadena(cad);
		while(res && es_localizador(siguiente(loc,cad)))
		{
			localizador_t loc_sig = siguiente(loc,cad);
			if ( numero_info(info_cadena(loc,cad)) >
				numero_info(info_cadena(loc_sig,cad)) )
				res = false;
			else
				loc = siguiente(loc,cad);
		}
	}
	return res;
}

bool es_final_cadena(localizador_t loc, cadena_t cad)
{
	return (loc == final_cadena(cad));
}

bool es_inicio_cadena(localizador_t loc, cadena_t cad)
{
	return (loc == inicio_cadena(cad));	
}

bool localizador_en_cadena(localizador_t loc, cadena_t cad)
{
	bool loc_find = false;
	if (!es_vacia_cadena(cad) && es_localizador(loc))
	{
		localizador_t cursor = inicio_cadena(cad);
		
		while( (es_localizador(cursor) ) && (!loc_find) )
		{
			if (son_iguales(loc->dato,cursor->dato)) loc_find = true;
			cursor = cursor->siguiente;
		}
	}
	return loc_find;
}

bool precede_en_cadena(localizador_t loc1, localizador_t loc2, cadena_t cad)
{
	localizador_t cursor = loc1;
	while(es_localizador(cursor) && cursor != loc2)
	cursor = siguiente(cursor,cad);
	
	return ( (cursor == loc2) && (localizador_en_cadena(loc1,cad) ) );
}

localizador_t inicio_cadena(cadena_t cad)
{
	localizador_t inicio;

	if (!es_vacia_cadena(cad))inicio = cad->inicio;
	else inicio = NULL;

	return inicio;
}

localizador_t final_cadena(cadena_t cad)
{
	localizador_t final;
	if (!es_vacia_cadena(cad)) final = cad->final;
	else final = NULL;

	return final;
}

localizador_t kesimo(nat k, cadena_t cad)
{
	localizador_t loc_k = NULL;
	if (k > 0)
	{
		loc_k = inicio_cadena(cad);
		k--;
		while( k != 0 && es_localizador(loc_k))
		{
			loc_k = siguiente(loc_k,cad);
			k--;
		}	
		if (k != 0 && !es_localizador(loc_k)) loc_k = NULL;
	}
	return loc_k;
}

localizador_t siguiente(localizador_t loc, cadena_t cad)
{
	assert(localizador_en_cadena(loc, cad));
	localizador_t loc_sig = NULL;
	if(!es_final_cadena(loc,cad)) loc_sig = loc->siguiente;
	return loc_sig;
}

localizador_t anterior(localizador_t loc, cadena_t cad)
{
	assert(localizador_en_cadena(loc, cad));
	localizador_t loc_ant = NULL;
	if(!es_inicio_cadena(loc,cad)) loc_ant = loc->anterior;
	return loc_ant;
}

localizador_t menor_en_cadena(localizador_t loc, cadena_t cad)
{
	assert(localizador_en_cadena(loc, cad));
	localizador_t res = loc;
	while(es_localizador(siguiente(loc,cad)))
	{
		loc = siguiente(loc,cad);
		if (numero_info(info_cadena(loc,cad)) < numero_info(info_cadena(res,cad)))
		res = loc;
	}
	return res;
}

localizador_t siguiente_clave(int clave, localizador_t loc, cadena_t cad)
{
	assert(es_vacia_cadena(cad) || localizador_en_cadena(loc,cad));
	localizador_t res = loc;
	if (es_vacia_cadena(cad))
		res = NULL;
	else
	{
		while(es_localizador(res) && numero_info(info_cadena(res,cad)) != clave )
		res = siguiente(res,cad);
	}
	return res;
}

localizador_t anterior_clave(int clave, localizador_t loc, cadena_t cad)
{
	assert(es_vacia_cadena(cad) || localizador_en_cadena(loc,cad));
	localizador_t res = loc;
	if (es_vacia_cadena(cad))
		res = NULL;
	else
	{
		while(es_localizador(res) && numero_info(info_cadena(res,cad)) != clave )
		res = anterior(res,cad);
	}
	return res;
}

info_t info_cadena(localizador_t loc, cadena_t cad)
{
	//assert(localizador_en_cadena(loc, cad));
	return loc->dato;
}
void cambiar_en_cadena(info_t i, localizador_t loc, cadena_t &cad)
{
	assert(localizador_en_cadena(loc, cad));
	loc->dato = i;
}
void intercambiar(localizador_t loc1, localizador_t loc2, cadena_t &cad)
{
	assert(localizador_en_cadena(loc1, cad) && localizador_en_cadena(loc2, cad) );
	info_t swap_info = info_cadena(loc2,cad);
	cambiar_en_cadena(info_cadena(loc1,cad),loc2,cad);
	cambiar_en_cadena(swap_info,loc1,cad);
}

void imprimir_cadena(cadena_t cad)
{
	localizador_t cursor = inicio_cadena(cad);
	
	while(es_localizador(cursor) )
	{
	
		char *text = info_a_texto(info_cadena(cursor,cad));
		for (unsigned t = 0; t < strlen(text); t++) printf("%c",text[t]);
		cursor = siguiente(cursor,cad);
	}
	printf("\n");
} 