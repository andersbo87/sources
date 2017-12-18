namespace Sorteringsprogram
{
    partial class Form1
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
            this.btnGenerateRandomNumbers = new System.Windows.Forms.Button();
            this.buttonMergesort = new System.Windows.Forms.Button();
            this.buttonQuicksort = new System.Windows.Forms.Button();
            this.buttonCreateReversedSortedNumbers = new System.Windows.Forms.Button();
            this.buttonInsertionSort = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnGenerateRandomNumbers
            // 
            this.btnGenerateRandomNumbers.Location = new System.Drawing.Point(13, 13);
            this.btnGenerateRandomNumbers.Name = "btnGenerateRandomNumbers";
            this.btnGenerateRandomNumbers.Size = new System.Drawing.Size(139, 23);
            this.btnGenerateRandomNumbers.TabIndex = 0;
            this.btnGenerateRandomNumbers.Text = "Lag tilfeldige tall";
            this.btnGenerateRandomNumbers.UseVisualStyleBackColor = true;
            this.btnGenerateRandomNumbers.Click += new System.EventHandler(this.btnGenerateRandomNumbers_Click);
            // 
            // buttonMergesort
            // 
            this.buttonMergesort.Location = new System.Drawing.Point(13, 71);
            this.buttonMergesort.Name = "buttonMergesort";
            this.buttonMergesort.Size = new System.Drawing.Size(139, 23);
            this.buttonMergesort.TabIndex = 1;
            this.buttonMergesort.Text = "Flettesortering";
            this.buttonMergesort.UseVisualStyleBackColor = true;
            this.buttonMergesort.Click += new System.EventHandler(this.buttonMergesort_Click);
            // 
            // buttonQuicksort
            // 
            this.buttonQuicksort.Location = new System.Drawing.Point(13, 101);
            this.buttonQuicksort.Name = "buttonQuicksort";
            this.buttonQuicksort.Size = new System.Drawing.Size(139, 23);
            this.buttonQuicksort.TabIndex = 2;
            this.buttonQuicksort.Text = "QuickSort";
            this.buttonQuicksort.UseVisualStyleBackColor = true;
            this.buttonQuicksort.Click += new System.EventHandler(this.buttonQuicksort_Click);
            // 
            // buttonCreateReversedSortedNumbers
            // 
            this.buttonCreateReversedSortedNumbers.Location = new System.Drawing.Point(12, 42);
            this.buttonCreateReversedSortedNumbers.Name = "buttonCreateReversedSortedNumbers";
            this.buttonCreateReversedSortedNumbers.Size = new System.Drawing.Size(139, 23);
            this.buttonCreateReversedSortedNumbers.TabIndex = 3;
            this.buttonCreateReversedSortedNumbers.Text = "Lag omvendt sorterte tall";
            this.buttonCreateReversedSortedNumbers.UseVisualStyleBackColor = true;
            this.buttonCreateReversedSortedNumbers.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonInsertionSort
            // 
            this.buttonInsertionSort.Location = new System.Drawing.Point(13, 163);
            this.buttonInsertionSort.Name = "buttonInsertionSort";
            this.buttonInsertionSort.Size = new System.Drawing.Size(139, 23);
            this.buttonInsertionSort.TabIndex = 4;
            this.buttonInsertionSort.Text = "Innsettingssortering";
            this.buttonInsertionSort.UseVisualStyleBackColor = true;
            this.buttonInsertionSort.Click += new System.EventHandler(this.buttonInsertionSort_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(13, 131);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(138, 23);
            this.button1.TabIndex = 5;
            this.button1.Text = "\"Randomized Quick Sort\"";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(13, 193);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(138, 23);
            this.button2.TabIndex = 6;
            this.button2.Text = "Heap sort";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.buttonInsertionSort);
            this.Controls.Add(this.buttonCreateReversedSortedNumbers);
            this.Controls.Add(this.buttonQuicksort);
            this.Controls.Add(this.buttonMergesort);
            this.Controls.Add(this.btnGenerateRandomNumbers);
            this.Name = "Form1";
            this.Text = "Sorteringsprogram";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnGenerateRandomNumbers;
        private System.Windows.Forms.Button buttonMergesort;
        private System.Windows.Forms.Button buttonQuicksort;
        private System.Windows.Forms.Button buttonCreateReversedSortedNumbers;
        private System.Windows.Forms.Button buttonInsertionSort;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
    }
}

