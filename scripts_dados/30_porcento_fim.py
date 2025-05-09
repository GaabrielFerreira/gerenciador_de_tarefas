import random

categorias = ["Estudos", "Trabalho", "Casa", "Pessoal", "Saude", "Lazer"]

def gerar_arquivo_misto_id_crescente(nome, quantidade):
    qtd_desordenada = int(quantidade * 0.7)
    qtd_ordenada = quantidade - qtd_desordenada

    tarefas = []

    # Parte 1: gerar dados aleatorios com ID crescente (dados desordenados)
    for id_atual in range(1, qtd_desordenada + 1):
        prioridade = random.randint(1, 5)
        nome_tarefa = f"Tarefa {id_atual} {'Importante' if id_atual % 10 == 0 else ''}"
        descricao = f"Descricao detalhada da tarefa numero {id_atual}"
        categoria = random.choice(categorias)
        tarefas.append((id_atual, nome_tarefa, descricao, prioridade, categoria))

    # Parte 2: gerar dados ordenados por prioridade com ID crescente
    id_atual = qtd_desordenada + 1
    por_prioridade = qtd_ordenada // 5
    for prioridade in range(1, 6):
        for _ in range(por_prioridade):
            nome_tarefa = f"Tarefa {id_atual} {'Importante' if id_atual % 10 == 0 else ''}"
            descricao = f"Descricao detalhada da tarefa numero {id_atual}"
            categoria = categorias[(id_atual - 1) % len(categorias)]
            tarefas.append((id_atual, nome_tarefa, descricao, prioridade, categoria))
            id_atual += 1

    # Escreve no arquivo mantendo IDs crescentes
    with open(nome, "w") as f:
        for tarefa in tarefas:
            f.write(f"{tarefa[0]};{tarefa[1]};{tarefa[2]};{tarefa[3]};{tarefa[4]}\n")

if __name__ == "__main__":
    tamanhos = [100, 1000, 10000, 20000, 30000, 40000, 50000]
    for tam in tamanhos:
        gerar_arquivo_misto_id_crescente(f"tarefas_misto_id_crescente_{tam}.txt", tam)
    print("Arquivos com dados mistos e IDs crescentes gerados com sucesso!")
