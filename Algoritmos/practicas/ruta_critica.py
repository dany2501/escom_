import string

"""
    Ruta critica por matriz de adyacencia
    Método BFS
"""

class RC(dict):

    duration = 0
    tut = 0
    tpt = 0
    tui = 0
    th = 0

    def __init__(self,duration,tut,tpt=0,tui=0,th=0):
        self.duration=duration
        self.tut = tut
        self.tpt=tpt
        self.tui=tui
        self.th=th
        dict.__init__(self,duration=duration,tut=tut,tpt=tpt,tui=tui,th=th)
        

class MatrizAdyacencia:

    n = 0
    matriz = {"graph":[]}

    visited = []
    queue = []
    ruta = ["A"]
    

    def __init__(self,n):
        for i in range(0,n):
            if i != 0:
                print("Ingresa los siguientes datos para la actividad #"+str(i))
                duration = input("Duración: ")
                tut = input("Tiempo último de terminación: ")
            else:
                duration = 0
                tut = 0

            rc = RC(duration,tut)
            aux = []
            for j in range(0,n):
                aux.append(0)

            x = chr(ord("A") + i)
            self.matriz["graph"].append({x:[aux,rc]})

    def add(self,i,j):
        x = chr(ord("A") + i)
        self.matriz["graph"][i][x][0][j] += 1

    def remove(self,i,j):
        if self.matriz["graph"][i][0][j] > 0:
            self.matriz["graph"][i][0][j] -=1
        
    def printMatriz(self):
        for i in self.matriz["graph"]:
            print(i)
            print(" ")

    def bfs(self,node):
      self.visited.append(node)
      self.queue.append(node)

      while self.queue:
        m = self.queue.pop(0)
        obj = self.matriz["graph"]
        print("Nodo actual",m)
        nodes = obj[string.ascii_uppercase.index(m)][m][0]
        rc = obj[string.ascii_uppercase.index(m)][m][1]
        #tpt = 
        for i,item in enumerate(nodes):
          l = chr(ord("A") + i)
          if item == 1:
              print("De nodo "+m+" a nodo "+l)
              data = obj[string.ascii_uppercase.index(l)][l][1]
              data["tpi"] = int(rc['tpt'])
              data['tpt'] = int(rc['tpt']) + int(data['duration'])
              data['tui'] = int(data['tut']) - int(data['duration'])
              data['th'] = int(data['tui']) - int(data['tpi'])
              if data['th'] == 0:
                  self.ruta.append(l)
              print(data)
                
          if l not in self.visited and item == 1:

              self.visited.append(l)
              self.queue.append(l)
        print("")
        
      print("====== Ruta critica ======")
      print(self.ruta)


class Grafo:

  matriz = None
    
  def __init__(self):
      pass


  def start(self):
  
      self.matriz = MatrizAdyacencia(7)

      print("Matriz vacia")

      self.matriz.printMatriz()

      print("Matriz llena")
      self.matriz.add(0,1)
      self.matriz.add(1,2)
      self.matriz.add(1,3)
      self.matriz.add(1,4)
      self.matriz.add(2,5)
      self.matriz.add(3,5)
      self.matriz.add(4,6)
      self.matriz.add(5,6)
      self.matriz.printMatriz()

      self.matriz.bfs("A")



Grafo().start()