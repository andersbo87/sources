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
using Npgsql;

namespace jobb
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        PsqlLogin pl;
        InsertSoknad ins;
        ViewApplications va;
        SQLCommands sc;
        NewCountry nc;
        NewStatus ns;
        NewTown nt;
        ViewCountries vc;
        ViewTowns vt;
        ViewStatuses vs;
        public psql p;
        private void initialize() // Kjører denne som en egen (rekursiv) metode ettersom at jeg ikke ser noen grunn til å risikere å lage flere instanser av de ulike objektene.
        {
            DialogResult dr = pl.ShowDialog();
            if (dr == DialogResult.OK)
            {
                if (!p.Init())
                    initialize();
            }
            else
            {
                Application.Exit();
            }
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            p = new psql();
            pl = new PsqlLogin();
            ins = new InsertSoknad();
            nc = new NewCountry();
            nt = new NewTown();
            ns = new NewStatus();
            initialize();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult dr = ins.ShowDialog();
            if(dr == DialogResult.OK)
            {
                if(!p.InsertApplication(ins.GetTitle(), ins.GetCompany(), ins.GetCityID(), ins.GetStatusID(), ins.GetDate()))
                {
                    MessageBox.Show("Kunne ikke registrere den nye søknaden: " + p.getError(), Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
                else
                {
                    MessageBox.Show("Den nye søknaden ble lagt inn med følgende data:\nTittel: "+ ins.GetTitle() + "\nBedrift: " + ins.GetCompany() + "\nStedid: " + ins.GetCityID() + "\nStatusID: " + ins.GetStatusID() + "\nSøknadsfrist: " + ins.GetDate(), Program.title, MessageBoxButtons.OK,MessageBoxIcon.Information);
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            va = new ViewApplications();
            va.Show();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            sc = new SQLCommands();
            sc.Show();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            vc = new ViewCountries();
            vc.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            vt = new ViewTowns();
            vt.Show();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            //nc = new NewCountry();
            DialogResult dr = nc.ShowDialog();
            if(dr == DialogResult.OK)
            {
                if (!p.InsertCountry(nc.getCountryName()))
                {
                    MessageBox.Show("Kunne ikke legge inn " + nc.getCountryName() + " i databasen. Feilmedling: " + p.getError(), Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
                else
                {
                    MessageBox.Show(nc.getCountryName() + " ble lagt inn i databasen.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            DialogResult dr = nt.ShowDialog();
            if(dr == DialogResult.OK)
            {
                if(!p.InsertTown(nt.getTown(), nt.getCountryID()))
                {
                    MessageBox.Show("Kunne ikke legge inn " + nt.getTown() + " i databasen. Feilmedling: " + p.getError(), Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
                else
                {
                    MessageBox.Show(nt.getTown() + " ble lagt inn i databasen.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            DialogResult dr = ns.ShowDialog();
            if (dr == DialogResult.OK)
            {
                if (p.InsertStatus(ns.getStatus()))
                {
                    MessageBox.Show(ns.getStatus() + " ble lagt inn i databasen.", Program.title, MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                else
                {
                    MessageBox.Show("Kunne ikke legge inn " + ns.getStatus() + " i databasen. Feilmedling: " + p.getError(), Program.title, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                }
            }
        }

        private void button10_Click(object sender, EventArgs e)
        {
            vs = new ViewStatuses();
            vs.Show();
        }
    }
}
