import matplotlib.pyplot as plt


values = []
with open('objective_values.txt', 'r') as file:
    for line in file:
        values.append(float(line.strip()))

plt.figure(figsize=(10, 6))
plt.plot(values, label="Objective Function Value")
plt.xlabel("Iteration")
plt.ylabel("Objective Function Value")
plt.title("Objective Function Value over Iterations")
plt.legend()
plt.grid(True)
plt.show()
