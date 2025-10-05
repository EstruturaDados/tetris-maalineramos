#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.
#define MAX 5
#define MAX_PILHA 3

// --- Estruturas Principais ---
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

// --- Histórico de Ações ---
typedef struct {
    char acao; // 'J' = jogar, 'R' = reservar, 'U' = usar
    Peca peca;
} Acao;

typedef struct {
    Acao itens[20];
    int topo;
} PilhaHistorico;

// --- Funções  ---
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

void inicializarHistorico(PilhaHistorico *h) {
    h->topo = -1;
}

int filaCheia(Fila *f) { return f->total == MAX; }

int pilhaCheia(Pilha *p) { return p->topo == MAX_PILHA - 1; }

int filaVazia(Fila *f) { return f->total == 0; }

int pilhaVazia(Pilha *p) { return p->topo == -1; }

int historicoVazio(PilhaHistorico *h) { return h->topo == -1; }

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

// --- Funções de Exibição ---
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

// ---  Gerar Peça ---
void gerarPeca(Peca *p, int *idGlobal) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indice = rand() % 4; 
    p->tipo[0] = tipos[indice];
    p->tipo[1] = '\0';
    p->id = (*idGlobal)++;
}

// --- Funções de Troca ---
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

// --- Histórico ---
void registrarAcao(PilhaHistorico *h, char tipo, Peca *p) {
    if (h->topo == 19) return;
    h->topo++;
    h->itens[h->topo].acao = tipo;
    h->itens[h->topo].peca = *p;
}

void desfazer(PilhaHistorico *h, Fila *f, Pilha *p) {
    if (historicoVazio(h)) {
        printf("Nenhuma jogada para desfazer.\n");
        return;
    }

    Acao ultima = h->itens[h->topo--];

    switch (ultima.acao) {
        case 'J': // desfaz jogar
            if (!filaCheia(f)) {
                f->inicio = (f->inicio - 1 + MAX) % MAX;
                f->itens[f->inicio] = ultima.peca;
                f->total++;
                printf("Desfez jogada: [%s,%d] voltou à fila.\n", ultima.peca.tipo, ultima.peca.id);
            }
            break;
        case 'R': // desfaz reserva
            if (!pilhaVazia(p)) {
                Peca removida;
                pop(p, &removida);
                inserir(f, &removida);
                printf("Desfez reserva: [%s,%d] voltou à fila.\n", removida.tipo, removida.id);
            }
            break;
        case 'U': // desfaz uso
            if (!pilhaCheia(p)) {
                push(p, &ultima.peca);
                printf("Desfez uso: [%s,%d] devolvida à reserva.\n", ultima.peca.tipo, ultima.peca.id);
            }
            break;
        default:
            printf("Ação desconhecida.\n");
    }
}

// --- Inversão Geral ---
void inverterEstruturas(Fila *f, Pilha *p) {
    Fila novaFila;
    Pilha novaPilha;
    inicializarFila(&novaFila);
    inicializarPilha(&novaPilha);

    for (int i = p->topo; i >= 0; i--)
        inserir(&novaFila, &p->itens[i]);

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX)
        push(&novaPilha, &f->itens[idx]);

    *f = novaFila;
    *p = novaPilha;

    printf("Fila e pilha foram invertidas!\n");
}

// --- Menu ---
void menu() {
    printf("\n===== MENU =====\n");
    printf("1 - Jogar peça\n");
    printf("2 - Reservar peça\n");
    printf("3 - Usar peça da reserva\n");
    printf("4 - Trocar peça da frente com topo da pilha\n");
    printf("5 - Desfazer última jogada\n");
    printf("6 - Inverter fila com pilha\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    srand(time(NULL));
    Fila f;
    Pilha reserva;
    PilhaHistorico historico;
    
    inicializarFila(&f);
    inicializarPilha(&reserva);
    inicializarHistorico(&historico);
    
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
            if (filaVazia(&f) || pilhaCheia(&reserva)) {
                printf("Nao e possivel reservar.\n");
                break;
            }
            remover(&f, &temp);
            registrarAcao(&historico, 'R', &temp);
            push(&reserva, &temp);
            gerarPeca(&temp, &idGlobal);
            inserir(&f, &temp);
            printf("Peca reservada!\n");
            break;
        case 3:
            // Usar peça da reserva
            if (pilhaVazia(&reserva)) {
                printf("Reserva vazia!\n");
                break;
            }
            pop(&reserva, &temp);
            registrarAcao(&historico, 'U', &temp);
            printf("Peca usada: [%s,%d]\n", temp.tipo, temp.id);
            break;
        case 4:
            // Trocar peça da frente com topo da pilha
            trocarFrenteComTopo(&f, &reserva);
            break;
        case 5:
            // Desfazer última jogada
            desfazer(&historico, &f, &reserva);
            break;
        case 6:
            // Inverter fila com pilha
            inverterEstruturas(&f, &reserva);
            break;    
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            break;
        }
    } while (opcao != 0);

    return 0;
}

