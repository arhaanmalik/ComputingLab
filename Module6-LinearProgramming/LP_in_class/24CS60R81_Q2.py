from ortools.linear_solver import pywraplp

def create_variables(solver, n):
    """Create variables for each cell on the chessboard."""
    return {(i, j): solver.BoolVar(f'queen_{i}_{j}') for i in range(n) for j in range(n)}

def add_constraints(solver, queens, n):
    """Add constraints to ensure only one queen per row, column, and diagonal."""
    # Row constraints
    for i in range(n):
        solver.Add(sum(queens[i, j] for j in range(n)) == 1)

    # Column constraints
    for j in range(n):
        solver.Add(sum(queens[i, j] for i in range(n)) == 1)

    # Diagonal constraints
    for d in range(1 - n, n):
        solver.Add(sum(queens[i, i - d] for i in range(max(d, 0), min(n + d, n))) <= 1)
        solver.Add(sum(queens[i, d + i] for i in range(max(-d, 0), min(n - d, n))) <= 1)

def solve_and_output(solver, queens, n):
    """Solve the problem and write the solution to output.txt."""
    if solver.Solve() == pywraplp.Solver.OPTIMAL:
        solution = []
        for i in range(n):
            solution.append(" ".join('Q' if queens[i, j].solution_value() == 1 else '_' for j in range(n)))

        with open('output.txt', 'w') as outfile:
            outfile.write("\n".join(solution) + '\n')
    else:
        with open('output.txt', 'w') as outfile:
            outfile.write('No solution exists\n')

def n_queens(n):
    # Initialize solver
    solver = pywraplp.Solver.CreateSolver('SCIP')
    if solver is None:
        return

    # Step 1: Create variables
    queens = create_variables(solver, n)

    # Step 2: Add constraints
    add_constraints(solver, queens, n)

    # Step 3: Solve and output the solution
    solve_and_output(solver, queens, n)

with open('input.txt') as f:
    n = int(f.readline().strip())
n_queens(n)
