# TDA ABB

## Repositorio de (Nombre Apellido) - (Padrón) - (Mail)

- Para compilar:
bash .algo2/test.sh

---
##  Funcionamiento

Explicación de cómo funcionan las estructuras desarrolladas en el TP y el funcionamiento general del mismo.

Aclarar en esta parte todas las decisiones que se tomaron al realizar el TP, cosas que no se aclaren en el enunciado, fragmentos de código que necesiten explicación extra, etc.

Incluír **EN TODOS LOS TPS** los diagramas relevantes al problema (mayormente diagramas de memoria para explicar las estructuras, pero se pueden utilizar otros diagramas si es necesario).

### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---



arbol: es un conjunto de nodos conectador por aristas, cada arbol tiene un nodo llamado raiz, a partir de este nodo se ramifican los demas nodos, estos nodos se dividen en niveles, los nodos que se encuentran en el mismo nivel de llaman nodos hermanos, un nodo de un nivel superior se llama padre y los nodos de niveles inferies se llaman hijos

arbol binario: en este cada nodo puede tener como maximo dos hijos, estos son el hijo izquierdo y el hijo derecho. hay 3 formas de recorrer un arbol binario: estas son preorden (raiz, izquierda, derecha), inorden (izquierda, raiz, derecha), postorden (izquierda, derecha, raiz)

arbol binario de busqueda: este es un tipo especifico de arbol binario, todos los nodos del lado izquierdo tienen valores menores que el nodo actual, y en el cado de los nodos del lado derecho tienen valores mayores. En este tipo de arbol las busquedas son mas eficientes ya que se puede descartar la mitad de un arbol en cada paso de la busqueda

las operaciones basicas de un arbol binario de busqueda son
insercion, esta consiste en añadir un nuevo nodo al arbol manteniendo las propiedades del mismo, O(log n) siendo n el valor de nodos en el arbol
busqueda,  esta conciste en buscar un nodo con un valor especifico en el arbol, O(log n)
eliminacion, consiste en eliminar un nodo especifico, O(log n)
recorridos, recorre todos los nodos del arbol en un orden especifico (preorden, inorden y postorden) O(n)


stack: se utiliza para almacenar variables locales e informarcion temporal, en mi codigo lo he utilizado en abb_insertar_rec con las variables nodo_actual y nodo_insertado, cuando la funcion termina estas variables se eliminan del stack

heap: se utiliza para la memoria dinamica, los datos que se guardan siguen existiendo luego de que la funcion termine, uso malloc y free para asignar y liberar memoria, en mi programa lo he utilizado por ejemplo en abb_insertar, con la variable nodo_a_insertar


diagrama:

main -> variables locales en el stack (ejemplo nodo_actual y nodo_insertado)

variables locales en el stack (ejemplo nodo_actual y nodo_insertado) -> llamo a abb_crear() 
estructura del arbol en el heap

llamo a abb_crear() -> nodo en el heap (nodo_a_insertar)

 nodo en el heap (nodo_a_insertar) -> abb_destruir, libero la memoria en el heap




