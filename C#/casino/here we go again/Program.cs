using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace here_we_go_again
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("vítejte v kasínu, kolik si přejete dnes u nás utratit?");
            int budget = Int32.Parse(Console.ReadLine());
            Console.WriteLine("Váš budget je: " + budget);
            Console.WriteLine("Kolik si přejete vsadit? Pokud si přejete odejít, napište 0");
            int bet = Int32.Parse(Console.ReadLine());
            if (bet > 0)
            {
                Console.WriteLine("hrajete o : " + bet);

                Random rnd = new Random();

                int[] slot1 = new int[10];
                int[] slot2 = new int[10];
                int[] slot3 = new int[10];

                // Generování náhodných čísel pro sloty
                for (int i = 0; i < 10; i++)
                {
                    slot1[i] = rnd.Next(1, 4);
                    slot2[i] = rnd.Next(1, 4);
                    slot3[i] = rnd.Next(1, 4);
                }

                // Zobrazení výsledků
                for (int i = 0; i < 10; i++)
                {
                    Console.WriteLine($"{slot1[i]} {slot2[i]} {slot3[i]}");
                }

                if (slot1 == slot2 )
                {
                    Console.WriteLine("Gratuluji, VYHRÁLI jste ");
                    budget = budget * 2;
                    Console.WriteLine("Tvůj budget je : " + budget);
                }
                else
                {
                    Console.WriteLine("právě jsi podělal celej tvůj nájem lol");
                    budget = budget / 2;
                    Console.WriteLine("Tvůj budget je : " + budget);
                }
            }
            else 
            {
                Console.WriteLine("Děkujeme za hru, váš zůstatek je : " + budget);
                    }
            Console.ReadLine();

        }

    }
}
