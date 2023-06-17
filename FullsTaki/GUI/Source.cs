using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using GUI.Forms;

namespace GUI
{
    internal static class Source
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Login());
        }

        public static bool CheckInput(Control.ControlCollection controlCollection)
        {
            foreach (Control c in controlCollection)
            {
                if (c is GroupBox || c is Panel)
                {
                    bool filled = CheckInput(c.Controls);
                    if (!filled)
                    {
                        return false;
                    }
                }

                if (c is TextBox textBox)
                {
                    if (textBox.Text == "")
                    {
                        return false;
                    }
                }

                if (c is ListBox listBox)
                {
                    if (listBox.SelectionMode != SelectionMode.None)
                    {
                        if (listBox.SelectedIndex == -1)
                        {
                            return false;
                        }
                    }
                }
            }
            return true;
        }
    }
}
