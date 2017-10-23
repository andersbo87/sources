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


using Npgsql;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace jobb
{
    public partial class ViewApplications : Form
    {
        Form1 f = Program.f1;
        psql p;
        private const string table = "soknad", primaryKey = "soknadid";
        int c = 0;
        bool opening = false;
        int max;
        public ViewApplications()
        {
            InitializeComponent();
        }
        private string title, company, date;
        private int cityID, countryID, statusID;
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
        /// Sets the ID of the country where the job is located.
        /// </summary>
        /// <param name="newCountryID">The country's ID</param>
        public void SetCountryID(int newCountryID)
        {
            countryID = newCountryID;
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
        /// Gets the ID of the country where the job is located.
        /// </summary>
        /// <returns>The country's ID</returns>
        public int GetCountryID()
        {
            return countryID;
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

        private void ViewApplications_Load(object sender, EventArgs e)
        {
            opening = true;
            p = f.p;
            List<string> l = p.GetData("SELECT soknadid FROM view_soknad ORDER BY soknadid asc", 0);
            int i = 0;
            while (i < l.Count)
            {
                comboBoxApplicationID.Items.Add(l.ElementAt(i));
                i++;
            }
            max = Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count - 1].ToString());
            if(c == 0) { 
                getData(Int32.Parse(comboBoxApplicationID.Items[0].ToString()));
                c++;
            }
            getCities(Int32.Parse(comboBoxApplicationID.Items[0].ToString()));
            getStatuses(Int32.Parse(comboBoxApplicationID.Items[0].ToString()));
            if (Int32.Parse(comboBoxApplicationID.Text) == Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count - 1].ToString()))
            {
                buttonNext.Enabled = false;
                buttonLast.Enabled = false;
            }
            opening = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                getData(Int32.Parse(comboBoxApplicationID.Items[0].ToString()));
                getCities(Int32.Parse(comboBoxApplicationID.Items[0].ToString()));
                comboBoxApplicationID.Text = comboBoxApplicationID.Items[0].ToString();
                getStatuses(Int32.Parse(comboBoxApplicationID.Items[0].ToString()));
            }
            catch(SocketException se)
            {
                buttonNext.Enabled = true;
                buttonLast.Enabled = true;
                MessageBox.Show("Kan ikke hente de føste dataene pga et problem i forbindelsen med ekstern server: " + se.ToString(), Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            catch(Exception ex)
            {
                MessageBox.Show("Kan ikke hente de føste dataene: " + ex.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            finally
            {
                buttonPrevious.Enabled = false;
                buttonFirst.Enabled = false;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if(!getPrev(Int32.Parse(comboBoxApplicationID.Text) - 1))
            {
                buttonFirst.Enabled = false;
                buttonPrevious.Enabled = false;
                MessageBox.Show("Kan ikke hente data fordi en feil oppstod.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show("Er du sikker på at du vil fjerne gjeldende rad fra databasen? Denne handlingen kan ikke angres!", Program.title, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if(res == DialogResult.Yes)
            {
                // Fjern gjeldende element fra databasen
                try
                {
                    if (p.DeleteItem("soknad", "soknadid", Int32.Parse(comboBoxApplicationID.Text)))
                    {
                        MessageBox.Show("Søknaden med søknadsid " + Int32.Parse(comboBoxApplicationID.Text) + " ble fjernet fra databasen.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                        int item = Int32.Parse(comboBoxApplicationID.SelectedItem.ToString());
                        comboBoxApplicationID.Items.Remove(comboBoxApplicationID.SelectedItem);
                        comboBoxApplicationID.Text = (item + 1).ToString();
                        if ((item+1) == Int32.Parse(comboBoxApplicationID.Items[0].ToString()))
                        {
                            buttonPrevious.Enabled = false;
                            buttonFirst.Enabled = false;
                        }
                        if (!getNext(Int32.Parse(comboBoxApplicationID.Text)))
                        {
                            if (!getPrev(Int32.Parse(comboBoxApplicationID.Text)))
                            {
                                MessageBox.Show("Det siste elementet har blitt fjernet. Vinduet vil nå lukkes.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                                Close();
                            }
                        }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show("En feil oppstod under eller etter sletting av data: " + ex.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try
            {
                int idx = Int32.Parse(comboBoxApplicationID.Text);
                getData(idx);
                getCities(idx);
                getStatuses(idx);
                comboBoxApplicationID.Text = idx.ToString();
            }
            catch(Exception ex)
            {
                MessageBox.Show("Kan ikke oppdatere vinduet: " + ex.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        bool getNext(int index)
        {
            int idx = index;

            try
            {
                if (Int32.Parse(comboBoxApplicationID.Text) != Int32.Parse(comboBoxApplicationID.Items[0].ToString()))
                {
                    buttonPrevious.Enabled = true;
                    buttonFirst.Enabled = true;
                }
                if (idx <= max)
                {
                    getData(idx);
                    getCities(idx);
                    getStatuses(idx);
                    comboBoxApplicationID.Text = idx.ToString();
                    if (idx == Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count - 1].ToString()))
                    {
                        buttonLast.Enabled = false;
                        buttonNext.Enabled = false;
                    }
                    return true;
                }
                else {
                    return false;
                }
            }
            catch (SocketException)
            {
                return false;
            }
            catch(NpgsqlException ne)
            {
                MessageBox.Show("En PostgreSQL-feil har oppstått: " + ne.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                return false;
            }
        }
        bool getPrev(int index)
        {
            try
            {
                int idx = index;
                buttonNext.Enabled = true;
                buttonLast.Enabled = true;
                if (idx >= 1)
                {
                    getData(idx);
                    comboBoxApplicationID.Text = idx.ToString();
                    if (idx == 1 || idx == Int32.Parse(comboBoxApplicationID.Items[0].ToString()))
                    {
                        buttonPrevious.Enabled = false;
                        buttonFirst.Enabled = false;
                    }
                    else if(idx == Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count-1].ToString()))
                    {
                        buttonLast.Enabled = false;
                        buttonNext.Enabled = false;
                    }
                    return true;
                }
                else
                    return false;
            }
            catch (SocketException)
            {
                return false;
            }
            catch (Exception)
            {
                return getPrev(index - 1);
            }
        }
        private void button5_Click(object sender, EventArgs e)
        {
            if(!getNext(Int32.Parse(comboBoxApplicationID.Text) + 1))
            {
                buttonNext.Enabled = false;
                buttonLast.Enabled = false;
                MessageBox.Show("Kan ikke hente resultater fordi en feil oppstod.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }

        private void comboBoxApplicationID_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!opening)
            {
                int idx = Int32.Parse(comboBoxApplicationID.Text);
                getData(idx);
                getCities(idx);
                getStatuses(idx);
                if(idx == Int32.Parse(comboBoxApplicationID.Items[0].ToString()))
                {
                    buttonPrevious.Enabled = false;
                    buttonFirst.Enabled = false;
                    buttonNext.Enabled = true;
                    buttonLast.Enabled = true;
                }
                else if(idx == Int32.Parse(comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count-1].ToString()))
                {
                    buttonNext.Enabled = false;
                    buttonLast.Enabled = false;
                    buttonFirst.Enabled = true;
                    buttonPrevious.Enabled = true;
                }
                else
                {
                    // Mulig de fire neste linjene er unødige:
                    buttonNext.Enabled = true;
                    buttonLast.Enabled = true;
                    buttonPrevious.Enabled = true;
                    buttonFirst.Enabled = true;
                }
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            try
            {
                int idx = max;
                getData(idx);
                getCities(idx);
                getStatuses(idx);
                comboBoxApplicationID.Text = comboBoxApplicationID.Items[comboBoxApplicationID.Items.Count - 1].ToString();
            }
            catch(SocketException se)
            {
                MessageBox.Show("Kan ikke hente data pga et problem med forbindelsen med ekstern server: " + se.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                buttonFirst.Enabled = false;
                buttonPrevious.Enabled = false;
            }
            catch(Exception ex)
            {
                MessageBox.Show("Kan ikke hente de føste dataene: " + ex.ToString(), Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            finally
            {
                buttonNext.Enabled = false;
                buttonLast.Enabled = false;
            }
        }

        private void linkLabelTitleUpdate_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            p.UpdateDatabase(table, "tittel", textBoxTitle.Text, primaryKey, Int32.Parse(comboBoxApplicationID.Text));
        }

        private void linkLabelCompanyUpdate_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            p.UpdateDatabase(table, "bedrift", textBoxCompany.Text, primaryKey, Int32.Parse(comboBoxApplicationID.Text));
        }

        private void linkLabelCityIDUpdate_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            p.UpdateDatabase(table, "stedid", Int32.Parse(comboBoxCityID.Text), primaryKey, Int32.Parse(comboBoxApplicationID.Text));
        }

        private void linkLabelCountryIDUpdate_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            p.UpdateDatabase(table, "landid", Int32.Parse(labelCountryID.Text), primaryKey, Int32.Parse(comboBoxApplicationID.Text));
        }

        private void linkLabelStatusIDUpdate_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            p.UpdateDatabase(table, "statusid", Int32.Parse(comboBoxStatusID.Text), primaryKey, Int32.Parse(comboBoxApplicationID.Text));
        }

        private void linkLabelDateUpdate_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            p.UpdateDatabase(table, "soknadsfrist", textBoxDate.Text, primaryKey, Int32.Parse(comboBoxApplicationID.Text));
        }

        private void getCities(int index)
        {
            List<string> cityList = p.GetData("SELECT stedid FROM sted ORDER BY stedid asc",0);
            int i = 0;
            if (comboBoxCityID.Items.Count == 0)
            {
                while (i < cityList.Count)
                {
                    comboBoxCityID.Items.Add(cityList.ElementAt(i));
                    i++;
                }
            }
            comboBoxCityID.Text = p.GetCityID(index).ToString();
        }

        private void getStatuses(int index)
        {
            List<string> statusList = p.GetData("SELECT statusid FROM status order by statusid asc", 0);
            int i = 0;
            if (comboBoxStatusID.Items.Count == 0)
            {
                while (i < statusList.Count)
                {
                    comboBoxStatusID.Items.Add(statusList.ElementAt(i));
                    i++;
                }
            }
            comboBoxStatusID.Text = p.GetStatusID(index).ToString();
        }

        /// <summary>
        /// Fills the labels, comboboxes and text boxes with information about current application based on the application ID.
        /// </summary>
        /// <param name="index">The identification number of the job application in question.</param>
        private void getData(int index)
        {
            try
            { 
                List<string> applicationData = p.GetApplications(index);
                textBoxTitle.Text = applicationData.ElementAt(0);
                textBoxCompany.Text = applicationData.ElementAt(1);
                labelCity.Text = applicationData.ElementAt(3);
                labelCountryID.Text = applicationData.ElementAt(4);
                labelCountry.Text = applicationData.ElementAt(5);
                labelStatus.Text = applicationData.ElementAt(7);
                textBoxDate.Text = applicationData.ElementAt(8);
                comboBoxApplicationID.Text = index.ToString();
            }
            catch(InvalidOperationException)
            {
                return;
            }
            catch(System.FormatException)
            {

            }
        }
    }
}
