using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sorteringsprogram
{
    public partial class MergeSortGUI : Form
    {
        ArrayIO aio;
        mergesort ms;
        string input, output;
        long elements;
        public MergeSortGUI()
        {
            InitializeComponent();
        }

        private void MergeSortGUI_Load(object sender, EventArgs e)
        {
            aio = new ArrayIO();
            ms = new mergesort();
        }

        private void buttonBrowse_Click(object sender, EventArgs e)
        {
            try
            {
                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    textBoxFilePath.Text = openFileDialog1.FileName;
                    string file = Path.GetFileName(openFileDialog1.FileName);
                    string path = Path.GetFullPath(file);
                    input = File.ReadAllText(openFileDialog1.FileName);
                    buttonSort.Enabled = true;
                    buttonDetails.Enabled = true;
                }
            }
            catch(OutOfMemoryException)
            {
                MessageBox.Show("Tekstfilen er for stor. Last inn en tekstfil mindre enn 1 GB.", "Sorteringsprogram", MessageBoxButtons.OK,MessageBoxIcon.Exclamation);
            }
        }

        private void buttonSort_Click(object sender, EventArgs e)
        {
            long[] A = input.Split(' ').Select(n => Convert.ToInt64(n)).ToArray();
            elements = A[0];
            long[] B = new long[A.Length - 1];
            for (long i = 1; i <= B.Length; i++)
                B[i-1] = A[i];

            //timer1.Start();
            System.Diagnostics.Stopwatch sw = new System.Diagnostics.Stopwatch();
            sw.Start();
            ms.sort(B);
            sw.Stop();
            long mis = sw.ElapsedMilliseconds;
            toolStripStatusLabel1.Text = "Flettesortering av " + elements + " elementer utført på " + TimeSpan.FromMilliseconds(mis);
            output = string.Join(" ", B);
        }

        private void buttonDetails_Click(object sender, EventArgs e)
        {
            textBoxUnsorted.Text = input;
            textBoxSorted.Text = output;
        }
    }
}
