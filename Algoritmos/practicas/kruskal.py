#Lista de pares key/value
padre = dict()
costos = dict()

#BUSCAR ARBOL MINIMO 

#Crea listas key/value con los nodos y asigna costos
def armar_serie(nodo):
    padre[nodo] = nodo
    costos[nodo] = 0

#Busca el nodo padre del ingresado y lo retorna
def search(nodo):
    if padre[nodo] != nodo:
        padre[nodo] = search(padre[nodo])
    return padre[nodo]

#Toma la decisión de tomar los nodos con la menor arista
def union(nodo1, nodo2):
    
    #Toma la raiz de cada nodo
    raiz1 = search(nodo1)
    raiz2 = search(nodo2)
    #Corrobora que el padre de los nodos sea distinto para no crear ciclos
    if raiz1 != raiz2:
        #Comprueba que el costo que almacena la llave costos[raiz1] sea mayor
        #de serlo, se almacena raiz1 en la llave padre[raiz2]
        if costos[raiz1] > costos[raiz2]:

            #Asigna un nodo el nodo de destino a la tupla 
            #Si raiz1 == A y raiz2 == C se almacena en la lista padre el valor "C:A"
            padre[raiz2] = raiz1

        else:
            padre[raiz1] = raiz2

            if costos[raiz1] == costos[raiz2]: 
                costos[raiz2] += 1


def kruskal(grafo):
    for nodo in grafo['nodos']:
        armar_serie(nodo)

    #Longitud minima recorrida
    lmr = 0
    arbol_minimo = list()
    #Transforma las aristas en listas
    aristas = list(grafo['aristas'])
    #Ordena las aristas de menos a mayor
    aristas.sort()

    #Recorre las aristas ordenadas
    for arista in aristas:
        costo, nodo1, nodo2 = arista

        if search(nodo1) != search(nodo2):
            union(nodo1, nodo2)
            #Agrega la arista a la lista
            lmr = lmr +costo 
            arbol_minimo.append(arista)

    return arbol_minimo,lmr

#Grafo a recorrer
grafo = {
        'nodos': ['A','B','C','D','E','F','G','H','I'],
        'aristas': [
            (4,'A','B'),(8,'A','H'),
            (11,'B','H'),(8,'B','C'),
            (7,'C','D'),(4,'C','F'),(2,'C','I'),
            (14,'D','F'),(9,'D','E'),
            (10,'E','F'),
            (2,'F','G'),
            (1,'G','H'),(6,'G','I'),
            (7,'H','I')
            ]
        }
recorrido, lmr = kruskal(grafo)
print ("Recorrido: ")
for x in recorrido:
    print(x[1]+" -> "+x[2]+" Costo: "+str(x[0]))

print ("Costo total: ",lmr)
