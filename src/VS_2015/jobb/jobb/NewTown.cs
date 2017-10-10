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
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace jobb
{
    public partial class NewTown : Form
    {
        bool insertButtonClicked = false;
        void GetCountry(int index)
        {
            List<string> countryList = p.GetData("SELECT landid FROM land ORDER BY landid asc", 0);
            int i = 0;
            if (comboBoxCountryID.Items.Count == 0)
            {
                while (i < countryList.Count)
                {
                    comboBoxCountryID.Items.Add(countryList.ElementAt(i));
                    i++;
                }
            }
            //comboBoxCountryID.SelectedIndex = p.GetCountryID(index) - 1;
            comboBoxCountryID.SelectedIndex = 0;
        }
        string town;
        int countryID;
        Form1 f = Program.f1;
        psql p;
        bool textChanged = false;
        public string getTown()
        {
            return town;
        }
        public int getCountryID()
        {
            return countryID;
        }
        public void setTown(string newTown)
        {
            town = newTown;
        }
        public void setCountryID(int newCountryID)
        {
            countryID = newCountryID;
        }
        public NewTown()
        {
            InitializeComponent();
        }

        private void NewTown_Load(object sender, EventArgs e)
        {
            buttonOK.DialogResult = DialogResult.OK;
            p = f.p;
            GetCountry(1);
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            labelCountry.Text = p.GetCountryName(Int32.Parse(comboBoxCountryID.Text));
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            textChanged = true;
        }

        private void NewTown_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(insertButtonClicked)
            {
                if(getTown().Length == 0)
                {
                    MessageBox.Show("Vennligst angi et bynavn.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    insertButtonClicked = false;
                    e.Cancel = true;
                }
            }
            else
            {
                if (textChanged)
                {
                    DialogResult d = MessageBox.Show("Du har forandret teksten. Vil du lagre endringene i databasen?", Program.title, MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                    if (d == DialogResult.Yes)
                    {
                        //setTown(textBox1.Text);
                        //setCountryID(Int32.Parse(comboBoxCountryID.Text));
                        //p.InsertTown(getTown(), getCountryID());
                        buttonOK.PerformClick();
                    }
                    else if (d == DialogResult.Cancel)
                        e.Cancel = true;
                }
            }
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            insertButtonClicked = true;
            textChanged = false;
            setTown(textBox1.Text);
            setCountryID(Int32.Parse(comboBoxCountryID.Text));
            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
