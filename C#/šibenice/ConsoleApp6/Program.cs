using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hangman
{
    internal class Program
    {
        static void Main(string[] args)
        {

            Random rnd = new Random();

  
            string[] words = { "mouse", "apple", "banana", "car", "dog", "elephant", "fish", "guitar", "house", "igloo", "jacket", "kite", "lemon", "monkey", "notebook", "orange", "penguin", "queen", "rainbow", "strawberry", "turtle", "umbrella", "violin", "watermelon", "xylophone", "zebra", "airplane", "butterfly", "candle", "dolphin", "eagle", "flamingo", "giraffe", "hamburger", "ice cream", "jellyfish", "kangaroo", "lighthouse", "moon", "noodle", "octopus", "parrot", "quokka", "rose", "sunflower", "tiger", "umbrella", "volcano", "waterfall", "xylophone", "yacht", "zeppelin", "ant", "beach", "caterpillar", "daisy", "elephant", "fireworks", "globe", "helicopter", "igloo", "jungle", "koala", "lion", "mango", "nightingale", "ocean", "panda", "quokka", "raccoon", "sun", "tulip", "unicorn", "vulture", "whale", "xylophone", "yacht", "zeppelin", "apricot", "blueberry", "cucumber", "dandelion", "eggplant", "flute", "gazelle", "hibiscus", "iguana", "jackal", "kiwi", "lemur", "mongoose", "narwhal", "otter", "panda", "quill", "rhubarb", "strudel", "tangerine", "urchin", "violet", "wombat", "x-ray", "yogurt" };


            int index = rnd.Next(words.Length);


            string hadane_slovo = words[index];

            string pocet_pismen = ("_ ");

            Console.WriteLine("Welcome in my game called The Hangman, i think you all know the rules to this game so... good luck ");

 
            bool win = false;
            bool loose = false;
            while (win == false || loose == false)
            {

                for (int j = 0; j <= hadane_slovo.Length; j++)
                {
                    Console.Write(pocet_pismen);

                }
                Console.WriteLine();
                char hadane_pismeno = Console.ReadKey().KeyChar;
                
                if (hadane_slovo.Contains(hadane_pismeno) == true)
                {
                    for (int j = 0; j <= hadane_slovo.Length; j++)
                    {
                        Console.Write(pocet_pismen);
                    }
                    string str = hadane_slovo;
                    Console.WriteLine(pocet_pismen);

                }
                else { Console.WriteLine("L"); }
















                Console.ReadLine();
            }

        }
    }
}
