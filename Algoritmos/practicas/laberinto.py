import time
start_time = time.time()
matriz=[['x','1','1','1','1',' ',' '],
        [' ',' ',' ',' ','1',' ',' '],
        ['1',' ','1','1','1',' ',' '],
        [' ',' ','1',' ',' ','1',' '],
        ['1',' ','1','1','1',' ','1'],
        [' ',' ',' ',' ',' ',' ',' '],
        [' ','1',' ',' ','1',' ',' ']]

def printMatriz():
    for i in matriz:
        print(i)
    print()

def moveFront(row,column):
    matriz[row][column+1]=matriz[row][column]
    matriz[row][column]=' '

def moveBack(row,column):
    matriz[row][column-1]=matriz[row][column]
    matriz[row][column]=' '

def moveDown(row,column):
    matriz[row+1][column] = matriz[row][column] 
    matriz[row][column] = ' '

def moveUp(row,column):
    matriz[row-1][column] = matriz[row][column] 
    matriz[row][column] = ' '

def validateFront(row,column):
    try:
        if matriz[row][column+1] == ' ':
            moveFront(row,column)
            return True
        else:
            return 
    except IndexError:
        return

def validateDown(row,column):
    
    try:
        if matriz[row+1][column] == ' ':
            moveDown(row,column)
            return True
        else:
            return
    except IndexError:
        return

def validateUp(row,column):
    try:
        if matriz[row-1][column] == ' ':
            moveUp(row,column)
            return True
        else:
            return
    except IndexError:
        return

def map(row,column,up=False,movs=0):
    printMatriz()
    if row == 6 and column == 6:
        print("Movimientos",movs-1)
        print("--- Finalizado en %s segundos ---" % round(time.time() - start_time,5))
        return 
    else:
        if not up and validateDown(row,column):
            map(row+1,column,movs=movs+1)
        elif validateFront(row,column):
            map(row,column+1,movs=movs+1)
        elif validateUp(row,column):
            map(row-1,column,True,movs=movs+1)
        else:
            moveBack(row,column)
            map(row,column-1,movs=movs+1)

map(0,0)
