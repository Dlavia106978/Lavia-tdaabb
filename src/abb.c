#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

void *buscar_predecesor(nodo_abb_t *nodo_actual);
bool con_cada_inorden(nodo_abb_t *nodo_actual, bool (*funcion)(void *, void *),
		      void *aux, size_t *veces_invocada);
bool con_cada_postorden(nodo_abb_t *nodo_actual,
			bool (*funcion)(void *, void *), void *aux,
			size_t *veces_invocada);
bool con_cada_preorden(nodo_abb_t *nodo_actual, bool (*funcion)(void *, void *),
		       void *aux, size_t *veces_invocada);
size_t rellenar_array_inorden(abb_t *arbol, void **array, size_t tamanio_array,
			      size_t index, nodo_abb_t *nodo_actual);
size_t rellenar_array_postorden(abb_t *arbol, void **array,
				size_t tamanio_array, size_t index,
				nodo_abb_t *nodo_actual);
size_t rellenar_array_preorden(abb_t *arbol, void **array, size_t tamanio_array,
			       size_t index, nodo_abb_t *nodo_actual);

abb_t *abb_crear(abb_comparador comparador)
{
	if (comparador == NULL) {
		return NULL;
	}

	abb_t *arbol = malloc(sizeof(abb_t));
	if (arbol != NULL) {
		arbol->nodo_raiz = NULL;
		arbol->comparador = comparador;
		arbol->tamanio = 0;
	}

	return arbol;
}

abb_t *abb_insertar_rec(abb_t *arbol, nodo_abb_t **nodo_actual,
			nodo_abb_t *nodo_insertado)
{
	if (*nodo_actual == NULL) {
		*nodo_actual = nodo_insertado;
		arbol->tamanio++;
		return arbol;
	}
	int comparacion = arbol->comparador((*nodo_actual)->elemento,
					    nodo_insertado->elemento);
	if (comparacion >= 0) {
		arbol = abb_insertar_rec(arbol, &((*nodo_actual)->izquierda),
					 nodo_insertado);
	} else {
		arbol = abb_insertar_rec(arbol, &((*nodo_actual)->derecha),
					 nodo_insertado);
	}
	return arbol;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}
	nodo_abb_t *nodo_a_insertar = malloc(sizeof(nodo_abb_t));
	if (!nodo_a_insertar) {
		return arbol;
	}
	nodo_a_insertar->elemento = elemento;
	nodo_a_insertar->derecha = NULL;
	nodo_a_insertar->izquierda = NULL;
	return abb_insertar_rec(arbol, &(arbol->nodo_raiz), nodo_a_insertar);
}
void *abb_quitar_rec(abb_t *arbol, nodo_abb_t **papa, nodo_abb_t **nodo_actual,
		     void *elemento)
{
	if (*nodo_actual == NULL) {
		return NULL;
	}

	int comparacion = arbol->comparador((*nodo_actual)->elemento, elemento);

	if (comparacion > 0) {
		return abb_quitar_rec(arbol, nodo_actual,
				      &((*nodo_actual)->izquierda), elemento);
	} else if (comparacion < 0) {
		return abb_quitar_rec(arbol, nodo_actual,
				      &((*nodo_actual)->derecha), elemento);
	} else {
		void *elemento_eliminado = (*nodo_actual)->elemento;
		nodo_abb_t *nodo_hijo = NULL;

		if ((*nodo_actual)->izquierda == NULL) {
			nodo_hijo = (*nodo_actual)->derecha;
		} else if ((*nodo_actual)->derecha == NULL) {
			nodo_hijo = (*nodo_actual)->izquierda;
		} else {
			void *predecesor = buscar_predecesor(*nodo_actual);
			(*nodo_actual)->elemento = predecesor;
			abb_quitar_rec(arbol, nodo_actual,
				       &((*nodo_actual)->izquierda),
				       predecesor);
			return elemento_eliminado;
		}

		free(*nodo_actual);

		if (papa == NULL) {
			arbol->nodo_raiz = nodo_hijo;
		} else if ((*papa)->izquierda == *nodo_actual) {
			(*papa)->izquierda = nodo_hijo;
		} else if ((*papa)->derecha == *nodo_actual) {
			(*papa)->derecha = nodo_hijo;
		}

		arbol->tamanio--;
		return elemento_eliminado;
	}
}

void *buscar_predecesor(nodo_abb_t *nodo_actual)
{
	if (!nodo_actual) {
		return NULL;
	}

	nodo_abb_t *siguiente = nodo_actual->izquierda;

	while (siguiente->derecha != NULL) {
		siguiente = siguiente->derecha;
	}

	return siguiente->elemento;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (!arbol) {
		return NULL;
	}

	return abb_quitar_rec(arbol, NULL, &(arbol->nodo_raiz), elemento);
}

void *abb_buscar_rec(abb_t *arbol, nodo_abb_t *nodo_actual, void *elemento)
{
	if (nodo_actual == NULL) {
		return NULL;
	}

	int comparacion = arbol->comparador(nodo_actual->elemento, elemento);
	if (comparacion == 0) {
		return nodo_actual->elemento;
	} else if (comparacion > 0) {
		return abb_buscar_rec(arbol, nodo_actual->izquierda, elemento);
	} else {
		return abb_buscar_rec(arbol, nodo_actual->derecha, elemento);
	}
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (!arbol || !arbol->nodo_raiz) {
		return NULL;
	}
	return abb_buscar_rec(arbol, arbol->nodo_raiz, elemento);
}

bool abb_vacio(abb_t *arbol)
{
	if (abb_tamanio(arbol) == 0) {
		return true;
	}
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol) {
		return 0;
	}
	return arbol->tamanio;
}

void abb_destruir_rec(abb_t *arbol, nodo_abb_t *nodo_actual,
		      void (*destructor)(void *))
{
	if (nodo_actual == NULL) {
		return;
	}
	abb_destruir_rec(arbol, nodo_actual->izquierda, destructor);
	abb_destruir_rec(arbol, nodo_actual->derecha, destructor);
	if (destructor != NULL) {
		destructor(nodo_actual->elemento);
	}
	free(nodo_actual);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL) {
		return;
	}
	abb_destruir_rec(arbol, arbol->nodo_raiz, destructor);
	free(arbol);
}
void abb_destruir(abb_t *arbol)
{
	if (arbol == NULL) {
		return;
	}

	abb_destruir_rec(arbol, arbol->nodo_raiz, NULL);
	free(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	size_t veces_invocada = 0;
	if (!arbol || !funcion) {
		return veces_invocada;
	}

	if (recorrido == INORDEN) {
		con_cada_inorden(arbol->nodo_raiz, funcion, aux,
				 &veces_invocada);
	} else if (recorrido == POSTORDEN) {
		con_cada_postorden(arbol->nodo_raiz, funcion, aux,
				   &veces_invocada);
	} else if (recorrido == PREORDEN) {
		con_cada_preorden(arbol->nodo_raiz, funcion, aux,
				  &veces_invocada);
	}

	return veces_invocada;
}

bool con_cada_inorden(nodo_abb_t *nodo_actual, bool (*funcion)(void *, void *),
		      void *aux, size_t *veces_invocada)
{
	if (nodo_actual == NULL) {
		return true;
	}
	if (con_cada_inorden(nodo_actual->izquierda, funcion, aux,
			     veces_invocada) == false) {
		return false;
	}
	(*veces_invocada)++;
	if (funcion(nodo_actual->elemento, aux) == false) {
		return false;
	}
	return con_cada_inorden(nodo_actual->derecha, funcion, aux,
				veces_invocada);
}

bool con_cada_postorden(nodo_abb_t *nodo_actual,
			bool (*funcion)(void *, void *), void *aux,
			size_t *veces_invocada)
{
	if (nodo_actual == NULL) {
		return true;
	}

	if (!con_cada_postorden(nodo_actual->izquierda, funcion, aux,
				veces_invocada)) {
		return false;
	}

	if (!con_cada_postorden(nodo_actual->derecha, funcion, aux,
				veces_invocada)) {
		return false;
	}

	(*veces_invocada)++;

	if (!funcion(nodo_actual->elemento, aux)) {
		return false;
	}

	return true;
}

bool con_cada_preorden(nodo_abb_t *nodo_actual, bool (*funcion)(void *, void *),
		       void *aux, size_t *veces_invocada)
{
	if (nodo_actual == NULL) {
		return true;
	}

	(*veces_invocada)++;

	if (!funcion(nodo_actual->elemento, aux)) {
		return false;
	}

	if (!con_cada_preorden(nodo_actual->izquierda, funcion, aux,
			       veces_invocada)) {
		return false;
	}

	if (!con_cada_preorden(nodo_actual->derecha, funcion, aux,
			       veces_invocada)) {
		return false;
	}

	return true;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (!arbol || !arbol->nodo_raiz) {
		return 0;
	}

	size_t index = 0;
	if (recorrido == INORDEN) {
		index = rellenar_array_inorden(arbol, array, tamanio_array,
					       index, arbol->nodo_raiz);
	} else if (recorrido == PREORDEN) {
		index = rellenar_array_preorden(arbol, array, tamanio_array,
						index, arbol->nodo_raiz);
	} else if (recorrido == POSTORDEN) {
		index = rellenar_array_postorden(arbol, array, tamanio_array,
						 index, arbol->nodo_raiz);
	}

	return index;
}
size_t rellenar_array_inorden(abb_t *arbol, void **array, size_t tamanio_array,
			      size_t index, nodo_abb_t *nodo_actual)
{
	if (nodo_actual == NULL || index >= tamanio_array) {
		return index;
	}
	index = rellenar_array_inorden(arbol, array, tamanio_array, index,
				       nodo_actual->izquierda);
	if (index < tamanio_array) {
		array[index] = nodo_actual->elemento;
		index++;
	}
	return rellenar_array_inorden(arbol, array, tamanio_array, index,
				      nodo_actual->derecha);
}

size_t rellenar_array_postorden(abb_t *arbol, void **array,
				size_t tamanio_array, size_t index,
				nodo_abb_t *nodo_actual)
{
	if (nodo_actual == NULL || index >= tamanio_array) {
		return index;
	}
	index = rellenar_array_postorden(arbol, array, tamanio_array, index,
					 nodo_actual->izquierda);
	index = rellenar_array_postorden(arbol, array, tamanio_array, index,
					 nodo_actual->derecha);
	if (index < tamanio_array) {
		array[index] = nodo_actual->elemento;
		index++;
	}
	return index;
}

size_t rellenar_array_preorden(abb_t *arbol, void **array, size_t tamanio_array,
			       size_t index, nodo_abb_t *nodo_actual)
{
	if (nodo_actual == NULL || index >= tamanio_array) {
		return index;
	}
	if (index < tamanio_array) {
		array[index] = nodo_actual->elemento;
		index++;
	}
	index = rellenar_array_preorden(arbol, array, tamanio_array, index,
					nodo_actual->izquierda);
	index = rellenar_array_preorden(arbol, array, tamanio_array, index,
					nodo_actual->derecha);
	return index;
}
