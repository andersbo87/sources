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


namespace jobb
{
    partial class InsertSoknad
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.textBoxPositionTitle = new System.Windows.Forms.TextBox();
            this.textBoxCompany = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.cities = new System.Windows.Forms.ComboBox();
            this.statuses = new System.Windows.Forms.ComboBox();
            this.buttonInsert = new System.Windows.Forms.Button();
            this.buttonClose = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.textBoxDate = new System.Windows.Forms.TextBox();
            this.labelCityName = new System.Windows.Forms.Label();
            this.labelStatusName = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(61, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Stillingstittel";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 35);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Bedrift";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 61);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(40, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "StedID";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(12, 91);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(48, 13);
            this.label5.TabIndex = 4;
            this.label5.Text = "StatusID";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(12, 118);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "Søknadsfrist";
            // 
            // textBoxPositionTitle
            // 
            this.textBoxPositionTitle.Location = new System.Drawing.Point(79, 6);
            this.textBoxPositionTitle.Name = "textBoxPositionTitle";
            this.textBoxPositionTitle.Size = new System.Drawing.Size(121, 20);
            this.textBoxPositionTitle.TabIndex = 6;
            this.textBoxPositionTitle.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // textBoxCompany
            // 
            this.textBoxCompany.Location = new System.Drawing.Point(79, 32);
            this.textBoxCompany.Name = "textBoxCompany";
            this.textBoxCompany.Size = new System.Drawing.Size(121, 20);
            this.textBoxCompany.TabIndex = 7;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(13, 168);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(0, 13);
            this.label7.TabIndex = 12;
            // 
            // cities
            // 
            this.cities.FormattingEnabled = true;
            this.cities.Location = new System.Drawing.Point(79, 61);
            this.cities.Name = "cities";
            this.cities.Size = new System.Drawing.Size(121, 21);
            this.cities.TabIndex = 14;
            this.cities.SelectedIndexChanged += new System.EventHandler(this.cities_SelectedIndexChanged);
            // 
            // statuses
            // 
            this.statuses.FormattingEnabled = true;
            this.statuses.Location = new System.Drawing.Point(79, 91);
            this.statuses.Name = "statuses";
            this.statuses.Size = new System.Drawing.Size(121, 21);
            this.statuses.TabIndex = 16;
            this.statuses.SelectedIndexChanged += new System.EventHandler(this.statuses_SelectedIndexChanged);
            // 
            // buttonInsert
            // 
            this.buttonInsert.Location = new System.Drawing.Point(12, 202);
            this.buttonInsert.Name = "buttonInsert";
            this.buttonInsert.Size = new System.Drawing.Size(75, 23);
            this.buttonInsert.TabIndex = 17;
            this.buttonInsert.Text = "Sett inn";
            this.buttonInsert.UseVisualStyleBackColor = true;
            this.buttonInsert.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonClose
            // 
            this.buttonClose.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonClose.Location = new System.Drawing.Point(94, 202);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(75, 23);
            this.buttonClose.TabIndex = 18;
            this.buttonClose.Text = "Lukk";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.button2_Click);
            // 
            // label8
            // 
            this.label8.Location = new System.Drawing.Point(12, 144);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(308, 55);
            this.label8.TabIndex = 19;
            this.label8.Text = "Dersom det i annonsen ikke står oppgitt en søknadsfrist, bør du likevel oppgi en " +
    "eller annen dato. Dette fordi det oppstår en feil i programmet dersom datoen ikk" +
    "e er gitt på korrekt måte.";
            // 
            // textBoxDate
            // 
            this.textBoxDate.Location = new System.Drawing.Point(79, 118);
            this.textBoxDate.Name = "textBoxDate";
            this.textBoxDate.Size = new System.Drawing.Size(121, 20);
            this.textBoxDate.TabIndex = 20;
            // 
            // labelCityName
            // 
            this.labelCityName.AutoSize = true;
            this.labelCityName.Location = new System.Drawing.Point(207, 61);
            this.labelCityName.Name = "labelCityName";
            this.labelCityName.Size = new System.Drawing.Size(46, 13);
            this.labelCityName.TabIndex = 21;
            this.labelCityName.Text = "labelCity";
            // 
            // labelStatusName
            // 
            this.labelStatusName.AutoSize = true;
            this.labelStatusName.Location = new System.Drawing.Point(206, 91);
            this.labelStatusName.Name = "labelStatusName";
            this.labelStatusName.Size = new System.Drawing.Size(59, 13);
            this.labelStatusName.TabIndex = 22;
            this.labelStatusName.Text = "labelStatus";
            // 
            // InsertSoknad
            // 
            this.AcceptButton = this.buttonInsert;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.buttonClose;
            this.ClientSize = new System.Drawing.Size(332, 234);
            this.ControlBox = false;
            this.Controls.Add(this.labelStatusName);
            this.Controls.Add(this.labelCityName);
            this.Controls.Add(this.textBoxDate);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.buttonInsert);
            this.Controls.Add(this.statuses);
            this.Controls.Add(this.cities);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.textBoxCompany);
            this.Controls.Add(this.textBoxPositionTitle);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Name = "InsertSoknad";
            this.Text = "Ny søknad";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.InsertSoknad_FormClosing);
            this.Load += new System.EventHandler(this.InsertSoknad_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox textBoxPositionTitle;
        private System.Windows.Forms.TextBox textBoxCompany;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ComboBox cities;
        private System.Windows.Forms.ComboBox statuses;
        private System.Windows.Forms.Button buttonInsert;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBoxDate;
        private System.Windows.Forms.Label labelCityName;
        private System.Windows.Forms.Label labelStatusName;
    }
}