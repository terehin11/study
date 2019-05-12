using System;
namespace Diagram
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.Diagram = new System.Windows.Forms.PictureBox();
            this.button1 = new System.Windows.Forms.Button();
            this.k = new System.Windows.Forms.TextBox();
            this.m = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.Diagram)).BeginInit();
            this.SuspendLayout();
            // 
            // Diagram
            // 
            this.Diagram.Location = new System.Drawing.Point(-1, 2);
            this.Diagram.Name = "Diagram";
            this.Diagram.Size = new System.Drawing.Size(800, 403);
            this.Diagram.TabIndex = 0;
            this.Diagram.TabStop = false;
         //   this.Diagram.Click += new System.EventHandler(this.Diagram_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(595, 415);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "Старт";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // k
            // 
            this.k.Location = new System.Drawing.Point(118, 437);
            this.k.Name = "k";
            this.k.Size = new System.Drawing.Size(67, 20);
            this.k.TabIndex = 2;
            // 
            // m
            // 
            this.m.Location = new System.Drawing.Point(214, 437);
            this.m.Name = "m";
            this.m.Size = new System.Drawing.Size(67, 20);
            this.m.TabIndex = 3;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(115, 415);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(51, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Столбцы";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(211, 415);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(43, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Cтроки";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 469);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.m);
            this.Controls.Add(this.k);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.Diagram);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.Diagram)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion


        //public float mas(float [,]a/*, int k , int m*/)
        //{
        //    a = new float[k, m];
        //    Random random = new Random();
        //    for(int i = 0; i < k; i++)
        //    {
        //        for(int j = 0; j < m;j++)
        //        {
        //            a[i, j] = random.Next(100);
        //        }
        //    }
        //    return a[k,m];
        //}


        private System.Windows.Forms.PictureBox Diagram;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox k;
        private System.Windows.Forms.TextBox m;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

