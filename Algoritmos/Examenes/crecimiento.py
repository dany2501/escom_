

#x(t) = xo * b^t
from tabulate import tabulate as tab
import matplotlib.pyplot as plt

tabs = []
axisX = []
axisY = []
fig, ax = plt.subplots()

""" T será el día en el que se desea saber los contagios
    Aux son los contagios del día anterior """

def grow(t,aux):

    """ Verificamos si el día es menor o igual a 14 """
    if t <= 14:

        """ Se realiza el calculo de personas contagiadas """
        x = 1 * pow(2,t)

        """ Los datos se agregan a una lista para posteriormente ser mostrados en la tabla"""
        tabs.append(["Dia "+str(t),x - aux,str(x)+" = 2^"+str(t)])

        """ Agregamos los valores de los contagios para ser graficados en el eje Y """
        axisY.append(x)

        """ Agregamos los valores de los contagios para ser graficados en el eje X """
        axisX.append(t)

        """ Sumamos un día """
        t = t+1

        """Se vuelve a ejecutar la función"""
        grow(t,x)

    else:
        """ Imprimimos la tabla """
        print(tab(tabs,headers=["Día","Contagios nuevos","Total enfermos"],tablefmt="fancy_grid"))

        """ Se asignan los valores en los ejes antes de ser graficados """
        ax.scatter(axisX,axisY)
        ax.plot(axisX,axisY)
        """------------------------------------------------------------"""

        """ Agregamos las etiquetas en los ejes """
        ax.set_ylabel('Contagios')
        ax.set_xlabel('Días')
        """--------------------------------------"""

        """ Mostramos la grafica """
        plt.show()

        """Finalizamos el programa"""
        return

grow(0,0)