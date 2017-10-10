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
    partial class ViewCountries
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
            this.labelCountryID = new System.Windows.Forms.Label();
            this.labelCountryName = new System.Windows.Forms.Label();
            this.textBoxCountry = new System.Windows.Forms.TextBox();
            this.buttonFirst = new System.Windows.Forms.Button();
            this.buttonPrevious = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonNext = new System.Windows.Forms.Button();
            this.buttonLast = new System.Windows.Forms.Button();
            this.updateLabel = new System.Windows.Forms.LinkLabel();
            this.comboBoxCountryID = new System.Windows.Forms.ComboBox();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // labelCountryID
            // 
            this.labelCountryID.AutoSize = true;
            this.labelCountryID.Location = new System.Drawing.Point(13, 13);
            this.labelCountryID.Name = "labelCountryID";
            this.labelCountryID.Size = new System.Drawing.Size(42, 13);
            this.labelCountryID.TabIndex = 0;
            this.labelCountryID.Text = "LandID";
            // 
            // labelCountryName
            // 
            this.labelCountryName.AutoSize = true;
            this.labelCountryName.Location = new System.Drawing.Point(13, 37);
            this.labelCountryName.Name = "labelCountryName";
            this.labelCountryName.Size = new System.Drawing.Size(55, 13);
            this.labelCountryName.TabIndex = 1;
            this.labelCountryName.Text = "Landnavn";
            // 
            // textBoxCountry
            // 
            this.textBoxCountry.Location = new System.Drawing.Point(74, 34);
            this.textBoxCountry.Name = "textBoxCountry";
            this.textBoxCountry.Size = new System.Drawing.Size(103, 20);
            this.textBoxCountry.TabIndex = 2;
            // 
            // buttonFirst
            // 
            this.buttonFirst.Enabled = false;
            this.buttonFirst.Location = new System.Drawing.Point(16, 71);
            this.buttonFirst.Name = "buttonFirst";
            this.buttonFirst.Size = new System.Drawing.Size(36, 23);
            this.buttonFirst.TabIndex = 4;
            this.buttonFirst.Text = "<<";
            this.buttonFirst.UseVisualStyleBackColor = true;
            this.buttonFirst.Click += new System.EventHandler(this.buttonFirst_Click);
            // 
            // buttonPrevious
            // 
            this.buttonPrevious.Enabled = false;
            this.buttonPrevious.Location = new System.Drawing.Point(58, 71);
            this.buttonPrevious.Name = "buttonPrevious";
            this.buttonPrevious.Size = new System.Drawing.Size(36, 23);
            this.buttonPrevious.TabIndex = 5;
            this.buttonPrevious.Text = "<";
            this.buttonPrevious.UseVisualStyleBackColor = true;
            this.buttonPrevious.Click += new System.EventHandler(this.buttonPrevious_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(100, 71);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(36, 23);
            this.buttonDelete.TabIndex = 6;
            this.buttonDelete.Text = "X";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // buttonNext
            // 
            this.buttonNext.Location = new System.Drawing.Point(178, 71);
            this.buttonNext.Name = "buttonNext";
            this.buttonNext.Size = new System.Drawing.Size(36, 23);
            this.buttonNext.TabIndex = 7;
            this.buttonNext.Text = ">";
            this.buttonNext.UseVisualStyleBackColor = true;
            this.buttonNext.Click += new System.EventHandler(this.buttonNext_Click);
            // 
            // buttonLast
            // 
            this.buttonLast.Location = new System.Drawing.Point(220, 71);
            this.buttonLast.Name = "buttonLast";
            this.buttonLast.Size = new System.Drawing.Size(36, 23);
            this.buttonLast.TabIndex = 8;
            this.buttonLast.Text = ">>";
            this.buttonLast.UseVisualStyleBackColor = true;
            this.buttonLast.Click += new System.EventHandler(this.buttonLast_Click);
            // 
            // updateLabel
            // 
            this.updateLabel.AutoSize = true;
            this.updateLabel.Location = new System.Drawing.Point(183, 37);
            this.updateLabel.Name = "updateLabel";
            this.updateLabel.Size = new System.Drawing.Size(51, 13);
            this.updateLabel.TabIndex = 9;
            this.updateLabel.TabStop = true;
            this.updateLabel.Text = "Oppdater";
            this.updateLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.updateLabel_LinkClicked);
            // 
            // comboBoxCountryID
            // 
            this.comboBoxCountryID.FormattingEnabled = true;
            this.comboBoxCountryID.Location = new System.Drawing.Point(74, 10);
            this.comboBoxCountryID.Name = "comboBoxCountryID";
            this.comboBoxCountryID.Size = new System.Drawing.Size(104, 21);
            this.comboBoxCountryID.TabIndex = 10;
            this.comboBoxCountryID.SelectedIndexChanged += new System.EventHandler(this.comboBoxCountryID_SelectedIndexChanged);
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Location = new System.Drawing.Point(142, 71);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(30, 23);
            this.buttonRefresh.TabIndex = 13;
            this.buttonRefresh.Text = "R";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // ViewCountries
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(262, 106);
            this.Controls.Add(this.buttonRefresh);
            this.Controls.Add(this.comboBoxCountryID);
            this.Controls.Add(this.updateLabel);
            this.Controls.Add(this.buttonLast);
            this.Controls.Add(this.buttonNext);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonPrevious);
            this.Controls.Add(this.buttonFirst);
            this.Controls.Add(this.textBoxCountry);
            this.Controls.Add(this.labelCountryName);
            this.Controls.Add(this.labelCountryID);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ViewCountries";
            this.ShowIcon = false;
            this.Text = "Vis innlagte land";
            this.Load += new System.EventHandler(this.ViewCountries_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelCountryID;
        private System.Windows.Forms.Label labelCountryName;
        private System.Windows.Forms.TextBox textBoxCountry;
        private System.Windows.Forms.Button buttonFirst;
        private System.Windows.Forms.Button buttonPrevious;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonNext;
        private System.Windows.Forms.Button buttonLast;
        private System.Windows.Forms.LinkLabel updateLabel;
        private System.Windows.Forms.ComboBox comboBoxCountryID;
        private System.Windows.Forms.Button buttonRefresh;
    }
}