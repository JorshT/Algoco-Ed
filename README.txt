El código principal se encuentra en el archivo main.cpp. Compilar utilizando linux: g++ main.cpp -o out -Wall
Para ejecutar el código ya compilado: ./out

En la carpeta de test_cases se encuentra un archivo python que genera las matrices de costos utilizadas en el main.cpp.

Los 4 casos de prueba, para un mayor control de las pruebas, fueron diseñados por mi a mano.
El Caso_1 corresponde a pruebas en donde se comparan strings con uno o dos caracteres y otro string con
mas palabras, ésto con el fin de ver que pasa en estos casos.

El Caso_2 corresponde a calcular la ed entre dos strings ambos con mayor numero de caracteres para ver que pasa 
cuando tienen distintos caracteres, otros muy parecidos y otros no tan parecidos.

El Caso_3 contiene ejemplos regulares en donde es posible en varios casos la transposicion, esto con el fin
de ver como impacta esta operacion en los resultados.

El Caso_4 contiene ejemplos generales o cotidianos.