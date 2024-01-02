using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp8
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("rock(1) paper(2) scissors(3) shoot");
            Console.WriteLine("Choose from rock paper or scissors");
            int throw_player = Convert.ToInt32(Console.ReadLine());
            switch(throw_player)
            {
                case 1: Console.WriteLine("You picked rock");
                break;
                
                case 2:
                Console.WriteLine("You picked paper");
                break;


                case 3: 
                Console.WriteLine("you picked scissors");
                break;


                default: Console.WriteLine("Wrong input, you can select either rock(1) paper(2) or scissors(3)");
                break;
            }
            

            Random random = new Random();

            int throw_robot = random.Next(1, 4);
           
            switch (throw_robot)
            {
                case 1:
                    Console.WriteLine("robot picked rock");
                    break;

                case 2:
                    Console.WriteLine("robot picked paper");
                    break;


                case 3:
                    Console.WriteLine("robot picked scissors");
                    break;
            }

            Console.WriteLine(throw_robot);

            if (throw_robot == throw_player)
                Console.WriteLine("It is a draw");

            else if ((throw_player == 1 && throw_robot == 3))
                Console.WriteLine("You win");

            else if (throw_player == 3 && throw_robot == 2)
                Console.WriteLine("You lost");

            else
                Console.WriteLine("You win");

                Console.ReadLine();
        }
    }
}
