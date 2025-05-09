import random

categorias = ["Estudos", "Trabalho", "Casa", "Pessoal", "Saude", "Lazer"]

def gerar_arquivo(nome, quantidade):
    indices_importantes = set(random.sample(range(1, quantidade + 1), int(quantidade * 0.3)))

    with open(nome, "w") as f:
        for i in range(1, quantidade + 1):
            importante = "Importante" if i in indices_importantes else ""
            nome_tarefa = f"Tarefa {i} {importante}"
            descricao = f"Descricao detalhada da tarefa numero {i}"
            prioridade = random.randint(1, 5)
            categoria = random.choice(categorias)
            f.write(f"{i};{nome_tarefa};{descricao};{prioridade};{categoria}\n")

if __name__ == "__main__":
    tamanhos = [100, 1000, 10000, 20000, 30000, 40000, 50000]
    for tam in tamanhos:
        gerar_arquivo(f"tarefas_{tam}.txt", tam)
    print("Arquivos gerados com sucesso!")