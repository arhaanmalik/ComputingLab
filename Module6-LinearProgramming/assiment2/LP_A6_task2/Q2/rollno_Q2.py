from ortools.linear_solver import pywraplp

def price_sweet_box(n, box_x, box_y, sweets_x, sweets_y, sweets_cost):

    # write your code here
    
    # write the output to output.txt
    
    pass #remove this line after writing your code



with open('input.txt') as f:
    lines=f.readlines()


n=int(lines[0].strip())
box_x, box_y = map(int, lines[1].strip().split())
sweets_x=list(map(int,lines[2].strip().split(' ')))
sweets_y=list(map(int,lines[3].strip().split(' ')))
sweets_cost=list(map(int,lines[4].strip().split(' ')))


price_sweet_box(n, box_x, box_y, sweets_x, sweets_y, sweets_cost)