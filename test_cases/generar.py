from random import randint
import numpy as np



# matriz de costos


n = 300 


costos_sustitucion = np.random.randint(1,6,size=(n,n))

costo_transposicion = np.random.randint(1,6,size=(n,n))

costo_insert = np.random.randint(1,5,size=n)

costo_delete = np.random.randint(1,5,size=n)


#np.fill_diagonal(costo_transposicion, 0)
#np.fill_diagonal(costos_sustitucion, 0)

with open("cost_insert.txt","w") as archivo:
    archivo.write(str(n)+"\n")
    for elem in costo_insert:
        archivo.write(str(elem)+"\n")


with open("cost_delete.txt","w") as archivo:
    archivo.write(str(n)+"\n")
    for elem in costo_delete:
        archivo.write(str(elem)+"\n")

with open("cost_replace.txt","w") as archivo:
    archivo.write(str(n)+"\n")
    for elems in costos_sustitucion:
        for elem in elems:
            archivo.write(str(elem)+" ")
        archivo.write("\n")

with open("cost_transpose.txt","w") as archivo:
    archivo.write(str(n)+"\n")
    for elems in costo_transposicion:
        for elem in elems:
            archivo.write(str(elem)+" ")
        archivo.write("\n")



