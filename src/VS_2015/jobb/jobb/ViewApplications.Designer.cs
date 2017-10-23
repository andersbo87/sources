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
    partial class ViewApplications
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
            this.buttonFirst = new System.Windows.Forms.Button();
            this.buttonPrevious = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonUpdate = new System.Windows.Forms.Button();
            this.buttonNext = new System.Windows.Forms.Button();
            this.buttonLast = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.comboBoxApplicationID = new System.Windows.Forms.ComboBox();
            this.comboBoxCityID = new System.Windows.Forms.ComboBox();
            this.comboBoxStatusID = new System.Windows.Forms.ComboBox();
            this.textBoxTitle = new System.Windows.Forms.TextBox();
            this.textBoxCompany = new System.Windows.Forms.TextBox();
            this.labelCity = new System.Windows.Forms.Label();
            this.labelCountry = new System.Windows.Forms.Label();
            this.labelStatus = new System.Windows.Forms.Label();
            this.linkLabelTitleUpdate = new System.Windows.Forms.LinkLabel();
            this.linkLabelCompanyUpdate = new System.Windows.Forms.LinkLabel();
            this.linkLabelCityIDUpdate = new System.Windows.Forms.LinkLabel();
            this.linkLabelStatusIDUpdate = new System.Windows.Forms.LinkLabel();
            this.linkLabelDateUpdate = new System.Windows.Forms.LinkLabel();
            this.textBoxDate = new System.Windows.Forms.TextBox();
            this.labelCountryID = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // buttonFirst
            // 
            this.buttonFirst.Enabled = false;
            this.buttonFirst.Location = new System.Drawing.Point(12, 288);
            this.buttonFirst.Name = "buttonFirst";
            this.buttonFirst.Size = new System.Drawing.Size(75, 23);
            this.buttonFirst.TabIndex = 0;
            this.buttonFirst.Text = "Første";
            this.buttonFirst.UseVisualStyleBackColor = true;
            this.buttonFirst.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonPrevious
            // 
            this.buttonPrevious.Enabled = false;
            this.buttonPrevious.Location = new System.Drawing.Point(93, 288);
            this.buttonPrevious.Name = "buttonPrevious";
            this.buttonPrevious.Size = new System.Drawing.Size(75, 23);
            this.buttonPrevious.TabIndex = 1;
            this.buttonPrevious.Text = "Forrige";
            this.buttonPrevious.UseVisualStyleBackColor = true;
            this.buttonPrevious.Click += new System.EventHandler(this.button2_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(176, 288);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(75, 23);
            this.buttonDelete.TabIndex = 2;
            this.buttonDelete.Text = "Slett";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.button3_Click);
            // 
            // buttonUpdate
            // 
            this.buttonUpdate.Location = new System.Drawing.Point(257, 288);
            this.buttonUpdate.Name = "buttonUpdate";
            this.buttonUpdate.Size = new System.Drawing.Size(75, 23);
            this.buttonUpdate.TabIndex = 3;
            this.buttonUpdate.Text = "Oppdater";
            this.buttonUpdate.UseVisualStyleBackColor = true;
            this.buttonUpdate.Click += new System.EventHandler(this.button4_Click);
            // 
            // buttonNext
            // 
            this.buttonNext.Location = new System.Drawing.Point(338, 288);
            this.buttonNext.Name = "buttonNext";
            this.buttonNext.Size = new System.Drawing.Size(75, 23);
            this.buttonNext.TabIndex = 4;
            this.buttonNext.Text = "Neste";
            this.buttonNext.UseVisualStyleBackColor = true;
            this.buttonNext.Click += new System.EventHandler(this.button5_Click);
            // 
            // buttonLast
            // 
            this.buttonLast.Location = new System.Drawing.Point(419, 288);
            this.buttonLast.Name = "buttonLast";
            this.buttonLast.Size = new System.Drawing.Size(75, 23);
            this.buttonLast.TabIndex = 5;
            this.buttonLast.Text = "Siste";
            this.buttonLast.UseVisualStyleBackColor = true;
            this.buttonLast.Click += new System.EventHandler(this.button6_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "SøknadID";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 39);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(30, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "Tittel";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 66);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(37, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Bedrift";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(13, 93);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(40, 13);
            this.label4.TabIndex = 9;
            this.label4.Text = "StedID";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(13, 119);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(19, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "By";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(13, 145);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(42, 13);
            this.label6.TabIndex = 11;
            this.label6.Text = "LandID";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(13, 171);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(31, 13);
            this.label7.TabIndex = 12;
            this.label7.Text = "Land";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(13, 199);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(48, 13);
            this.label8.TabIndex = 13;
            this.label8.Text = "StatusID";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(13, 226);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(37, 13);
            this.label9.TabIndex = 14;
            this.label9.Text = "Status";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(13, 253);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(65, 13);
            this.label10.TabIndex = 15;
            this.label10.Text = "Søknadsfrist";
            // 
            // comboBoxApplicationID
            // 
            this.comboBoxApplicationID.FormattingEnabled = true;
            this.comboBoxApplicationID.Location = new System.Drawing.Point(93, 6);
            this.comboBoxApplicationID.Name = "comboBoxApplicationID";
            this.comboBoxApplicationID.Size = new System.Drawing.Size(317, 21);
            this.comboBoxApplicationID.TabIndex = 16;
            this.comboBoxApplicationID.SelectedIndexChanged += new System.EventHandler(this.comboBoxApplicationID_SelectedIndexChanged);
            // 
            // comboBoxCityID
            // 
            this.comboBoxCityID.FormattingEnabled = true;
            this.comboBoxCityID.Location = new System.Drawing.Point(93, 90);
            this.comboBoxCityID.Name = "comboBoxCityID";
            this.comboBoxCityID.Size = new System.Drawing.Size(317, 21);
            this.comboBoxCityID.TabIndex = 17;
            // 
            // comboBoxStatusID
            // 
            this.comboBoxStatusID.FormattingEnabled = true;
            this.comboBoxStatusID.Location = new System.Drawing.Point(93, 196);
            this.comboBoxStatusID.Name = "comboBoxStatusID";
            this.comboBoxStatusID.Size = new System.Drawing.Size(317, 21);
            this.comboBoxStatusID.TabIndex = 19;
            // 
            // textBoxTitle
            // 
            this.textBoxTitle.Location = new System.Drawing.Point(93, 39);
            this.textBoxTitle.Name = "textBoxTitle";
            this.textBoxTitle.Size = new System.Drawing.Size(317, 20);
            this.textBoxTitle.TabIndex = 21;
            // 
            // textBoxCompany
            // 
            this.textBoxCompany.Location = new System.Drawing.Point(93, 66);
            this.textBoxCompany.Name = "textBoxCompany";
            this.textBoxCompany.Size = new System.Drawing.Size(317, 20);
            this.textBoxCompany.TabIndex = 22;
            // 
            // labelCity
            // 
            this.labelCity.AutoSize = true;
            this.labelCity.Location = new System.Drawing.Point(93, 118);
            this.labelCity.Name = "labelCity";
            this.labelCity.Size = new System.Drawing.Size(46, 13);
            this.labelCity.TabIndex = 23;
            this.labelCity.Text = "labelCity";
            // 
            // labelCountry
            // 
            this.labelCountry.AutoSize = true;
            this.labelCountry.Location = new System.Drawing.Point(93, 171);
            this.labelCountry.Name = "labelCountry";
            this.labelCountry.Size = new System.Drawing.Size(65, 13);
            this.labelCountry.TabIndex = 24;
            this.labelCountry.Text = "labelCountry";
            // 
            // labelStatus
            // 
            this.labelStatus.AutoSize = true;
            this.labelStatus.Location = new System.Drawing.Point(93, 226);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(59, 13);
            this.labelStatus.TabIndex = 25;
            this.labelStatus.Text = "labelStatus";
            // 
            // linkLabelTitleUpdate
            // 
            this.linkLabelTitleUpdate.AutoSize = true;
            this.linkLabelTitleUpdate.Location = new System.Drawing.Point(416, 39);
            this.linkLabelTitleUpdate.Name = "linkLabelTitleUpdate";
            this.linkLabelTitleUpdate.Size = new System.Drawing.Size(51, 13);
            this.linkLabelTitleUpdate.TabIndex = 26;
            this.linkLabelTitleUpdate.TabStop = true;
            this.linkLabelTitleUpdate.Text = "Oppdater";
            this.linkLabelTitleUpdate.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelTitleUpdate_LinkClicked);
            // 
            // linkLabelCompanyUpdate
            // 
            this.linkLabelCompanyUpdate.AutoSize = true;
            this.linkLabelCompanyUpdate.Location = new System.Drawing.Point(416, 69);
            this.linkLabelCompanyUpdate.Name = "linkLabelCompanyUpdate";
            this.linkLabelCompanyUpdate.Size = new System.Drawing.Size(51, 13);
            this.linkLabelCompanyUpdate.TabIndex = 27;
            this.linkLabelCompanyUpdate.TabStop = true;
            this.linkLabelCompanyUpdate.Text = "Oppdater";
            this.linkLabelCompanyUpdate.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelCompanyUpdate_LinkClicked);
            // 
            // linkLabelCityIDUpdate
            // 
            this.linkLabelCityIDUpdate.AutoSize = true;
            this.linkLabelCityIDUpdate.Location = new System.Drawing.Point(416, 93);
            this.linkLabelCityIDUpdate.Name = "linkLabelCityIDUpdate";
            this.linkLabelCityIDUpdate.Size = new System.Drawing.Size(51, 13);
            this.linkLabelCityIDUpdate.TabIndex = 28;
            this.linkLabelCityIDUpdate.TabStop = true;
            this.linkLabelCityIDUpdate.Text = "Oppdater";
            this.linkLabelCityIDUpdate.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelCityIDUpdate_LinkClicked);
            // 
            // linkLabelStatusIDUpdate
            // 
            this.linkLabelStatusIDUpdate.AutoSize = true;
            this.linkLabelStatusIDUpdate.Location = new System.Drawing.Point(416, 196);
            this.linkLabelStatusIDUpdate.Name = "linkLabelStatusIDUpdate";
            this.linkLabelStatusIDUpdate.Size = new System.Drawing.Size(51, 13);
            this.linkLabelStatusIDUpdate.TabIndex = 30;
            this.linkLabelStatusIDUpdate.TabStop = true;
            this.linkLabelStatusIDUpdate.Text = "Oppdater";
            this.linkLabelStatusIDUpdate.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelStatusIDUpdate_LinkClicked);
            // 
            // linkLabelDateUpdate
            // 
            this.linkLabelDateUpdate.AutoSize = true;
            this.linkLabelDateUpdate.Location = new System.Drawing.Point(416, 253);
            this.linkLabelDateUpdate.Name = "linkLabelDateUpdate";
            this.linkLabelDateUpdate.Size = new System.Drawing.Size(51, 13);
            this.linkLabelDateUpdate.TabIndex = 31;
            this.linkLabelDateUpdate.TabStop = true;
            this.linkLabelDateUpdate.Text = "Oppdater";
            this.linkLabelDateUpdate.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelDateUpdate_LinkClicked);
            // 
            // textBoxDate
            // 
            this.textBoxDate.Location = new System.Drawing.Point(93, 253);
            this.textBoxDate.Name = "textBoxDate";
            this.textBoxDate.Size = new System.Drawing.Size(317, 20);
            this.textBoxDate.TabIndex = 32;
            // 
            // labelCountryID
            // 
            this.labelCountryID.AutoSize = true;
            this.labelCountryID.Location = new System.Drawing.Point(93, 144);
            this.labelCountryID.Name = "labelCountryID";
            this.labelCountryID.Size = new System.Drawing.Size(76, 13);
            this.labelCountryID.TabIndex = 33;
            this.labelCountryID.Text = "labelCountryID";
            // 
            // ViewApplications
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(503, 321);
            this.Controls.Add(this.labelCountryID);
            this.Controls.Add(this.textBoxDate);
            this.Controls.Add(this.linkLabelDateUpdate);
            this.Controls.Add(this.linkLabelStatusIDUpdate);
            this.Controls.Add(this.linkLabelCityIDUpdate);
            this.Controls.Add(this.linkLabelCompanyUpdate);
            this.Controls.Add(this.linkLabelTitleUpdate);
            this.Controls.Add(this.labelStatus);
            this.Controls.Add(this.labelCountry);
            this.Controls.Add(this.labelCity);
            this.Controls.Add(this.textBoxCompany);
            this.Controls.Add(this.textBoxTitle);
            this.Controls.Add(this.comboBoxStatusID);
            this.Controls.Add(this.comboBoxCityID);
            this.Controls.Add(this.comboBoxApplicationID);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonLast);
            this.Controls.Add(this.buttonNext);
            this.Controls.Add(this.buttonUpdate);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonPrevious);
            this.Controls.Add(this.buttonFirst);
            this.Name = "ViewApplications";
            this.ShowIcon = false;
            this.Text = "Vis søknader";
            this.Load += new System.EventHandler(this.ViewApplications_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonFirst;
        private System.Windows.Forms.Button buttonPrevious;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonUpdate;
        private System.Windows.Forms.Button buttonNext;
        private System.Windows.Forms.Button buttonLast;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox comboBoxApplicationID;
        private System.Windows.Forms.ComboBox comboBoxCityID;
        private System.Windows.Forms.ComboBox comboBoxStatusID;
        private System.Windows.Forms.TextBox textBoxTitle;
        private System.Windows.Forms.TextBox textBoxCompany;
        private System.Windows.Forms.Label labelCity;
        private System.Windows.Forms.Label labelCountry;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.LinkLabel linkLabelTitleUpdate;
        private System.Windows.Forms.LinkLabel linkLabelCompanyUpdate;
        private System.Windows.Forms.LinkLabel linkLabelCityIDUpdate;
        private System.Windows.Forms.LinkLabel linkLabelStatusIDUpdate;
        private System.Windows.Forms.LinkLabel linkLabelDateUpdate;
        private System.Windows.Forms.TextBox textBoxDate;
        private System.Windows.Forms.Label labelCountryID;
    }
}