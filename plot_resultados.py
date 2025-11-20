import pandas as pd
import matplotlib.pyplot as plt

# Lê o CSV gerado pela sua main em C
df = pd.read_csv("resultados.csv")

# Garante tipos numéricos corretos
df["tamanho"] = df["tamanho"].astype(int)
df["tempo_s"] = df["tempo_s"].astype(float)
df["comparacoes"] = df["comparacoes"].astype(int)
df["movimentacoes"] = df["movimentacoes"].astype(int)

# Só para deixar os algoritmos sempre na mesma ordem nos gráficos
ordem_algoritmos = [
    "BubbleSort",
    "SelectionSort",
    "InsertionSort",
    "ShellSort",
    "QuickSort",
    "HeapSort",
    "MergeSort",
    "ContagemDosMenores",
    "RadixSort",
]
df["algoritmo"] = pd.Categorical(df["algoritmo"], categories=ordem_algoritmos, ordered=True)

# ---------- 1) Gráficos de linha: Tempo x Tamanho (um por caso) ----------
for caso in df["caso"].unique():
    subset = df[df["caso"] == caso]

    plt.figure()
    for alg in subset["algoritmo"].unique():
        sub_alg = subset[subset["algoritmo"] == alg]
        # média por tamanho (caso tenha várias runs para aleatório)
        media = sub_alg.groupby("tamanho", as_index=False)["tempo_s"].mean()
        plt.plot(media["tamanho"], media["tempo_s"], marker="o", label=alg)

    plt.xlabel("Tamanho do vetor (n)")
    plt.ylabel("Tempo médio (s)")
    plt.title(f"Tempo x Tamanho - Caso: {caso}")
    plt.xscale("log")  # tamanhos 100, 1000, 10000, 100000 -> melhor em escala log
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"tempo_vs_tamanho_{caso}.png")

# ---------- 2) Gráficos de linha: Comparações x Tamanho (um por caso) ----------
for caso in df["caso"].unique():
    subset = df[df["caso"] == caso]

    plt.figure()
    for alg in subset["algoritmo"].unique():
        sub_alg = subset[subset["algoritmo"] == alg]
        media = sub_alg.groupby("tamanho", as_index=False)["comparacoes"].mean()
        plt.plot(media["tamanho"], media["comparacoes"], marker="o", label=alg)

    plt.xlabel("Tamanho do vetor (n)")
    plt.ylabel("Comparações médias")
    plt.title(f"Comparações x Tamanho - Caso: {caso}")
    plt.xscale("log")
    plt.yscale("log")  # costuma crescer ~ n log n ou n² -> log ajuda
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"comparacoes_vs_tamanho_{caso}.png")

# ---------- 3) Gráficos de linha: Movimentações x Tamanho (um por caso) ----------
for caso in df["caso"].unique():
    subset = df[df["caso"] == caso]

    plt.figure()
    for alg in subset["algoritmo"].unique():
        sub_alg = subset[subset["algoritmo"] == alg]
        media = sub_alg.groupby("tamanho", as_index=False)["movimentacoes"].mean()
        plt.plot(media["tamanho"], media["movimentacoes"], marker="o", label=alg)

    plt.xlabel("Tamanho do vetor (n)")
    plt.ylabel("Movimentações médias")
    plt.title(f"Movimentações x Tamanho - Caso: {caso}")
    plt.xscale("log")
    plt.yscale("log")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"movimentacoes_vs_tamanho_{caso}.png")

print("Gráficos gerados: tempo_vs_tamanho_*.png, comparacoes_vs_tamanho_*.png, movimentacoes_vs_tamanho_*.png")
