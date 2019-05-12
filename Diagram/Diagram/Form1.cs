using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Diagram
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            k.Text = Convert.ToString(50);
            m.Text = Convert.ToString(50);

        }

        Bitmap bmp;

        private void painting()
        {
         

           
        }


        private void button1_Click(object sender, EventArgs e)
        {
            int a = int.Parse(k.Text);
            int b = int.Parse(m.Text);

            float[,] mas = new float[a, b];

            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    mas[i, j] = 0;
                }
            }

            Random random = new Random();

            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    mas[i, j] = random.Next(100);
                }
            }

            double min = 0;
            double max = 0;
            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    if (mas[i, j] > max) max = mas[i, j];
                    if (mas[i, j] < min) min = mas[i, j];
                }
            }
            double size = max - min;

            bmp = new Bitmap(Diagram.Width, Diagram.Height);
            Graphics g = Graphics.FromImage(bmp); ;

            for (int i = 0; i < a; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    int color = (int)(((mas[i, j] - min) / size) * 255);
                    var maColor = Color.FromArgb(color,color,color);
                    SolidBrush brush_back = new SolidBrush(maColor);
                    g.FillRectangle(brush_back, 0, 0, Diagram.Width, Diagram.Height);
                }
            }
            /*
             * void CDynamicsWaveProcessDlg::Risunok(CDC *PicDc, vector<vector <double>> Mass, int xmin, int xmax, int ymin, int ymax, double xp, double yp)
    {
        double size, min, max;
        min = max = 0;
        for (int i = 0; i < Mass.size(); i++)
        {
            for (int j = 0; j < Mass[i].size(); j++)
            {
                if (Mass[i][j] > max) max = Mass[i][j];
                if (Mass[i][j] < min) min = Mass[i][j];
            }
        }
        size = max - min;
        for (int i = 0; i < Mass.size(); i++)
        {
            for (int j = 0; j < Mass[i].size(); j++)
            {
                int color = (int)(((Mass[i][j] - min) / size) * 255);
                PicDc->FillSolidRect((xp*((i)-xmin)), (yp*((j)-ymax)), xp, yp, RGB(color, color, color));
            }
        }
    }

             */
        }
    }
}
