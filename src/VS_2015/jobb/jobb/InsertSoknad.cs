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
    public partial class InsertSoknad : Form
    {
        // Private variabler:
        Form1 f = Program.f1;
        psql p;
        List<string> statusList, cityList;
        private string title, company, date;
        private int cityID, statusID;
        bool textChanged = false, insertButtonClicked = false;
        public InsertSoknad()
        {
            InitializeComponent();
        }
        

        // Private methods
        bool preInsertApplication()
        {
            if (textBoxPositionTitle.Text.Length == 0)
            {
                MessageBox.Show("Du må angi en tittel til jobben.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return false;
            }
            else
            {
                SetTitle(textBoxPositionTitle.Text);
            }
            if (textBoxCompany.Text.Length == 0)
            {
                MessageBox.Show("Du må angi et navn til bedriften.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return false;
            }
            else
                SetCompany(textBoxCompany.Text);
            if (cities.Text.Length == 0)
            {
                MessageBox.Show("Du må angi et navn på byen hvor jobben er.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return false;
            }
            else
                SetCityID(Int32.Parse(cities.Text));
            if (statuses.Text.Length == 0)
            {
                MessageBox.Show("Vennligst angi en status for jobben.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return false;
            }
            else
                SetStatusID(Int32.Parse(statuses.Text));

            SetDate(textBoxDate.Text);
            return true;
        }
        private void GetCities()
        {
            cityList = p.GetData("SELECT stedid FROM sted", 0);
            int i = 0;
            while(i < cityList.Count)
            {
                cities.Items.Add(cityList.ElementAt(i));
                i++;
            }
        }
        private void GetStatuses()
        {
            statusList = p.GetData("SELECT statusID FROM status", 0);
            int i = 0;
            while(i < statusList.Count)
            {
                statuses.Items.Add(statusList.ElementAt(i));
                i++;
            }
        }
        private void InsertSoknad_Load(object sender, EventArgs e)
        {
            p = f.p;
            GetStatuses();
            GetCities();
            buttonInsert.DialogResult = DialogResult.OK;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            insertButtonClicked = true;
            textChanged = false;
            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            insertButtonClicked = false;
            Close();
        }
        // End of private methods

        //Public methods
        //"Setters"
        /// <summary>
        /// Sets the title of the new job
        /// </summary>
        /// <param name="newTitle">The title of the new job</param>
        public void SetTitle(string newTitle)
        {
            title = newTitle;
        }
        /// <summary>
        /// Sets the name of the company
        /// </summary>
        /// <param name="newCompany">The name of the company</param>
        public void SetCompany(string newCompany)
        {
            company = newCompany;
        }
        
        /// <summary>
        /// Sets the ID of the city where the job is located.
        /// </summary>
        /// <param name="newCityID">The city's ID</param>
        public void SetCityID(int newCityID)
        {
            cityID = newCityID;
        }

        /// <summary>
        /// Sets the new status ID (added, sent, interested/interview, rejected)
        /// </summary>
        /// <param name="newStatusID">The ID of the status</param>
        public void SetStatusID(int newStatusID)
        {
            statusID = newStatusID;
        }

        /// <summary>
        /// Sets the application deadline of the new job.
        /// </summary>
        /// <param name="newDate">The deadline date of the new job</param>
        public void SetDate(string newDate)
        {
            date = newDate;
        }

        private void InsertSoknad_FormClosing(object sender, FormClosingEventArgs e)
        {
            if(insertButtonClicked)
            {
                if (!preInsertApplication())
                {
                    e.Cancel = true;
                    insertButtonClicked = false;
                }
            }
            else
            {
                if (textChanged)
                {
                    if (textBoxPositionTitle.Text.Length != 0 && textBoxCompany.Text.Length != 0 && cities.Text.Length != 0  && statuses.Text.Length != 0)
                    {
                        DialogResult d = MessageBox.Show("Du har noen ulagrede endringer. Vil du lagre disse i databasen?", Program.title, MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                        if (d == DialogResult.Yes)
                        {
                            buttonInsert.PerformClick();
                        }
                        else if (d == DialogResult.Cancel)
                            e.Cancel = true;
                    }
                }
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            textChanged = true;
        }

        private void cities_SelectedIndexChanged(object sender, EventArgs e)
        {
            textChanged = true;
        }

        /// <summary>
        /// Gets the title of the new job.
        /// </summary>
        /// <returns>The job title</returns>
        public string GetTitle()
        {
            return title;
        }

        /// <summary>
        /// Gets the company that offers the new job.
        /// </summary>
        /// <returns>The name of the company</returns>
        public string GetCompany()
        {
            return company;
        }

        /// <summary>
        /// Gets the ID of the city where the job is located.
        /// </summary>
        /// <returns>The city's ID</returns>
        public int GetCityID()
        {
            return cityID;
        }

        /// <summary>
        /// Gets the status ID of the new job.
        /// </summary>
        /// <returns>The status ID of the new job.</returns>
        public int GetStatusID()
        {
            return statusID;
        }

        /// <summary>
        /// Gets the application deadline of the new job.
        /// </summary>
        /// <returns>The deadline date of the new job</returns>
        public string GetDate()
        {
            return date;
        }
        // End of public methods
        
    }
}
