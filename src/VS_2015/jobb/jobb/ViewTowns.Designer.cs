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
    partial class ViewTowns
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
            this.components = new System.ComponentModel.Container();
            this.labelInfo = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxTownName = new System.Windows.Forms.TextBox();
            this.comboBoxTownID = new System.Windows.Forms.ComboBox();
            this.linkLabelUpdate = new System.Windows.Forms.LinkLabel();
            this.buttonLast = new System.Windows.Forms.Button();
            this.buttonNext = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonPrevious = new System.Windows.Forms.Button();
            this.buttonFirst = new System.Windows.Forms.Button();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.labelCountryID = new System.Windows.Forms.Label();
            this.comboBoxCountryID = new System.Windows.Forms.ComboBox();
            this.labelCountry = new System.Windows.Forms.Label();
            this.labelCountryValue = new System.Windows.Forms.Label();
            this.toolTip1 = new System.Windows.Forms.ToolTip(this.components);
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // labelInfo
            // 
            this.labelInfo.Dock = System.Windows.Forms.DockStyle.Top;
            this.labelInfo.Location = new System.Drawing.Point(0, 0);
            this.labelInfo.Name = "labelInfo";
            this.labelInfo.Size = new System.Drawing.Size(270, 30);
            this.labelInfo.TabIndex = 0;
            this.labelInfo.Text = "Her finner du kort informasjon (id og hvilket land byen ligger i) om de ulike bye" +
    "ne som er lagt inn i databasen.";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 45);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "StedID";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 68);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Stedsnavn";
            // 
            // textBoxTownName
            // 
            this.textBoxTownName.Location = new System.Drawing.Point(78, 68);
            this.textBoxTownName.Name = "textBoxTownName";
            this.textBoxTownName.Size = new System.Drawing.Size(121, 20);
            this.textBoxTownName.TabIndex = 3;
            // 
            // comboBoxTownID
            // 
            this.comboBoxTownID.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxTownID.FormattingEnabled = true;
            this.comboBoxTownID.Location = new System.Drawing.Point(78, 41);
            this.comboBoxTownID.Name = "comboBoxTownID";
            this.comboBoxTownID.Size = new System.Drawing.Size(121, 21);
            this.comboBoxTownID.TabIndex = 4;
            this.comboBoxTownID.SelectedIndexChanged += new System.EventHandler(this.comboBoxTownID_SelectedIndexChanged);
            // 
            // linkLabelUpdate
            // 
            this.linkLabelUpdate.AutoSize = true;
            this.linkLabelUpdate.Location = new System.Drawing.Point(206, 74);
            this.linkLabelUpdate.Name = "linkLabelUpdate";
            this.linkLabelUpdate.Size = new System.Drawing.Size(34, 13);
            this.linkLabelUpdate.TabIndex = 5;
            this.linkLabelUpdate.TabStop = true;
            this.linkLabelUpdate.Text = "Lagre";
            this.linkLabelUpdate.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelUpdate_LinkClicked);
            // 
            // buttonLast
            // 
            this.buttonLast.Location = new System.Drawing.Point(191, 142);
            this.buttonLast.Name = "buttonLast";
            this.buttonLast.Size = new System.Drawing.Size(30, 23);
            this.buttonLast.TabIndex = 11;
            this.buttonLast.Text = ">>";
            this.buttonLast.UseVisualStyleBackColor = true;
            this.buttonLast.Click += new System.EventHandler(this.buttonLast_Click);
            this.buttonLast.MouseHover += new System.EventHandler(this.buttonLast_MouseHover);
            // 
            // buttonNext
            // 
            this.buttonNext.Location = new System.Drawing.Point(155, 142);
            this.buttonNext.Name = "buttonNext";
            this.buttonNext.Size = new System.Drawing.Size(30, 23);
            this.buttonNext.TabIndex = 10;
            this.buttonNext.Text = ">";
            this.buttonNext.UseVisualStyleBackColor = true;
            this.buttonNext.Click += new System.EventHandler(this.buttonNext_Click);
            this.buttonNext.MouseHover += new System.EventHandler(this.buttonNext_MouseHover);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(84, 142);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(30, 23);
            this.buttonDelete.TabIndex = 8;
            this.buttonDelete.Text = "X";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            this.buttonDelete.MouseHover += new System.EventHandler(this.buttonDelete_MouseHover);
            // 
            // buttonPrevious
            // 
            this.buttonPrevious.Enabled = false;
            this.buttonPrevious.Location = new System.Drawing.Point(48, 142);
            this.buttonPrevious.Name = "buttonPrevious";
            this.buttonPrevious.Size = new System.Drawing.Size(30, 23);
            this.buttonPrevious.TabIndex = 7;
            this.buttonPrevious.Text = "<";
            this.buttonPrevious.UseVisualStyleBackColor = true;
            this.buttonPrevious.Click += new System.EventHandler(this.buttonPrevious_Click);
            this.buttonPrevious.MouseHover += new System.EventHandler(this.buttonPrevious_MouseHover);
            // 
            // buttonFirst
            // 
            this.buttonFirst.Enabled = false;
            this.buttonFirst.Location = new System.Drawing.Point(12, 142);
            this.buttonFirst.Name = "buttonFirst";
            this.buttonFirst.Size = new System.Drawing.Size(30, 23);
            this.buttonFirst.TabIndex = 6;
            this.buttonFirst.Text = "<<";
            this.buttonFirst.UseVisualStyleBackColor = true;
            this.buttonFirst.Click += new System.EventHandler(this.buttonFirst_Click);
            this.buttonFirst.MouseHover += new System.EventHandler(this.buttonFirst_MouseHover);
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Location = new System.Drawing.Point(120, 142);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(30, 23);
            this.buttonRefresh.TabIndex = 12;
            this.buttonRefresh.Text = "R";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            this.buttonRefresh.MouseHover += new System.EventHandler(this.buttonRefresh_MouseHover);
            // 
            // labelCountryID
            // 
            this.labelCountryID.AutoSize = true;
            this.labelCountryID.Location = new System.Drawing.Point(12, 95);
            this.labelCountryID.Name = "labelCountryID";
            this.labelCountryID.Size = new System.Drawing.Size(42, 13);
            this.labelCountryID.TabIndex = 13;
            this.labelCountryID.Text = "LandID";
            // 
            // comboBoxCountryID
            // 
            this.comboBoxCountryID.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBoxCountryID.FormattingEnabled = true;
            this.comboBoxCountryID.Location = new System.Drawing.Point(78, 95);
            this.comboBoxCountryID.Name = "comboBoxCountryID";
            this.comboBoxCountryID.Size = new System.Drawing.Size(121, 21);
            this.comboBoxCountryID.TabIndex = 14;
            this.comboBoxCountryID.SelectedIndexChanged += new System.EventHandler(this.comboBoxCountryID_SelectedIndexChanged);
            // 
            // labelCountry
            // 
            this.labelCountry.AutoSize = true;
            this.labelCountry.Location = new System.Drawing.Point(13, 122);
            this.labelCountry.Name = "labelCountry";
            this.labelCountry.Size = new System.Drawing.Size(55, 13);
            this.labelCountry.TabIndex = 15;
            this.labelCountry.Text = "Landnavn";
            // 
            // labelCountryValue
            // 
            this.labelCountryValue.AutoSize = true;
            this.labelCountryValue.Location = new System.Drawing.Point(78, 122);
            this.labelCountryValue.Name = "labelCountryValue";
            this.labelCountryValue.Size = new System.Drawing.Size(35, 13);
            this.labelCountryValue.TabIndex = 16;
            this.labelCountryValue.Text = "label3";
            // 
            // linkLabel1
            // 
            this.linkLabel1.AutoSize = true;
            this.linkLabel1.Location = new System.Drawing.Point(205, 98);
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.Size = new System.Drawing.Size(34, 13);
            this.linkLabel1.TabIndex = 17;
            this.linkLabel1.TabStop = true;
            this.linkLabel1.Text = "Lagre";
            this.linkLabel1.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // ViewTowns
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(270, 177);
            this.Controls.Add(this.linkLabel1);
            this.Controls.Add(this.labelCountryValue);
            this.Controls.Add(this.labelCountry);
            this.Controls.Add(this.comboBoxCountryID);
            this.Controls.Add(this.labelCountryID);
            this.Controls.Add(this.buttonRefresh);
            this.Controls.Add(this.buttonLast);
            this.Controls.Add(this.buttonNext);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonPrevious);
            this.Controls.Add(this.buttonFirst);
            this.Controls.Add(this.linkLabelUpdate);
            this.Controls.Add(this.comboBoxTownID);
            this.Controls.Add(this.textBoxTownName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.labelInfo);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ViewTowns";
            this.ShowIcon = false;
            this.Text = "Byer i Jobber-databasen";
            this.Load += new System.EventHandler(this.ViewTowns_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelInfo;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxTownName;
        private System.Windows.Forms.ComboBox comboBoxTownID;
        private System.Windows.Forms.LinkLabel linkLabelUpdate;
        private System.Windows.Forms.Button buttonLast;
        private System.Windows.Forms.Button buttonNext;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonPrevious;
        private System.Windows.Forms.Button buttonFirst;
        private System.Windows.Forms.Button buttonRefresh;
        private System.Windows.Forms.Label labelCountryID;
        private System.Windows.Forms.ComboBox comboBoxCountryID;
        private System.Windows.Forms.Label labelCountry;
        private System.Windows.Forms.Label labelCountryValue;
        private System.Windows.Forms.ToolTip toolTip1;
        private System.Windows.Forms.LinkLabel linkLabel1;
    }
}