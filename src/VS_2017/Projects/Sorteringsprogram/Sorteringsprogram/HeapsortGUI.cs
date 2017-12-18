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
    public partial class HeapsortGUI : Form
    {
        string input, output;
        long elements;
        heapsort hs;
        public HeapsortGUI()
        {
            InitializeComponent();
        }

        private void buttonBrowse_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    textBoxFilePath.Text = openFileDialog1.FileName;
                    string file = Path.GetFileName(openFileDialog1.FileName);
                    string path = Path.GetFullPath(file);
                    input = File.ReadAllText(openFileDialog1.FileName);
                    buttonSort.Enabled = true;
                    textBoxUnsorted.Text = input;
                }
                catch (OutOfMemoryException)
                {
                    MessageBox.Show("Tekstfilen du forsøkte å laste inn, er for stor. Prøv med en mindre fil isteden.", "Sorteringsprogram", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
        }

        private void buttonSort_Click(object sender, EventArgs e)
        {
            try
            {
                long[] A = input.Split(' ').Select(n => Convert.ToInt64(n)).ToArray();
                elements = A[0];
                long[] B = new long[A.Length - 1];
                for (long i = 1; i <= B.Length; i++)
                    B[i - 1] = A[i];

                //timer1.Start();
                System.Diagnostics.Stopwatch sw = new System.Diagnostics.Stopwatch();
                sw.Start();
                hs.heapSort(B);
                sw.Stop();
                long mis = sw.ElapsedMilliseconds;
                toolStripStatusLabel1.Text = "Heapsort av " + elements + " elementer utført på " + TimeSpan.FromMilliseconds(mis);
                output = string.Join(" ", B);
                textBoxSorted.Text = output;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Noe gikk galt: " + ex.ToString(), "Sorteringsprogram", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void HeapsortGUI_Load(object sender, EventArgs e)
        {
            hs = new heapsort();
        }
    }
}
