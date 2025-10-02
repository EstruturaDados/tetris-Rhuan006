// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

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
    inicializarFila(&fila);

    //inicializar a fila com 5 peçaas
    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca());
    }
    
    int opcao;
    do{
        mostrarFila(&fila);

        printf("Opções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
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
            Peca nova = gerarPeca();
            inserir(&fila, nova);
            printf("➕ Inserida peça [%c %d]\n", nova.tipo, nova.id);
        }
        else if (opcao == 0) {
            printf("👋 Saindo do jogo...\n");      
        }
        else {
            printf("Opção inválida!\n");
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

