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
    partial class ViewStatuses
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
            this.labelStatusID = new System.Windows.Forms.Label();
            this.labelStatus = new System.Windows.Forms.Label();
            this.comboBoxStatusID = new System.Windows.Forms.ComboBox();
            this.textBoxStatus = new System.Windows.Forms.TextBox();
            this.linkLabelOppdater = new System.Windows.Forms.LinkLabel();
            this.buttonLast = new System.Windows.Forms.Button();
            this.buttonNext = new System.Windows.Forms.Button();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.buttonPrevious = new System.Windows.Forms.Button();
            this.buttonFirst = new System.Windows.Forms.Button();
            this.buttonRefresh = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // labelStatusID
            // 
            this.labelStatusID.AutoSize = true;
            this.labelStatusID.Location = new System.Drawing.Point(13, 13);
            this.labelStatusID.Name = "labelStatusID";
            this.labelStatusID.Size = new System.Drawing.Size(48, 13);
            this.labelStatusID.TabIndex = 0;
            this.labelStatusID.Text = "StatusID";
            // 
            // labelStatus
            // 
            this.labelStatus.AutoSize = true;
            this.labelStatus.Location = new System.Drawing.Point(13, 43);
            this.labelStatus.Name = "labelStatus";
            this.labelStatus.Size = new System.Drawing.Size(37, 13);
            this.labelStatus.TabIndex = 1;
            this.labelStatus.Text = "Status";
            // 
            // comboBoxStatusID
            // 
            this.comboBoxStatusID.FormattingEnabled = true;
            this.comboBoxStatusID.Location = new System.Drawing.Point(68, 13);
            this.comboBoxStatusID.Name = "comboBoxStatusID";
            this.comboBoxStatusID.Size = new System.Drawing.Size(121, 21);
            this.comboBoxStatusID.TabIndex = 2;
            this.comboBoxStatusID.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            // 
            // textBoxStatus
            // 
            this.textBoxStatus.Location = new System.Drawing.Point(68, 43);
            this.textBoxStatus.Name = "textBoxStatus";
            this.textBoxStatus.Size = new System.Drawing.Size(121, 20);
            this.textBoxStatus.TabIndex = 3;
            // 
            // linkLabelOppdater
            // 
            this.linkLabelOppdater.AutoSize = true;
            this.linkLabelOppdater.Location = new System.Drawing.Point(196, 49);
            this.linkLabelOppdater.Name = "linkLabelOppdater";
            this.linkLabelOppdater.Size = new System.Drawing.Size(51, 13);
            this.linkLabelOppdater.TabIndex = 4;
            this.linkLabelOppdater.TabStop = true;
            this.linkLabelOppdater.Text = "Oppdater";
            this.linkLabelOppdater.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelOppdater_LinkClicked);
            // 
            // buttonLast
            // 
            this.buttonLast.Location = new System.Drawing.Point(218, 78);
            this.buttonLast.Name = "buttonLast";
            this.buttonLast.Size = new System.Drawing.Size(36, 23);
            this.buttonLast.TabIndex = 13;
            this.buttonLast.Text = ">>";
            this.buttonLast.UseVisualStyleBackColor = true;
            this.buttonLast.Click += new System.EventHandler(this.buttonLast_Click);
            // 
            // buttonNext
            // 
            this.buttonNext.Location = new System.Drawing.Point(176, 78);
            this.buttonNext.Name = "buttonNext";
            this.buttonNext.Size = new System.Drawing.Size(36, 23);
            this.buttonNext.TabIndex = 12;
            this.buttonNext.Text = ">";
            this.buttonNext.UseVisualStyleBackColor = true;
            this.buttonNext.Click += new System.EventHandler(this.buttonNext_Click);
            // 
            // buttonDelete
            // 
            this.buttonDelete.Location = new System.Drawing.Point(100, 78);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(36, 23);
            this.buttonDelete.TabIndex = 11;
            this.buttonDelete.Text = "X";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.Click += new System.EventHandler(this.buttonDelete_Click);
            // 
            // buttonPrevious
            // 
            this.buttonPrevious.Enabled = false;
            this.buttonPrevious.Location = new System.Drawing.Point(58, 78);
            this.buttonPrevious.Name = "buttonPrevious";
            this.buttonPrevious.Size = new System.Drawing.Size(36, 23);
            this.buttonPrevious.TabIndex = 10;
            this.buttonPrevious.Text = "<";
            this.buttonPrevious.UseVisualStyleBackColor = true;
            this.buttonPrevious.Click += new System.EventHandler(this.buttonPrevious_Click);
            // 
            // buttonFirst
            // 
            this.buttonFirst.Enabled = false;
            this.buttonFirst.Location = new System.Drawing.Point(16, 78);
            this.buttonFirst.Name = "buttonFirst";
            this.buttonFirst.Size = new System.Drawing.Size(36, 23);
            this.buttonFirst.TabIndex = 9;
            this.buttonFirst.Text = "<<";
            this.buttonFirst.UseVisualStyleBackColor = true;
            this.buttonFirst.Click += new System.EventHandler(this.buttonFirst_Click);
            // 
            // buttonRefresh
            // 
            this.buttonRefresh.Location = new System.Drawing.Point(142, 78);
            this.buttonRefresh.Name = "buttonRefresh";
            this.buttonRefresh.Size = new System.Drawing.Size(30, 23);
            this.buttonRefresh.TabIndex = 14;
            this.buttonRefresh.Text = "R";
            this.buttonRefresh.UseVisualStyleBackColor = true;
            this.buttonRefresh.Click += new System.EventHandler(this.buttonRefresh_Click);
            // 
            // ViewStatuses
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 126);
            this.Controls.Add(this.buttonRefresh);
            this.Controls.Add(this.buttonLast);
            this.Controls.Add(this.buttonNext);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.buttonPrevious);
            this.Controls.Add(this.buttonFirst);
            this.Controls.Add(this.linkLabelOppdater);
            this.Controls.Add(this.textBoxStatus);
            this.Controls.Add(this.comboBoxStatusID);
            this.Controls.Add(this.labelStatus);
            this.Controls.Add(this.labelStatusID);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ViewStatuses";
            this.ShowIcon = false;
            this.Text = "Vis innlagte statuser";
            this.Load += new System.EventHandler(this.ViewStatuses_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelStatusID;
        private System.Windows.Forms.Label labelStatus;
        private System.Windows.Forms.ComboBox comboBoxStatusID;
        private System.Windows.Forms.TextBox textBoxStatus;
        private System.Windows.Forms.LinkLabel linkLabelOppdater;
        private System.Windows.Forms.Button buttonLast;
        private System.Windows.Forms.Button buttonNext;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Button buttonPrevious;
        private System.Windows.Forms.Button buttonFirst;
        private System.Windows.Forms.Button buttonRefresh;
    }
}