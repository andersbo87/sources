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
    public partial class NewCountry : Form
    {
        // Private variabler
        string countryName;
        bool textChanged = false, insertButtonClicked = false;
        Form1 f = Program.f1;
        psql p;
        
        public void setCountryName(string name)
        {
            countryName = name;
        }
        public string getCountryName()
        {
            return countryName;
        }
        public NewCountry()
        {
            InitializeComponent();
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            textChanged = false;
            insertButtonClicked = true;
            setCountryName(textBoxCountry.Text);
            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            insertButtonClicked = false;
            Close();
        }

        private void NewCountry_Load(object sender, EventArgs e)
        {
            p = f.p;
            buttonOK.DialogResult = DialogResult.OK;
        }

        private void textBoxCountry_TextChanged(object sender, EventArgs e)
        {
            textChanged = true;
        }

        private void NewCountry_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (insertButtonClicked)
            {
                if (getCountryName().Length == 0)
                {
                    MessageBox.Show("Du må angi et unikt landnavn.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    insertButtonClicked = false;
                    e.Cancel = true;
                }
                insertButtonClicked = false;
            }
            else
            {
                if (textChanged)
                {
                    DialogResult d = MessageBox.Show("Du har endret på teksten i tekstboksen for land. Vil du lagre disse endringene i databasen?", Program.title, MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                    if (d == DialogResult.OK)
                    {
                        buttonOK.PerformClick();
                    }
                    else if (d == DialogResult.Cancel)
                        e.Cancel = true;
                }
            }
        }
    }
}
