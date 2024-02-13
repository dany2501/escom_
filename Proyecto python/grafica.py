
import tkinter as tk
from tkinter import Image, Label, PhotoImage, Scrollbar
import os
from tkinter.constants import ACTIVE, CENTER, COMMAND, DISABLED, TOP
from typing import Text
from tkinter import messagebox


def proba_simple():
    proba1 = tk.Toplevel()

    proba1.geometry("1200x1200")
    proba1.config(bg="gray22",)
    proba1.iconbitmap('icono.ico')
    fondo2 = tk.Label(
        proba1, text="", font=("Courier", 16, "italic"), bg="gray22",)
    fondo2.pack(fill=tk.X)
    simp_1 = tk.Label(
        proba1, text="Probabilidad simple - Teoría", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_1.pack()
    boton_aux = tk.Button(proba1, text="Regresar", font=(
        "Comic Sans MS", 16, "italic"), bg="RoyalBlue4", width=20, height=2, foreground="white", command=proba1.destroy)
    boton_aux.place(x=450, y=950)

    img = tk.PhotoImage(file="ProbaSimp.png")
    img_sub = img.subsample(1)
    panel = tk.Label(proba1, image=img_sub)
    panel.photo = img_sub
    panel.place(x=230, y=70)
    simp_2 = tk.Label(
        proba1, text="Probabilidad simple - Problema", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_2.place(x=450, y=465)
    simp_3 = tk.Label(
        proba1, text="Se tiran dos dados al azar.", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_4 = tk.Label(
        proba1, text="Seleccione un numero para calcular las probabilidades de que la suma de los resultados, de ese numero: ", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_3.place(x=20, y=500)
    simp_4.place(x=20, y=530)
    entrada_simp = tk.Entry(proba1, width=2, font=(
        "Comic Sans MS", 25, "italic"), justify="center", bg="gray40", foreground="white")
    entrada_simp.place(x=550, y=580)
    simp_boton = tk.Button(proba1, text="Calcular", font=(
        "Comic Sans MS", 16, "italic"), bg="RoyalBlue4", width=15, height=1, foreground="white", command=lambda: calculo_simp(int(entrada_simp.get())))
    simp_boton.place(x=610, y=580)
    simp_res = tk.Label(proba1, text="", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white")
    simp_res.place(x=900, y=760)
    combinaciones_simp = tk.Message(proba1, text="", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white", justify="center", anchor=CENTER)
    combinaciones_simp.place(x=450, y=650)
    simp_5 = tk.Button(proba1, text="Posibles combinaciones:", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white")
    simp_5.place(x=50, y=750)
    simp_6 = tk.Button(proba1, text="Probabilidad:", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white")
    simp_6.place(x=650, y=750)

    def calculo_simp(entrada):
        lista = []
        posibles = [1, 2, 3, 4, 5, 6]
        contador = 0
        for i in posibles:
            for j in posibles:
                if i + j == entrada:
                    contador = contador + 1

                    lista.append((f"{i} + {j}"))

        if((len(lista) > 2)):
            combinaciones_simp.place(x=450, y=650)
        else:
            combinaciones_simp.place(x=450, y=750)
        cadena = "\n".join(x for x in lista)

        resultado = (contador / 36)*100
        resultado = f"{resultado: .2f}"
        res = f"{str(resultado)}%"
        simp_res.config(text=res)
        combinaciones_simp.config(text=cadena)


def proba_condicional():
    proba1 = tk.Toplevel()

    proba1.geometry("1200x1200")
    proba1.config(bg="gray22",)
    proba1.iconbitmap('icono.ico')
    fondo2 = tk.Label(
        proba1, text="", font=("Courier", 16, "italic"), bg="gray22",)
    fondo2.pack(fill=tk.X)
    simp_1 = tk.Label(
        proba1, text="Probabilidad Condicional - Teoría", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_1.pack()
    boton_aux = tk.Button(proba1, text="Regresar", font=(
        "Comic Sans MS", 16, "italic"), bg="RoyalBlue4", foreground="white", width=20, height=2, command=proba1.destroy)
    boton_aux.place(x=450, y=950)

    path = "Condicional.png"
    img = tk.PhotoImage(file="Condicional.png")
    img_sub = img.subsample(1)
    panel = tk.Label(proba1, image=img_sub)
    panel.photo = img_sub
    panel.place(x=230, y=70)
    simp_2 = tk.Label(
        proba1, text="Probabilidad Condicional - Problema", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_2.place(x=450, y=465)
    simp_3 = tk.Label(
        proba1, text="Se lanzan dos dados, desafortunadamente, uno esta cargado para obtener un resultado.", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_4 = tk.Label(
        proba1, text="Seleccione el numero que siempre cae en el dado cargado: ", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_3.place(x=20, y=500)
    simp_4.place(x=20, y=540)
    entrada_simp = tk.Entry(proba1, width=2, font=(
        "Comic Sans MS", 25, "italic"), justify="center", bg="gray40", foreground="white")
    entrada_simp.place(x=550, y=580)
    simp_7 = tk.Label(
        proba1, text="Seleccione un numero para calcular las probabilidades de que la suma de los resultados, de ese numero:  ", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_7.place(x=20, y=650)
    simp_boton = tk.Button(proba1, text="Calcular", font=(
        "Comic Sans MS", 16, "italic"), bg="RoyalBlue4", width=15, height=1, foreground="white", command=lambda: calculo_cond(int(entrada_simp.get()), int(entrada_simp2.get())))
    simp_boton.place(x=900, y=700)
    entrada_simp2 = tk.Entry(proba1, width=2, font=(
        "Comic Sans MS", 25, "italic"), justify="center", bg="gray40", foreground="white")
    entrada_simp2.place(x=550, y=700)
    simp_res = tk.Label(proba1, text="", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white")
    simp_res.place(x=1000, y=795)
    combinaciones_simp = tk.Message(proba1, text="", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white", justify="center", anchor=CENTER)
    combinaciones_simp.place(x=450, y=780)
    simp_5 = tk.Button(proba1, text="Posible combinacion:", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white")
    simp_5.place(x=50, y=780)
    simp_6 = tk.Button(proba1, text="Probabilidad de A|B:", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white")
    simp_6.place(x=650, y=780)
    cond_boton2 = tk.Button(proba1, text="Mas info", font=(
        "Comic Sans MS", 16, "italic"), bg="gray", width=15, height=1, foreground="white", command=lambda: info(int(entrada_simp2.get()), int(entrada_simp.get())), state=DISABLED)
    cond_boton2.place(x=50, y=880)

    def info(A, B):
        posibles = [1, 2, 3, 4, 5, 6]
        contador1 = 0
        contador2 = 0
        contador3 = 0
        # Probabilidad de A
        print(f"salidas que suman {A}: ")
        for i in posibles:
            for j in posibles:
                if i + j == A:
                    contador1 = contador1 + 1
                    print(f"{i} + {j}")
        # Probabilidad de B
        print(f"salidas con el dado cargado en {B}: ")
        for i in posibles:
            for j in posibles:
                if i == B:
                    print(f"{i} + {j}")
                    contador3 = contador3 + 1

        simp_5.config(text=f"# Salidas que suman {A}:")
        simp_6.config(text=f"# Salidas con {B}:")
        combinaciones_simp.config(text=f"{contador1}/36")
        simp_res.config(text=f"{contador3}/36")

    def calculo_cond(cargado, entrada):
        posibles = [1, 2, 3, 4, 5, 6]
        contador1 = 0
        contador2 = 0
        contador3 = 0
        lista = []
    # Probabilidad de A
        print(f"salidas que suman {entrada}: ")
        for i in posibles:
            for j in posibles:
                if i + j == entrada:
                    contador1 = contador1 + 1
                    print(f"{i} + {j}")
        # Probabilidad de B
        print(f"salidas con el dado cargado en {cargado}: ")
        for i in posibles:
            for j in posibles:
                if i == cargado:
                    print(f"{i} + {j}")
                    contador3 = contador3 + 1
    # Probabilidad de interseccion
        print(f"salidas con el dado cargado que suman {entrada}: ")
        for i in posibles:
            if cargado + i == entrada:
                contador2 = contador2 + 1
                print(f"3 + {i}")
                lista.append((f"{cargado} + {i}"))
        cadena = "\n".join(x for x in lista)

    # Probabilidad condicional A de B
        print(f"probabilidad de A = {contador1}/36")
        print(f"probabilidad de B = {contador3}/36")
        print(f"probabilidad de A interseccion B = {contador2}/36")

        interseccion = contador2 / 36
        prob_b = contador3 / 36
        resultado = ((interseccion) / (prob_b)) * 100
        print(f"El resultado de (A|B) es ={resultado:.2f}%")
        combinaciones_simp.config(text=cadena)
        resultado = f"{resultado: .2f}"
        res = f"{str(resultado)}%"
        simp_res.config(text=res)
        cond_boton2.config(state=ACTIVE, bg="RoyalBlue4")


def indepen():
    canicas = {"rojo": 4, "verde": 3, "azul": 2}
    red = 4
    green = 3
    blue = 2
    em = red+green+blue
    extracciones = []
    numero = [0]
    result = 1

    def seleccionar_color(color):
        if numero[-1] <= 7:
            extracciones.append(color)
            numero.append(numero[-1]+1)
        cadena = ' '.join([str(item)
                           for item in extracciones])
        orden.config(text=cadena)
        print(f"Extraccion: canica {color}")

    Indepen = tk.Toplevel()

    Indepen.geometry("1200x1200")
    Indepen.config(bg="gray22",)
    Indepen.iconbitmap('icono.ico')
    fondo2 = tk.Label(
        Indepen, text="", font=("Courier", 16, "italic"), bg="gray22",)
    fondo2.pack(fill=tk.X)
    simp_1 = tk.Label(
        Indepen, text="Independencia - Teoría", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_1.pack()
    boton_aux = tk.Button(Indepen, text="Regresar", font=(
        "Comic Sans MS", 16, "italic"), bg="RoyalBlue4", width=20, height=2, command=Indepen.destroy, foreground="white")
    boton_aux.place(x=450, y=950)

    path = "Indepen.png"
    img = tk.PhotoImage(file="Independencia.png")
    img_sub = img.subsample(1)
    panel = tk.Label(Indepen, image=img_sub)
    panel.photo = img_sub
    panel.place(x=230, y=70)
    simp_2 = tk.Label(
        Indepen, text="Independencia - Problema", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_2.place(x=450, y=465)

    simp_3 = tk.Label(
        Indepen, text="Una caja contiene 4 canicas rojas, 3 canicas verdes y 2 canicas azules.", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_3.place(x=20, y=500)

    simp_4 = tk.Label(
        Indepen, text=f"¿Que color quieres sacar para la extracción con remplazo?", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_4.place(x=20, y=600)
    indepen_2 = tk.Label(
        Indepen, text=f"Selecciona hasta 8 extracciones para calcular la probabilidad", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    indepen_2.place(x=20, y=550)

    def imprimir():
        print(extracciones)
        print(numero)
        result = (canicas[extracciones[0]]/em)
        for y in range(len(extracciones)-1):
            result = result * (canicas[extracciones[y+1]]/em)
        print(result)
        resultado2.config(text=f"{result:.4f} o {(result * 100):.4f}%")

    boton_inde_1 = tk.Button(Indepen, text="Calcular", font=(
        "Comic Sans MS", 16, "italic"), bg="RoyalBlue4", width=15, height=1, foreground="white", command=imprimir)
    boton_inde_1.place(x=420, y=850)
    tit_extracciones = tk.Label(Indepen, text=f"Extracciones: ", font=(
        "Comic Sans MS", 19, "italic"), bg="gray22", foreground="white")
    tit_extracciones.place(x=850, y=460)
    orden = tk.Message(Indepen, text="", font=(
        "Comic Sans MS", 17, "italic"), bg="gray22", foreground="white", width=80)
    orden.place(x=850, y=500)
    resultado1 = tk.Message(Indepen, text="Probabilidades", font=(
        "Comic Sans MS", 17, "italic"), bg="gray22", foreground="white", width=200)
    resultado1.place(x=850, y=780)
    resultado2 = tk.Message(Indepen, text="", font=(
        "Comic Sans MS", 20, "italic"), bg="gray22", foreground="white", width=200)
    resultado2.place(x=870, y=830)

    img2 = tk.PhotoImage(file='canicarj.png')
    panel2 = tk.Label(Indepen, image=img_sub, borderwidth=0)
    panel2.photo = img2
    boton_ejemplo1 = tk.Button(
        Indepen, image=img2, borderwidth=0, highlightthickness=0, command=lambda: seleccionar_color("rojo"))
    boton_ejemplo1.place(x=30, y=650)

    img3 = tk.PhotoImage(file='canicavd.png')
    panel2 = tk.Label(Indepen, image=img_sub, borderwidth=0)
    panel2.photo = img3
    boton_ejemplo2 = tk.Button(
        Indepen, image=img3, borderwidth=0, highlightthickness=0, command=lambda: seleccionar_color("verde"))
    boton_ejemplo2.place(x=220, y=650)

    img4 = tk.PhotoImage(file='canicaaz.png')
    panel2 = tk.Label(Indepen, image=img_sub, borderwidth=0)
    panel2.photo = img4
    boton_ejemplo3 = tk.Button(
        Indepen, image=img4, borderwidth=0, highlightthickness=0, command=lambda: seleccionar_color("azul"))
    boton_ejemplo3.place(x=410, y=650)

    simp_5 = tk.Button(Indepen, text="Con remplazo, es decir, se devuelve la bola obtenida:", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white")
    simp_6 = tk.Button(Indepen, text="¿Que color quieres sacar como segunda opción?", font=(
        "Comic Sans MS", 25, "italic"), bg="gray22", foreground="white")


def bayes():

    Indepen = tk.Toplevel()

    Indepen.geometry("1200x1200")
    Indepen.config(bg="gray22",)
    Indepen.iconbitmap('icono.ico')
    fondo2 = tk.Label(
        Indepen, text="", font=("Courier", 16, "italic"), bg="gray22",)
    fondo2.pack(fill=tk.X)
    simp_1 = tk.Label(
        Indepen, text="Teorema de bayes - Teoría", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_1.pack()
    boton_aux = tk.Button(Indepen, text="Regresar", font=(
        "Comic Sans MS", 16, "italic"), bg="RoyalBlue4", width=20, height=2, command=Indepen.destroy, foreground="white")
    boton_aux.place(x=450, y=950)

    path = "Indepen.png"
    img = tk.PhotoImage(file="Bayes.png")
    img_sub = img.subsample(1)
    panel = tk.Label(Indepen, image=img_sub)
    panel.photo = img_sub
    panel.place(x=230, y=70)
    simp_2 = tk.Label(
        Indepen, text="Teorema de bayes - Problema", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    simp_2.place(x=450, y=465)

    positivo1 = tk.Label(
        Indepen, text="¿Cual es el indice de efectividad de la prueba?", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    positivo1.place(x=20, y=550)
    positivo2 = tk.Entry(Indepen, width=2, font=(
        "Comic Sans MS", 25, "italic"), justify="center", bg="gray40", foreground="white")

    positivo2.place(x=490, y=540)
    positivo3 = tk.Label(
        Indepen, text=" % ", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    positivo3.place(x=540, y=550)

    pregunta = tk.Label(
        Indepen, text="Tu diagnóstico es:", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    pregunta.place(x=20, y=650)
    pregunta2 = tk.Label(
        Indepen, text="", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    pregunta2.place(x=500, y=650)

    def posit():
        global diagnose
        diagnose = "positivo"

        pregunta2.config(text="Positivo para SARS-CoV-2.")

    def negat():
        global diagnose
        diagnose = "negativo"
        pregunta2.config(text="Negativo para SARS-CoV-2.")

    posi = tk.Button(Indepen, text="+", font=(
        "Comic Sans MS", 22, "italic"), bg="Green", width=3, height=1, foreground="white", command=posit)
    posi.place(x=250, y=650)
    nega = tk.Button(Indepen, text="-", font=(
        "Comic Sans MS", 22, "italic"), bg="Red", width=3, height=1, foreground="white", command=negat)
    nega.place(x=320, y=650)
    pregunta3 = tk.Label(
        Indepen, text="Prevalencia del virus: (%)", font=("Comic Sans MS", 16, "italic"), bg="gray22", foreground="white")
    pregunta3.place(x=820, y=650)
    prev = tk.Entry(Indepen, width=2, font=(
        "Comic Sans MS", 25, "italic"), justify="center", bg="gray40", foreground="white")
    prev.place(x=1100, y=650)

    diagnosticc = tk.Label(Indepen, text="aiii", font=(
        "Comic Sans MS", 22, "italic"), bg="gray22", foreground="white")

    def diagnost():
        posi_posi = (int(positivo2.get()))/100
        print(posi_posi)
        posi_nega = 1-posi_posi
        print(posi_nega)

        nega_posi = 1-posi_posi
        print(nega_posi)
        nega_nega = (int(positivo2.get()))/100
        print(nega_nega)

        posibilidad_positiva = ((int(prev.get())/100)
                                * posi_posi)+((1-(int(prev.get())/100))*posi_nega)

        posibilidad_negativa = 1-posibilidad_positiva

        covid_positivo = (posi_posi*(int(prev.get())/100))/posibilidad_positiva
        covid_negativo = (posi_nega*(int(prev.get())/100))/posibilidad_negativa

        nocovid_positivo = (
            nega_posi*(1-(int(prev.get())/100)))/posibilidad_positiva
        nocovid_negativo = (
            nega_nega*(1-(int(prev.get())/100)))/posibilidad_negativa

        # diagnosticc.config(width=800)

        diagnosticc.place(x=20, y=750)
        print(diagnose)

        if (diagnose) == "positivo":
            texto = f"La probabilidad de que tengas covid es de: {(covid_positivo*100):.4f}%"
            print(texto)
            diagnosticc.config(text=texto)
        else:
            texto = f"La probabilidad de que tengas covid es de: {(covid_negativo*100):.4f}%"
            print(texto)
            diagnosticc.config(text=texto)

    boton_inde_1 = tk.Button(Indepen, text="Calcular", font=(
        "Comic Sans MS", 16, "italic"), bg="RoyalBlue4", width=15, height=1, foreground="white", command=diagnost)
    boton_inde_1.place(x=380, y=870)


ventana = tk.Tk()
ventana.geometry("600x700")
ventana.config(bg="gray22")
ventana.title("Probabilidad y Estadística")
ventana.iconbitmap('icono.ico')


Principal = tk.Label(
    ventana, text="Programa Probabilidad y Estadística", font=("Comic Sans MS", 23, "italic"), bg="gray22", foreground="white")
Fondo = tk.Label(
    ventana, text="", font=("Courier", 16, "italic"), bg="gray22",)

boton1 = tk.Button(ventana, text="Probabilidad",
                   font=("Comic Sans MS", 16, "italic"), bg="gray35", width=20, height=2, foreground="white", command=proba_simple)
boton2 = tk.Button(ventana, text="Probabilidad Condicional",
                   font=("Comic Sans MS", 16, "italic"), bg="gray35", width=20, height=2, foreground="white", command=proba_condicional)
boton3 = tk.Button(ventana, text="Independencia",
                   font=("Comic Sans MS", 16, "italic"), bg="gray35", width=20, height=2, foreground="white", command=indepen)
boton4 = tk.Button(ventana, text="Teorema de Bayes",
                   font=("Comic Sans MS", 16, "italic"), bg="gray35", width=20, height=2, foreground="white", command=bayes)
boton5 = tk.Button(ventana, text="Salir",
                   font=("Comic Sans MS", 16, "italic"), bg="RoyalBlue4", width=20, height=2, foreground="white", command=ventana.destroy)

Fondo.pack(fill=tk.X)

Principal.pack()

boton1.place(x=170, y=180)
boton2.place(x=170, y=261)
boton3.place(x=170, y=342)
boton4.place(x=170, y=423)
boton5.place(x=170, y=560)
boton1.bind("<Enter>", lambda animacion: boton1.config(
    bg="gray22", foreground="white"))
boton1.bind("<Leave>", lambda animacion: boton1.config(
    bg="gray35", foreground="white"))
boton2.bind("<Enter>", lambda animacion: boton2.config(
    bg="gray22", foreground="white"))
boton2.bind("<Leave>", lambda animacion: boton2.config(
    bg="gray35", foreground="white"))
boton3.bind("<Enter>", lambda animacion: boton3.config(
    bg="gray22", foreground="white"))
boton3.bind("<Leave>", lambda animacion: boton3.config(
    bg="gray35", foreground="white"))
boton4.bind("<Enter>", lambda animacion: boton4.config(
    bg="gray22", foreground="white"))
boton4.bind("<Leave>", lambda animacion: boton4.config(
    bg="gray35", foreground="white"))


ventana.mainloop()
