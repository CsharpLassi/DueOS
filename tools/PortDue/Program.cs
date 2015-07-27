using System;
using System.IO.Ports;

namespace PortDue
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			if (args.Length != 1) {
				throw new ArgumentException ("Port angeben");
			}

			SerialPort port = new SerialPort (args[0], 1200);
			port.Open ();

			port.Close ();
		}
	}
}
