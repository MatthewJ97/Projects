using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Input;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

using System.Windows.Threading;

namespace CsAssignment  {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public static int MapRows;
        public static int MapColumns;
        public static Grid Tiles;
        public static int tileSize = 64;
        public static Tile[,] TileDisplay;
        public static Dictionary<string, ImageBrush> ImageTable = new Dictionary<string, ImageBrush>();

        double windowWidth;
        double windowHeight;
        public enum ETileType { TERRAIN, WALL, OBJ};
        public static ETileType currentType = ETileType.TERRAIN;
        public MainWindow()
        {
            InitializeComponent();

            DispatcherTimer timer = new DispatcherTimer(new TimeSpan(0, 0, 1), DispatcherPriority.Normal, delegate
            {
                this.Time.Text = DateTime.Now.ToString("HH:mm:ss");
                this.Date.Text = DateTime.Now.ToShortDateString();
                
            }, this.Dispatcher);

            this.DataContext = this;
            windowHeight = this.Height;
            windowWidth = this.Width;
            MapColumns = 11;
            MapRows= 11;
            currentType = ETileType.TERRAIN;
            MapScroller.Height = Height;
            MapScroller.Width = Width;
            Tiles = new Grid();
            //TileDis.Background = Brushes.White;
            GenerateMap();

        }

        private void WindowResize(object sender, SizeChangedEventArgs e)
        {
            MapScroller.Height = Height;
            MapScroller.Width = Width;
        }
        //public static void Refresh(this UIElement uiElement)
        //{
        //    uiElement.Dispatcher.Invoke(DispatcherPriority.Render, EmptyDelegate);
        //}

        public void GenerateMap()
        {
            Tiles.RowDefinitions.Clear();
            Tiles.ColumnDefinitions.Clear();
            Tiles.Children.Clear();
            TileDisplay = new Tile[MapRows, MapColumns];
            for (int i = 0; i < MapRows; i++)
            {
                for (int j = 0; j < MapColumns; j++)
                {
                    TileDisplay[i, j] = new Tile(i, j);

                    Tile currentTile = TileDisplay[i, j];
                    currentTile.Width = tileSize;
                    currentTile.Height = tileSize;
                    currentTile.SetValue(Grid.ColumnProperty, j);
                    currentTile.SetValue(Grid.RowProperty, i);
                    
                    ColumnDefinition col = new ColumnDefinition();
                    col.Width = new GridLength(tileSize);
                    Tiles.ColumnDefinitions.Add(col);
                    TileDis.Children.Add(currentTile);
                    //Tiles.Children.Add(currentTile);
                }
                RowDefinition row = new RowDefinition();
                row.Height = new GridLength(tileSize);
                Tiles.RowDefinitions.Add(row);

            }
        }
        private void LoadImages( ) {
            ImageTable["Nothing"] = new ImageBrush(new BitmapImage(new Uri("Resources/TileSelect.png", UriKind.Relative)));
            ImageTable["Wall"] = new ImageBrush(new BitmapImage(new Uri("Resources/Tower01.png", UriKind.Relative)));
            ImageTable["Tower"] = new ImageBrush(new BitmapImage(new Uri("Resources/Tower02.png", UriKind.Relative)));

        }
        private void ExitCommand_CanExecute(object sender, CanExecuteRoutedEventArgs e) {
            e.CanExecute = true;
        }
        private void ExitCommand_Executed(object sender, ExecutedRoutedEventArgs e) {
            Application.Current.Shutdown();
        }

        private void TerrainType(object sender, RoutedEventArgs e) {
            currentType = ETileType.TERRAIN;
            TileSelect.Items.Clear();
            MenuItem Tower1 = new MenuItem();
            Tower1.Header = ImageTable["Nothing"];
            MenuItem Tower2 = new MenuItem();
            Tower2.Header = ImageTable["Wall"];
            MenuItem Tower3 = new MenuItem();
            Tower3.Header = ImageTable["Tower"];
            TileSelect.Items.Add(Tower1);
            TileSelect.Items.Add(Tower2);
            TileSelect.Items.Add(Tower3);

        }

        private void WallType(object sender, RoutedEventArgs e)
        {
            currentType = ETileType.WALL;
        }

        private void ObjType(object sender, RoutedEventArgs e)
        {
            currentType = ETileType.OBJ;
        }

        private void NewMap(object sender, MouseButtonEventArgs e)
        {
            NewMapWindow rowColChanger = new NewMapWindow();
            rowColChanger.ShowInTaskbar = false;
            rowColChanger.Owner = this;
            rowColChanger.Show();
        }
    }
    public static class Commands {
        public static readonly RoutedUICommand Exit = new RoutedUICommand
                        (
                                "Exit",
                                "Exit",
                                typeof(Commands),
                                new InputGestureCollection()
                                {
                                        new KeyGesture(Key.F4, ModifierKeys.Alt)
                                }
                        );

        //Define more commands here, just like the one above
    }

}
