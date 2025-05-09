import sys

categorias = ["Estudos", "Trabalho", "Casa", "Pessoal", "Saúde", "Lazer"]

def gerar_arquivo_decrescente(nome, quantidade):
    with open(nome, "w") as f:
        por_prioridade = quantidade // 5
        id_atual = 1

        for prioridade in range(5, 0, -1):  # 5 a 1
            for _ in range(por_prioridade):
                nome_tarefa = f"Tarefa {id_atual} {'Importante' if id_atual % 10 == 0 else ''}"
                descricao = f"Descrição detalhada da tarefa número {id_atual}"
                categoria = categorias[(id_atual - 1) % len(categorias)]
                f.write(f"{id_atual};{nome_tarefa};{descricao};{prioridade};{categoria}\n")
                id_atual += 1

if __name__ == "__main__":
    tamanhos = [100, 1000, 10000, 20000, 30000, 40000, 50000]
    for tam in tamanhos:
        gerar_arquivo_decrescente(f"tarefas_decrescente_{tam}.txt", tam)
    print("Arquivos DECRESCENTES gerados com sucesso!")