<h1>Sistemas Operativos: Laboratorio 3</h1>

Este repositorio contiene el tercer laboratorio del curso de Sistemas Operativos, principalmente enfocado en el manejo de hebras utilizando el sistema operativo Linux.

<h2>Laboratorio 3: Funciones Unix - hebras </h2>

Este laboratorio tiene como objetivo aplicar técnicas de programación imperativa mediante lenguaje C, como la recepción de parámetros mediante getopt y compilación mediante Makefile. Ademas de aplicar conocimiento adquiridos en catedra sobre Concurrencia, Multihebrado, y llamados al SO Linux de manera exitosa.

<h3>Autor: Nicolas Gajardo & Cristian Romero</h3>

<h3>Fecha: 19-12-2024</h3>

Cómo ejecutar este proyecto

0.Se requiere un sistema operativo linux-based.

1.Compilar mediante el comando <code>make</code>.

2.Para ejecutar debes estar conciente de las siguientes definiciones para los flags para los diferentes archivos:

<h3>Primer Programa archivo lab3.c</h3>

       -i: es el archivo de entrada 
       
       -o: es el archivo de salida
       
       -D: flag para mostrar por stdout el arreglo al finalizar
       
      
Ejemplo de comando para ejecutar:

              ./lab3 -i input.txt -o output.txt -D    

<h3>Segundo Programa "funciones.c"</h3>

En este programa se encuentran todas las funciones que el programa principal (lab3.c) hace llamado, se utiliza esta division para mayor entendimiento del codigo.
      
<h3>Tercer Programa "funciones.h"</h3>

En este programa se encuentran todas las funciones que el programa principal (lab3.c) hace llamado principalmente su definicion como encapsulamiento (cabecera), se utiliza esta division para mayor entendimiento del codigo.
Luego el programa principal hace llamado de este programa para traer todas las funciones a las cuales hace referencia.
Para ello se incluye en el programa principal el siguiente include:

              #include "funciones.h"
      
Obs: El programa está preparado para entregar los valores solicitados de ejemplo en la rubrica y divido en archivos llamado funciones.c y .h para su mayor entendimiento.

            
<h2>Descripción</h2>

Dado un arreglo de números enteros, de largo N, existe el problema de conocer cúal es el máximo valor que posee dicha colección de valores. Un enfoque de solución está dado por la utilización de hebras que permitan paralelizar el proceso de comparación de los valores del arreglo en cuestión. De esta forma, se debe crear una cantidad de hebras igual a la cantidad de posiciones que tenga el arreglo. En otras palabras, si el arreglo tiene 10 posiciones, entonces se deben crear 10 hebras.

Para esta aplicación, los números en el arreglo serán únicos. Es decir, no hay repeticiones.

<h2>Logica de la sólucion</h2>

1. El programa recibe, por línea de comando, el nombre del archivo que contiene los valores a estudiar, con el fin de crear un arreglo A de tamaño igual a la cantidad de números que tenga el archivo.
2. A continuación, se crea una cantidad de hebras igual al largo del arreglo A.
3. Cada hebra i almacenar a en una variable local myval, el valor inicial A[i].
4. Cada hebra i solo puede acceder a las posiciones i e i−1, y el arreglo se trata en forma circular.
5. Repetidamente, cada hebra i, compara A[i-1] con myval. Si A[i-1] es mayor que myval,
entonces copia A[i-1] en A[i].

6. Este proceso continúa, asíncronamente y concurrentemente, hasta que el valor máximo se haya propagado por todo el arreglo. Una vez suceda esto, el programa finaliza. Usted debe diseñar una estrategia eficiente de cómo detectar el fin de la iteración.
7. Al finalizar, el máximo estará en todas las posiciones del arreglo.
8. Sería muy ineficiente, en cada momento preguntar si el número es el mismo en todas las posiciones.
