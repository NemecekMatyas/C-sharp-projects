using System;
using System.Collections.Generic;

namespace KingdomComeDiceGame
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Welcome to the Kingdom Come Dice Game!");

            int totalScore = 0;
            int roundScore = 0;
            int roundNumber = 1;

            while (true)
            {
                Console.WriteLine("Round " + roundNumber + " - Total Score: " + totalScore);

                int roll = RollDice();
                roundScore += roll;

                Console.WriteLine("You rolled a " + roll + " - Round Score: " + roundScore);

                if (roll == 1)
                {
                    Console.WriteLine("You lose! Your round score of " + roundScore + " is erased.");
                    roundScore = 0;
                    break;
                }
                else if (roll == 6)
                {
                    Console.WriteLine("Congratulations! Your score for this round is doubled!");
                    roundScore *= 2;
                }

                Console.WriteLine("Enter 'k' to keep your round score or 'r' to roll again.");
                string selection = Console.ReadLine();

                while (!IsValidSelection(new List<int> { 'k', 'r' }, (int)selection[0]))
                {
                    Console.WriteLine("Invalid selection. Enter 'k' to keep your round score or 'r' to roll again.");
                    selection = Console.ReadLine();
                }

                if (selection[0] == 'k')
                {
                    totalScore += roundScore;
                    roundScore = 0;
                    roundNumber++;
                }
            }

            Console.WriteLine("Game over! Total score: " + totalScore);
            Console.ReadLine();
        }

        static int RollDice()
        {
            Random random = new Random();
            return random.Next(1, 7);
        }

        static bool IsValidSelection(List<int> validOptions, int selection)
        {
            return validOptions.Contains(selection);
        }
    }
}
