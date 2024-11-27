#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct purshase_orderk
{
    int vbeln;
    int date;
    char buyer[30];
    float netwr;
};

struct purshase_orderp
{
    int vbeln;
    int vbelp;
    int matnr;
    float menge;
    float netwr;
};

struct matnr
{
    int id;
    char description[50];
    float netwr;
    float menge;
};

void fill_mat(struct matnr *material, int id, char *descr, float valor, float peso, int tam)
{
    material[tam].id = id;
    strcpy(material[tam].description, descr);
    material[tam].netwr = valor;
    material[tam].menge = peso; // Preencher a quantidade
}

void print_matnr(struct matnr *material)
{
    printf(" ______________________________________________\n");
    printf("|ID |    Descricao       |  Total    |  Peso   |\n");
    printf("|______________________________________________|\n");

    for (int i = 0; i < 6; i++)
    {
        printf("|%2d | %-18s | %-10.2f| %-8.2f|\n", i, material[i].description, material[i].netwr, material[i].menge);
        printf("|______________________________________________|\n");
    }
}

struct purshase_orderp *add_order(struct purshase_orderp *pedp,
                                  int vbeln,
                                  int matnr,
                                  int menge,
                                  float netwr,
                                  int *size)
{
    pedp = realloc(pedp, (*size + 1) * sizeof(struct purshase_orderp));

    if (pedp == NULL)
    {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    pedp[*size].vbeln = vbeln;
    pedp[*size].vbelp = *size;
    pedp[*size].matnr = matnr;
    pedp[*size].menge = menge;
    pedp[*size].netwr = netwr * menge; // Total é o preço unitário multiplicado pela quantidade

    (*size)++;

    return pedp; // Retorna o ponteiro atualizado
}
struct purshase_orderk *add_orderk(struct purshase_orderk *pedk,
                                   int vbeln,
                                   float netwr,
                                   int date,
                                   char buyer[30],
                                   int *size)
{
    pedk = realloc(pedk, (*size + 1) * sizeof(struct purshase_orderk));

    if (pedk == NULL)
    {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    strcpy(pedk[*size].buyer, buyer);
    pedk[*size].netwr = netwr; //+ pedk[*size].netwr; // Total é o preço unitário multiplicado pela quantidade
    pedk[*size].vbeln = vbeln;

    (*size)++;

    return pedk; // Retorna o ponteiro atualizado
}
int print_pedk(struct purshase_orderk *pedk, int size)
{

    printf("digite o numero do pedido ou \n");
    printf(".________________________________________.\n");
    printf("| ID |  Data   |  Comprador  |   Total   |\n");
    printf("|________________________________________|\n");
    for (int i = 0; i < size; i++)
    {
        printf("| %2d | %8d | %-10s |  %6.2f   |\n", pedk[i].vbeln, pedk[i].date, pedk[i].buyer, pedk[i].netwr);
        printf("|________________________________________|\n");
    }
}
void print_pedido_itens(struct purshase_orderp *pedp, int size, int vbeln, struct matnr *material)
{
    printf("\nItens do pedido %d:\n", vbeln);
    printf(" ______________________________________________\n");
    printf("|ID Matnr |  Descricao       |  Qtd   |  Total |\n");
    printf("|______________________________________________|\n");

    for (int i = 0; i < size; i++)
    {
        if (pedp[i].vbeln == vbeln)
        {
            printf("|%8d | %-15s | %-6.2f | %-7.2f |\n",
                   pedp[i].matnr, material[pedp[i].matnr].description, pedp[i].menge, pedp[i].netwr);
        }
    }
    printf("|______________________________________________|\n");
}

int main()
{   
    struct matnr material[10];
    struct purshase_orderk *pedk = NULL;
    struct purshase_orderp *pedp = NULL;
    char c1[50];
    char nome[30];
    int var;
    int varmain = 0;
    int quant;
    int size = 0;
    int size2 = 0;
    int count = 0;
    int item_pedido_selecionado;
    int i;
    int countwhile = 0;

    // Inicialização manual dos materiais
    strcpy(c1, "pacoca");
    fill_mat(material, 1, c1, 1.50, 30, 0);

    strcpy(c1, "bolo");
    fill_mat(material, 1, c1, 330.00, 300, 1);

    strcpy(c1, "frango");
    fill_mat(material, 1, c1, 21.00, 1000, 2);

    strcpy(c1, "pizza");
    fill_mat(material, 1, c1, 60.00, 800, 3);

    strcpy(c1, "hotdog");
    fill_mat(material, 1, c1, 30.00, 100, 4);

    strcpy(c1, "arroz");
    fill_mat(material, 1, c1, 30.00, 1000, 5);

    // Início da seleção
    printf("Digite 1 para continuar ou -1 para cancelar ver relatorios de todos os pedidos\n");

    scanf("%d", &varmain);

    while (varmain != -1)
    {
        printf("Digite seu nome:\n");

        scanf("%s", nome);

        pedk = add_orderk(pedk, count, 0, 0, nome, &size2);
        printf("\nSelecione os IDs dos itens que quer adicionar ou Digite -1 para voltar:\n");
        print_matnr(material);
        scanf("%d", &var);

        while (var != -1)
        {
            if ( (var >=0 ) && ( var <= 5 ) ) 
            {
                printf("Quantos (%s)?\n", material[var].description);
                scanf("%d", &quant);
                pedp = add_order(pedp, count, var, quant, material[var].netwr, &size);
                pedk[count].netwr = (pedk[count].netwr + (material[var].netwr * quant));
            }
            else
            {
                printf("\n ID Invalido");
            };
            printf("\nSelecione outro ID ou Digite -1 para finalizar:\n");
            scanf("%d", &var);
        };

        count = count + 1;

        printf("Digite qualquer caracter para continuar (exceto -1) para continuar ou -1 para cancelar ver relatorios de todos os pedidos\n");

        scanf("%d", &varmain);
    }

    do
    {
        item_pedido_selecionado = print_pedk(pedk, size2);

        printf("Digite o id do pedido para visualizar seus itens ou -1 para sair: ");
        scanf("%d", &i);

        if (i != -1)
        {
            print_pedido_itens(pedp, size, i, material);
        }
    } while (i != -1);

    printf("Prontinho!!\n");
    free(pedk);
    free(pedp);
    return 0;
};