IA-Entrega 2

Nombre: Ignacio Andrés Cofré Velarde
Rol:    201473607-K

Librerias usadas:

    No se utilizan librerias externas a C++, las librerias usadas son las siguientes: 

        <fstream>		//lectura y escritura de archivos
        <iostream>
        <string>
        <algorithm>     //funcion find()
        <regex>         //parseo archivo
        <random>        //números random
        <cstdio>		//timer
        <ctime> 		//timer 
        <sstream>		//input 

Uso del algoritmo:

    Para ejecutar el algoritmo se debe ir por consola a la carpeta donde se encuentre el codigo.
    Luego, se puede ejecutar el código con el comando

        make

    Para borrar los ejecutables y los archivos output.tex y log.txt se debe ejecutar el siguiente comando:

        make clean

    Una vez ya ejecutado el programa, se le pedirá si desea usar la configuración por defecto o no:
        y : utiliza la configuracion por defecto
        n : utiliza configuración manual
    
    En caso de seleccionar la configuración por defecto, se utilizaran los siguiente parametros:
        Instancia:      5
        N° reinicios:   100
        Vecindarios:    50
        Vecinos:        50

    El tiempo de ejecucion del caso por defecto es de alrededor de 150 segundos.

    En caso contrario se le pedira ingresar:
        Número de la instancia a utilizar: debe ser un numero desde el 1 al 24.
        Número de reinicios: debe ser un número igual o mayor a 0.
        Número de vecindarios: corresponde a la cantidad de vecindarios visitados por cada reinicio, debe ser un número mayor a 0.
        Número de vecinos: corresponde a la poblacion de cada vecindario, debe ser un número mayor a 0.

    Las intancias ya se encuentran en la carpera "Instances"    


Archivos de salida: El programa genera dos archivos de salida.
    output.txt  : archivo con el formato que se pide sobre la solución y costos involucrados.
    logs.txt     : archivo con informacion sobre la configuracion utilizada en cada ejecucion del programa.