import matplotlib.pyplot as plt

probabilities = []
with open("probability_values.txt", "r") as file:
    for line in file:
        probabilities.append(float(line.strip()))

plt.figure(figsize=(10, 6))
plt.plot(probabilities, label="e^(ΔE/T)", color="orange")
plt.title("Probability e^(ΔE/T) over Iterations")
plt.xlabel("Iteration")
plt.ylabel("Probability Value")
plt.legend()
plt.grid(True)
plt.show()
