#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.
#define MAX 5
#define MAX_PILHA 3

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

typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
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

void push(Pilha *p, Peca *nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Nao e possivel inserir.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = *nova;
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

void pop(Pilha *p, Peca *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Nao e possivel remover.\n");
        return;
    }
    *removida = p->itens[p->topo];
    p->topo--;
}

void exibirFila(Fila *f) {
  printf("Fila de Peças: ");

  for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
    printf("[%s, %d] ", f->itens[idx].tipo, f->itens[idx].id);
  }
  printf("\n");
}

void exibirPilha(Pilha *p) {
    printf("Pilha Reserva: ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%s,%d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}

void exibirEstadoAtual(Fila *f, Pilha *p) {
    exibirFila(f);
    exibirPilha(p);
}


void gerarPeca(Peca *p, int *idGlobal) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4; 
    p->tipo[0] = tipos[indice];
    p->tipo[1] = '\0';
    p->id = (*idGlobal)++;
}

void trocarFrenteComTopo(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Nao e possivel trocar! Fila ou Pilha vazia.\n");
        return;
    }
    int idxFila = f->inicio;
    Peca temp = f->itens[f->inicio];
    f->itens[f->inicio] = p->itens[p->topo];
    p->itens[p->topo] = temp;
    printf("Troca realizada entre a frente da fila e o topo da pilha.\n");
}

void trocarTres(Fila *f, Pilha *p) {
    if (f->total < 3 || p->topo < 2) {
        printf("Nao e possivel trocar! Fila ou Pilha nao possuem 3 pecas.\n");
        return;
    }
    for (int i = 0; i < 3; i++) {
        int idxFila = (f->inicio + i) % MAX;
        Peca temp = f->itens[idxFila];
        f->itens[idxFila] = p->itens[p->topo - i];
        p->itens[p->topo - i] = temp;
    }
    printf("Troca realizada entre os 3 primeiros da fila e os 3 da pilha.\n");
}

void menu() {
    printf("\n===== MENU =====\n");
    printf("1 - Jogar peça\n");
    printf("2 - Reservar peça\n");
    printf("3 - Usar peça da reserva\n");
    printf("4 - Trocar peça da frente com topo da pilha\n");
    printf("5 - Trocar 3 primeiros da fila com os 3 da pilha\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    srand(time(NULL));
    Fila f;
    Pilha reserva;
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
    inicializarPilha(&reserva);

    int idGlobal = 1;
    for (int i = 0; i < MAX; i++) {
        Peca nova;
        gerarPeca(&nova, &idGlobal);
        inserir(&f, &nova);
    }
    
    int opcao;
    do {
        exibirEstadoAtual(&f, &reserva);
        menu();
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado
        printf("\n");
        
        Peca temp;
    
        switch (opcao)
        {
        case 1:
            // Jogar peça
            remover(&f, &temp);
            printf("Peca jogada: [%s, %d]\n", temp.tipo, temp.id);
            gerarPeca(&temp, &idGlobal);
            inserir(&f, &temp);
            break;
        case 2:
            // Reservar peça
            if (filaVazia(&f)) {
                printf("Fila vazia! Nao e possivel reservar.\n");
            } else if (pilhaCheia(&reserva)) {
                printf("Pilha cheia! Nao e possivel reservar mais pecas.\n");
            } else {
                remover(&f, &temp);
                push(&reserva, &temp);
                gerarPeca(&temp, &idGlobal);
                inserir(&f, &temp);
                printf("Peca reservada: [%s, %d]\n", reserva.itens[reserva.topo].tipo, reserva.itens[reserva.topo].id);
            }
            break;
        case 3:
            // Usar peça da reserva
            if (pilhaVazia(&reserva)) {
                printf("Pilha vazia! Nao ha pecas para usar.\n");
            } else {
                pop(&reserva, &temp);
                printf("Peca usada da reserva: [%s, %d]\n", temp.tipo, temp.id);
            }
            break;
        case 4:
            // Trocar peça da frente com topo da pilha
            trocarFrenteComTopo(&f, &reserva);
            break;
        case 5:
            // Trocar 3 primeiros da fila com os 3 da pilha
            trocarTres(&f, &reserva);
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

