// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define MAX_PILHA 3

//  Struct que representa uma peça
typedef struct {
    char tipo;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// ESTRUTURA DA PILHA LINEAR
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// Variável global para controlar IDs
int contadorID = 0;

// Funções de fila
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

//enqueue(inserir)
void inserir(Fila *f, Peca p) {
    if(filaCheia(f)) {
        printf("Fila cheia. Não é possivel inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

//dequeue(Remover)
Peca remover(Fila *f) {
    Peca removido = {'-', -1}; // peça nula
    if(filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return removido;
    }
    removido = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return removido;
}

void mostrarFila(Fila *f) {
    printf("\n🎮 Fila de Peças Futuras:\n");
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c %d] ", f->itens[idx].tipo, f->itens[idx].id);
    }
    printf("\n\n");
}

//Funções da Pilha
void inicializarPilha(Pilha *p) {
    p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca elem) {
    if (pilhaCheia(p)) {
        printf("⚠️ Pilha cheia! Não é possível reservar mais peças.\n");
        return;
    }
    p->itens[++p->topo] = elem;
}

Peca pop(Pilha *p) {
    Peca removido = {'-', -1};
    if (pilhaVazia(p)) {
        printf("⚠️ Pilha vazia! Não há peças reservadas.\n");
        return removido;
    }
    return p->itens[p->topo--];
}

void mostrarPilha(Pilha *p) {
    printf("Pilha de reserva (Topo -> Base): ");
    if (pilhaVazia(p)) {
        printf("(vazia)\n");
        return;
    }
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}

// Função para gerar peças automaticamente
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4]; // escolhe aleatoriamente
    nova.id = contadorID++;
    return nova;
}

int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    srand(time(NULL)); //para gerar peças diferentes a cada execução
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    //inicializar a fila com 5 peçaas
    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca());
    }
    
    int opcao;
    do{
        printf("\n=== Estado atual ===\n");
        mostrarFila(&fila);
        mostrarPilha(&pilha);

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            Peca jogada = remover(&fila);
            if (jogada.id != -1) {
                printf("➡️ Jogou a peça [%c %d]\n", jogada.tipo, jogada.id);
                inserir(&fila, gerarPeca());
            }
        }
        else if (opcao == 2) {
            if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                Peca reservada = remover(&fila);
                push(&pilha, reservada);
                printf("📥 Reservou a peça [%c %d]\n", reservada.tipo, reservada.id);
                inserir(&fila, gerarPeca()); // mantém fila cheia
            } else {
                printf("⚠️ Não foi possível reservar (fila vazia ou pilha cheia).\n");
            }
        }
        else if (opcao == 3) {
            Peca usada = pop(&pilha);
            if (usada.id != -1)
                printf("🎯 Usou a peça reservada [%c %d]\n", usada.tipo, usada.id);
            inserir(&fila, gerarPeca()); // mantém fila cheia
        }
        else if (opcao == 0) {
            printf("👋 Saindo...\n");
        }
        else {
            printf("⚠️ Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}