
from ortools.linear_solver import pywraplp

def solve_diet_problem(A,B):
    from ortools.linear_solver import pywraplp

    solver = pywraplp.Solver.CreateSolver("GLOP")





    x1 = solver.NumVar(0, solver.infinity(), "x1")
    x2 = solver.NumVar(0, solver.infinity(), "x2")
    x3 = solver.NumVar(0, solver.infinity(), "x3")
    x4 = solver.NumVar(0, solver.infinity(), "x4")
    x5 = solver.NumVar(0, solver.infinity(), "x5")

    print("Number of variables =", solver.NumVariables())


    solver.Add(250*x1 + 200*x2 +50*x3 + 300*x4 + 220*x5>=1500)
    solver.Add(30* x1 + 5* x2 + 4 * x3+ 25*x4 + 8* x5>= 70)
    solver.Add(0* x1 + 45* x2 + 10 * x3 + 0* x4 + 39 * x5>=150)
    solver.Add(10* x1 + 1 * x2 + 0.5* x3 + 20* x4 + 4* x5>=40)


    print("Number of constraints =", solver.NumConstraints())

    solver.Minimize(5* x1+ 2*x2+ 1*x3+ 8*x4+ 4*x5)



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
        print(f"Objective value = {solver.Objective().Value():0.2f}")
        print(f"x1 = {x1.solution_value():0.2f}")
        print(f"x2 = {x2.solution_value():0.2f}")
        print(f"x3 = {x3.solution_value():0.2f}")
        print(f"x4 = {x4.solution_value():0.2f}")
        print(f"x5 = {x5.solution_value():0.2f}")

        file.write(f"Objective value = {solver.Objective().Value():0.2f}\n")
        file.write(f"x1 = {x1.solution_value():0.2f}\n")
        file.write(f"x2 = {x2.solution_value():0.2f}\n")
        file.write(f"x3 = {x3.solution_value():0.2f}\n")
        file.write(f"x4 = {x4.solution_value():0.2f}\n")
        file.write(f"x5 = {x5.solution_value():0.2f}\n")

    else:
     print("The problem does not have an optimal solution.")






with open('input.txt') as f:
    lines=f.readlines()

A=float(lines[0])
B=float(lines[1])
solve_diet_problem(A,B)