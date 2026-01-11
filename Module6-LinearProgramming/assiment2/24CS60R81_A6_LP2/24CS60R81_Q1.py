from ortools.linear_solver import pywraplp

class Item:
   def __init__(self, weight, value):
      self.weight = weight
      self.value = value
      self.ratio = value/weight

def fractional_knapsack(w, n, values, weights):
    solver = pywraplp.Solver.CreateSolver("GLOP")
    if not solver :
       print(" Solver not found")
    # write your code here
       
    ratio = [(values[i]/ weights[i], values[i],weights[i]) for i in range(n)]

    ratio.sort(reverse = True)
    totalvalue =0
    currentweight =0

    for ratio, values, weights in ratio : 
       if currentweight + weights <= w:
          totalvalue += values
          currentweight += weights
        else:
          fraction = (w-currentweight)/weights
          totalvalue += values*fraction
        break
    
          

    var = []

    for i in range(n):
        var.append(solver.NumVar(0, solver.infinity(), f"x[i]"))

    print("Number of variables =", solver.NumVariables())
   
    w.sort(key = lambda x: x.ratio, reverse = True)
    
    for i in values :
       if w < weights :
          
          weight
       
       



    


    result_status = solver.Solve()
    print(f"Status: {result_status}")
    if result_status != pywraplp.Solver.OPTIMAL:
     print("The problem does not have an optimal solution!")
    # you can print the solutions here.
    if result_status == pywraplp.Solver.FEASIBLE:
        print("A potentially suboptimal solution was found")
    else:
        print("The solver could not solve the problem.")



    file = open("output.txt",'w')
    if result_status == pywraplp.Solver.OPTIMAL:
        

        file.write(f"Objective value = {solver.Objective().Value():0.2f}\n")
        
    else:
     print("The problem does not have an optimal solution.")

    # write the output to output.txt
    
    



with open('input.txt') as f:
    lines=f.readlines()


w=int(lines[0].strip())
n=int(lines[1].strip())
values=list(map(int,lines[2].strip().split(',')))
weights=list(map(int,lines[3].strip().split(',')))



fractional_knapsack(w, n, values, weights)