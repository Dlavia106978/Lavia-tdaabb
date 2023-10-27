#include "pa2m.h"
#include <string.h>
#include "src/abb.h"

int comparar_elementos(void *elemento1, void *elemento2)
{
	if (elemento1 == NULL || elemento2 == NULL) {
		return 0;
	}

	return strcmp((char *)elemento1, (char *)elemento2);
}

void prueba_insercion_multiple()
{
	pa2m_nuevo_grupo("Prueba de inserción múltiple de elementos");

	abb_t *arbol = abb_crear(comparar_elementos);

	char *elementos[] = { "hola",	  "mundo",  "abb",  "binario",
			      "busqueda", "prueba", "arbol" };

	for (int i = 0; i < sizeof(elementos) / sizeof(elementos[0]); ++i) {
		arbol = abb_insertar(arbol, elementos[i]);
	}

	pa2m_afirmar(!abb_vacio(arbol),
		     "El árbol no está vacío después de la inserción múltiple");
	pa2m_afirmar(
		abb_tamanio(arbol) == sizeof(elementos) / sizeof(elementos[0]),
		"El tamaño del árbol es correcto después de la inserción múltiple");

	for (int i = 0; i < sizeof(elementos) / sizeof(elementos[0]); ++i) {
		pa2m_afirmar(
			abb_buscar(arbol, elementos[i]) != NULL,
			"El elemento insertado se puede encontrar en el árbol");
	}

	abb_destruir(arbol);
}

void prueba_creacion_arbol()
{
	pa2m_afirmar(1, "Prueba de creación de árbol");

	abb_t *arbol = abb_crear(comparar_elementos);

	pa2m_afirmar(arbol != NULL, "El árbol se crea correctamente");
	pa2m_afirmar(abb_vacio(arbol),
		     "El árbol está vacío después de la creación");

	abb_destruir(arbol);
}

void prueba_insercion_elemento()
{
	pa2m_nuevo_grupo("Prueba de inserción de elementos");

	abb_t *arbol = abb_crear(comparar_elementos);

	char *elemento = "ejemplo";
	arbol = abb_insertar(arbol, elemento);

	pa2m_afirmar(!abb_vacio(arbol),
		     "El árbol no está vacío después de la inserción");
	pa2m_afirmar(abb_tamanio(arbol) == 1,
		     "El tamaño del árbol es 1 después de la inserción");
	pa2m_afirmar(abb_buscar(arbol, elemento) != NULL,
		     "El elemento insertado se puede encontrar en el árbol");

	abb_destruir(arbol);
}

void prueba_eliminacion_multiple()
{
	pa2m_nuevo_grupo("Prueba de eliminación de múltiples elementos");

	abb_t *arbol = abb_crear(comparar_elementos);

	char *elementos[] = { "hola",	  "mundo",  "abb",  "binario",
			      "busqueda", "prueba", "arbol" };

	for (int i = 0; i < sizeof(elementos) / sizeof(elementos[0]); ++i) {
		arbol = abb_insertar(arbol, elementos[i]);
	}

	abb_quitar(arbol, "prueba");
	abb_quitar(arbol, "hola");
	abb_quitar(arbol, "arbol");

	pa2m_afirmar(abb_buscar(arbol, "prueba") == NULL,
		     "El elemento 'prueba' ha sido eliminado correctamente");
	pa2m_afirmar(abb_buscar(arbol, "hola") == NULL,
		     "El elemento 'hola' ha sido eliminado correctamente");
	pa2m_afirmar(abb_buscar(arbol, "arbol") == NULL,
		     "El elemento 'arbol' ha sido eliminado correctamente");

	pa2m_afirmar(abb_buscar(arbol, "mundo") != NULL,
		     "El elemento 'mundo' está presente en el árbol");
	pa2m_afirmar(abb_buscar(arbol, "abb") != NULL,
		     "El elemento 'abb' está presente en el árbol");
	pa2m_afirmar(abb_buscar(arbol, "binario") != NULL,
		     "El elemento 'binario' está presente en el árbol");
	pa2m_afirmar(abb_buscar(arbol, "busqueda") != NULL,
		     "El elemento 'busqueda' está presente en el árbol");

	abb_destruir(arbol);
}

void prueba_eliminacion_elementos_no_existentes()
{
	pa2m_nuevo_grupo("Prueba de eliminación de elementos no existentes");

	abb_t *arbol = abb_crear(comparar_elementos);

	char *elementos[] = { "hola",	  "mundo",  "abb",  "binario",
			      "busqueda", "prueba", "arbol" };

	for (int i = 0; i < sizeof(elementos) / sizeof(elementos[0]); ++i) {
		arbol = abb_insertar(arbol, elementos[i]);
	}

	pa2m_afirmar(abb_quitar(arbol, "no_existente_1") == NULL,
		     "Intento de eliminar elemento no existente 1");
	pa2m_afirmar(abb_quitar(arbol, "no_existente_2") == NULL,
		     "Intento de eliminar elemento no existente 2");

	for (int i = 0; i < sizeof(elementos) / sizeof(elementos[0]); ++i) {
		pa2m_afirmar(abb_buscar(arbol, elementos[i]) != NULL,
			     "El elemento original está presente en el árbol");
	}

	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo("PRUEBAS DEL ÁRBOL BINARIO DE BÚSQUEDA");
	prueba_creacion_arbol();
	prueba_insercion_elemento();
	prueba_insercion_multiple();
	prueba_eliminacion_multiple();
	prueba_eliminacion_elementos_no_existentes();
	return pa2m_mostrar_reporte();
}
