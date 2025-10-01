#include <stdio.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.

//int main() {

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Max_Fila 5
#define Max_Nome_Peca 15

typedef struct {                //Struct da peca
   char nome[Max_Nome_Peca];
   int  id;             //Identifica a peca 
} Pecas;

typedef struct {            //Struct da fila
    Pecas itens[Max_Fila];
    int inicio; 
    int fim;
    int total;  
} Fila;


//-----PROTOTIPO DE FUNCOES AUXILIARES-----
void Menu();
void LimparBuffer();
void GerarPeca(Pecas *p);
void InicializarFila(Fila *f);
int FilaCheia(Fila *f);
int FilaVazia(Fila *f);

//-----PROTOTIPO DE FUNCOES DA FILA
void Inserir_Enqueue(Fila *f, Pecas *p);        //Insere no final da fila
Pecas Remover_Dequeue(Fila *f);                  //Remove do inicio
void Exibir(Fila *f);

int main(){
    int opcao;
    Fila f;
    Pecas p;
    Pecas peca_removida;

    srand(time(NULL)); //Para as pecas nao serem sempre iguais

    InicializarFila(&f);


    printf("Jogo Tetris Stack\n\n");
    printf("---------------------\n");

    do{
        Menu();
        printf("Escolha um opcao: \n");
        scanf("%d", &opcao);
        LimparBuffer();

        switch (opcao) {
        
            case 1:
                    printf("----Jogar peca----\n");
                    printf("---------------------\n");
                    
                    peca_removida = Remover_Dequeue(&f);
                    if (peca_removida.id != 0) {
                    printf("Peca jogada: [%s, ID:%d]\n", peca_removida.nome, peca_removida.id);
                    }
                    Exibir(&f);
              
                break;

            case 2:
                    printf("----Inserir peca----\n");
                    printf("---------------------\n");
                    GerarPeca(&p);
                    Inserir_Enqueue(&f, &p);
                    Exibir(&f);
                break;

            case 0: 
                printf("Saindo \n");
                break;
        
        default:
            printf("Opcao invalida\n");
            break;
        }

    } while (opcao != 0);
    

    return 0;
}

//-----FUNCOES AUXILIARES-----
void Menu(){
    printf("1- Jogar Peca(dequeue)\n");
    printf("2- Inserir Peca (enqueue)\n");
    printf("0- Sair\n");
}
void LimparBuffer(){
    int c; 
    while ((c = getchar()) != '\n' && c != EOF); 
}
void GerarPeca(Pecas *p) {
    static int contador_id = 1; // Garante IDs únicos entre chamadas
    char nomes[][Max_Nome_Peca] = {"O", "I", "T", "L"}; // Pecas do Tetris
    int total_nomes = 4;

    int indice = rand() % total_nomes; // Escolher nome aleatório

    strcpy(p->nome, nomes[indice]);     //Copia o nome gerado para a fila
    p->id = contador_id++;              //Atualiza o id com incremento

    printf("Peca gerada: [%s, ID:%d]\n", p->nome, p->id);
}


void InicializarFila(Fila *f){

    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}
int FilaCheia(Fila *f) {        //Funcao de verificacao de fila cheia. Para nao fazer manualmente 
    return f->total == Max_Fila;
}
int FilaVazia(Fila *f){         //Funcao de verificacao de fila vazia. Para nao fazer manualmente
    return f->total == 0;
}

//-----FUNCOES DA FILA-----
void Inserir_Enqueue(Fila *f, Pecas *p){
    if (FilaCheia(f)) {                      //Verifica se a fila esta cheia.                            
        printf("Fila cheia, nao é possivel inserir \n");
        return;
    }
    //Insere 
    f->itens[f->fim] = *p;
    f->fim = (f->fim +1) % Max_Fila;    //Logica circular
    f->total++;                    //Atualizacao da fila com incremento

}

Pecas Remover_Dequeue(Fila *f) {
    Pecas peca_nula = { .id = 0, .nome = "" };

    if (FilaVazia(f)) {                     //Verifica se a fila esta vazia
        printf("Fila vazia, nao é possivel remover item\n");
        return peca_nula;
    }
    //Remove as pecas
    Pecas removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % Max_Fila;         //Logica circular
    f->total--;                                     //Atualiza a fila com decremento 

    return removida;
}

void Exibir(Fila *f){

    printf("Fila: ");

    if (FilaVazia(f)) {                         //Verifica se a fila noa esta vazia
        printf("Fila Vazia, não há o que exibir\n");
        return;
    }
    
     int id_atual = f->inicio;
    for (int i = 0; i < f->total;  i++) {   //for que percorre a fila 
    
        printf("[%s, ID:%d]", f->itens[id_atual].nome, f->itens[id_atual].id);
        
        if (i < f->total - 1) {     //Imprime '-' entre os elementos da fila
            printf(" - ");      
        }

        id_atual = (id_atual + 1) % Max_Fila;   // Move para a próxima posição da fila segundo a lógica circular
    }
    printf("\n");

}

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


    //return 0;
//}

