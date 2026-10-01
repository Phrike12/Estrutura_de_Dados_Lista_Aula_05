#include <stdio.h>
#include <string.h>
#include "Lista.h"

static struct produto mk_prod(int codigo, const char *nome, float preco) {
    struct produto p;
    p.codigo = codigo;
    strncpy(p.nome, nome, sizeof(p.nome) - 1);
    p.nome[sizeof(p.nome) - 1] = '\0';
    p.preco = preco;
    return p;
}

static void imprime(const char *rotulo, Lista *li) {
    int i, n = tamanho_lista(li);
    struct produto p;
    printf("\n=== %s (qtd=%d) ===\n", rotulo, n);
    for (i = 1; i <= n; i++) {
        busca_lista_pos(li, i, &p);
        printf("Cod: %d | Nome: %-10s | Preco: R$ %.2f\n", p.codigo, p.nome, p.preco);
    }
    printf("==================================\n");
}

int main(void) {
    Lista *li = cria_lista();
    struct produto p;

    printf("Testando as novas funcoes da UFPB...\n");

    insere_lista_final(li, mk_prod(101, "Mouse", 50.0));
    insere_lista_final(li, mk_prod(102, "Teclado", 150.0));
    insere_lista_final(li, mk_prod(103, "Monitor", 800.0));
    insere_lista_final(li, mk_prod(104, "Fone", 120.0));
    
    imprime("Lista Inicial", li);

    printf("Q1 - Tem espaco para mais 5 itens? %s\n", lista_tem_espaco(li, 5) ? "Sim" : "Nao");

    printf("Q2 - Soma total dos precos: R$ %.2f\n", soma_precos(li));

    if (busca_por_nome(li, "Teclado", &p)) {
        printf("Q3 - Busca por nome ('Teclado'): Encontrado! Codigo: %d, Preco: R$ %.2f\n", p.codigo, p.preco);
    }

    Lista *li_dec = cria_lista();
    insere_lista_decrescente(li_dec, mk_prod(201, "SSD", 250.0));
    insere_lista_decrescente(li_dec, mk_prod(202, "Placa Mae", 600.0));
    insere_lista_decrescente(li_dec, mk_prod(203, "Cabo", 20.0));
    insere_lista_decrescente(li_dec, mk_prod(204, "Processador", 1200.0));
    imprime("Q4 - Lista Decrescente (Por Preco)", li_dec);

    if (remove_mais_caro(li, &p)) {
        printf("Q5 - Produto mais caro removido: %s (R$ %.2f)\n", p.nome, p.preco);
    }
    imprime("Apos remover o mais caro", li);

    int faixa = conta_faixa_preco(li, 50.0, 160.0);
    printf("Q6 - Produtos entre R$ 50 e R$ 160: %d\n", faixa);

    int qtd_removidos = remove_abaixo_de(li, 100.0);
    printf("Q7 - Removidos %d produtos abaixo de R$ 100.00\n", qtd_removidos);
    imprime("Apos remover os baratos", li);


    int qtd_mesclados = mescla_listas(li, li_dec);
    printf("Q8 - Foram mesclados %d produtos da lista de origem para a destino\n", qtd_mesclados);
    imprime("Lista Final apos a Mescla", li);

    libera_lista(li);
    libera_lista(li_dec);

    return 0;
}