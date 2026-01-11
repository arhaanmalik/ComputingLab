from ortools.linear_solver import pywraplp

def create_data_model():
    """Create the data for the problem."""
    data = {}
    data['products'] = ['A', 'B', 'C', 'D']
    data['factories'] = [1, 2, 3]
    
    data['price'] = {'A': 100, 'B': 120, 'C': 80, 'D': 150}
    
    data['cost'] = {
        ('A', 1): 60, ('A', 2): 65, ('A', 3): 55,
        ('B', 1): 70, ('B', 2): 75, ('B', 3): 80,
        ('C', 1): 40, ('C', 2): 45, ('C', 3): 50,
        ('D', 1): 90, ('D', 2): 100, ('D', 3): 95
    }
    
    data['raw_material'] = {'A': 2, 'B': 3, 'C': 1.5, 'D': 4}
    data['labor_hours'] = {'A': 3, 'B': 4, 'C': 2, 'D': 5}
    data['co2_emissions'] = {'A': 5, 'B': 7, 'C': 3, 'D': 8}
    
    data['total_raw_material'] = 5000
    data['labor_hours_per_factory'] = 800
    data['production_capacity_per_factory'] = 1000
    data['min_production_per_product'] = 100
    data['max_storage_per_product'] = 2000
    data['max_co2_emissions'] = 10000
    data['max_production_budget'] = 500000
    
    data['market_demand'] = {'A': 1500, 'B': 1200, 'C': 1800, 'D': 1000}
    
    return data


def globtech_manufacturing_solution(data):
    # write your code here
    
    # write the output in the output.txt file
    
    pass # remove this line after writing the code

    
data=create_data_model()

globtech_manufacturing_solution(data)

