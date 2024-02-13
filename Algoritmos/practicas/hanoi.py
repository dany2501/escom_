################################
## ITERATIVE TOWER OF HANOI
## Name: Eitan Yehuda
## Date: Mar.31,2017
################################

## Class and Methods ##
import time
start_time = time.time()

cnt = 1
 
def move (id, ori, to): # Método de movimiento de impresión: número, de qué placa a qué placa
	global cnt
	print ("Paso {}: mover {} de {} a {}". format(cnt, id, ori, to))
	cnt+=1
	
def hanoi(n, x, y, z):
 
    if n == 0:
    	return
    hanoi(n - 1, x, z, y)
    
    move(n, x, z);
    hanoi(n - 1, y, x, z)
    print("--- %s seconds ---" % (time.time() - start_time))
 
hanoi(5, 'A', 'B', 'C',)
