import random
import sys

categorias = ["Estudos", "Trabalho", "Casa", "Pessoal", "Saúde", "Lazer"]

def gerar_arquivo(nome, quantidade):
    with open(nome, "w") as f:
        for i in range(1, quantidade+1):
            nome_tarefa = f"Tarefa {i} {'Importante' if i%10 == 0 else ''}"  # 10% com 'Importante'
            descricao = f"Descrição detalhada da tarefa número {i}"
            prioridade = random.randint(1, 5)
            categoria = random.choice(categorias)
            f.write(f"{i};{nome_tarefa};{descricao};{prioridade};{categoria}\n")

if __name__ == "__main__":
    tamanhos = [100, 1000, 10000, 20000, 30000, 40000, 50000]
    for tam in tamanhos:
        gerar_arquivo(f"tarefas_{tam}.txt", tam)
    print("Arquivos gerados com sucesso!")