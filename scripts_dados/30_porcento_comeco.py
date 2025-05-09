import random

categorias = ["Estudos", "Trabalho", "Casa", "Pessoal", "Saude", "Lazer"]

def gerar_arquivo_misto(nome, quantidade):
    qtd_ordenada = int(quantidade * 0.3)
    qtd_restante = quantidade - qtd_ordenada

    tarefas = []

    # Parte 1: tarefas ordenadas por prioridade (1 a 5)
    por_prioridade = qtd_ordenada // 5
    id_atual = 1
    for prioridade in range(1, 6):
        for _ in range(por_prioridade):
            nome_tarefa = f"Tarefa {id_atual} {'Importante' if id_atual % 10 == 0 else ''}"
            descricao = f"Descricao detalhada da tarefa numero {id_atual}"
            categoria = categorias[(id_atual - 1) % len(categorias)]
            tarefas.append((id_atual, nome_tarefa, descricao, prioridade, categoria))
            id_atual += 1

    # Parte 2: tarefas aleatorias e desordenadas
    for _ in range(qtd_restante):
        prioridade = random.randint(1, 5)
        nome_tarefa = f"Tarefa {id_atual} {'Importante' if id_atual % 10 == 0 else ''}"
        descricao = f"Descricao detalhada da tarefa numero {id_atual}"
        categoria = random.choice(categorias)
        tarefas.append((id_atual, nome_tarefa, descricao, prioridade, categoria))
        id_atual += 1

    # Embaralha apenas a parte não ordenada (os últimos 70%)
    parte_ordenada = tarefas[:qtd_ordenada]
    parte_bagunçada = tarefas[qtd_ordenada:]
    random.shuffle(parte_bagunçada)

    # Junta e escreve no arquivo
    tarefas_finais = parte_ordenada + parte_bagunçada
    with open(nome, "w") as f:
        for tarefa in tarefas_finais:
            f.write(f"{tarefa[0]};{tarefa[1]};{tarefa[2]};{tarefa[3]};{tarefa[4]}\n")

if __name__ == "__main__":
    tamanhos = [100, 1000, 10000, 20000, 30000, 40000, 50000]
    for tam in tamanhos:
        gerar_arquivo_misto(f"tarefas_misto_{tam}.txt", tam)
    print("Arquivos com 30 por cento ordenado gerados com sucesso!")
