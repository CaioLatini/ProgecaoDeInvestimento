using System;
using System.Globalization;

class SimuladorInvestimento
{
    const float TAXA_JUROS_MENSAL = 2f;
    const int MAX_REGISTROS = 100;

    static float[,] matrizMensal = new float[MAX_REGISTROS, 3];
    static float[,] matrizUnica = new float[MAX_REGISTROS, 2];

    static float valorMensal, valorFinal, depositoInicial;
    static int tempo, anos, meses;
    static int xMensal = 0;
    static int xUnico = 0;
    static bool contato = false;
    static bool valido = false;

    static void Main()
    {
        if (PrimeiroContato())
        {
            Apresentacao();
        }
        SimulacaoInvestimento();
    }

    static void Apresentacao()
    {
        Console.WriteLine("Bem-vindo ao seu simulador de investimento, vamos começar!");
        contato = true;
    }

    static void SimulacaoInvestimento()
    {
        int resp = 0;

        while (!valido)
        {
            Console.WriteLine("Qual tipo de investimento será realizado?\n1 - Depósito único\n2 - Depósito mensal");
            if (int.TryParse(Console.ReadLine(), out resp) && (resp == 1 || resp == 2))
            {
                valido = true;
            }
            else
            {
                Console.WriteLine("Resposta inválida!");
            }
        }

        if (resp == 2)
        {
            Console.WriteLine("Terá valor inicial em seu investimento? (S / N)");
            char respChar = Console.ReadKey().KeyChar;
            Console.WriteLine();

            if (char.ToUpper(respChar) == 'S')
            {
                Console.WriteLine("Qual será o valor inicial do investimento?");
                depositoInicial = LerFloatPositivo();
            }
            else
            {
                depositoInicial = 1;
            }

            Console.WriteLine("Quanto será investido mensalmente?");
            valorMensal = LerFloatPositivo();

            Console.WriteLine("Quanto tempo manterá o investimento? (Em meses)");
            tempo = LerInteiroPositivo();

            CalculoMensal();
            MesesParaAnos();
            RelatorioDosInvestimentosMensais(xMensal);
            xMensal++;
        }
        else if (resp == 1)
        {
            Console.WriteLine("Qual será o valor depositado?");
            depositoInicial = LerFloatPositivo();

            Console.WriteLine("Quanto tempo manterá o investimento? (Em meses)");
            tempo = LerInteiroPositivo();

            CalculoUnico();
            MesesParaAnos();
            RelatorioDosInvestimentosUnico(xUnico);
            xUnico++;
        }

        FinalizaOuReinicia();
    }

    static void CalculoMensal()
    {
        double elevacaoTempo = depositoInicial * Math.Pow(1 + (TAXA_JUROS_MENSAL / 100.0), tempo);
        double taxaReincidencia = valorMensal * ((Math.Pow(1 + (TAXA_JUROS_MENSAL / 100.0), tempo) - 1) / (TAXA_JUROS_MENSAL / 100.0));
        valorFinal = (float)(elevacaoTempo + taxaReincidencia);
    }

    static void CalculoUnico()
    {
        double taxaComposta = Math.Pow(1 + (TAXA_JUROS_MENSAL / 100.0), tempo);
        valorFinal = (float)(depositoInicial * taxaComposta);
    }

    static bool PrimeiroContato()
    {
        return !contato;
    }

    static void MesesParaAnos()
    {
        anos = tempo / 12;
        meses = tempo % 12;
        Console.WriteLine($"Com esse investimento você terá, ao fim de {anos} anos e {meses} meses, um retorno de R$ {valorFinal:F2}");
    }

    static void FinalizaOuReinicia()
    {
        Console.WriteLine("Gostaria de calcular novamente? (S / N)");
        char resp = Console.ReadKey().KeyChar;
        Console.WriteLine();

        if (char.ToUpper(resp) == 'S')
        {
            valido = false;
            SimulacaoInvestimento();
        }
        else
        {
            ExibirRelatorioDosInvestimentosMensais(xMensal);
            ExibirRelatorioDosInvestimentosUnico(xUnico);
            Console.WriteLine("Obrigado por usar o simulador! O programa será encerrado.");
            Console.WriteLine("Pressione qualquer tecla para encerrar...");
            Console.ReadKey();
        }
    }

    static void RelatorioDosInvestimentosMensais(int x)
    {
        matrizMensal[x, 0] = depositoInicial;
        matrizMensal[x, 1] = valorMensal;
        matrizMensal[x, 2] = valorFinal;
    }

    static void RelatorioDosInvestimentosUnico(int x)
    {
        matrizUnica[x, 0] = depositoInicial;
        matrizUnica[x, 1] = valorFinal;
    }

    static void ExibirRelatorioDosInvestimentosMensais(int x)
    {
        if (x == 0) return;

        Console.WriteLine("\nRelatório dos Investimentos Mensais\n");
        Console.WriteLine("| Valor Inicial | Valor Mensal | Valor Final |");
        for (int i = 0; i < x; i++)
        {
            Console.WriteLine($"| {matrizMensal[i, 0]:F2} | {matrizMensal[i, 1]:F2} | {matrizMensal[i, 2]:F2} |");
        }
    }

    static void ExibirRelatorioDosInvestimentosUnico(int x)
    {
        if (x == 0) return;

        Console.WriteLine("\nRelatório dos Investimentos Únicos\n");
        Console.WriteLine("| Valor Inicial | Valor Final |");
        for (int i = 0; i < x; i++)
        {
            Console.WriteLine($"| {matrizUnica[i, 0]:F2} | {matrizUnica[i, 1]:F2} |");
        }
    }

    static float LerFloatPositivo()
    {
        float valor;
        while (!float.TryParse(Console.ReadLine(), NumberStyles.Any, CultureInfo.InvariantCulture, out valor) || valor <= 0)
        {
            Console.WriteLine("Entrada inválida. Tente novamente.");
        }
        return valor;
    }

    static int LerInteiroPositivo()
    {
        int valor;
        while (!int.TryParse(Console.ReadLine(), out valor) || valor <= 0)
        {
            Console.WriteLine("Entrada inválida. Tente novamente.");
        }
        return valor;
    }
}
