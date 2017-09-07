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
    public partial class ViewTowns : Form
    {
        Form1 f = Program.f1;
        psql p;
        List<string> l;
        bool opening = false;
        int max, c= 0, itms;
        public ViewTowns()
        {
            InitializeComponent();
        }

        private void ViewTowns_Load(object sender, EventArgs e)
        {
            p = f.p;
            opening = true;
            try
            {
                l = p.GetData("SELECT stedid FROM sted ORDER BY stedid asc", 0);
                int i = 0;
                while (i < l.Count)
                {
                    itms = comboBoxTownID.Items.Add(l.ElementAt(i));
                    i++;
                }
                max = Int32.Parse(comboBoxTownID.Items[comboBoxTownID.Items.Count - 1].ToString());
                //comboBoxTownID.Text = "1";
                if (c == 0)
                {
                    getData(Int32.Parse(comboBoxTownID.Items[0].ToString()));
                    c++;
                }
                if (Int32.Parse(comboBoxTownID.Text) == Int32.Parse(comboBoxTownID.Items[comboBoxTownID.Items.Count - 1].ToString()))
                {
                    buttonNext.Enabled = false;
                    buttonLast.Enabled = false;
                }
            }
            catch(Exception ex)
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
            //getCities(1);
            comboBoxTownID.Text = "1";
            buttonPrevious.Enabled = false;
            buttonFirst.Enabled = false;
            buttonNext.Enabled = true;
            buttonLast.Enabled = true;
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
                    //getCities(idx);
                    comboBoxTownID.Text = idx.ToString();
                    if (idx == Int32.Parse(comboBoxTownID.Items[0].ToString()))
                    {
                        buttonPrevious.Enabled = false;
                        buttonFirst.Enabled = false;
                    }
                    return true;
                }
                else
                    return false;
            }
            catch(Exception)
            {
                return getPrev(index - 1);
            }
        }
        private void buttonPrevious_Click(object sender, EventArgs e)
        {
            getPrev(Int32.Parse(comboBoxTownID.Text) - 1);
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show("Er du sikker på at du vil fjerne gjeldende rad fra databasen? Denne handlingen kan ikke angres!", Program.title, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (res == DialogResult.Yes)
            {
                // Fjern gjeldende element fra databasen
                try
                {
                    if(p.DeleteItem("sted", "stedid", Int32.Parse(comboBoxTownID.Text)))
                    {
                        MessageBox.Show("Stedet med stedid " + Int32.Parse(comboBoxTownID.Text) + " ble fjernet fra databasen.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                        int item = Int32.Parse(comboBoxTownID.SelectedItem.ToString());
                        comboBoxTownID.Items.Remove(comboBoxTownID.SelectedItem);
                        comboBoxTownID.Text = (item + 1).ToString();
                        if ((item + 1) == Int32.Parse(comboBoxTownID.Items[0].ToString()))
                        {
                            buttonPrevious.Enabled = false;
                            buttonFirst.Enabled = false;
                        }
                        if (!getNext(Int32.Parse(comboBoxTownID.Text)))
                            if (!getPrev(Int32.Parse(comboBoxTownID.Text)))
                            {
                                MessageBox.Show("Det siste elementet har blitt fjernet. Vinduet vil nå lukkes.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                                Close();
                            }
                        /*int idx = Int32.Parse(comboBoxTownID.Text) + 1;
                        buttonPrevious.Enabled = true;
                        if (idx <= max)
                        {
                            getData(idx);
                            //getCities(idx);
                            if (idx == max)
                            {
                                buttonNext.Enabled = false;
                            }
                        }
                        comboBoxTownID.Text = idx.ToString();*/
                    }
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message, Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
        }

        private void buttonUpdate_Click(object sender, EventArgs e)
        {
            int idx = Int32.Parse(comboBoxTownID.Text);
            getData(idx);
            //getCities(idx);
            comboBoxTownID.Text = idx.ToString();
        }
        bool getNext(int index)
        {
            int idx = index;
            
            try
            {
                if (Int32.Parse(comboBoxTownID.Text) != Int32.Parse(comboBoxTownID.Items[0].ToString()))
                {
                    buttonPrevious.Enabled = true;
                    buttonFirst.Enabled = true;
                }
                if (idx <= max)
                {
                    getData(idx);
                    comboBoxTownID.Text = idx.ToString();
                    //if (comboBoxTownID.Text.Equals(max.ToString()))
                    if(idx == Int32.Parse(comboBoxTownID.Items[comboBoxTownID.Items.Count-1].ToString()))
                    {
                        buttonNext.Enabled = false;
                        buttonLast.Enabled = false;
                    }
                    return true;
                }
                else
                    return false;
            }
            catch(ArgumentOutOfRangeException)
            {
                return getNext(idx + 1);
            }
            catch (Exception)
            {
                return getNext(idx+1);
            }
        }
        private void buttonNext_Click(object sender, EventArgs e)
        {
            getNext(Int32.Parse(comboBoxTownID.Text)+1);
            
        }

        private void buttonLast_Click(object sender, EventArgs e)
        {
            int idx = max;
            getData(idx);
            comboBoxTownID.Text = comboBoxTownID.Items[comboBoxTownID.Items.Count - 1].ToString();
            buttonNext.Enabled = false;
            buttonLast.Enabled = false;
        }
        private void getCities(int index)
        {
            List<string> cityList = p.GetData("SELECT stedid FROM sted ORDER BY stedid asc", 0);
            int i = 0;
            if (comboBoxTownID.Items.Count == 0)
            {
                while (i < cityList.Count)
                {
                    comboBoxTownID.Items.Add(cityList.ElementAt(i));
                    i++;
                }
            }
            comboBoxTownID.SelectedIndex = p.GetCityID(index) - 1;
        }

        private void comboBoxTownID_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!opening)
            {
                //int idx = comboBoxTownID.SelectedIndex + 1;
                int idx = Int32.Parse(comboBoxTownID.Text);
                getData(idx);
                //getCities(idx);
                /*if (idx == max)
                {
                    buttonLast.Enabled = false;
                    buttonNext.Enabled = false;
                    buttonPrevious.Enabled = true;
                    buttonFirst.Enabled = true;
                }
                else if (idx == 1)
                {
                    buttonFirst.Enabled = false;
                    buttonPrevious.Enabled = false;
                    buttonNext.Enabled = true;
                    buttonLast.Enabled = true;
                }*/
                if (idx == Int32.Parse(comboBoxTownID.Items[0].ToString()))
                {
                    buttonPrevious.Enabled = false;
                    buttonFirst.Enabled = false;
                    buttonNext.Enabled = true;
                    buttonLast.Enabled = true;
                }
                else if (idx == Int32.Parse(comboBoxTownID.Items[comboBoxTownID.Items.Count - 1].ToString()))
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
            int idx = Int32.Parse(comboBoxTownID.Text);
            getData(idx);
            comboBoxTownID.Text = idx.ToString();
        }

        private void linkLabelUpdate_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            p.UpdateDatabase("sted", "stedsnavn", textBoxTownName.Text, "stedid", Int32.Parse(comboBoxTownID.Text));
        }

        private void getData(int index)
        {
            List<string> cityData = p.GetCities(index);
            textBoxTownName.Text = cityData.ElementAt(1);
            comboBoxTownID.Text = index.ToString();
        }
    }
}
