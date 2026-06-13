#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_PRODUTOS  50
#define MAX_VENDAS    100
#define MAX_NOME      60
#define MAX_MARCA     4
#define LARGURA       70

struct Produto {
    int    codigo;
    char   nome[MAX_NOME];
    char   marca[MAX_MARCA];
    char   categoria[MAX_NOME];
    float  preco;
    int    estoque;
    int    ativo;
};
 
struct Venda {
    int   numero;
    int   codProduto;
    int   quantidade;
    float valorTotal;
    char  cliente[MAX_NOME];
    char  formaPagamento[MAX_NOME];
};

struct Produto produtos[MAX_PRODUTOS];
struct Venda   listaVendas[MAX_VENDAS];
int totalProdutos = 0;
int totalVendas   = 0;


void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void corVermelha()  { printf("\033[1;31m"); }
void corVerde()     { printf("\033[1;32m"); }
void corAmarela()   { printf("\033[1;33m"); }
void corAzul()      { printf("\033[1;34m"); }
void corMagenta()   { printf("\033[1;35m"); }
void corCiano()     { printf("\033[1;36m"); }
void corBranca()    { printf("\033[1;37m"); }
void corReset()     { printf("\033[0m");    }
void corFundoAzul() { printf("\033[44m");   }
void corFundoPreto(){ printf("\033[40m");   }

void imprimirLinhaMoldura(char canto_esq, char linha, char canto_dir) {
    corCiano();
    printf("%c", canto_esq);
    int i;
    for (i = 0; i < LARGURA - 2; i++) printf("%c", linha);
    printf("%c\n", canto_dir);
    corReset();
}

void imprimirLinha(const char *conteudo, int centralizado) {
    int len = strlen(conteudo);
    int espacos;
    corCiano();
    printf("#");
    corReset();
    if (centralizado) {
        espacos = (LARGURA - 2 - len) / 2;
        int i;
        for (i = 0; i < espacos; i++) printf(" ");
        printf("%s", conteudo);
        espacos = LARGURA - 2 - len - espacos;
        for (i = 0; i < espacos; i++) printf(" ");
    } else {
        printf(" %-*s", LARGURA - 3, conteudo);
    }
    corCiano();
    printf("#\n");
    corReset();
}

void imprimirLinhaVazia() {
    imprimirLinha("", 0);
}

/* TELA DE ENTRADA */
void telaEntrada() {
    limparTela();

    imprimirLinhaMoldura('#', '=', '#');
    imprimirLinhaVazia();

    corCiano();
    printf("#"); corAmarela();
    printf("     _____ _____ ____ _   _   _   _ _______  ____  __ _   _ ____  ");
    corCiano(); printf("#\n");

    printf("#"); corAmarela();
    printf("    |_   _| ____/ ___| | | | | \\ | | ____\\ \\/ / | | | | / ___| ");
    corCiano(); printf("#\n");

    printf("#"); corAmarela();
    printf("      | | |  _|| |   | |_| | |  \\| |  _|  \\  /| | | | \\___ \\ ");
    corCiano(); printf("#\n");

    printf("#"); corAmarela();
    printf("      | | | |__| |___|  _  | | |\\  | |___ /  \\| |_| |  ___) |");
    corCiano(); printf("#\n");

    printf("#"); corAmarela();
    printf("      |_| |_____\\____|_| |_| |_| \\_|_____/_/\\_\\\\___/  |____/ ");
    corCiano(); printf("#\n");

    corReset();
    imprimirLinhaVazia();

    /* Desenho de circuito / chip */
    corCiano(); printf("#"); corVerde();
    printf("         +-------[CPU]-------+    +--[GPU]--+              ");
    corCiano(); printf("#\n");

    corCiano(); printf("#"); corVerde();
    printf("         |  +-+ +-+ +-+ +-+ |    |  [] []  |              ");
    corCiano(); printf("#\n");

    corCiano(); printf("#"); corVerde();
    printf("    ===--+  |_| |_| |_| |_| +--  +--[MEM]--+  --===      ");
    corCiano(); printf("#\n");

    corCiano(); printf("#"); corVerde();
    printf("         |  +-+ +-+ +-+ +-+ |    | [SSD]   |              ");
    corCiano(); printf("#\n");

    corCiano(); printf("#"); corVerde();
    printf("         +---[MOTHERBOARD]---+    +---------+              ");
    corCiano(); printf("#\n");

    corReset();
    imprimirLinhaVazia();

    /* Subtitulo */
    corCiano(); printf("#"); corBranca();
    printf("      >>> Solucoes em Tecnologia & Inovacao para Voce <<<  ");
    corCiano(); printf("      #\n"); corReset();

    corCiano(); printf("#"); corMagenta();
    printf("         Smartphones | Notebooks | Gadgets | Wearables     ");
    corCiano(); printf("       #\n"); corReset();

    imprimirLinhaVazia();
    imprimirLinhaMoldura('#', '=', '#');

    printf("\n");
    corAmarela();
    printf("  Pressione [ENTER] para acessar o sistema...");
    corReset();
    getchar();
}

void cabecalho(const char *titulo) {
    limparTela();
    imprimirLinhaMoldura('#', '=', '#');

    char buf[80];
    sprintf(buf, "TECH NEXUS - %s", titulo);
    corAmarela();
    /* linha com titulo */
    corCiano(); printf("#"); corAmarela();
    int len = strlen(buf);
    int esp = (LARGURA - 2 - len) / 2;
    int i;
    for (i = 0; i < esp; i++) printf(" ");
    printf("%s", buf);
    esp = LARGURA - 2 - len - esp;
    for (i = 0; i < esp; i++) printf(" ");
    corCiano(); printf("#\n"); corReset();

    imprimirLinhaMoldura('#', '=', '#');
    printf("\n");
}

/* MENU PRINCIPAL */
void menuPrincipal() {
    imprimirLinhaMoldura('#', '-', '#');

    corCiano(); printf("#"); corBranca();
    printf("  [1] Cadastro de Produtos                                  ");
    corCiano(); printf("   #\n"); corReset();

    corCiano(); printf("#"); corBranca();
    printf("  [2] Movimentacao (Entrada de Estoque)                     ");
    corCiano(); printf("   #\n"); corReset();

    corCiano(); printf("#"); corBranca();
    printf("  [3] Vendas                                                ");
    corCiano(); printf("   #\n"); corReset();

    corCiano(); printf("#"); corBranca();
    printf("  [4] Relatorio                                             ");
    corCiano(); printf("   #\n"); corReset();

    corCiano(); printf("#"); corVermelha();
    printf("  [0] Sair                                                  ");
    corCiano(); printf("   #\n"); corReset();

    imprimirLinhaMoldura('#', '-', '#');
}

int buscarProduto(int codigo) {
    int i;
    for (i = 0; i < totalProdutos; i++)
        if (produtos[i].codigo == codigo && produtos[i].ativo)
            return i;
    return -1;
}

void pausar() {
    printf("\n");
    corAmarela();
    printf("  Pressione [ENTER] para continuar...");
    corReset();
    getchar();
    getchar();
}
/* MODULO CADASTRO*/
void cadastroProdutos() {
    int opcao;
    do {
        cabecalho("CADASTRO DE PRODUTOS");
        imprimirLinhaMoldura('#', '-', '#');
        corCiano(); printf("#"); corBranca();
        printf("  [1] Novo Produto                                           ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corBranca();
        printf("  [2] Consultar Produto                                      ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corBranca();
        printf("  [3] Listar Todos os Produtos                               ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corVermelha();
        printf("  [0] Voltar ao Menu Principal                               ");
        corCiano(); printf("#\n"); corReset();
        imprimirLinhaMoldura('#', '-', '#');

        corAmarela(); printf("\n  Opcao: "); corReset();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                /* Novo Produto */
                if (totalProdutos >= MAX_PRODUTOS) {
                    corVermelha();
                    printf("\n  ERRO: Limite maximo de produtos atingido!\n");
                    corReset();
                    pausar();
                    break;
                }
                cabecalho("NOVO PRODUTO");
                printf("\n");

                struct Produto p;
                p.ativo = 1;
                p.codigo = totalProdutos + 1001;

                printf("  Codigo gerado automaticamente: ");
                corAmarela(); printf("%d\n", p.codigo); corReset();

                printf("  Nome do Produto : "); getchar();
                fgets(p.nome, MAX_NOME, stdin);
                p.nome[strcspn(p.nome, "\n")] = 0;

                printf("  Marca           : ");
                fgets(p.marca, MAX_MARCA, stdin);
                p.marca[strcspn(p.marca, "\n")] = 0;

                printf("  Categoria       : ");
                printf("\n  (Ex: Smartphone, Notebook, Wearable, Gadget, Acessorio)\n  > ");
                fgets(p.categoria, MAX_NOME, stdin);
                p.categoria[strcspn(p.categoria, "\n")] = 0;

                printf("  Preco (R$)      : ");
                scanf("%f", &p.preco);

                printf("  Estoque inicial : ");
                scanf("%d", &p.estoque);

                produtos[totalProdutos] = p;
                totalProdutos++;

                corVerde();
                printf("\n  Produto cadastrado com sucesso! Codigo: %d\n", p.codigo);
                corReset();
                pausar();
                break;
            }
            case 2: {
                /* Consultar */
                cabecalho("CONSULTAR PRODUTO");
                int cod;
                printf("\n  Informe o codigo do produto: ");
                scanf("%d", &cod);

                int idx = buscarProduto(cod);
                if (idx == -1) {
                    corVermelha();
                    printf("\n  Produto nao encontrado!\n");
                    corReset();
                } else {
                    printf("\n");
                    imprimirLinhaMoldura('+', '-', '+');
                    printf("  Codigo    : "); corAmarela(); printf("%d\n", produtos[idx].codigo); corReset();
                    printf("  Nome      : "); corBranca(); printf("%s\n", produtos[idx].nome); corReset();
                    printf("  Marca     : %s\n", produtos[idx].marca);
                    printf("  Categoria : %s\n", produtos[idx].categoria);
                    printf("  Preco     : "); corVerde(); printf("R$ %.2f\n", produtos[idx].preco); corReset();
                    printf("  Estoque   : ");
                    if (produtos[idx].estoque < 5) corVermelha(); else corVerde();
                    printf("%d unidades\n", produtos[idx].estoque);
                    corReset();
                    imprimirLinhaMoldura('+', '-', '+');
                }
                pausar();
                break;
            }
            case 3: {
                /* Listar tudo */
                cabecalho("LISTA DE PRODUTOS");
                if (totalProdutos == 0) {
                    corAmarela();
                    printf("\n  Nenhum produto cadastrado.\n");
                    corReset();
                } else {
                    int i;
                    printf("\n");
                    corBranca();
                    printf("  %-6s %-25s %-15s %-12s %8s %7s\n",
                        "COD","NOME","MARCA","CATEGORIA","PRECO","ESTQ");
                    printf("  ");
                    int j;
                    for(j=0;j<65;j++) printf("-");
                    printf("\n");
                    corReset();
                    for (i = 0; i < totalProdutos; i++) {
                        if (!produtos[i].ativo) continue;
                        if (produtos[i].estoque < 5) corVermelha();
                        else corVerde();
                        printf("  %-6d %-25s %-15s %-12s R$%6.2f %5d\n",
                            produtos[i].codigo,
                            produtos[i].nome,
                            produtos[i].marca,
                            produtos[i].categoria,
                            produtos[i].preco,
                            produtos[i].estoque);
                    }
                    corReset();
                    corVermelha(); printf("\n  * Vermelho = estoque baixo (< 5 unidades)\n"); corReset();
                }
                pausar();
                break;
            }
            case 0:
                break;
            default:
                corVermelha(); printf("\n  Opcao invalida!\n"); corReset();
                pausar();
        }
    } while (opcao != 0);
}

/* MOVIMENTACAO*/
void movimentacao() {
    int opcao;
    do {
        cabecalho("MOVIMENTACAO DE ESTOQUE");
        imprimirLinhaMoldura('#', '-', '#');
        corCiano(); printf("#"); corBranca();
        printf("  [1] Entrada de Estoque (Reabastecimento)                   ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corBranca();
        printf("  [2] Consultar Saldo de Estoque                             ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corVermelha();
        printf("  [0] Voltar ao Menu Principal                               ");
        corCiano(); printf("#\n"); corReset();
        imprimirLinhaMoldura('#', '-', '#');

        corAmarela(); printf("\n  Opcao: "); corReset();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                cabecalho("ENTRADA DE ESTOQUE");
                int cod, qtd;
                printf("\n  Codigo do produto : ");
                scanf("%d", &cod);

                int idx = buscarProduto(cod);
                if (idx == -1) {
                    corVermelha();
                    printf("\n  Produto nao encontrado!\n");
                    corReset();
                } else {
                    corBranca();
                    printf("  Produto: %s | Estoque atual: %d unidades\n",
                        produtos[idx].nome, produtos[idx].estoque);
                    corReset();
                    printf("  Quantidade a adicionar: ");
                    scanf("%d", &qtd);
                    if (qtd <= 0) {
                        corVermelha();
                        printf("\n  Quantidade invalida!\n");
                        corReset();
                    } else {
                        produtos[idx].estoque += qtd;
                        corVerde();
                        printf("\n  Estoque atualizado! Novo saldo: %d unidades.\n",
                            produtos[idx].estoque);
                        corReset();
                    }
                }
                pausar();
                break;
            }
            case 2: {
                cabecalho("SALDO DE ESTOQUE");
                if (totalProdutos == 0) {
                    corAmarela(); printf("\n  Nenhum produto cadastrado.\n"); corReset();
                } else {
                    int i;
                    printf("\n");
                    corBranca();
                    printf("  %-6s %-30s %10s  STATUS\n","COD","PRODUTO","ESTOQUE");
                    printf("  ");
                    int j; for(j=0;j<55;j++) printf("-"); printf("\n");
                    corReset();
                    for (i = 0; i < totalProdutos; i++) {
                        if (!produtos[i].ativo) continue;
                        const char *status;
                        if (produtos[i].estoque == 0) { corVermelha(); status = "SEM ESTOQUE"; }
                        else if (produtos[i].estoque < 5) { corAmarela(); status = "CRITICO";   }
                        else { corVerde(); status = "OK"; }
                        printf("  %-6d %-30s %10d  %s\n",
                            produtos[i].codigo,
                            produtos[i].nome,
                            produtos[i].estoque,
                            status);
                        corReset();
                    }
                }
                pausar();
                break;
            }
            case 0: break;
            default:
                corVermelha(); printf("\n  Opcao invalida!\n"); corReset();
                pausar();
        }
    } while (opcao != 0);
}

/* VENDAS*/
void menuVendas() {
    int opcao;
    do {
        cabecalho("VENDAS");
        imprimirLinhaMoldura('#', '-', '#');
        corCiano(); printf("#"); corBranca();
        printf("  [1] Registrar Nova Venda                                   ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corBranca();
        printf("  [2] Historico de Vendas                                    ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corVermelha();
        printf("  [0] Voltar ao Menu Principal                               ");
        corCiano(); printf("#\n"); corReset();
        imprimirLinhaMoldura('#', '-', '#');

        corAmarela(); printf("\n  Opcao: "); corReset();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                if (totalVendas >= MAX_VENDAS) {
                    corVermelha(); printf("\n  Limite de vendas atingido!\n"); corReset();
                    pausar(); break;
                }
                cabecalho("NOVA VENDA");
                struct Venda v;
                v.numero = totalVendas + 1;

                printf("\n  Nome do cliente   : "); getchar();
                fgets(v.cliente, MAX_NOME, stdin);
                v.cliente[strcspn(v.cliente, "\n")] = 0;

                printf("  Codigo do produto : ");
                scanf("%d", &v.codProduto);

                int idx = buscarProduto(v.codProduto);
                if (idx == -1) {
                    corVermelha(); printf("\n  Produto nao encontrado!\n"); corReset();
                    pausar(); break;
                }

                corBranca();
                printf("  Produto: %s | Preco: R$ %.2f | Estoque: %d\n",
                    produtos[idx].nome, produtos[idx].preco, produtos[idx].estoque);
                corReset();

                printf("  Quantidade        : ");
                scanf("%d", &v.quantidade);

                if (v.quantidade <= 0 || v.quantidade > produtos[idx].estoque) {
                    corVermelha();
                    printf("\n  Quantidade invalida ou estoque insuficiente!\n");
                    corReset();
                    pausar(); break;
                }

                printf("  Forma de pagamento: ");
                printf("\n  (Ex: Credito, Debito, Pix, Dinheiro, Parcelado)\n  > ");
                getchar();
                fgets(v.formaPagamento, MAX_NOME, stdin);
                v.formaPagamento[strcspn(v.formaPagamento, "\n")] = 0;

                v.valorTotal = produtos[idx].preco * v.quantidade;
                produtos[idx].estoque -= v.quantidade;

                listaVendas[totalVendas] = v;
                totalVendas++;

                printf("\n");
                imprimirLinhaMoldura('+', '=', '+');
                corVerde();
                printf("  VENDA REALIZADA COM SUCESSO!\n");
                printf("  Venda N. : %d\n", v.numero);
                printf("  Cliente  : %s\n", v.cliente);
                printf("  Produto  : %s\n", produtos[idx].nome);
                printf("  Qtde     : %d unidades\n", v.quantidade);
                printf("  Total    : R$ %.2f\n", v.valorTotal);
                printf("  Pagamento: %s\n", v.formaPagamento);
                corReset();
                imprimirLinhaMoldura('+', '=', '+');
                pausar();
                break;
            }
            case 2: {
                cabecalho("HISTORICO DE VENDAS");
                if (totalVendas == 0) {
                    corAmarela(); printf("\n  Nenhuma venda registrada.\n"); corReset();
                } else {
                    int i;
                    float totalGeral = 0;
                    printf("\n");
                    corBranca();
                    printf("  %-4s %-20s %-8s %-5s %10s  PAGAMENTO\n",
                        "N.","CLIENTE","COD.PROD","QTDE","TOTAL");
                    printf("  "); int j; for(j=0;j<65;j++) printf("-"); printf("\n");
                    corReset();
                    for (i = 0; i < totalVendas; i++) {
                        printf("  %-4d %-20s %-8d %-5d R$%7.2f  %s\n",
                            listaVendas[i].numero,
                            listaVendas[i].cliente,
                            listaVendas[i].codProduto,
                            listaVendas[i].quantidade,
                            listaVendas[i].valorTotal,
                            listaVendas[i].formaPagamento);
                        totalGeral += listaVendas[i].valorTotal;
                    }
                    printf("  "); for(int j=0;j<65;j++) printf("-"); printf("\n");
                    corVerde();
                    printf("  Total de vendas: %d  |  Faturamento total: R$ %.2f\n",
                        totalVendas, totalGeral);
                    corReset();
                }
                pausar();
                break;
            }
            case 0: break;
            default:
                corVermelha(); printf("\n  Opcao invalida!\n"); corReset();
                pausar();
        }
    } while (opcao != 0);
}

/* RELATORIO */
void relatorio() {
    int opcao;
    do {
        cabecalho("RELATORIOS");
        imprimirLinhaMoldura('#', '-', '#');
        corCiano(); printf("#"); corBranca();
        printf("  [1] Relatorio Geral do Sistema                             ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corBranca();
        printf("  [2] Relatorio de Produtos por Categoria                    ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corBranca();
        printf("  [3] Relatorio Financeiro de Vendas                         ");
        corCiano(); printf("#\n"); corReset();
        corCiano(); printf("#"); corVermelha();
        printf("  [0] Voltar ao Menu Principal                               ");
        corCiano(); printf("#\n"); corReset();
        imprimirLinhaMoldura('#', '-', '#');

        corAmarela(); printf("\n  Opcao: "); corReset();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                cabecalho("RELATORIO GERAL");
                int semEstoque = 0, estoqueTotal = 0;
                float valorEstoque = 0;
                int i;
                for (i = 0; i < totalProdutos; i++) {
                    if (!produtos[i].ativo) continue;
                    if (produtos[i].estoque == 0) semEstoque++;
                    estoqueTotal += produtos[i].estoque;
                    valorEstoque += produtos[i].preco * produtos[i].estoque;
                }
                float faturamento = 0;
                for (i = 0; i < totalVendas; i++) faturamento += listaVendas[i].valorTotal;

                printf("\n");
                imprimirLinhaMoldura('+', '=', '+');
                corBranca(); printf("  RESUMO EXECUTIVO - TECH NEXUS\n"); corReset();
                imprimirLinhaMoldura('+', '-', '+');
                printf("  Total de produtos cadastrados : ");
                corAmarela(); printf("%d\n", totalProdutos); corReset();
                printf("  Produtos sem estoque          : ");
                corVermelha(); printf("%d\n", semEstoque); corReset();
                printf("  Unidades em estoque           : ");
                corVerde(); printf("%d\n", estoqueTotal); corReset();
                printf("  Valor total em estoque        : ");
                corVerde(); printf("R$ %.2f\n", valorEstoque); corReset();
                printf("  Total de vendas realizadas    : ");
                corAmarela(); printf("%d\n", totalVendas); corReset();
                printf("  Faturamento total             : ");
                corVerde(); printf("R$ %.2f\n", faturamento); corReset();
                imprimirLinhaMoldura('+', '=', '+');
                pausar();
                break;
            }
            case 2: {
                cabecalho("PRODUTOS POR CATEGORIA");
                if (totalProdutos == 0) {
                    corAmarela(); printf("\n  Sem produtos cadastrados.\n"); corReset();
                } else {
                    /* Categorias unicas via busca linear simples */
                    char categorias[MAX_PRODUTOS][MAX_NOME];
                    int numCats = 0;
                    int i, j;
                    for (i = 0; i < totalProdutos; i++) {
                        if (!produtos[i].ativo) continue;
                        int existe = 0;
                        for (j = 0; j < numCats; j++)
                            if (strcmp(categorias[j], produtos[i].categoria) == 0) { existe = 1; break; }
                        if (!existe) {
                            strcpy(categorias[numCats], produtos[i].categoria);
                            numCats++;
                        }
                    }
                    for (j = 0; j < numCats; j++) {
                        printf("\n");
                        corMagenta(); printf("  [%s]\n", categorias[j]); corReset();
                        for (i = 0; i < totalProdutos; i++) {
                            if (!produtos[i].ativo) continue;
                            if (strcmp(produtos[i].categoria, categorias[j]) == 0) {
                                printf("    %-6d %-28s R$ %7.2f  Estq: %d\n",
                                    produtos[i].codigo,
                                    produtos[i].nome,
                                    produtos[i].preco,
                                    produtos[i].estoque);
                            }
                        }
                    }
                }
                pausar();
                break;
            }
            case 3: {
                cabecalho("RELATORIO FINANCEIRO");
                if (totalVendas == 0) {
                    corAmarela(); printf("\n  Nenhuma venda registrada.\n"); corReset();
                } else {
                    float totalCredito = 0, totalDebito = 0, totalPix = 0,
                          totalDinheiro = 0, totalOutros = 0;
                    int i;
                    for (i = 0; i < totalVendas; i++) {
                        char *fp = listaVendas[i].formaPagamento;
                        if      (strstr(fp,"redito") || strstr(fp,"REDITO")) totalCredito  += listaVendas[i].valorTotal;
                        else if (strstr(fp,"ebito")  || strstr(fp,"EBITO"))  totalDebito   += listaVendas[i].valorTotal;
                        else if (strstr(fp,"ix")     || strstr(fp,"IX"))     totalPix      += listaVendas[i].valorTotal;
                        else if (strstr(fp,"inheiro") || strstr(fp,"INHEIRO")) totalDinheiro += listaVendas[i].valorTotal;
                        else totalOutros += listaVendas[i].valorTotal;
                    }
                    float total = totalCredito + totalDebito + totalPix + totalDinheiro + totalOutros;

                    printf("\n");
                    imprimirLinhaMoldura('+', '=', '+');
                    corBranca(); printf("  FATURAMENTO POR FORMA DE PAGAMENTO\n"); corReset();
                    imprimirLinhaMoldura('+', '-', '+');
                    printf("  Cartao de Credito  : "); corVerde();  printf("R$ %9.2f\n", totalCredito);  corReset();
                    printf("  Cartao de Debito   : "); corVerde();  printf("R$ %9.2f\n", totalDebito);   corReset();
                    printf("  Pix                : "); corCiano();  printf("R$ %9.2f\n", totalPix);      corReset();
                    printf("  Dinheiro           : "); corAmarela();printf("R$ %9.2f\n", totalDinheiro); corReset();
                    printf("  Outros             : "); corBranca(); printf("R$ %9.2f\n", totalOutros);   corReset();
                    imprimirLinhaMoldura('+', '-', '+');
                    printf("  TOTAL FATURADO     : "); corVerde();  printf("R$ %9.2f\n", total);         corReset();
                    imprimirLinhaMoldura('+', '=', '+');
                }
                pausar();
                break;
            }
            case 0: break;
            default:
                corVermelha(); printf("\n  Opcao invalida!\n"); corReset();
                pausar();
        }
    } while (opcao != 0);
}

/*  TELA DE SAIDA */
void telaSaida() {
    limparTela();
    imprimirLinhaMoldura('#', '=', '#');
    imprimirLinhaVazia();

    corCiano(); printf("#"); corAmarela();
    printf("           Obrigado por usar o TECH NEXUS!                ");
    corCiano(); printf("     #\n"); corReset();

    imprimirLinhaVazia();

    corCiano(); printf("#"); corVerde();
    printf("        \"Inovar e transformar o impossivel em realidade.\" ");
    corCiano(); printf(" #\n"); corReset();

    imprimirLinhaVazia();
    imprimirLinhaMoldura('#', '=', '#');
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    telaEntrada();

    int opcao;
    do {
        cabecalho("MENU PRINCIPAL");
        menuPrincipal();

        corAmarela();
        printf("\n  Sua opcao: ");
        corReset();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastroProdutos();
                break;
            case 2:
                movimentacao();
                break;
            case 3:
                menuVendas();
                break;
            case 4:
                relatorio();
                break;
            case 0:
                telaSaida();
                break;
            default:
                limparTela();
                corVermelha();
                printf("\n  Opcao invalida! Tente novamente.\n");
                corReset();
                pausar();
        }
    } while (opcao != 0);

    return 0;
}