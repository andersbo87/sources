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
    public partial class ViewStatuses : Form
    {
        // Private variabler
        bool opening = false;
        List<string> l;
        int max, c = 0, itms;
        Form1 f = Program.f1;
        psql p;

        private void ViewStatuses_Load(object sender, EventArgs e)
        {
            p = f.p;
            opening = true;
            try
            {
                l = p.GetData("SELECT statusid FROM status ORDER BY statusid asc", 0);
                int i = 0;
                while (i < l.Count)
                {
                    itms = comboBoxStatusID.Items.Add(l.ElementAt(i));
                    i++;
                }
                max = Int32.Parse(comboBoxStatusID.Items[comboBoxStatusID.Items.Count - 1].ToString());
                //comboBoxStatusID.Text = "1";
                if (c == 0)
                {
                    getData(Int32.Parse(comboBoxStatusID.Items[0].ToString()));
                    c++;
                }
                if (Int32.Parse(comboBoxStatusID.Text) == Int32.Parse(comboBoxStatusID.Items[comboBoxStatusID.Items.Count - 1].ToString()))
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
            //getCities(1);
            comboBoxStatusID.Text = "1";
            buttonPrevious.Enabled = false;
            buttonFirst.Enabled = false;
            buttonNext.Enabled = true;
            buttonLast.Enabled = true;
        }

        private void buttonPrevious_Click(object sender, EventArgs e)
        {
            getPrev(Int32.Parse(comboBoxStatusID.Text) - 1);
        }

        private void buttonDelete_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show("Er du sikker på at du vil fjerne gjeldende rad fra databasen? Denne handlingen kan ikke angres!", Program.title, MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (res == DialogResult.Yes)
            {
                // Fjern gjeldende element fra databasen
                try
                {
                    if(p.DeleteItem("status", "statusid", Int32.Parse(comboBoxStatusID.Text)))
                    {
                        MessageBox.Show("StatusID " + Int32.Parse(comboBoxStatusID.Text) + " ble fjernet fra databasen.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                        int item = Int32.Parse(comboBoxStatusID.SelectedItem.ToString());
                        comboBoxStatusID.Items.Remove(comboBoxStatusID.SelectedItem);
                        comboBoxStatusID.Text = (item + 1).ToString();
                        if ((item + 1) == Int32.Parse(comboBoxStatusID.Items[0].ToString()))
                        {
                            buttonPrevious.Enabled = false;
                            buttonFirst.Enabled = false;
                        }
                        if (!getNext(Int32.Parse(comboBoxStatusID.Text)))
                            if (!getPrev(Int32.Parse(comboBoxStatusID.Text)))
                            {
                                MessageBox.Show("Det siste elementet har blitt fjernet. Vinduet vil nå lukkes.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                                Close();
                            }
                        /*int idx = Int32.Parse(comboBoxStatusID.Text) + 1;
                        buttonPrevious.Enabled = true;
                        if (idx <= max)
                        {
                            getData(idx);
                            //getCities(idx);
                            if (idx == max)
                            {
                                buttonNext.Enabled = false;
                                buttonLast.Enabled = false;
                            }
                        }
                        comboBoxStatusID.Text = idx.ToString();*/
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
            getNext(Int32.Parse(comboBoxStatusID.Text) + 1);
        }

        private void buttonLast_Click(object sender, EventArgs e)
        {
            int idx = max;
            //int idx = Int32.Parse(comboBoxTownID.Text);
            getData(idx);
            //getCities(idx);
            //comboBoxTownID.Text = idx.ToString();
            //comboBoxStatusID.SelectedIndex = idx - 1;
            comboBoxStatusID.Text = comboBoxStatusID.Items[comboBoxStatusID.Items.Count - 1].ToString();
            buttonNext.Enabled = false;
            buttonLast.Enabled = false;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (!opening)
            {
                //int idx = comboBoxTownID.SelectedIndex + 1;
                int idx = Int32.Parse(comboBoxStatusID.Text);
                getData(idx);
                //getCities(idx);
                if (idx == Int32.Parse(comboBoxStatusID.Items[0].ToString()))
                {
                    buttonPrevious.Enabled = false;
                    buttonFirst.Enabled = false;
                    buttonNext.Enabled = true;
                    buttonLast.Enabled = true;
                }
                else if (idx == Int32.Parse(comboBoxStatusID.Items[comboBoxStatusID.Items.Count - 1].ToString()))
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

        public void getData(int index)
        {
            List<string> cityData = p.GetStatuses(index);
            textBoxStatus.Text = cityData.ElementAt(1);
            comboBoxStatusID.Text = index.ToString();
        }

        public bool getNext(int index)
        {
            int idx = index;

            try
            {
                if (Int32.Parse(comboBoxStatusID.Text) != Int32.Parse(comboBoxStatusID.Items[0].ToString()))
                {
                    buttonPrevious.Enabled = true;
                    buttonFirst.Enabled = true;
                }
                if (idx <= max)
                {
                    getData(idx);
                    comboBoxStatusID.Text = idx.ToString();
                    if (idx == Int32.Parse(comboBoxStatusID.Items[comboBoxStatusID.Items.Count - 1].ToString()))
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

        private void linkLabelOppdater_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            p.UpdateDatabase("status", "statusid", textBoxStatus.Text, "statusid", Int32.Parse(comboBoxStatusID.Text));
            //p.UpdateDatabase("status", "tittel", textBoxTitle.Text, primaryKey, Int32.Parse(comboBoxApplicationID.Text));
        }

        private void buttonRefresh_Click(object sender, EventArgs e)
        {
            int idx = Int32.Parse(comboBoxStatusID.Text);
            getData(idx);
            comboBoxStatusID.Text = idx.ToString();
        }

        public bool getPrev(int index)
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
                    comboBoxStatusID.Text = idx.ToString();
                    if (idx == Int32.Parse(comboBoxStatusID.Items[0].ToString()))
                    {
                        buttonPrevious.Enabled = false;
                        buttonFirst.Enabled = false;
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

        public ViewStatuses()
        {
            InitializeComponent();
        }
    }
}
