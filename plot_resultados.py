import pandas as pd
import matplotlib.pyplot as plt
import os
import numpy as np
import math

# Criar pasta de graficos se não existir
os.makedirs("graficos", exist_ok=True)

# === 1. Ler CSV ===
df = pd.read_csv("resultados.csv")

# Garantir tipos corretos
df["tamanho"] = df["tamanho"].astype(int)
df["tempo_s"] = df["tempo_s"].astype(float)
df["comparacoes"] = df["comparacoes"].astype(float)
df["movimentacoes"] = df["movimentacoes"].astype(float)

# Ordem fixa dos algoritmos
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
df["algoritmo"] = pd.Categorical(
    df["algoritmo"],
    categories=ordem_algoritmos,
    ordered=True
)

# === 2. Agregar por (algoritmo, caso, tamanho) -> médias ===
agrupado = df.groupby(["algoritmo", "caso", "tamanho"], as_index=False).mean()

casos = sorted(agrupado["caso"].unique())
tamanhos = sorted(agrupado["tamanho"].unique())
algoritmos_presentes = [a for a in ordem_algoritmos
                        if a in agrupado["algoritmo"].unique()]

# Pequeno epsilon se um dia quiser evitar log(0)
EPS_TEMPO = 0.0

# === 3. Tempo medio × Tamanho (linha) — manter TODOS os algoritmos ===
for caso in casos:
    sub = agrupado[agrupado["caso"] == caso]

    plt.figure()
    for alg in algoritmos_presentes:
        sub_alg = sub[sub["algoritmo"] == alg]
        if sub_alg.empty:
            continue
        sub_alg = sub_alg.sort_values("tamanho")
        xs = sub_alg["tamanho"].values
        ys = (sub_alg["tempo_s"] + EPS_TEMPO).values

        plt.plot(xs, ys, marker="o", alpha=0.5, label=alg)

    plt.xlabel("Tamanho do vetor (n)")
    plt.ylabel("Tempo medio (s)")
    plt.title(f"Tempo medio x Tamanho - Caso: {caso}")
    plt.xscale("log")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"graficos/tempo_vs_tamanho_{caso}.png")

# === 4. Tempo medio por CADA tamanho de vetor (um gráfico por tamanho) ===
# Para cada caso e cada tamanho, um gráfico de barras: algoritmos no eixo x, tempo no eixo y
for caso in casos:
    sub_caso = agrupado[agrupado["caso"] == caso]

    for tam in tamanhos:
        sub_ct = sub_caso[sub_caso["tamanho"] == tam]
        if sub_ct.empty:
            continue

        # algoritmos realmente presentes para esse (caso, tamanho)
        algs_tam = [alg for alg in algoritmos_presentes
                    if alg in sub_ct["algoritmo"].values]

        tempos = []
        for alg in algs_tam:
            tempo_alg = sub_ct[sub_ct["algoritmo"] == alg]["tempo_s"].values[0]
            tempos.append(tempo_alg)

        x = np.arange(len(algs_tam))

        plt.figure(figsize=(8, 5))
        plt.bar(x, np.array(tempos) + EPS_TEMPO)
        plt.xticks(x, algs_tam, rotation=45, ha="right")
        plt.xlabel("Algoritmo")
        plt.ylabel("Tempo medio (s)")
        plt.title(f"Tempo medio por algoritmo — Tamanho {tam} — Caso: {caso}")
        plt.tight_layout()
        plt.savefig(f"graficos/barras_tempo_tam{tam}_{caso}.png")

# === 5. Movimentacoes × Tamanho (linha) — manter como estava ===
for caso in casos:
    sub = agrupado[agrupado["caso"] == caso]

    plt.figure()
    for alg in algoritmos_presentes:
        sub_alg = sub[sub["algoritmo"] == alg]
        if sub_alg.empty:
            continue
        sub_alg = sub_alg.sort_values("tamanho")
        xs = sub_alg["tamanho"].values
        ys = sub_alg["movimentacoes"].values

        plt.plot(xs, ys, marker="o", alpha=0.5, label=alg)

    plt.xlabel("Tamanho do vetor (n)")
    plt.ylabel("Movimentacoes medias")
    plt.title(f"Movimentacoes x Tamanho - Caso: {caso}")
    plt.xscale("log")
    plt.yscale("log")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"graficos/movimentacoes_vs_tamanho_{caso}.png")

# === 6. Comparacoes × Tamanho — APENAS em grade (um subplot por algoritmo) ===
for caso in casos:
    sub_caso = agrupado[agrupado["caso"] == caso]

    algs = [alg for alg in algoritmos_presentes
            if alg in sub_caso["algoritmo"].values]
    n = len(algs)
    cols = 3
    rows = math.ceil(n / cols)

    fig, axes = plt.subplots(
        rows, cols,
        figsize=(4 * cols, 3 * rows),
        sharex=True, sharey=True
    )
    axes = axes.ravel()

    for i, alg in enumerate(algs):
        ax = axes[i]
        sub_alg = sub_caso[sub_caso["algoritmo"] == alg].sort_values("tamanho")

        xs = sub_alg["tamanho"].values
        ys = sub_alg["comparacoes"].values

        ax.plot(xs, ys, marker="o", linewidth=2, alpha=0.85)
        ax.set_title(alg, fontsize=10)
        ax.set_xscale("log")
        ax.set_yscale("log")
        ax.grid(True, which="both", linestyle="--", linewidth=0.5)

        if i % cols == 0:
            ax.set_ylabel("Comparacoes medias")
        if i // cols == rows - 1:
            ax.set_xlabel("Tamanho (n)")

    # Apaga eixos restantes se sobrar espaço na grade
    for j in range(i + 1, rows * cols):
        fig.delaxes(axes[j])

    fig.suptitle(f"Comparacoes x Tamanho — Painel por algoritmo — Caso: {caso}",
                 fontsize=14)
    plt.tight_layout(rect=[0, 0, 1, 0.95])
    plt.savefig(f"graficos/painel_comparacoes_{caso}.png")
    plt.close(fig)

print("Graficos gerados (arquivos .png) na pasta 'graficos'.")
