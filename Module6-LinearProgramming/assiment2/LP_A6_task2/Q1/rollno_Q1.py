from ortools.linear_solver import pywraplp

def fractional_knapsack(w, n, values, weights):

    # write your code here
    
    # write the output to output.txt
    
    pass #remove this line after writing your code



with open('input.txt') as f:
    lines=f.readlines()


w=int(lines[0].strip())
n=int(lines[1].strip())
values=list(map(int,lines[2].strip().split(',')))
weights=list(map(int,lines[3].strip().split(',')))



fractional_knapsack(w, n, values, weights)
