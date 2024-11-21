#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define TAXA_JUROS_MENSAL 1
#define MAX_REGISTROS 100

float matrizMensal[MAX_REGISTROS][3];
float matrizUnica[MAX_REGISTROS][2];

float valorMensal, valorFinal, depositoInicial;
int tempo, anos, meses;
int xMensal = 0;
int xUnico = 0;
bool contato = false;
bool valido = false;

// Declaração das funções
void Apresentacao();
void SimulacaoInvestimento();
bool PrimeiroContato();
void MesesParaAnos();
void FinalizaOuReinicia();
void MathMensal();
void MethUnic();
void RelatorioDosInvestimentosMensais(int x);
void RelatorioDosInvestimentosUnico(int x);
void ExibirRelatorioDosInvestimentosMensais(int x);
void ExibirRelatorioDosInvestimentosUnico(int x);
bool ValidarEntradaFloat(float *valor);

int main()
{
    if (PrimeiroContato())
    {
        Apresentacao();
    }
    SimulacaoInvestimento();
    return 0;
}

void Apresentacao()
{
    printf("Bem vindo ao seu simulador de investimento, vamos comecar!\n");
    contato = true;
}

void SimulacaoInvestimento()
{
    int resp;
    while (!valido)
    {
        printf("Qual tipo de investimento sera realizado? \n1 - Deposito unico\n2 - Deposito mensal\n");
        scanf("%d", &resp);
        if (resp == 1 || resp == 2)
        {
            valido = true;
        }
        else
        {
            printf("Resposta invalida! \n");
            valido = false;
        }
    }

    if (resp == 2)
    {
        printf("Ok, tera valor inicial em seu investimento? (S / N)\n");
        char respChar;
        scanf(" %c", &respChar);
        if (respChar == 'S' || respChar == 's')
        {
            printf("Qual sera o valor inicial do investimento? \n");
            while (!ValidarEntradaFloat(&depositoInicial))
            {
                printf("Entrada inválida. Tente novamente.\n");
            }
        }
        else
            depositoInicial = 1;

        printf("Quanto sera investido mensalmente?\n");
        while (!ValidarEntradaFloat(&valorMensal))
        {
            printf("Entrada invalida. Tente novamente.\n");
        }

        printf("Quanto tempo mantera o investimento? (Em meses)\n");
        while (scanf("%d", &tempo) != 1 || tempo <= 0)
        {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n');
        }

        MathMensal();
        MesesParaAnos();
        RelatorioDosInvestimentosMensais(xMensal);
        xMensal++;
    }
    else if (resp == 1)
    {
        printf("Qual sera o valor depositado?\n");
        while (!ValidarEntradaFloat(&depositoInicial))
        {
            printf("Entrada invalida. Tente novamente.\n");
        }

        printf("Quanto tempo mantera o investimento? (Em meses)\n");
        while (scanf("%d", &tempo) != 1 || tempo <= 0)
        {
            printf("Entrada invalida. Tente novamente.\n");
            while (getchar() != '\n');
        }

        MethUnic();
        MesesParaAnos();
        RelatorioDosInvestimentosUnico(xUnico);
        xUnico++;
    }

    FinalizaOuReinicia();
}

void MathMensal()
{
    double elevacaoTempo = depositoInicial * pow((1 + (TAXA_JUROS_MENSAL / 100.0)), tempo);
    double taxaReincidencia = valorMensal * ((pow(1 + (TAXA_JUROS_MENSAL / 100.0), tempo) - 1) / (TAXA_JUROS_MENSAL / 100.0));
    valorFinal = elevacaoTempo + taxaReincidencia;
}

void MethUnic()
{
    double taxaComposta = pow((TAXA_JUROS_MENSAL / 100.0 + 1), tempo);
    valorFinal = depositoInicial * taxaComposta;
}

bool PrimeiroContato()
{
    return !contato;
}

void MesesParaAnos()
{
    anos = tempo / 12;
    meses = tempo % 12;
    printf("Com esse investimento voce tera, ao fim desses %d anos e %d meses, um retorno de %.2f\n", anos, meses, valorFinal);
}

void FinalizaOuReinicia()
{
    char resp;
    printf("Gostaria de calcular novamente? (S / N)\n");
    scanf(" %c", &resp);
    if (resp == 'S' || resp == 's')
    {
        valido = false;
        SimulacaoInvestimento();
    }
    else
    {
        ExibirRelatorioDosInvestimentosMensais(xMensal);
        ExibirRelatorioDosInvestimentosUnico(xUnico);
        printf("Obrigado por usar o simulador! O programa sera encerrado.\n");

        
        printf("Pressione qualquer tecla para encerrar...\n");
        getchar();
        getchar();
    }
}

void RelatorioDosInvestimentosMensais(int x)
{
    matrizMensal[x][0] = depositoInicial;
    matrizMensal[x][1] = valorMensal;
    matrizMensal[x][2] = valorFinal;
}

void RelatorioDosInvestimentosUnico(int x)
{
    matrizUnica[x][0] = depositoInicial;
    matrizUnica[x][1] = valorFinal;
}

void ExibirRelatorioDosInvestimentosMensais(int x)
{
    printf("Relatorio dos Investimentos Mensais\n\n");
    printf("| Valor Inicial | Valor Mensal | Valor Final |\n");
    for (int i = 0; i < x; i++)
    {
        printf("| %.2f |  %.2f | %.2f |\n\n", matrizMensal[i][0], matrizMensal[i][1], matrizMensal[i][2]);
    }
}

void ExibirRelatorioDosInvestimentosUnico(int x)
{
    printf("Relatorio dos Investimentos Unicos\n\n");
    printf("| Valor Inicial | Valor Final |\n");
    for (int i = 0; i < x; i++)
    {
        printf("| %.2f | %.2f |\n\n", matrizUnica[i][0], matrizUnica[i][1]);
    }
}

bool ValidarEntradaFloat(float *valor)
{
    if (scanf("%f", valor) != 1 || *valor <= 0)
    {
        while (getchar() != '\n'); 
        return false;
    }
    return true;
}
