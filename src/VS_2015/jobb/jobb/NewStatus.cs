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
    public partial class NewStatus : Form
    {
        // Private variable
        string status;
        Form1 f = Program.f1;
        bool textChanged = false, insertButtonClicked = false;

        /// <summary>
        /// Angir hvilken status som skal settes inn i databasen.
        /// </summary>
        /// <param name="newStatus">Statusen som skal settes inn.</param>
        public void setStatus(string newStatus)
        {
            status = newStatus;
        }

        /// <summary>
        /// Henter statusen som skal settes inn.
        /// </summary>
        /// <returns>statusen som skal settes inn.</returns>
        public string getStatus()
        {
            return status;
        }
        public NewStatus()
        {
            InitializeComponent();
        }

        private void textBoxStatus_TextChanged(object sender, EventArgs e)
        {
            textChanged = true;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            insertButtonClicked = true;
            textChanged = false;
            setStatus(textBoxStatus.Text);
            Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            insertButtonClicked = false;
            Close();
        }

        private void NewStatus_Load(object sender, EventArgs e)
        {
            buttonOK.DialogResult = DialogResult.OK;
        }

        private void NewStatus_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (insertButtonClicked)
            {
                if(getStatus().Length == 0)
                {
                    MessageBox.Show("Du må angi en unik status.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    insertButtonClicked = false;
                    e.Cancel = true;
                }
                insertButtonClicked = false;
            }
            else
            {
                if (textChanged)
                {
                    DialogResult dr = MessageBox.Show("Du har endret på statusteksten. Vil du lagre endringene i databasen?", Program.title, MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                    if (dr == DialogResult.Yes)
                    {
                        buttonOK.PerformClick();
                    }
                    else if (dr == DialogResult.Cancel)
                        e.Cancel = true;
                }
            }
        }
    }
}
