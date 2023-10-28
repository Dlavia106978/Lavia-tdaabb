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

void probar_abb_buscar()
{
	pa2m_nuevo_grupo("Pruebas de abb_buscar");

	abb_t *arbol = abb_crear(comparar_elementos);

	pa2m_afirmar(abb_buscar(arbol, "hola") == NULL,
		     "Buscar en un árbol vacío");

	abb_insertar(arbol, "hola");
	abb_insertar(arbol, "mundo");
	abb_insertar(arbol, "prueba");

	pa2m_afirmar(strcmp((char *)abb_buscar(arbol, "mundo"), "mundo") == 0,
		     "Buscar un elemento existente");

	pa2m_afirmar(abb_buscar(arbol, "openai") == NULL,
		     "Buscar un elemento que no está en el árbol");

	abb_destruir(arbol);
}

void probar_abb_quitar()
{
	pa2m_nuevo_grupo("Pruebas de abb_quitar");

	abb_t *arbol = abb_crear(comparar_elementos);

	abb_insertar(arbol, "hola");
	abb_insertar(arbol, "mundo");
	abb_insertar(arbol, "prueba");

	pa2m_afirmar(abb_quitar(arbol, "mundo") != NULL,
		     "Eliminar un elemento existente");
	pa2m_afirmar(abb_buscar(arbol, "mundo") == NULL,
		     "Verificar que el elemento eliminado no exista");

	pa2m_afirmar(abb_quitar(arbol, "openai") == NULL,
		     "Eliminar un elemento que no está en el árbol");

	abb_destruir(arbol);
}

bool imprimir_elemento(void *elemento, void *aux)
{
	printf("%s ", (char *)elemento);
	return true;
}

void probar_con_cada_elemento()
{
	pa2m_nuevo_grupo("Pruebas de abb_con_cada_elemento");

	abb_t *arbol = abb_crear(comparar_elementos);

	abb_insertar(arbol, "hola");
	abb_insertar(arbol, "mundo");
	abb_insertar(arbol, "prueba");

	pa2m_afirmar(abb_con_cada_elemento(arbol, 1, imprimir_elemento, NULL) ==
			     3,
		     "Recorrer en inorden e imprimir elementos");

	pa2m_afirmar(abb_con_cada_elemento(arbol, 2, imprimir_elemento, NULL) ==
			     3,
		     "Recorrer en postorden e imprimir elementos");

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
	probar_abb_buscar();
	probar_abb_quitar();
	probar_con_cada_elemento();
	return pa2m_mostrar_reporte();
}
