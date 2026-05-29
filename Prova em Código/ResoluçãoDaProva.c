#include <stdio.h>
#include <string.h>

#define TAM 100

struct Categoria {
    int codigo;
    char nome[50];
};

struct Produto {
    int codigo;
    char titulo[100];
    char descricao[256];
    int categoria; 
    int preco;   
};

// Questão 1
void cadastrarCategoria(struct Categoria v[], int *qtd) {
    
    if (*qtd >= TAM) {
        printf("Capacidade máxima de categorias atingida.\n");
        return;
    }

    int cod;
    char nome[50];
    int codigo_existente;

    do {
        codigo_existente = 0;
        printf("Digite o código da categoria: ");
        scanf("%d", &cod);
       
        for (int i = 0; i < *qtd; i++) {
            if (v[i].codigo == cod) {
                printf("Código já cadastrado. Digite outro.\n");
                codigo_existente = 1;
                break;
            }
        }
    } while (codigo_existente);

    printf("Digite o nome da categoria: ");
    scanf(" %49[^\n]", nome); 

    v[*qtd].codigo = cod;
    strcpy(v[*qtd].nome, nome);

    (*qtd)++;
}

// Questão 2
void imprimirCategorias(struct Categoria v[], int qtd) {
    printf("\n--- Categorias cadastradas ---\n");
    for (int i = 0; i < qtd; i++) {
        printf("Código: %d | Nome: %s\n", v[i].codigo, v[i].nome);
    }
}

// Questão 3
void imprimirProdutos(struct Produto vp[], int qtdProdutos,
                      struct Categoria vc[], int qtdCategorias) {
    printf("\n--- Lista de Produtos ---\n");
    for (int i = 0; i < qtdProdutos; i++) {
        
        char nomeCategoria[50] = "Nao encontrada";
        for (int j = 0; j < qtdCategorias; j++) {
            if (vp[i].categoria == vc[j].codigo) {
                strcpy(nomeCategoria, vc[j].nome);
                break;
            }
        }

        
        double preco_real = vp[i].preco / 100.0;

        
        printf("Código: %d\n", vp[i].codigo);
        printf("Título: %s\n", vp[i].titulo);
        printf("Descrição: %s\n", vp[i].descricao);
        printf("Categoria: %s\n", nomeCategoria);
        printf("Preço: R$ %.2f\n\n", preco_real);
    }
}

// Questão 4
void selectionSortPorDescricao(struct Produto v[], int qtd) {
    int i, j, min_idx;
    struct Produto temp;
    
    for (i = 0; i < qtd - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < qtd; j++) {
            if (strcmp(v[j].descricao, v[min_idx].descricao) < 0) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            temp = v[i];
            v[i] = v[min_idx];
            v[min_idx] = temp;
        }
    }
}

// Questão 5
void buscaBinariaPorDescricao(struct Produto v[], int qtd, char *x) {
    int esq = 0, dir = qtd - 1, meio;
    int encontrado = -1;

    while (esq <= dir) {
        meio = (esq + dir) / 2;
        int cmp = strcmp(v[meio].descricao, x);
        if (cmp == 0) {
            encontrado = meio;
            break;
        } else if (cmp < 0) {
            esq = meio + 1;
        } else {
            dir = meio - 1;
        }
    }

    if (encontrado != -1) {
        printf("Produto encontrado:\n");
        printf("Código: %d\n", v[encontrado].codigo);
        printf("Título: %s\n", v[encontrado].titulo);
        printf("Descrição: %s\n", v[encontrado].descricao);
        printf("Categoria (código): %d\n", v[encontrado].categoria);
        printf("Preço: R$ %.2f\n", v[encontrado].preco / 100.0);
    } else {
        printf("Nenhum produto com a descrição \"%s\" foi encontrado.\n", x);
    }
}