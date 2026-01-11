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
    
    # write the output in the output.txt file
    
    pass # remove this line after writing the code

    
data=create_data_model()

project_investment(data)