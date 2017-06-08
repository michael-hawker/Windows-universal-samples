using System;
using System.Diagnostics;
using Windows.System;
using TreeViewControl;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace SDKTemplate
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            TreeNode workFolder = CreateFolderNode("Work Documents");
            workFolder.Add(CreateFileNode("Feature Functional Spec"));
            workFolder.Add(CreateFileNode("Feature Schedule"));
            workFolder.Add(CreateFileNode("Overall Project Plan"));
            workFolder.Add(CreateFileNode("Feature Resource allocation"));
            sampleTreeView.RootNode.Add(workFolder);

            TreeNode remodelFolder = CreateFolderNode("Home Remodel");
            remodelFolder.IsExpanded = true;
            remodelFolder.Add(CreateFileNode("Contactor Contact Information"));
            remodelFolder.Add(CreateFileNode("Paint Color Scheme"));
            remodelFolder.Add(CreateFileNode("Flooring woodgrain types"));
            remodelFolder.Add(CreateFileNode("Kitchen cabinet styles"));

            TreeNode personalFolder = CreateFolderNode("Personal Documents");
            personalFolder.IsExpanded = true;
            personalFolder.Add(remodelFolder);

            sampleTreeView.RootNode.Add(personalFolder);

            sampleTreeView.ContainerContentChanging += SampleTreeView_ContainerContentChanging;
        }

        private void SampleTreeView_ContainerContentChanging(ListViewBase sender, ContainerContentChangingEventArgs args)
        {
            var node = args.Item as TreeNode;
            if (node != null)
            {
                var data = node.Data as FileSystemData;
                if (data != null)
                {
                    args.ItemContainer.AllowDrop = data.IsFolder;
                }
            }

            args.ItemContainer.KeyDown += ItemContainer_KeyDown;
            args.ItemContainer.DoubleTapped += ItemContainer_DoubleTapped;
        }

        private static TreeNode CreateFileNode(string name)
        {
            return new TreeNode() { Data = new FileSystemData(name) };
        }

        private static TreeNode CreateFolderNode(string name)
        {
            return new TreeNode() { Data = new FileSystemData(name) { IsFolder = true } };
        }

        /**
         * Tied to TreeViewList Tapped event to detect clicks/taps on control and determine node from that.
         */
        private void ListControl_Tapped(object sender, TappedRoutedEventArgs e)
        {
            var control = sender as TreeView;
            var source = e.OriginalSource as DependencyObject;
            var parent = VisualTreeUtils.FindVisualParent<TreeViewItem>(source);

            if (parent != null)
            {
                var item = control?.ItemFromContainer(parent) as TreeNode;

                var node = item?.Data as FileSystemData;

                Debug.WriteLine("Tapped on " + node?.Name);
            }
        }

        /**
         * The following two functions control the behavior of showing controls when hovering over an item using the VSM.
         */
        private void UserControl_PointerEntered(object sender, PointerRoutedEventArgs e)
        { 
            VisualStateManager.GoToState((Control)sender, "HoverInlineCommandsVisible", true);
        }

        private void UserControl_PointerExited(object sender, PointerRoutedEventArgs e)
        {
            VisualStateManager.GoToState((Control)sender, "HoverInlineCommandsInvisible", true);
        }

        /**
         * The following two functions control the behavior of switching to edit mode and focusing on the textbox when the text is clicked on.
         */
        private void TextBlock_PointerReleased(object sender, PointerRoutedEventArgs e)
        {
            var item = ((FrameworkElement)e.OriginalSource).DataContext as TreeNode;

            var node = item?.Data as FileSystemData;

            if (node != null)
            {
                Debug.WriteLine("Click on " + node.Name);

                node.IsEditing = true;

                var grid = VisualTreeUtils.FindVisualParent<Grid>((DependencyObject) sender);
                var textbox = grid.Tag as TextBox;
                textbox?.Focus(FocusState.Keyboard);
                textbox?.SelectAll();
            }
        }

        private void editorBox_LostFocus(object sender, RoutedEventArgs e)
        {
            var item = ((FrameworkElement)e.OriginalSource).DataContext as TreeNode;

            var node = item?.Data as FileSystemData;

            if (node != null)
            {
                Debug.WriteLine("Focus Lost on " + node.Name);

                node.IsEditing = false;
            }
        }

        /*
         * Start Editing when user hits enter on treeview item.
         */
        private void ItemContainer_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == VirtualKey.Enter)
            {
                var item = ((TreeViewItem)sender).Content as TreeNode;

                var node = item?.Data as FileSystemData;

                Debug.WriteLine("Enter Edit on " + node?.Name);

                if (node != null)
                {
                    node.IsEditing = true;

                    var grid = VisualTreeUtils.FindVisualChild<Grid>((DependencyObject)sender);
                    var textbox = grid.Tag as TextBox;
                    textbox?.Focus(FocusState.Keyboard);
                    textbox?.SelectAll();
                }
            }
        }

        /*
         * Commit change when the user hits enter key in textbox.
         */
        private void editorBox_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            if (e.Key == VirtualKey.Enter)
            {
                var item = ((FrameworkElement)e.OriginalSource).DataContext as TreeNode;

                var node = item?.Data as FileSystemData;

                Debug.WriteLine("Enter Exit on " + node?.Name);

                if (node != null)
                {
                    node.IsEditing = false;

                    e.Handled = true;
                    // Note: Will also cause a lost focus event, but we need that for mouse interaction too (clicking away)
                }
            }
        }

        /*
         * Allow double-clicking on entire row in order to enter edit mode (in case text is cleared)
         */
        private void ItemContainer_DoubleTapped(object sender, DoubleTappedRoutedEventArgs e)
        {
            var item = ((TreeViewItem)sender).Content as TreeNode;

            var node = item?.Data as FileSystemData;

            if (node != null)
            {
                Debug.WriteLine("Double Click Edit on " + node.Name);

                node.IsEditing = true;

                var grid = VisualTreeUtils.FindVisualChild<Grid>((DependencyObject)sender);
                var textbox = grid.Tag as TextBox;
                textbox?.Focus(FocusState.Keyboard);
                textbox?.SelectAll();
            }
        }

        private void ListControl_DragItemsStarting(object sender, DragItemsStartingEventArgs e)
        {
            // TODO: Bring from C++
        }
    }
}