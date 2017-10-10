using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
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
    public partial class RandomNumbersGenerator : Form
    {
        bool canClose;
        public RandomNumbersGenerator()
        {
            InitializeComponent();
        }
        void writeToFile(string filename)
        {
            try
            {
                if (textBox1.Text.Length == 0)
                {
                    MessageBox.Show("Vennligst angi en verdi i tekstboksen.", "Sorteringsprogram", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    canClose = false;
                }
                int arg0;
                arg0 = Int32.Parse(textBox1.Text);
                TextWriter writer;
                //string path = "C:\\Users\\a-bol\\fil.txt";
                string path = filename;
                if (File.Exists(path))
                {
                    writer = File.CreateText(path);
                    RandomNumbersGenerator ng = new RandomNumbersGenerator();
                    List<Int32> list = new List<Int32>();
                    for (int i = 1; i < arg0 + 1; i++)
                    {
                        list.Add(i);
                    }

                    shuffler.shuffle(list);
                    writer.Write(list.Count + " ");
                    for (int i = 0; i < arg0; i++)
                    {
                        if(i == arg0 - 1)
                        {
                            writer.Write(list.ElementAt(i));
                        }
                        else
                            writer.Write(list.ElementAt(i) + " ");
                    }
                    writer.Close();
                    canClose = true;
                    Close();
                }
                else
                {
                    File.Create(path).Close();
                    writeToFile(filename);
                }
                
            }
            catch (FileNotFoundException fnfe)
            {
                //System.err.println(name + ": " + e.toString());
                //Logger.getLogger(numberGenerator.class.getName()).log(Level.SEVERE, null, e);
                MessageBox.Show(fnfe.Message, "Sorteringsprogram", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                //System.err.println(name + ": " +ex.toString());
                //Logger.getLogger(numberGenerator.class.getName()).log(Level.SEVERE, null, ex);
                MessageBox.Show(ex.Message, "Sorteringsprogram", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void buttonOK_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
        }

        private void RandomNumbersGenerator_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (!canClose)
                e.Cancel = true;
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            canClose = true;
            Close();
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            writeToFile(saveFileDialog1.FileName);
        }
    }
    static class shuffler
    {
        static Random r = new Random();

       // Plasserer tallene mellom 0 og n på tilfeldig plass
        public static void shuffle<T>(this List<T> list)
        {
            int n = list.Count;
            while (n > 1)
            {
                n--;
                int k = r.Next(n + 1);
                T value = list[k];
                list[k] = list[n];
                list[n] = value;
            }
        }
    }

}
