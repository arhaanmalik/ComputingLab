from ortools.linear_solver import pywraplp

def create_data_model():
    """Create the data for the optimization problem."""
    data = {}
    
    # List of projects
    data['projects'] = [1, 2, 3, 4]  # Projects are 1, 2, 3, 4
    
    # Return for each project
    data['return'] = {1: 0.2, 2: 0.3, 3: 0.5, 4: 0.1}
    
    # Capital requirements for each year (project, year)
    data['cost'] = {
        (1, 1): 0.5, (1, 2): 0.3, (1, 3): 0.2,
        (2, 1): 1.0, (2, 2): 0.8, (2, 3): 0.2,
        (3, 1): 1.5, (3, 2): 1.5, (3, 3): 0.3,
        (4, 1): 0.1, (4, 2): 0.4, (4, 3): 0.1
    }
    
    # Available capital for each year
    data['available_capital'] = {1: 3.1, 2: 2.5, 3: 0.4}
    
    return data


def project_investment(data):
    # write your code here


    solver = pywraplp.Solver.CreateSolver("GLOP")


    x1 = solver.IntVar(0, 1, "x1")
    x2 = solver.IntVar(0, 1, "x2")
    x3 = solver.IntVar(0, 1, "x3")
    x4 = solver.IntVar(0, 1, "x4")
    



    solver.Add(data["cost"][(1,1)]*x1 + data["cost"][(2,1)]*x2 + data["cost"][(3,1)]*x3 + data["cost"][(4,1)]*x4  <= data["available_capital"][(1)])
    solver.Add(data["cost"][(1,2)]*x1 + data["cost"][(2,2)]*x2 + data["cost"][(3,2)]*x3 + data["cost"][(4,2)]*x4  <= data["available_capital"][(2)])
    solver.Add(data["cost"][(1,3)]*x1 + data["cost"][(2,3)]*x2 + data["cost"][(3,3)]*x3 + data["cost"][(4,3)]*x4  <= data["available_capital"][(3)])
    
    

    print("Number of constraints =", solver.NumConstraints())

    solver.Maximize(data["return"] [(1)] * x1+ data["return"] [(2)] *x2+ data["return"] [(3)] *x3+ data["return"] [(4)] *x4)



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
        

        file.write(f"Objective value = {solver.Objective().Value():0.2f}\n")
        file.write(f"x1 = {x1.solution_value():0.2f}\n")
        file.write(f"x2 = {x2.solution_value():0.2f}\n")
        file.write(f"x3 = {x3.solution_value():0.2f}\n")
        file.write(f"x4 = {x4.solution_value():0.2f}\n")
       

    else:
     print("The problem does not have an optimal solution.")
    # write the output in the output.txt file
    
    

    
data=create_data_model()

project_investment(data)