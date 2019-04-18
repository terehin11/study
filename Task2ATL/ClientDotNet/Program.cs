using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ComponentLib;
namespace ClientDotNet
{
    class Program
    {
        static void Main(string[] args)
        {
            ComponentClass ComCl = new ComponentClass();
            ComCl.Add(3);
            Console.WriteLine("Добавлен элемент 3");
            ComCl.Add(7.5);
            Console.WriteLine("Добавлен элемент 7.5");
            ulong count = ComCl.Count;
            Console.Write("Количество элементов: ");
            Console.WriteLine(count);
            double mean = ComCl.Mean;
            Console.WriteLine("Среднее значение: {0}", mean);
            double[] arr = (double[])ComCl.GetData();
            foreach(double it in arr)
            {
                Console.WriteLine(it);
            }
            
        }
    }
}
