#include <stdio.h>
#include <string.h>
 
/* ── Constantes ─────────────────────────────────────────── */
#define MAX_ALUNOS 100       /* Capacidade máxima do cadastro */
#define TAM_NOME   100       /* Tamanho máximo do nome        */
 
/* ── Estrutura de dados do aluno ────────────────────────── */
typedef struct {
    char  nome[TAM_NOME];   /* Nome completo do aluno        */
    int   idade;            /* Idade em anos                 */
    int   matricula;        /* Número de matrícula (único)   */
    float notaFinal;        /* Nota final (0.0 a 10.0)       */
} Aluno;
 
/* ── Protótipos das funções ─────────────────────────────── */
void  inserirAluno   (Aluno vetor[], int *total);
void  listarAlunos   (const Aluno vetor[], int total);
void  buscarAluno    (const Aluno vetor[], int total);
void  atualizarNota  (Aluno vetor[], int total);
int   encontrarIndice(const Aluno vetor[], int total, int matricula);
void  exibirAluno    (const Aluno *a);
void  exibirMenu     (void);
 
/* ============================================================
 *  FUNÇÃO PRINCIPAL
 * ============================================================ */
int main(void) {
    Aluno cadastro[MAX_ALUNOS]; /* Vetor que armazena todos os alunos */
    int   total = 0;            /* Quantidade atual de alunos         */
    int   opcao;
 
    printf("===========================================\n");
    printf("  SISTEMA DE GERENCIAMENTO DE ALUNOS\n");
    printf("===========================================\n");
 
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); /* Limpa o '\n' que sobra no buffer */
 
        switch (opcao) {
            case 1: inserirAluno (cadastro, &total);     break;
            case 2: listarAlunos (cadastro,  total);     break;
            case 3: buscarAluno  (cadastro,  total);     break;
            case 4: atualizarNota(cadastro,  total);     break;
            case 0: printf("\nSistema encerrado. Ate logo!\n"); break;
            default: printf("\nOpcao invalida. Tente novamente.\n");
        }
 
    } while (opcao != 0);
 
    return 0;
}
 
/* ============================================================
 *  exibirMenu
 *  Exibe as opções disponíveis ao usuário.
 * ============================================================ */
void exibirMenu(void) {
    printf("\n-------------------------------------------\n");
    printf("  [1] Inserir aluno\n");
    printf("  [2] Listar alunos\n");
    printf("  [3] Buscar aluno por matricula\n");
    printf("  [4] Atualizar nota final\n");
    printf("  [0] Sair\n");
    printf("-------------------------------------------\n");
}
 
/* ============================================================
 *  inserirAluno
 *  Adiciona um novo aluno ao vetor de cadastro.
 *  Verifica se a matrícula já existe antes de inserir.
 * ============================================================ */
void inserirAluno(Aluno vetor[], int *total) {
    /* Verifica se o cadastro atingiu o limite */
    if (*total >= MAX_ALUNOS) {
        printf("\nCadastro cheio! Limite de %d alunos atingido.\n", MAX_ALUNOS);
        return;
    }
 
    Aluno novo; /* Aluno temporário para receber os dados */
 
    printf("\n--- INSERIR ALUNO ---\n");
 
    printf("Nome: ");
    fgets(novo.nome, TAM_NOME, stdin);
    /* Remove o '\n' que fgets inclui no final da string */
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
 
    printf("Idade: ");
    scanf("%d", &novo.idade);
 
    printf("Matricula: ");
    scanf("%d", &novo.matricula);
 
    /* Verifica duplicidade de matrícula */
    if (encontrarIndice(vetor, *total, novo.matricula) != -1) {
        printf("\nErro: Matricula %d ja cadastrada!\n", novo.matricula);
        getchar();
        return;
    }
 
    printf("Nota final (0.0 a 10.0): ");
    scanf("%f", &novo.notaFinal);
    getchar();
 
    /* Insere o aluno no vetor e incrementa o contador */
    vetor[*total] = novo;
    (*total)++;
 
    printf("\nAluno \"%s\" cadastrado com sucesso!\n", novo.nome);
}
 
/* ============================================================
 *  listarAlunos
 *  Exibe todos os alunos cadastrados no sistema.
 * ============================================================ */
void listarAlunos(const Aluno vetor[], int total) {
    printf("\n--- LISTA DE ALUNOS (%d cadastrado(s)) ---\n", total);
 
    if (total == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }
 
    /* Percorre o vetor e exibe cada aluno */
    for (int i = 0; i < total; i++) {
        printf("\n[%d] ", i + 1);
        exibirAluno(&vetor[i]);
    }
}
 
/* ============================================================
 *  buscarAluno
 *  Solicita uma matrícula e exibe o aluno correspondente.
 * ============================================================ */
void buscarAluno(const Aluno vetor[], int total) {
    int matricula;
 
    printf("\n--- BUSCAR ALUNO ---\n");
    printf("Informe a matricula: ");
    scanf("%d", &matricula);
    getchar();
 
    int idx = encontrarIndice(vetor, total, matricula);
 
    if (idx == -1) {
        printf("\nAluno com matricula %d nao encontrado.\n", matricula);
        return;
    }
 
    printf("\nAluno encontrado:\n");
    exibirAluno(&vetor[idx]);
}
 
/* ============================================================
 *  atualizarNota
 *  Localiza um aluno pela matrícula e atualiza sua nota final.
 * ============================================================ */
void atualizarNota(Aluno vetor[], int total) {
    int   matricula;
    float novaNota;
 
    printf("\n--- ATUALIZAR NOTA ---\n");
    printf("Informe a matricula: ");
    scanf("%d", &matricula);
    getchar();
 
    int idx = encontrarIndice(vetor, total, matricula);
 
    if (idx == -1) {
        printf("\nAluno com matricula %d nao encontrado.\n", matricula);
        return;
    }
 
    printf("Aluno encontrado: %s\n", vetor[idx].nome);
    printf("Nota atual: %.2f\n", vetor[idx].notaFinal);
    printf("Nova nota (0.0 a 10.0): ");
    scanf("%f", &novaNota);
    getchar();
 
    /* Valida o intervalo da nota antes de salvar */
    if (novaNota < 0.0f || novaNota > 10.0f) {
        printf("\nNota invalida! Deve ser entre 0.0 e 10.0.\n");
        return;
    }
 
    vetor[idx].notaFinal = novaNota;
    printf("\nNota atualizada com sucesso!\n");
}
 
/* ============================================================
 *  encontrarIndice
 *  Busca um aluno pela matrícula e retorna seu índice no vetor.
 *  Retorna -1 caso não encontrado.
 * ============================================================ */
int encontrarIndice(const Aluno vetor[], int total, int matricula) {
    for (int i = 0; i < total; i++) {
        if (vetor[i].matricula == matricula) {
            return i; /* Índice encontrado */
        }
    }
    return -1; /* Não encontrado */
}
 
/* ============================================================
 *  exibirAluno
 *  Imprime as informações formatadas de um único aluno.
 * ============================================================ */
void exibirAluno(const Aluno *a) {
    printf("Nome     : %s\n",  a->nome);
    printf("Idade    : %d anos\n", a->idade);
    printf("Matricula: %d\n",  a->matricula);
    printf("Nota     : %.2f\n", a->notaFinal);
}
