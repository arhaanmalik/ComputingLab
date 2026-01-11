from ortools.linear_solver import pywraplp

def solve_diet_problem(A,B):
    
    # write your code here
    
    # write the output to output.txt
    
    pass #remove this line after writing your code



with open('input.txt') as f:
    lines=f.readlines()

A=float(lines[0])
B=float(lines[1])
solve_diet_problem(A,B)
