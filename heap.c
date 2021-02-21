#include "heap.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#define TAM_INI 10


/* ---------------------- FUNCIONES AUXILIARES ------------------------ */

void swap(void** arreglo, size_t a, size_t b){
	void* aux = arreglo[a];
	arreglo[a] = arreglo[b];
	arreglo[b] = aux;
}

void upheap(void** arreglo, size_t pos, cmp_func_t cmp){
	if(pos == 0){
		return;
	}
	size_t padre = (pos - 1) / 2;
	if(cmp(arreglo[padre], arreglo[pos]) < 0){
		swap(arreglo, padre, pos);
		upheap(arreglo, padre, cmp);
	}
}

void downheap(void** arreglo, size_t cantidad, size_t pos, cmp_func_t cmp){
	if(pos >= cantidad){
		return;
	}
	size_t mayor = pos;
	size_t hijo_izq = (pos * 2) + 1;
	size_t hijo_der = (pos * 2) + 2;
	if(hijo_izq < cantidad && cmp(arreglo[mayor], arreglo[hijo_izq]) < 0){
		mayor = hijo_izq;
	}
	if(hijo_der < cantidad && cmp(arreglo[mayor], arreglo[hijo_der]) < 0){
		mayor = hijo_der;
	}
	if(mayor != pos){
		swap(arreglo, pos, mayor);
		downheap(arreglo, cantidad, mayor, cmp);
	}
}

void heapify(void** arreglo, size_t cantidad, cmp_func_t cmp){
	for(size_t i = cantidad; i > 0; i--){
		downheap(arreglo, cantidad, i-1, cmp);
	}
}

/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heapify(elementos, cant, cmp);
	for(size_t i = 1; i <= cant; i++){
		swap(elementos, 0, cant-i);
		downheap(elementos, cant-i, 0, cmp);
	}
}

/* ------------------------------------------------------------------------
 * Implementación de un TAD cola de prioridad, usando un max-heap.
 *
 * Notar que al ser un max-heap el elemento mas grande será el de mejor
 * prioridad. Si se desea un min-heap, alcanza con invertir la función de
 * comparación.
 */

/* Tipo utilizado para el heap. */
struct heap{
	void** datos;
	size_t capacidad;
	size_t cant;
	cmp_func_t cmp;
};

/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap){
		return NULL;
	}
	void** datos = malloc(sizeof(void*) * TAM_INI);
	if(!datos){
		free(heap);
		return NULL;
	}
	heap->datos = datos;
	heap->capacidad = TAM_INI;
	heap->cant = 0;
	heap->cmp = cmp;
	return heap;
}

/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap){
		return NULL;
	}
	void** datos;
	if(n < TAM_INI){
		datos = malloc(sizeof(void*) * TAM_INI);
		heap->capacidad = TAM_INI;
	}
	else{
		datos = malloc(sizeof(void*) * (n * 2));
		heap->capacidad = n * 2;
	}
	if(!datos){
		free(heap);
		return NULL;
	}
	for(size_t i = 0; i < n; i++){
		datos[i] = arreglo[i];
	}
	heapify(datos, n, cmp);
	heap->datos = datos;
	heap->cant = n;
	heap->cmp = cmp;
	return heap;
}

/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if(destruir_elemento){
		for(size_t i = 0; i < heap->cant; i++){
			destruir_elemento(heap->datos[i]);
		}
	}
	free(heap->datos);
	free(heap);
}

/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	return heap->cant;
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){
	return heap->cant == 0;
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem){
	if (elem == NULL){
		return NULL;
	}
	if(heap->cant == heap->capacidad){
		void** datos = realloc(heap->datos, (heap->capacidad * 2) * sizeof(void*));
		if(!datos){
			return false;
		}
		heap->datos = datos;
		heap->capacidad = heap->capacidad * 2;
	}
	heap->datos[heap->cant] = elem;
	upheap(heap->datos, heap->cant, heap->cmp);
	heap->cant++;
	return true;
}

/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap){
	if(heap->cant == 0){
		return NULL;
	}
	return heap->datos[0];
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap){
	if(heap->cant == 0){
		return NULL;
	}
	if(heap->cant <= heap->capacidad / 4 && heap->capacidad > TAM_INI){
		void** datos = realloc(heap->datos, (heap->capacidad / 2) * sizeof(void*));
		if(datos){
			heap->datos = datos;
			heap->capacidad = heap->capacidad / 2;
		}
	}
	heap->cant--;
	swap(heap->datos, 0, heap->cant);
	downheap(heap->datos, heap->cant, 0, heap->cmp);
	return heap->datos[heap->cant];
}
