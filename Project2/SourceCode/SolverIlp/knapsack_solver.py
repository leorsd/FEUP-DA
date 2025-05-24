import pulp

with open("../SolverIlp/input.txt") as f:
    capacity, n = map(int, f.readline().split())
    weights, profits = [], []
    for _ in range(n):
        w, p = map(int, f.readline().split())
        weights.append(w)
        profits.append(p)

BIG = 10000 
# This is a large constant to ensure the profit maximization dominates the objective function
# when minimizing the number of pallets used.

prob = pulp.LpProblem("Knapsack", pulp.LpMaximize)
x = [pulp.LpVariable(f"x{i}", cat="Binary") for i in range(n)]

# Combined objective: maximize profit, minimize number of pallets
prob += pulp.lpSum(profits[i] * x[i] for i in range(n)) * BIG - pulp.lpSum(x[i] for i in range(n))

# Constraint: total weight must not exceed capacity
prob += pulp.lpSum(weights[i] * x[i] for i in range(n)) <= capacity
prob.solve(pulp.PULP_CBC_CMD(msg=0))

with open("../SolverIlp/output.txt", "w") as f:
    f.write(" ".join(str(int(x[i].varValue)) for i in range(n)))