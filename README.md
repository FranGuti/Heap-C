# TDA Heap
Es un trabajo realizado durante la cursada de Algoritmos y Programación II.
El mismo consta de la implementación y desarrollo del Tipo de Dato Abstracto Heap en el lenguaje de programación C. 
Tiene como objetivo la creación de una Cola de prioridad de máximos para posterior uso como librería con un correcto manejo de memoria y la implementación de sus métodos:

 - Heap Crear
     > Crea y devuelve una Cola de prioridad vacía. Recibe una función de comparación que es la que se va a usar para discernir entre los elementos de los cuales va a estar constituido el Heap

 - Heap Crear Arr
    >Crea y devuelve una Cola de prioridad creada a partir de un arreglo recibido
    
 - Heap Destruir
    >Destruye la Cola de prioridad. Recibe un puntero a función para destruir los datos que almacena, en caso de ser NULL se destruye solo el Heap
    
 - Heap Cantidad
   > Devuelve la cantidad de elementos que contiene la Cola de prioridad
 
 - Heap Esta Vacío
   > Devuelve True si la Cola de prioridad está vacía, False en caso contrario

 - Heap Encolar
   > Recibe un elemento y lo almacena dentro de la Cola de prioridad

- Heap Ver Maximo
   > Devuelve el mayor elemento que contenga la Cola de prioridad
 
 - Heap Desencolar
   > Se remueve el elemento de maxima prioridad del Heap y se lo devuelve
  
También, de manera externa al TDA se crea el método Heap Sort
que recibe un arreglo, su largo, y un puntero a una función de comparación. El método le aplica Heap Sort y ordena el arreglo de manera in-place.

[Video que explica el funcionamiento de Heap Sort](https://www.youtube.com/watch?v=MtQL_ll5KhQ).

El Heap o Cola de prioridad es un Tipo de Dato Abstracto, representado en forma de arreglo o árbol, que almacena los elementos de una manera tal que siempre queda el elemento de mayor "prioridad" en la primera posición del arreglo. Lo ventajoso de esto es que se pueda acceder al elemento deseado en O(1). El elemento de mayor "prioridad" puede ser el elemento mas grande si es un Heap de máximos (como este caso) o el mas chico si es un Heap de Mínimos.

¿De que manera la Cola de prioridad almacena sus datos?

Básicamente, si lo pensamos como un árbol, el criterio de ordenación del Heap es que el elemento "padre" es mayor que el elemento "hijo" si es un max Heap y ,al revés, si es un min Heap, eso se puede ver fácilmente en la siguiente ilustración:![enter image description here](https://i0.wp.com/yoandroide.xyz/wp-content/uploads/2017/06/Min-Max-Heap-monticulos-como-usar-explicacion.png?fit=681,397&ssl=1)
