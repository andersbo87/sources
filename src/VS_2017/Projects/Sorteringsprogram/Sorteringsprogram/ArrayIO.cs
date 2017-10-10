using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sorteringsprogram
{
    class ArrayIO
    {
        public ArrayIO()
        {

        }
        public string readArray(string filename)
        {
            try
            {
                /*FileStream fs = File.Open(filename,FileMode.Open);
                StreamReader sr = new StreamReader(fs, Encoding.UTF8);
                string res = sr.ReadToEnd();
                fs.Close();
                */
                
                return "";
            }
            catch(Exception e)
            {
                MessageBox.Show(e.Message, "Sorteringsprogram", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return null;
            }
        }
    }
}
