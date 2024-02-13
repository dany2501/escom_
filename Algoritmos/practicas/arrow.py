matriz=[[' ',' ',' ',' ',' ',' ','x','x'],
        [' ',' ',' ',' ',' ','x','x',' '],
        ['x',' ',' ',' ','x','x',' ',' '],
        ['x',' ',' ','x','x',' ',' ',' '],
        ['x',' ','x','x',' ',' ',' ',' '],
        ['x','x','x',' ',' ',' ',' ',' '],
        ['x','x',' ',' ',' ',' ',' ',' '],
        ['x','x','x','x','x','x',' ',' ']]

def printMatriz():
    for i in matriz:
        print(i)
    print("")

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
        if row!=0 and matriz[row-1][column] == ' ':
            moveUp(row,column)
            return True
        else:
            return
    except IndexError:
        return
    
def validateBack(row,column):
    try:
        if row!=0 and matriz[row][column-1] == ' ':
            moveBack(row,column)
            return True
        else:
            return
    except IndexError:
        return

def rotateFirstQuarter():
    for row, i in enumerate(matriz):
        for column, j in enumerate(i):
            if row >= 0 and row <=3 and column >= 0 and column <=3:
                if j=='x':
                    if row == 0:
                        validateFront(row,column)
                    elif row !=0 and column ==0:
                        validateUp(row,column)
                    
                    elif row == 3 or row == 2:
                        if column == 1:
                            validateUp(row,column)
                        elif column == 2 and row != 2:
                            validateUp(row,column)
                    
def rotateSecondQuarter():
    for row, i in enumerate(matriz):
        for column, j in enumerate(i):
            if row >= 0 and row <= 3 and column >= 4 and column <= 7:
                if j== 'x':
                    
                    if row == 0 and column in range(4,5):
                        validateFront(row,column)
                        
                    elif row == 0 and column >5:
                        validateDown(row,column)
                    elif row in range(1,4):
                        validateDown(row,column)
                        #return
def rotateThirthQuarter():
    for row, i in enumerate(matriz):
        for column, j in enumerate(i):
            if row >= 4 and row <=len(matriz)-1 and column >= 0 and column <=3:
                if j == 'x':
                    if column == 0 and row>=4 and row<=len(matriz)-1:
                        validateUp(row,column)

                    elif column !=0 and row == len(matriz)-1:
                        validateBack(row,column)

                    elif row>=4 and row<=len(matriz)-2:
                        validateUp(row,column)
    
def rotateFourthQuarter():
    for row, i in enumerate(matriz):
        for column, j in enumerate(i):
            if row >= 4 and row <=len(matriz)-1 and column >= 3 and column <=len(matriz):
                if j == 'x':
                    if column == len(matriz)-1:
                        validateDown(row,column)
                    elif column == len(matriz)-2 and row != len(matriz)-2:
                        validateDown(row,column)

                    elif column >= 3 and column <=len(matriz)-1  and row == len(matriz)-1:
                        validateBack(row,column)

                    elif column == 6 and row<7:
                        validateDown(row,column)

                    elif column == 4 and row<5:
                        validateDown(row,column)
                    
                    elif column == 5 and row<6:
                        validateDown(row,column)
                    
                    
                    #else:
                    #    validateUp(row,column)


def rotate(i):
    if i<=6:
        printMatriz()
        rotateFirstQuarter()
        rotateThirthQuarter()
        rotateSecondQuarter()
        rotateFourthQuarter()
        rotate(i+1)
    else:
        printMatriz()
        return 
    

rotate(0)