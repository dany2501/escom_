import os
from time import sleep


def imprimir():
    ##os.system("cls")
    print("--------------Probabilidad y Estadistica--------------")
    print("")
    print("Menú")
    print("1-Probabilidad")
    print("2-Probabilidad Condicional")
    print("3-Independencia")
    print("4-Regla de bayes")
    print("5-Salir")
    print("")


def Probabilidad():
    ##os.system("cls")
    Text = "Probabilidad"
    print(Text.center(100))
    print()
    print("La probabilidad mide las posibilidades de que cada uno de los posibles resultados en un suceso que depende del azar sea finalmente el que se dé")
    print()
    """#os.system("pause")
    #os.system("cls")"""
    Text = "Probabilidad Simple - Problema"
    print(Text.center(100))
    print("Se tiran dos dados al azar.")
    suma = int(input(
        "Seleccione un numero para calcular las probabilidades de que la suma de los resultados, de ese numero: "))
    print("Calculando...")
    sleep(2)
    posibles = [1, 2, 3, 4, 5, 6]
    contador = 0
    for i in posibles:
        for j in posibles:
            if i + j == suma:
                contador = contador + 1
                print(f"{i} + {j}")

    resultado = (contador / 36)*100
    print(
        f"La probabilidad de que los resultados sumen ese valor es de : {resultado:.2f}%")

    #os.system("pause")


def Probabilidad_condicional():
    #os.system("cls")
    Text = "Probabilidad condicional"
    print(Text.center(100))
    print()
    print("Probabilidad condicional es la probabilidad de que ocurra un evento A, sabiendo que también sucede otro evento B.")
    print("La probabilidad condicional se escribe P(A|B) o P(A/B), y se lee «la probabilidad de A dado B».")
    print("No tiene por qué haber una relación causal o temporal entre A y B.")
    print()
    #os.system("pause")
    #os.system("cls")
    Text = "Probabilidad Condicional - Problema"
    print(Text.center(100))
    print("Se lanzan dos dados, desafortunadamente, uno esta cargado para obtener un resultado")
    cargado = int(
        input("Seleccione el numero que siempre cae en el dado cargado: "))
    suma = int(input(
        "Seleccione un numero para calcular las probabilidades de que la suma de los resultados, de ese numero: "))
    print("Calculando...")
    sleep(2)
    posibles = [1, 2, 3, 4, 5, 6]
    contador1 = 0
    contador2 = 0
    contador3 = 0
    # Probabilidad de A
    print(f"salidas que suman {suma}: ")
    for i in posibles:
        for j in posibles:
            if i + j == suma:
                contador1 = contador1 + 1
                print(f"{i} + {j}")

    # Probabilidad de B
    print(f"salidas con el dado cargado en {cargado}: ")
    for i in posibles:
        for j in posibles:
            if i == cargado:
                print(f"{i} + {j}")
                contador3 = contador3 + 1

    # Probabilidad de A Interseccion B
    print(f"salidas con el dado cargado que suman {suma}: ")
    for i in posibles:
        if cargado + i == suma:
            contador2 = contador2 + 1
            print(f"3 + {i}")

    # Probabilidad condicional A de B
    print(f"probabilidad de A = {contador1}/36")
    print(f"probabilidad de B = {contador3}/36")
    print(f"probabilidad de A interseccion B = {contador2}/36")

    interseccion = contador2 / 36
    prob_b = contador3 / 36
    resultado = ((interseccion) / (prob_b)) * 100
    print(f"El resultado de (A|B) es ={resultado:.2f}%")

    #os.system("pause")


def Independencia():
    ##os.system("cls")
    canicas = {"rojo":4,"verde":3,"azul":2}
    red = 4
    green = 3
    blue = 2 
    em = red+green+blue
    Text = "Problema de Independencia.\n"
    print(Text.center(100))
    print("En teoría de probabilidades, se dice que dos sucesos aleatorios son independientes entre sí")
    print("cuando la probabilidad de cada uno de ellos no está influida porque el otro suceso ocurra o no.")
    print("Es decir, cuando ambos sucesos no están relacionados.\n")
    print("Se dice que A y B son independientes sí y sólo si\n")
    print("p(A∩B) = p(A)⋅p(B)\n".center(100))

    Text = "Independencia - Problema\n"
    print(Text.center(100))
    print("Una caja contiene 4 canicas rojas, 3 canicas verdes y 2 canicas azules.")
    first = str(input("¿Que color quieres sacar primero?\n")).lower()
    second = str(input("¿Que color quieres sacar despues del color "+first+"?\n")).lower()
    print("Calculando la probabilidad de que la primera sea color "+first+" y la segunda sea color "+second+"\n")
    sleep(2)
    print("----------Solución----------\n")
    p = "P ("+first+" luego "+second+") = "
    print(p+"P ("+first+") · P ("+second+")\n")
    
    print("Espacio Muestral = 4 Rojas + 3 Verdes + 2 Azules")
    print("⁂")
    print("Espacio Muestral = 9\n")

    print("P ("+first+") = "+str(canicas[first])+"/"+str(em))
    print("P ("+second+") = "+str(canicas[second])+"/"+str(em)+"\n")
    print(p+str(canicas[first])+"/"+str(em) +" * "+str(canicas[second])+"/"+str(em))
    result = (canicas[first]/em) * (canicas[second]/em) 
    print(p+str(canicas[first]*canicas[second])+"/"+str(em*em) +" ≈ "+str(result)+"\n")
    ##os.system("pause")


def Regla_de_Bayes():
    #os.system("cls")
    print("Problema de Regla de Bayes")
    #os.system("pause")


def menu():
    while True:
        imprimir()
        try:
            entrada_usuario = int(input("Seleccione una opcion: "))

            if entrada_usuario in range(6):

                if entrada_usuario == 5:
                    print("Adios! Finalizando programa...")
                    break
                print()
                if entrada_usuario == 1:
                    Probabilidad()
                if entrada_usuario == 2:
                    Probabilidad_condicional()
                if entrada_usuario == 3:
                    Independencia()
                if entrada_usuario == 4:
                    Regla_de_Bayes()
            else:
                print('Error, solo de aceptan numeros del 1 al 5')

        except ValueError:
            print("Error, ingrese solamente numeros")


if __name__ == '__main__':
    menu()