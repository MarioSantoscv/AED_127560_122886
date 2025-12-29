import pandas as pd
import matplotlib.pyplot as plt

# Ler os dados
data = pd.read_csv("resultados.csv")

# Gráfico: Tempo vs Número de Vértices
plt.figure(figsize=(8, 5))

plt.plot(data["Verts"], data["Time_MD"], marker='o', label="Min Dominating Set")
plt.plot(data["Verts"], data["Time_MWD"], marker='o', label="Min Weight Dominating Set")

plt.xlabel("Número de vértices")
plt.ylabel("Tempo de execução (s)")
plt.title("Tempo de execução vs Número de vértices")
plt.legend()
plt.grid(True)

# Guardar figura
plt.savefig("tempo_vs_vertices.png", dpi=300)
plt.show()
