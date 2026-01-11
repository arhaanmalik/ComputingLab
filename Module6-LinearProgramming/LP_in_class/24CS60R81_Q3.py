from ortools.linear_solver import pywraplp

def create_data_model():
    """Initialize data for the GlobalTech manufacturing optimization problem."""
    data = {}
    data['products'] = ['A', 'B', 'C', 'D']
    data['factories'] = [1, 2, 3]
    
    data['prices'] = {'A': 100, 'B': 120, 'C': 80, 'D': 150}
    
    data['production_cost'] = {
        ('A', 1): 60, ('A', 2): 65, ('A', 3): 55,
        ('B', 1): 70, ('B', 2): 75, ('B', 3): 80,
        ('C', 1): 40, ('C', 2): 45, ('C', 3): 50,
        ('D', 1): 90, ('D', 2): 100, ('D', 3): 95
    }
    
    data['resources'] = {
        'raw_material': {'A': 2, 'B': 3, 'C': 1.5, 'D': 4},
        'labor_hours': {'A': 3, 'B': 4, 'C': 2, 'D': 5},
        'co2_emissions': {'A': 5, 'B': 7, 'C': 3, 'D': 8},
    }
    
    data['limits'] = {
        'total_raw_material': 5000,
        'labor_hours_per_factory': 800,
        'production_capacity_per_factory': 1000,
        'min_production_per_product': 100,
        'max_storage_per_product': 2000,
        'max_co2_emissions': 10000,
        'max_production_budget': 500000,
    }
    
    data['market_demand'] = {'A': 1500, 'B': 1200, 'C': 1800, 'D': 1000}
    
    return data

def globtech_manufacturing_solution(data):
    solver = pywraplp.Solver.CreateSolver('SCIP')
    if not solver:
        return

    production_vars = {}
    for product in data['products']:
        for factory in data['factories']:
            production_vars[(product, factory)] = solver.IntVar(0, data['limits']['production_capacity_per_factory'], f'{product}_{factory}')

    # Objective: Maximize profit
    objective = solver.Objective()
    for product in data['products']:
        for factory in data['factories']:
            profit_contribution = data['prices'][product] - data['production_cost'][(product, factory)]
            objective.SetCoefficient(production_vars[(product, factory)], profit_contribution)
    objective.SetMaximization()

    # Constraints

    # Raw material usage constraint
    material_usage = solver.Constraint(0, data['limits']['total_raw_material'])
    index = 0
    while index < len(data['products']) * len(data['factories']):
        product = data['products'][index // len(data['factories'])]
        factory = data['factories'][index % len(data['factories'])]
        material_usage.SetCoefficient(production_vars[(product, factory)], data['resources']['raw_material'][product])
        index += 1

    # Labor hours constraints per factory
    plant_index = 0
    while plant_index < len(data['factories']):
        labor_constraint = solver.Constraint(0, data['limits']['labor_hours_per_factory'])
        product_index = 0
        while product_index < len(data['products']):
            labor_constraint.SetCoefficient(production_vars[(data['products'][product_index], data['factories'][plant_index])], data['resources']['labor_hours'][data['products'][product_index]])
            product_index += 1
        plant_index += 1

    # CO2 emissions constraint
    index = 0
    while index < len(data['products']) * len(data['factories']):
        product = data['products'][index // len(data['factories'])]
        factory = data['factories'][index % len(data['factories'])]
        emissions_constraint = solver.Constraint(0, data['limits']['max_co2_emissions'])
        emissions_constraint.SetCoefficient(production_vars[(product, factory)], data['resources']['co2_emissions'][product])
        index += 1

    # Market demand constraints
    product_index = 0
    while product_index < len(data['products']):
        product = data['products'][product_index]
        market_constraint = solver.Constraint(0, data['market_demand'][product])
        factory_index = 0
        while factory_index < len(data['factories']):
            factory = data['factories'][factory_index]
            market_constraint.SetCoefficient(production_vars[(product, factory)], 1)
            factory_index += 1
        product_index += 1

    # Production capacity constraints per factory
    plant_index = 0
    while plant_index < len(data['factories']):
        capacity_constraint = solver.Constraint(0, data['limits']['production_capacity_per_factory'])
        product_index = 0
        while product_index < len(data['products']):
            capacity_constraint.SetCoefficient(production_vars[(data['products'][product_index], data['factories'][plant_index])], 1)
            product_index += 1
        plant_index += 1

    # Minimum production constraints
    product_index = 0
    while product_index < len(data['products']):
        product = data['products'][product_index]
        min_production_constraint = solver.Constraint(data['limits']['min_production_per_product'], solver.infinity())
        factory_index = 0
        while factory_index < len(data['factories']):
            factory = data['factories'][factory_index]
            min_production_constraint.SetCoefficient(production_vars[(product, factory)], 1)
            factory_index += 1
        product_index += 1

    # Production budget constraint
    budget_constraint = solver.Constraint(0, data['limits']['max_production_budget'])
    index = 0
    while index < len(data['products']) * len(data['factories']):
        product = data['products'][index // len(data['factories'])]
        factory = data['factories'][index % len(data['factories'])]
        budget_constraint.SetCoefficient(production_vars[(product, factory)], data['production_cost'][(product, factory)])
        index += 1

    # Solve the model
    status = solver.Solve()

    with open('output.txt', 'w') as output_file:
        if status == pywraplp.Solver.OPTIMAL:
            total_raw_material_used = sum(
                production_vars[(product, factory)].solution_value() * data['resources']['raw_material'][product]
                for product in data['products'] for factory in data['factories']
            )
            total_labour_used = sum(
                production_vars[(product, factory)].solution_value() * data['resources']['labor_hours'][product]
                for product in data['products'] for factory in data['factories']
            )
            total_co2_emissions = sum(
                production_vars[(product, factory)].solution_value() * data['resources']['co2_emissions'][product]
                for product in data['products'] for factory in data['factories']
            )
            total_production_cost = sum(
                production_vars[(product, factory)].solution_value() * data['production_cost'][(product, factory)]
                for product in data['products'] for factory in data['factories']
            )

            for product in data['products']:
                for factory in data['factories']:
                    quantity = production_vars[(product, factory)].solution_value()
                    output_file.write(f'{int(quantity)}\n')

            output_file.write(f'{int(total_raw_material_used)} / {data["limits"]["total_raw_material"]}\n')
            output_file.write(f'{int(total_labour_used)} / {len(data["factories"]) * data["limits"]["labor_hours_per_factory"]}\n')
            output_file.write(f'{int(total_co2_emissions)} / {data["limits"]["max_co2_emissions"]}\n')
            output_file.write(f'{int(total_production_cost)} / {data["limits"]["max_production_budget"]}\n')
        else:
            output_file.write('No optimal solution found\n')
    
data=create_data_model()

globtech_manufacturing_solution(data)