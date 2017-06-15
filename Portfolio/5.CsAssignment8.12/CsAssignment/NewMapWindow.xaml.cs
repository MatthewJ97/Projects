
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace CsAssignment

{
    /// <summary>
    /// Interaction logic for NewMapWindow.xaml
    /// </summary>
    public partial class NewMapWindow : Window
    {
        public NewMapWindow()
        {
            InitializeComponent();
            Rows.Text = MainWindow.MapRows.ToString();
            Columns.Text = MainWindow.MapColumns.ToString();
        }

        private void CreateMap(object sender, RoutedEventArgs e)
        {
            MainWindow mainWindow = Application.Current.MainWindow as MainWindow;
            if (mainWindow != null && Columns.Text.Length != 0 && Rows.Text.Length != 0)
            {
                if (MainWindow.MapRows < 5 || MainWindow.MapColumns < 5)
                {
                    MessageBox.Show("Map size must be at least 5 x 5 ", "ERROR MAP TO SMALL", MessageBoxButton.OK, MessageBoxImage.Error);
                    MainWindow.MapColumns = 5;
                    MainWindow.MapRows = 5;
                    Columns.Text = "5";
                    Rows.Text = "5";

                }
                else
                {
                    MainWindow.MapColumns = int.Parse(Columns.Text);
                    MainWindow.MapRows = int.Parse(Rows.Text);
                    mainWindow.GenerateMap();
                    Close();
                }
            }
        }
        private void CloseWindow(object sender, RoutedEventArgs e)
        {
            Close();
        }
        private void Columns_TextChanged(object sender, TextChangedEventArgs e)
        {

        }

        private void Rows_TextChanged(object sender, TextChangedEventArgs e)
        {

        }
    }
}
