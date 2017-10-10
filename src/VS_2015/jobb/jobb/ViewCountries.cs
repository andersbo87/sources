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
    public partial class ViewCountries : Form
    {
        //Private variabler
        Form1 f = Program.f1;
        psql p;
        int max, itms, c = 0;
        List<string> l;
        bool opening = false;
        // Offentlige funksjoner
        public ViewCountries()
        {
            InitializeComponent();
        }
        // Private funksjoner:
        bool getPrev(int index)
        {
            try
            {
                int idx = index;
                if (Int32.Parse(comboBoxCountryID.Text) != Int32.Parse(comboBoxCountryID.Items[0].ToString()))
                {
                    buttonPrevious.Enabled = true;
                    buttonFirst.Enabled = true;
                }
                if (idx >= 1)
                {
                    getData(idx);
                    //getCities(idx);
                    comboBoxCountryID.Text = idx.ToString();
                    if (idx == Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString()))
                    {
                        buttonNext.Enabled = false;
                        buttonLast.Enabled = false;
                    }
                    return true;
                }
                else
                    return false;
            }
            catch (Exception)
            {
                return getPrev(index - 1);
            }
        }
        bool getNext(int index)
        {
            int idx = index;
            try
            {
                if (Int32.Parse(comboBoxCountryID.Text) != Int32.Parse(comboBoxCountryID.Items[0].ToString()))
                {
                    buttonPrevious.Enabled = true;
                    buttonFirst.Enabled = true;
                }
                if (idx <= max)
                {
                    getData(idx);
                    comboBoxCountryID.Text = idx.ToString();
                    if (idx == Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString()))
                    {
                        buttonNext.Enabled = false;
                        buttonLast.Enabled = false;
                    }
                    return true;
                }
                else
                    return false;
            }
            catch (ArgumentOutOfRangeException)
            {
                return getNext(idx + 1);
            }
            catch (Exception)
            {
                return getNext(idx + 1);
            }
        }
        private void getData(int index)
        {
            /*try
            {*/
                List<string> cityData = p.GetCountries(index);
                textBoxCountry.Text = cityData.ElementAt(1);
                comboBoxCountryID.Text = index.ToString();
            /*}
            catch(Exception)
            {
                getData(index + 1);
            }*/
        }
        private void ViewCountries_Load(object sender, EventArgs e)
        {
            opening = true;
            try
            {
                p = f.p;
                l = p.GetData("SELECT landid FROM land ORDER BY landid asc", 0);
                int i = 0;
                while (i < l.Count)
                {
                    itms = comboBoxCountryID.Items.Add(l.ElementAt(i));
                    i++;
                }
                max = Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString());
                //comboBoxCountryID.Text = "1";
                if (c == 0)
                {
                    getData(Int32.Parse(comboBoxCountryID.Items[0].ToString()));
                    c++;
                }
                if(Int32.Parse(comboBoxCountryID.Text) == Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString()))
                {
                    buttonNext.Enabled = false;
                    buttonLast.Enabled = false;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Noe har gått galt: " + ex.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            finally
            {
                opening = false;
            }
        }

        private void buttonFirst_Click(object sender, EventArgs e)
        {
            getData(1);
            comboBoxCountryID.Text = "1";
            buttonPrevious.Enabled = false;
            buttonFirst.Enabled = false;
            buttonNext.Enabled = true;
            buttonLast.Enabled = true;
        }

        private void buttonPrevious_Click(object sender, EventArgs e)
        {
            getPrev(Int32.Parse(comboBoxCountryID.Text) - 1);
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show("Er du sikker på at du vil fjerne gjeldende rad fra databasen? Denne handlingen kan ikke angres!", Program.title, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (res == DialogResult.Yes)
            {
                // Fjern gjeldende element fra databasen
                try
                {
                    if (p.DeleteItem("land", "landid", Int32.Parse(comboBoxCountryID.Text)))
                    {
                        MessageBox.Show("Landet med landid " + Int32.Parse(comboBoxCountryID.Text) + " ble fjernet fra databasen.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                        int item = Int32.Parse(comboBoxCountryID.SelectedItem.ToString());
                        comboBoxCountryID.Items.Remove(comboBoxCountryID.SelectedItem);
                        comboBoxCountryID.Text = (item + 1).ToString();
                        if ((item + 1) == Int32.Parse(comboBoxCountryID.Items[0].ToString()))
                        {
                            buttonPrevious.Enabled = false;
                            buttonFirst.Enabled = false;
                        }
                        if (!getNext(Int32.Parse(comboBoxCountryID.Text)))
                            if (!getPrev(Int32.Parse(comboBoxCountryID.Text)))
                            {
                                MessageBox.Show("Det siste elementet har blitt fjernet. Vinduet vil nå lukkes.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                                Close();
                            }
                    }
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
        }

        private void buttonNext_Click(object sender, EventArgs e)
        {
            getNext(Int32.Parse(comboBoxCountryID.Text) + 1);
        }

        private void comboBoxCountryID_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!opening)
            {
                //int idx = comboBoxTownID.SelectedIndex + 1;
                int idx = Int32.Parse(comboBoxCountryID.Text);
                getData(idx);
                //getCities(idx);
                if (idx == Int32.Parse(comboBoxCountryID.Items[0].ToString()))
                {
                    buttonPrevious.Enabled = false;
                    buttonFirst.Enabled = false;
                    buttonNext.Enabled = true;
                    buttonLast.Enabled = true;
                }
                else if (idx == Int32.Parse(comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString()))
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

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            int idx = Int32.Parse(comboBoxCountryID.Text);
            getData(idx);
            comboBoxCountryID.Text = idx.ToString();
        }

        private void buttonLast_Click(object sender, EventArgs e)
        {
            int idx = max;
            //int idx = Int32.Parse(comboBoxTownID.Text);
            getData(idx);
            //getCities(idx);
            //comboBoxTownID.Text = idx.ToString();
            //comboBoxCountryID.SelectedIndex = idx - 1;
            comboBoxCountryID.Text = comboBoxCountryID.Items[comboBoxCountryID.Items.Count - 1].ToString();
            buttonNext.Enabled = false;
            buttonLast.Enabled = false;
            buttonPrevious.Enabled = true;
            buttonFirst.Enabled = true;
        }

        private void updateLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            p.UpdateDatabase("land", "landid", textBoxCountry.Text, "landid", Int32.Parse(comboBoxCountryID.Text));
            //p.UpdateDatabase(table, "tittel", textBoxTitle.Text, primaryKey, Int32.Parse(comboBoxApplicationID.Text));
        }
    }
}
