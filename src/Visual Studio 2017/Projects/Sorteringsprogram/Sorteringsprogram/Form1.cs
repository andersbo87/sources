using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sorteringsprogram
{
    public partial class Form1 : Form
    {
        RandomNumbersGenerator rng;
        reversedSortedNumbersGenerator rsng;
        MergeSortGUI msgui;
        QuicksortGUI qsgui;
        InsertionSortGUI igui;
        public Form1()
        {
            InitializeComponent();
            rng = new RandomNumbersGenerator();
            rsng = new reversedSortedNumbersGenerator();
            msgui = new MergeSortGUI();
            qsgui = new QuicksortGUI();
            igui = new InsertionSortGUI();
        }

        private void btnGenerateRandomNumbers_Click(object sender, EventArgs e)
        {
            DialogResult dr = rng.ShowDialog();
            if(dr == DialogResult.OK)
            {
                // Lagre en fil med det tilfeldig genererte tallet
            }
        }

        private void buttonMergesort_Click(object sender, EventArgs e)
        {
            if (msgui.IsDisposed)
                msgui = new MergeSortGUI();
            msgui.Show();
        }

        private void buttonQuicksort_Click(object sender, EventArgs e)
        {
            if (qsgui.IsDisposed)
                qsgui = new QuicksortGUI();
            qsgui.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult dr = rsng.ShowDialog();
            if (dr == DialogResult.OK)
            {
                // Lagre en fil med det tilfeldig genererte tallet
            }
        }

        private void buttonInsertionSort_Click(object sender, EventArgs e)
        {
            if (igui.IsDisposed)
                igui = new InsertionSortGUI();
            igui.Show();
        }
    }
}
