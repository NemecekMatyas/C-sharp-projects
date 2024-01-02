using System;

namespace Šachovnice
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int velikost = 8;
            string[,] sachovnice = new string[velikost, velikost];

            for (int i = 0; i < velikost; i++)
            {
                for (int j = 0; j < velikost; j++)
                {
                    if ((i + j) % 2 == 0)
                    {
                        sachovnice[i, j] = "  ";
                    }
                    else
                    {
                        sachovnice[i, j] = "██";
                    }
                }
            }

            for (int i = 0; i < velikost; i++)
            {
                for (int j = 0; j < velikost; j++)
                {
                    Console.Write(sachovnice[i, j]);
                }
                Console.WriteLine();
            }

            Console.ReadLine();
        }
    }
}
