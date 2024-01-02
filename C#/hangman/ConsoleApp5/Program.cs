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
           
                Random rnd = new Random(); //Vytvoříme random

                //skupina "words", která obsahuje náhodná slova
                string[] words = { "mouse", "apple", "banana", "car", "dog", "elephant", "fish", "guitar", "house", "igloo", "jacket", "kite", "lemon", "monkey", "notebook", "orange", "penguin", "queen", "rainbow", "strawberry", "turtle", "umbrella", "violin", "watermelon", "xylophone", "zebra", "airplane", "butterfly", "candle", "dolphin", "eagle", "flamingo", "giraffe", "hamburger", "ice cream", "jellyfish", "kangaroo", "lighthouse", "moon", "noodle", "octopus", "parrot", "quokka", "rose", "sunflower", "tiger", "umbrella", "volcano", "waterfall", "xylophone", "yacht", "zeppelin", "ant", "beach", "caterpillar", "daisy", "elephant", "fireworks", "globe", "helicopter", "igloo", "jungle", "koala", "lion", "mango", "nightingale", "ocean", "panda", "quokka", "raccoon", "sun", "tulip", "unicorn", "vulture", "whale", "xylophone", "yacht", "zeppelin", "apricot", "blueberry", "cucumber", "dandelion", "eggplant", "flute", "gazelle", "hibiscus", "iguana", "jackal", "kiwi", "lemur", "mongoose", "narwhal", "otter", "panda", "quill", "rhubarb", "strudel", "tangerine", "urchin", "violet", "wombat", "x-ray", "yogurt" };

                //definujeme random velikost jako word
                int index = rnd.Next(words.Length);

                //definujeme hadane_slovo - to potřebujeme, aby jsme měli proměnou, která si pamatuje, co je zadane slovo
                string hadane_slovo = words[index];

                //potrebujeme definovat promennu, která bude vedet jak je dlouho hadane_slovo a podle toho vytvori policka
                // a nebo taky staci udelat loop - i > 2, i++ a tak dale
                string pocet_pismen = ("_ ");

                Console.WriteLine("Welcome in my game called The Hangman, i think you all know the rules to this game so... good luck ");

            //potřebujeme vytvořit velkou loopu, která ještě moc nevim jak bude fungovat a co vlastně bude dělat:)
                bool win = false;
                bool loose = false;
                while (win == false || loose == false) {


                //for loop, který vyjede počet _ tolikrát, kolik je písmen v hadanem slově
                for (int j = 0; j <= hadane_slovo.Length; j++)
                {
                    Console.Write(pocet_pismen);

                }
                //a teď ta zábavnější část, musíme vytvoři loop, který pokud zadáš správně písmeno z uhádnutého slova, loop vytvoří opět __
                // ovšem do správného místa dá uhádnuté písmeno
                // pomocí case??

                // user input hadane pismeno
                Console.WriteLine();
                char hadane_pismeno = Console.ReadKey().KeyChar;//also proč je kurva tak složitý dát blbej user input pro CHAR

                // unga bunga pokud je tam tohle, napiš tohle lol also .Contains je docela cool
                if (hadane_slovo.Contains(hadane_pismeno) == true)
                {
                    for (int j = 0; j <= hadane_slovo.Length; j++)
                    {
                        Console.Write(pocet_pismen);
                    }
                    string str = hadane_slovo;
                    Console.WriteLine(pocet_pismen+);

                }
                else { Console.WriteLine("L"); }















                Console.ReadLine();
            }
             
        }
    }
}
