class MatrizAdyacencia:

    n = 0
    matriz = []
    def __init__(self,n):
        

        for i in range(0,n):
            aux = []
            for j in range(0,n):
                aux.append(0)
            self.matriz.append(aux)


    

    def add(self,i,j):
        self.matriz[i][j] += 1

    def remove(self,i,j):
        if self.matriz[i][j] > 0:
            self.matriz[i][j] -=1
        
    def printMatriz(self):
        for i in self.matriz:
            print(i)
            print(" ")


class Grafo:

    def __init__(self):
        pass

    def start(self):
    
        matriz = MatrizAdyacencia(3)

        print("Matriz vacia")

        matriz.printMatriz()

        print("Matriz llena")
        matriz.add(0,1)
        matriz.add(0,2)
        matriz.add(1,0)
        matriz.add(1,2)
        matriz.add(2,0)

        matriz.printMatriz()



Grafo().start()