using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Threading;

namespace ConsoleApp1
{
    
    class Program
    {
        static SimpleSerial serial ;

        static void Main(string[] args)
        {
            serial = new SimpleSerial(args[0], 9600, true);

            serial.DataReady += Serial_DataReady;

            Console.WriteLine("Reading. Press any key to escape.");

            Console.ReadKey(false);

        }

        private static void Serial_DataReady(object sender, EventArgs e)
        {
            Console.WriteLine(serial.ReadString());
           
        }                      

    }
    
}
