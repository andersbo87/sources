﻿// Designerklasse for randomized Quicksort.
namespace Sorteringsprogram
{
    partial class RandomizedQuicksortGUI
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
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.textBoxSorted = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.buttonSort = new System.Windows.Forms.Button();
            this.textBoxUnsorted = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonBrowse = new System.Windows.Forms.Button();
            this.textBoxFilePath = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 266);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(429, 22);
            this.statusStrip1.TabIndex = 28;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(0, 17);
            // 
            // textBoxSorted
            // 
            this.textBoxSorted.Location = new System.Drawing.Point(218, 105);
            this.textBoxSorted.Multiline = true;
            this.textBoxSorted.Name = "textBoxSorted";
            this.textBoxSorted.ReadOnly = true;
            this.textBoxSorted.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxSorted.Size = new System.Drawing.Size(198, 159);
            this.textBoxSorted.TabIndex = 27;
            this.textBoxSorted.WordWrap = false;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(216, 89);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(38, 13);
            this.label3.TabIndex = 26;
            this.label3.Text = "Sortert";
            // 
            // buttonSort
            // 
            this.buttonSort.Enabled = false;
            this.buttonSort.Location = new System.Drawing.Point(341, 53);
            this.buttonSort.Name = "buttonSort";
            this.buttonSort.Size = new System.Drawing.Size(75, 23);
            this.buttonSort.TabIndex = 25;
            this.buttonSort.Text = "Sorter!";
            this.buttonSort.UseVisualStyleBackColor = true;
            this.buttonSort.Click += new System.EventHandler(this.buttonSort_Click);
            // 
            // textBoxUnsorted
            // 
            this.textBoxUnsorted.Location = new System.Drawing.Point(12, 106);
            this.textBoxUnsorted.Multiline = true;
            this.textBoxUnsorted.Name = "textBoxUnsorted";
            this.textBoxUnsorted.ReadOnly = true;
            this.textBoxUnsorted.ScrollBars = System.Windows.Forms.ScrollBars.Both;
            this.textBoxUnsorted.Size = new System.Drawing.Size(198, 159);
            this.textBoxUnsorted.TabIndex = 24;
            this.textBoxUnsorted.WordWrap = false;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 89);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(44, 13);
            this.label2.TabIndex = 23;
            this.label2.Text = "Usortert";
            // 
            // buttonBrowse
            // 
            this.buttonBrowse.Location = new System.Drawing.Point(260, 53);
            this.buttonBrowse.Name = "buttonBrowse";
            this.buttonBrowse.Size = new System.Drawing.Size(75, 23);
            this.buttonBrowse.TabIndex = 22;
            this.buttonBrowse.Text = "Bla gjennom";
            this.buttonBrowse.UseVisualStyleBackColor = true;
            this.buttonBrowse.Click += new System.EventHandler(this.buttonBrowse_Click);
            // 
            // textBoxFilePath
            // 
            this.textBoxFilePath.Enabled = false;
            this.textBoxFilePath.Location = new System.Drawing.Point(12, 56);
            this.textBoxFilePath.Name = "textBoxFilePath";
            this.textBoxFilePath.Size = new System.Drawing.Size(242, 20);
            this.textBoxFilePath.TabIndex = 21;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(404, 43);
            this.label1.TabIndex = 20;
            this.label1.Text = "Her kan du sortere usorterte tall ved hjelp av \"tilfeldig hurtigsortering\" (rando" +
    "mized quicksort). Last inn filen med de usorterte (eller omvendt sorterte) talle" +
    "ne og klikk sorter for å sortere dem.";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // RandomizedQuicksortGUI
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(429, 288);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.textBoxSorted);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.buttonSort);
            this.Controls.Add(this.textBoxUnsorted);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.buttonBrowse);
            this.Controls.Add(this.textBoxFilePath);
            this.Controls.Add(this.label1);
            this.Name = "RandomizedQuicksortGUI";
            this.Text = "\"Randomized Quicksort\".";
            this.Load += new System.EventHandler(this.RandomizedQuicksortGUI_Load);
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.TextBox textBoxSorted;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonSort;
        private System.Windows.Forms.TextBox textBoxUnsorted;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button buttonBrowse;
        private System.Windows.Forms.TextBox textBoxFilePath;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
    }
}