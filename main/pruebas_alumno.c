#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* ----------------------------------- FUNCIONES AUXILIARES --------------------------------- */
int comparar_enteros(const void* n1, const void* n2){
	if(*(int*)n1 < *(int*)n2){
		return -1;
	}
	if(*(int*)n1 == *(int*)n2){
		return 0;
	}
	return 1;
}

/* ----------------------------------------- PRUEBAS ---------------------------------------- */
void pruebas_heap_vacio(){
	printf("\n-------------- PRUEBAS HEAP VACIO --------------\n");
	heap_t* heap = heap_crear(comparar_enteros);

	print_test("El heap fue creado correctamente", heap != NULL);
	print_test("El heap tiene 0 elementos", heap_cantidad(heap) == 0);
	print_test("El heap está vacío", heap_esta_vacio(heap));
	print_test("Ver máximo de un heap vacío devuelve NULL", heap_ver_max(heap) == NULL);
	print_test("Desencolar un heap vacío devuelve NULL", heap_desencolar(heap) == NULL);
	
	heap_destruir(heap, NULL);
	print_test("El heap fue destruido correctamente", true);
}

void pruebas_heap_encolar_null(){
	printf("\n --------------------- PRUEBAS NULL -----------------------\n");
	heap_t* heap = heap_crear(comparar_enteros);
	print_test("El heap se creó correctamente", heap != NULL);

	print_test("No se puede encolar NULL", !heap_encolar(heap, NULL));
	print_test("La cantidad es 0", heap_cantidad(heap) == 0);
	print_test("El heap está vacío", heap_esta_vacio(heap));
	print_test("Ver máximo de un heap vacío es NULL", !heap_ver_max(heap));

	heap_destruir(heap,NULL);
	print_test("El heap fue destruido correctamente", true);
}

void pruebas_unitarias(){
	printf("\n------------------ PRUEBAS UNITARIAS -------------------\n");
	heap_t* heap = heap_crear(comparar_enteros);
	int uno = 1;

	print_test("El heap fue creado correctamente", heap != NULL);
	print_test("Encolo 'uno' al heap", heap_encolar(heap, &uno));
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	print_test("El heap tiene un elemento", heap_cantidad(heap) == 1);
	print_test("El máximo del heap es 'uno'", heap_ver_max(heap) == &uno);
	
	print_test("Desencolar devuelve 'uno'", heap_desencolar(heap) == &uno);
	print_test("La cantidad de elementos del heap es 0", heap_cantidad(heap) == 0);
	print_test("El heap está vacío", heap_esta_vacio(heap));
	print_test("Ver máximo devuelve NULL", heap_ver_max(heap) == NULL);

	heap_destruir(heap, NULL);
	print_test("El heap fue destruido correctamente", true);
}

void pruebas_heap_algunos_elementos(){

	printf("\n----------------- PRUEBAS ALGUNOS ELEMENTOS ---------------\n");
	heap_t* heap = heap_crear(comparar_enteros);
	int uno = 1;
	int dos = 2;
	int tres = 3;
	int tresb = 3;

	print_test("El heap se creó correctamente", heap != NULL);
	print_test("Encolo 'uno'", heap_encolar(heap, &uno));
	print_test("El heap no está vacio", !heap_esta_vacio(heap));
	print_test("El heap tiene un elemento", heap_cantidad(heap) == 1);
	print_test("El máximo es 'uno'", heap_ver_max(heap) == &uno);
	print_test("Desencolar es 'uno'", heap_desencolar(heap) == &uno);
	print_test("La cantidad de elementos del heap es 0", heap_cantidad(heap) == 0);
	print_test("El heap está vacío", heap_esta_vacio(heap));

	print_test("Encolo 'uno'", heap_encolar(heap, &uno));
	print_test("El heap no está vacio", !heap_esta_vacio(heap));
	print_test("El heap tiene un elemento", heap_cantidad(heap) == 1);
	print_test("El máximo es 'uno'", heap_ver_max(heap) == &uno);

	print_test("Encolo 'dos'", heap_encolar(heap, &dos));
	print_test("El heap no está vacio", !heap_esta_vacio(heap));
	print_test("El heap tiene dos elementos", heap_cantidad(heap) == 2);
	print_test("El máximo es 'dos'", heap_ver_max(heap) == &dos);

	print_test("Encolo 'tres'", heap_encolar(heap, &tres));
	print_test("El heap no está vacio", !heap_esta_vacio(heap));
	print_test("El heap tiene tres elementos", heap_cantidad(heap) == 3);
	print_test("El máximo es 'tres'", heap_ver_max(heap) == &tres);

	print_test("Encolo 'tresb'", heap_encolar(heap, &tresb));
	print_test("El heap no está vacio", !heap_esta_vacio(heap));
	print_test("El heap tiene cuatro elementos", heap_cantidad(heap) == 4);
	print_test("El máximo es 'tres'", heap_ver_max(heap) == &tres); //por como está definido upheap

	print_test("Desencolar es tres", heap_desencolar(heap) == &tres);
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	print_test("El heap tiene 3 elementos", heap_cantidad(heap) == 3);
	print_test("El máximo es tresb", heap_ver_max(heap) == &tresb);

	print_test("Desencolar es tresb", heap_desencolar(heap) == &tresb);
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	print_test("El heap tiene 2 elementos", heap_cantidad(heap) == 2);
	print_test("El máximo es dos", heap_ver_max(heap) == &dos);

	print_test("Desencolar es dos", heap_desencolar(heap) == &dos);
	print_test("El heap no está vacío", !heap_esta_vacio(heap));
	print_test("El heap tiene 1 elemento", heap_cantidad(heap) == 1);
	print_test("El máximo es uno", heap_ver_max(heap) == &uno);

	print_test("Desencolar es uno", heap_desencolar(heap) == &uno);
	print_test("El heap está vacío", heap_esta_vacio(heap));
	print_test("El heap tiene 0 elementos", heap_cantidad(heap) == 0);
	print_test("El máximo es NULL", heap_ver_max(heap) == NULL);
	print_test("Desencolar es NULL", heap_desencolar(heap) == NULL);
	
	heap_destruir(heap,NULL);
	print_test("El heap se destruyó correctamente", true);
}

bool pruebas_heap_volumen(size_t tam){
	printf("\n------------------- PRUEBAS DE VOLUMEN --------------------\n");
	int vector[tam];
	
	for(int i = 0; i < tam; i++){
		vector[i] = i;
	}

	heap_t* heap = heap_crear(comparar_enteros);
	if(!heap){
		return false;
	}

	bool estado = true;

	for(int i = 0; i < tam; i++){
		if(!heap_encolar(heap, &vector[i]) || heap_ver_max(heap) != &vector[i]){
			estado = false;
		}
	}
	
	for(int i = 1; i <= tam; i++){
		if(heap_ver_max(heap) != &vector[tam - i] || heap_desencolar(heap) != &vector[tam - i]){
			estado = false;
		}
	}

	heap_destruir(heap, NULL);
	return estado;
}

bool pruebas_arreglo_a_heap(size_t tam){
	printf("\n --------------------- PRUEBAS HEAP ARR ------------------\n");
	int vector[tam];

	for(int i = 0; i < tam; i++){
		vector[i] = i;
	}

	int* ptr_a_vec[tam];
	for(int i = 0; i < tam; i++){
		ptr_a_vec[i] = &vector[i];
	}

	bool estado = true;

	heap_t* heap = heap_crear_arr((void**)ptr_a_vec, tam, comparar_enteros);
	if(!heap){
		return false;
	}

	for(int i = 1; i <= tam; i++){
		if(heap_ver_max(heap) != ptr_a_vec[tam - i] || heap_desencolar(heap) != ptr_a_vec[tam - i]){
			estado = false;
		}
	}

	heap_destruir(heap,NULL);
	return estado;
}

bool pruebas_heap_sort(size_t tam){
	printf("\n ------------------- PRUEBAS DEL HEAPSORT -----------------\n");

	int vector[tam];
	int* ptr_a_vec[tam];
	bool estado = true;

	for(int i = (int)tam - 1; i >= 0; i--){
		vector[tam - i - 1] = i;
	}

	for(int i = 0; i < tam; i++){
		ptr_a_vec[i] = &vector[i];
	}

	heap_sort((void**)ptr_a_vec, tam, comparar_enteros);
	for(int i = 0; i < tam; i++){
		if(*(int*)ptr_a_vec[i] != i){
			estado = false;
		}
	}
	return estado;
}

void pruebas_heap_alumno(void){
	pruebas_heap_vacio();
	pruebas_heap_encolar_null();
	pruebas_unitarias();
	pruebas_heap_algunos_elementos();
	print_test("PRUEBAS DE VOLUMEN", pruebas_heap_volumen(10000));
	print_test("PRUEBA CONVERTIR ARREGLO A HEAP", pruebas_arreglo_a_heap(10000));
	print_test("PRUEBA HEAPSORT",pruebas_heap_sort(10000));
}
