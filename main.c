#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[40];
    int ra;
    float notas[4];
    int faltas;
} Aluno;

Aluno turma[30];
int pointer = 0;

void error(char *msg) {
    printf("\033[0;31m");
    printf("%s", msg);
    printf("\033[0m");
}

int indiceAluno(int ra) {
    for(int i = 0; i < pointer; i++) {
        if (turma[i].ra == ra) {
            return i;
            break;
        }
    }
    return -1;
}

int indiceAlunoByName(char *nome) {
    for(int i = 0; i < pointer; i++) {
        if (strcmp(turma[i].nome, nome) == 0) {
            return i;
            break;
        }
    }
    return -1;
}

int existeRa(int ra) {
    if (indiceAluno(ra) < 0) {
        return 0;
    } else {
        return 1;
    }
}

void guardarNovoAluno(Aluno novo_aluno) {
    turma[pointer].ra = novo_aluno.ra;
    turma[pointer].notas[0] = novo_aluno.notas[0];
    turma[pointer].notas[1] = novo_aluno.notas[1];
    turma[pointer].notas[2] = novo_aluno.notas[2];
    turma[pointer].notas[3] = novo_aluno.notas[3];
    turma[pointer].faltas = novo_aluno.faltas;
    strcpy(turma[pointer].nome, novo_aluno.nome);
}

void printAluno(Aluno aluno) {
    printf("\n-----------------------------------\n");
    printf("Nome: %s \n", aluno.nome);
    printf("RA: %i \n", aluno.ra);
    printf("Notas: %.2f - %.2f - %.2f - %.2f \n", aluno.notas[0], aluno.notas[1], aluno.notas[2], aluno.notas[3]);
    printf("Faltas: %i\n", aluno.faltas);
    printf("-----------------------------------\n\n");
}

float mediaAluno(Aluno aluno) {
    return ((aluno.notas[0]+aluno.notas[1]+aluno.notas[2]+aluno.notas[3])/4);
}

void cadastrarNovoAluno() {
    printf("\n----------- Cadastrar novo aluno -----------\n");
    
    char novo_aluno_nome[100] = "";
                
    while(strlen(novo_aluno_nome) < 1 || strlen(novo_aluno_nome) > 40) {
        printf("Nome do aluno (ate 40 caracteres): ");
        scanf(" %[^\n]", novo_aluno_nome);
        if (strlen(novo_aluno_nome) > 40) error("\nNome do aluno muito grande!\n\n");
    }

    int novo_aluno_ra = 0;
    while(novo_aluno_ra < 1 || existeRa(novo_aluno_ra)) {
        printf("RA do aluno (um numero inteiro maior que 0): ");
        scanf(" %i", &novo_aluno_ra);
        if (novo_aluno_ra < 1) error("\nPor favor, digite o RA do aluno corretamente.\n\n");
        if (existeRa(novo_aluno_ra)) error("\nEste RA ja esta cadastrado.\n\n");
    }

    Aluno novo_aluno;

    strcpy(novo_aluno.nome, novo_aluno_nome);
    novo_aluno.ra = novo_aluno_ra;
    novo_aluno.notas[0] = 0.0;
    novo_aluno.notas[1] = 0.0;
    novo_aluno.notas[2] = 0.0;
    novo_aluno.notas[3] = 0.0;
    novo_aluno.faltas = 0;

    guardarNovoAluno(novo_aluno);
    printAluno(turma[pointer]);
    pointer = pointer+1;

}

void lancarNotasProva() {

    if (pointer == 0) {
        error("\nNao existem alunos para lancar notas.\n\n");
    } else {

        printf("\n------- Lancar notas de uma avaliacao ------\n");
        int ava_op = 0;
        
        while(ava_op < 1 || ava_op > 4) {
            printf("\nQual avalicao sera lancada? (entre 1 e 4) ");
            scanf("%i", &ava_op);
            if (ava_op < 1 || ava_op > 4) error("\nEscolha uma avaliacao entre 1 e 4.\n\n");
        }

        ava_op = ava_op - 1;

        for(int i = 0; i < pointer; i++) {
            float nova_nota = -1.0;
            while(nova_nota < 0 || nova_nota > 100) {
                printf("\n%s == ", turma[i].nome);
                scanf("%f", &nova_nota);
                if (nova_nota < 0 || nova_nota > 100) error("\nA nota do aluno deve estar entre 0.0 e 100.0\n\n");
            }
            turma[i].notas[ava_op] = nova_nota;
        }

        printf("\n\nNotas lancadas com sucesso!\n");

    }
}

void lancarNotaAluno() {

    if (pointer == 0) {
        error("\nNao existem alunos para lancar notas.\n\n");
    } else {

        printf("\n--------- Alterar nota de um aluno ---------\n");
        int ava_op = 0;
        
        while(ava_op < 1 || ava_op > 4) {
            printf("\nQual avalicao sera lancada? (entre 1 e 4) ");
            scanf("%i", &ava_op);
            if (ava_op < 1 || ava_op > 4) error("\nEscolha uma avaliacao entre 1 e 4.\n\n");
        }

        ava_op = ava_op - 1;

        int ra_aluno = -1;

        while(ra_aluno < 0 || !existeRa(ra_aluno)) {
            printf("\nQual o RA do aluno que tera a nota alterada? ");
            scanf("%i", &ra_aluno);
            if (ra_aluno < 0) error("\nDigite um RA valido.\n\n");
            if (!existeRa(ra_aluno) && ra_aluno >= 0) error("\nDigite um RA cadastrado.\n\n");
        }

        float nova_nota = -1.0;

        while(nova_nota < 0 || nova_nota > 100) {
            printf("\n%s == ", turma[indiceAluno(ra_aluno)].nome);
            scanf("%f", &nova_nota);
            if (nova_nota < 0 || nova_nota > 100) error("\nA nota do aluno deve estar entre 0.0 e 100.0\n\n");
        }

        turma[indiceAluno(ra_aluno)].notas[ava_op] = nova_nota;

        printf("\n\n Nova nota salva com sucesso! \n\n");

    }
}

void alterarFaltasAluno() {

    if (pointer == 0) {
        error("\nNao existem alunos para lancar faltas.\n\n");
    } else {

        printf("\n-------- Alterar faltas de um aluno --------\n");

        int ra_aluno = -1;

        while(ra_aluno < 0 || !existeRa(ra_aluno)) {
            printf("\nQual o RA do aluno ? ");
            scanf("%i", &ra_aluno);
            if (ra_aluno < 0) error("\nDigite um RA valido.\n\n");
            if (!existeRa(ra_aluno) && ra_aluno >= 0) error("\nDigite um RA cadastrado.\n\n");
        }

        int nova_faltas = -1.0;

        while(nova_faltas < 0) {
            printf("\n%s == ", turma[indiceAluno(ra_aluno)].nome);
            scanf("%i", &nova_faltas);
            if (nova_faltas < 0) error("\nA quantidade faltas de um aluno deve ser maior que 0.\n\n");
        }

        turma[indiceAluno(ra_aluno)].faltas = nova_faltas;

        printf("\n\n Nova quantidade de faltas salva com sucesso! \n\n");

    }
}

void listarAlunos() {
    if (pointer == 0) {
        error("\nNao existem alunos para listar.\n\n");
    } else {
        printf("\n-------------- Listar alunos ---------------\n");

        int ord_op = 0;
        
        printf("\n1 - Ordem alfabetica");
        printf("\n2 - Ordem de RA");
        printf("\n3 - Ordem de insercao");
                

        while(ord_op < 1 || ord_op > 3) {
            printf("\nQual a ordem desejada? (entre 1 e 3) ");
            scanf("%i", &ord_op);
            if (ord_op < 1 || ord_op > 3) error("\nEscolha ordem entre 1 e 3.\n\n");
        }

        int vetor_ra[pointer];
        char vetor_nomes[pointer][40];

        switch(ord_op) {
            case 1:
                printf("\nORDEM ALFABETICA:\n");
                char aux[40];

                for(int i = 0; i < pointer; i++) {
                    strcpy(vetor_nomes[i], turma[i].nome);
                }

                for (int i = 1; i < pointer; i++) {
                    for (int j = 1; j < pointer; j++) {
                        if (strcmp(vetor_nomes[j - 1], vetor_nomes[j]) > 0) {
                            strcpy(aux, vetor_nomes[j - 1]);
                            strcpy(vetor_nomes[j - 1], vetor_nomes[j]);
                            strcpy(vetor_nomes[j], aux);
                        }
                    }
                }

                for(int i = 0; i < pointer; i++) {
                    printAluno(turma[indiceAlunoByName(vetor_nomes[i])]);
                }

                break;
            case 2:
                printf("\nORDEM DE RA:\n");
                int a;

                for(int i = 0; i < pointer; i++) {
                    vetor_ra[i] = turma[i].ra;
                }

                for (int i = 0; i < pointer; ++i) {
                    for (int j = i + 1; j < pointer; ++j) {
                        if (vetor_ra[i] > vetor_ra[j]) {
                            a =  vetor_ra[i];
                            vetor_ra[i] = vetor_ra[j];
                            vetor_ra[j] = a;
                        }
                    }
                }

                for(int i = 0; i < pointer; i++) {
                    printAluno(turma[indiceAluno(vetor_ra[i])]);
                }
                
                break;
            case 3:
                printf("\nORDEM DE INSERCAO:\n");
                for(int i = 0; i < pointer; i++) {
                    printAluno(turma[i]);
                }
                break;
        }
    }
}

void listarAlunosAprovados() {
    if (pointer == 0) {
        error("\nNao existem alunos para listar.\n\n");
    } else {
        printf("\n--------- Listar alunos aprovados ----------\n");

        for(int i = 0; i < pointer; i++) {
            if (mediaAluno(turma[i]) >= 60) {
                printAluno(turma[i]);
            }
        }
    }
}

void gravarEmArquivo() {
    FILE *pont_arq;
    pont_arq = fopen("state.data", "w+");
    fwrite(turma, sizeof(turma), 1, pont_arq);
    fclose(pont_arq);

    FILE *pont_arq_pointer;
    pont_arq_pointer = fopen("pointer.data", "w+");
    fwrite(&pointer, sizeof(int), 1, pont_arq_pointer);
    fclose(pont_arq_pointer);
}

void lerEmArquivo() {
    FILE *pont_arq;
    pont_arq = fopen("state.data", "r");
    if(pont_arq != NULL) {
        fread(&turma, sizeof(Aluno), 30, pont_arq);
        fclose(pont_arq);
    }

    FILE *pont_arq_pointer;
    pont_arq_pointer = fopen("pointer.data", "r");
    if(pont_arq_pointer != NULL) {
        fread(&pointer, sizeof(int), 1, pont_arq_pointer);
        fclose(pont_arq_pointer);
    }
}

int main() {

    lerEmArquivo();

    printf("-----------------------------------\n");
    printf("---------Sistema de Alunos---------\n");
    printf("-----------------------------------\n");
    
    while(1) {
    
        printf("\n1 - Inserir aluno na turma.");
        printf("\n2 - Lancar notas de uma avaliacao.");
        printf("\n3 - Alterar nota de um aluno.");
        printf("\n4 - Alterar faltas de um aluno.");
        printf("\n5 - Listas alunos.");
        printf("\n6 - Listar alunos aprovados.");
        printf("\n7 - Sair e gravar.\n");
        printf("\nO que deseja fazer? ");

        int option = 0;

        scanf("%i", &option);

        switch (option) {
        case 1:
            cadastrarNovoAluno();
            break;
        case 2:
            lancarNotasProva();
            break;
        case 3:
            lancarNotaAluno();
            break;
        case 4:
            alterarFaltasAluno();
            break;
        case 5:
            listarAlunos();
            break;
        case 6:
            listarAlunosAprovados();
            break;
        case 7:
            gravarEmArquivo();
            return 0;
            break;
        default:
            error("\n\n## Por favor escolha uma opcao valida na lista. ##\n\n");
            break;
        }

    }
}