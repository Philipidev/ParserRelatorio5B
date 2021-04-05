using System;
using System.IO;
using System.Linq;
using System.Text;

namespace Rel05B
{
    class Program
    {
        private static char X = ' ';
        private static char Y = ' ';

        static void Main(string[] args)
        {
            bool Selecionou = false;
            string[] TextoArquivo = new string[0];

            while (!Selecionou)
            {
                try
                {
                    Console.WriteLine("Seu arquivo deve estar no mesmo Path que a sua aplicação");
                    Console.WriteLine("Digite o nome do arquivo: ");
                    string NomeArquivo = Console.ReadLine();

                    TextoArquivo = File.ReadAllLines(NomeArquivo);
                    if (TextoArquivo.Length > 0)
                        Selecionou = true;
                }
                catch (FileNotFoundException ex)
                {
                    Console.WriteLine("\n Não foi possivel abrir o arquivo digitado..");
                    Console.ReadLine();
                    Console.Clear();
                }
            }

            ParseTextToHex(TextoArquivo);

            Console.WriteLine("\n\n Arquivo 'textohex.txt' foi gerado..");
            Console.ReadLine();
            Environment.Exit(0);
        }

        private static void ParseTextToHex(string[] linhasTexto)
        {
            int PosInicio = GetPosicaoInicio(linhasTexto);
            if (File.Exists("textohex.txt"))
                File.Delete("textohex.txt");
            using (StreamWriter sw = new StreamWriter("textohex.txt"))
            {
                for (int i = ++PosInicio; i < linhasTexto.Length && !linhasTexto[i].StartsWith("fim."); i++)
                {
                    string linhaPronta = ParseLine(linhasTexto[i]);

                    if (linhaPronta == null)
                        continue;

                    sw.WriteLine(linhaPronta);
                }
            }
        }

        private static string ParseLine(string linha)
        {
            if (linha == null || !linha.Any())
                return null;
            if (linha.Contains("="))
            {
                if (linha.ToLower().Contains("x"))
                    X = linha[linha.IndexOf("=") + 1];
                else
                    Y = linha[linha.IndexOf("=") + 1];
                return null;
            }
            else
            {
                string Operacao = linha.Substring(0, linha.Length - 1);
                return $"{X}{Y}{GetHexFromMnemonico(Operacao)}";
            }
        }

        private static char GetHexFromMnemonico(string operacao)
        {
            switch (operacao)
            {
                case "An":
                    return '0';
                case "nAoB":
                    return '1';
                case "AnB":
                    return '2';
                case "zeroL":
                    return '3';
                case "nAeB":
                    return '4';
                case "Bn":
                    return '5';
                case "AxB":
                    return '6';
                case "ABn":
                    return '7';
                case "AnoB":
                    return '8';
                case "nAxB":
                    return '9';
                case "B":
                    return 'A';
                case "AB":
                    return 'B';
                case "umL":
                    return 'C';
                case "AoBn":
                    return 'D';
                case "AoB":
                    return 'E';
                case "A":
                    return 'F';
                default:
                    return '?';
            }
        }

        private static int GetPosicaoInicio(string[] linhasTexto)
        {
            int posInicio = 0;
            for (int i = 0; i < linhasTexto.Length; i++)
            {
                if (linhasTexto[i].StartsWith("inicio:"))
                {
                    posInicio = i;
                    break;
                }
            }
            return posInicio;
        }
    }
}