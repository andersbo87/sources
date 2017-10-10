/*
 * Copyright (c) 2017, Anders Bolt-Evensen
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Anders Bolt-Evensen BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


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

namespace jobb
{
    public partial class SQLCommands : Form
    {
        Form1 f = Program.f1;
        psql p;
        public SQLCommands()
        {
            InitializeComponent();
        }

        private void SQLCommands_Load(object sender, EventArgs e)
        {
            p = f.p;
        }

        private void buttonExecute_Click(object sender, EventArgs e)
        {
            // La oss først tømme lista:
            //int i = 0;
            //dataGridView1.Columns.Clear();
            //dataGridView1.Rows.Clear();
            string command = textBoxCmd.Text;
            //List<string> lst = new List<string>();
            //string[] lst, title;
            string res;
            res = p.ExecQry(command);
            //title = p.GetTitle(command);
            /*while (i < title.Count())
            {
                dataGridView1.Columns.Add(title[i], title[i]);
                i++;
            }*/
            /*foreach(string list in title)
            {
                dataGridView1.Columns.Add(list, list);
            }
            foreach(string list in lst)
            {
                //var text = list.Split('\t');
                dataGridView1.Rows.Add(lst);
            }*/
            //string li;
            /*while(i < l.Count())
            {
                dataGridView1.Rows.Add(l[i]);
                i++;
            }*/
            textBoxOutput.Text = res;
            //StringBuilder sb = new StringBuilder();
            /*int i = 0;
            //while(i < lst.Count)
            {
                //textBoxOutput.AppendText(lst.ElementAt(i) + " ");
                i++;
            }*/
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if(e.Control && e.KeyCode == Keys.A)
            {
                textBoxCmd.SelectAll();
            }
        }
    }
}
