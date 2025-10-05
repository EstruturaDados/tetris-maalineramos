#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.
#define MAX 5

typedef struct {
    char tipo[2];
    int id;
} Peca;

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

void inserir(Fila *f, Peca *p){
    if(filaCheia(f)){
        printf("Fila cheia! Nao e possivel inserir.\n");
        return;
    }
    f->itens[f->fim] = *p;// Insere o elemento no fim da fila
    f->fim = (f->fim + 1) % MAX;// Incrementa o índice do fim circularmente
    f->total++;// Incrementa o total de elementos na fila

}

void remover(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia! Nao e possivel remover.\n");
        return;
    }
    *p = f->itens[f->inicio];// Obtém o elemento do início da fila
    f->inicio = (f->inicio + 1) % MAX;// Incrementa o índice do início circularmente
    f->total--;// Decrementa o total de elementos na fila
    
}

void exibirFila(Fila *f) {
  printf("Fila Atual: ");

  for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
    printf("[%s, %d] ", f->itens[idx].tipo, f->itens[idx].id);
  }
  printf("\n");
}

void menu() {
    printf("\nMenu:\n");
    printf("1 - Jogar peça (remover da frente)\n");
    printf("2 - Inserir nova peça (adicionar ao fim)\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

void gerarPeca(Peca *p, int *idGlobal) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4; 
    p->tipo[0] = tipos[indice];
    p->tipo[1] = '\0';
    p->id = (*idGlobal)++;
}


int main() {
    srand(time(NULL));
    Fila f;
    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.
    
    inicializarFila(&f);

    int 

    idGlobal = 1;
    for (int i = 0; i < MAX; i++) {
        Peca nova;
        gerarPeca(&nova, &idGlobal);
        inserir(&f, &nova);
    }

    
    int opcao;
    do {
        exibirFila(&f);
        menu();
        scanf("%d", &opcao);
        printf("\n");
        
        Peca removida, novaPeca;
    
        switch (opcao)
        {
        case 1:
            ;
            remover(&f, &removida);
            printf("Peca jogada: [%s, %d]\n", removida.tipo, removida.id);
            break;
        case 2:
            gerarPeca(&novaPeca, &idGlobal);
            inserir(&f, &novaPeca);
            printf("Nova peca inserida: [%s, %d]\n", novaPeca.tipo, novaPeca.id);
            break;
        
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    } while (opcao != 0);
 



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


    return 0;
}

