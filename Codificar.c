#include <stdio.h>
#include <stdlib.h>
#include <string.h>

union byte
{
    unsigned char b0:1;
    unsigned char b1:1;
    unsigned char b2:1;
    unsigned char b3:1;
    unsigned char b4:1;
    unsigned char b5:1;
    unsigned char b6:1;
    unsigned char b7:1;
};

struct lista
{
    int simbolo;
    char palavra[30];
    int freq;
    union byte byte;
    struct lista *prox;
};
typedef struct lista Lista;

void lerArquivo(Lista ** lista);
void CriaNoLista(Lista ** novo, int simbolo, char palavra[30]);
Lista *buscarPalavra(Lista * lista, char palavra[30]);
void inserirOrdenado(Lista ** lista, Lista *novo);
void exibirLista(Lista *lista);

void lerArquivo(Lista **lista)
{
    FILE *ptr = fopen("../TextoTeste.txt", "r");
    Lista *novo, *aux;
    Lista **atual;
    int c;
    char palavra[30];
    int i = 0;
    int simbolo = 0;

    if (ptr != NULL)
    {
        while (!feof(ptr))
        {
            c = fgetc(ptr);

            if (c != EOF && c != ' ' && c != '.' && c != ',')
            {
                palavra[i] = c;
                i++;
            }
            else if (i > 0)
            {
                palavra[i] = '\0';

                aux = buscarPalavra(*lista, palavra);

                if (aux != NULL)
                {
                    atual = lista;

                    while (*atual != aux)
                        atual = &(*atual)->prox;

                    *atual = aux->prox;

                    aux->freq++;
                    aux->prox = NULL;

                    inserirOrdenado(lista, aux);
                }
                else
                {
                    CriaNoLista(&novo, simbolo, palavra);

                    if (novo != NULL)
                    {
                        inserirOrdenado(lista, novo);
                        simbolo++;
                    }
                }

                i = 0;
            }
        }

        fclose(ptr);
    }
    else
    {
        printf("Problema ao ler arquivo!\n");
    }
}

void inserirOrdenado(Lista ** lista, Lista *novo)
{
    Lista *aux;
    if (*lista == NULL)
    {
        *lista = novo;
    }
    else
    {
        if (novo->freq < (*lista)->freq)
        {
            novo->prox = *lista;
            *lista = novo;
        }
        else
        {
            aux = *lista;

            while (aux->prox != NULL && novo->freq >= aux->prox->freq)
                aux = aux->prox;
            
            novo->prox = aux->prox;
            aux->prox = novo; 
        }
    }
}

void exibirLista(Lista *lista)
{
    while (lista != NULL)
    {
        printf("Simbolo: %d\n", lista->simbolo);
        printf("Palavra: %s\n", lista->palavra);
        printf("Frequencia: %d\n", lista->freq);

        lista = lista->prox;
    }
}

void CriaNoLista(Lista ** novo, int simbolo, char palavra[30])
{
    *novo = (Lista*)malloc(sizeof(Lista));

    (*novo)->simbolo = simbolo;
    strcpy((*novo)->palavra, palavra);
    (*novo)->freq = 1;
    (*novo)->prox = NULL;
}

Lista *buscarPalavra(Lista * lista, char palavra[30])
{
    while (lista != NULL)
    {
        if (strcmp(lista->palavra, palavra) == 0) 
        {
            return lista;
        }    

        lista = lista->prox;
    }

    return NULL;
}

int main()
{
    Lista * lista = NULL;
    printf("Codificacao\n");
    lerArquivo(&lista);
    exibirLista(lista);
    return 0;
}