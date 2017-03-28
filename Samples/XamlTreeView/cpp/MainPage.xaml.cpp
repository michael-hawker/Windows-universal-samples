//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "VisualTreeUtils.h"

using namespace SDKTemplate;
using namespace TreeViewControl;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
    InitializeComponent();

    TreeNode^ workFolder = CreateFolderNode("Work Documents");
    workFolder->Append(CreateFileNode("Feature Functional Spec"));
    workFolder->Append(CreateFileNode("Feature Schedule"));
    workFolder->Append(CreateFileNode("Overall Project Plan"));
    workFolder->Append(CreateFileNode("Feature Resource allocation"));
    sampleTreeView->RootNode->Append(workFolder);

    auto remodelFolder = CreateFolderNode("Home Remodel");
    remodelFolder->IsExpanded = true;
    remodelFolder->Append(CreateFileNode("Contactor Contact Information"));
    remodelFolder->Append(CreateFileNode("Paint Color Scheme"));
    remodelFolder->Append(CreateFileNode("Flooring woodgrain types"));
    remodelFolder->Append(CreateFileNode("Kitchen cabinet styles"));

    auto personalFolder = CreateFolderNode("Personal Documents");
    personalFolder->IsExpanded = true;
    personalFolder->Append(remodelFolder);
    sampleTreeView->RootNode->Append(personalFolder);

    sampleTreeView->ContainerContentChanging += ref new TypedEventHandler<ListViewBase^, ContainerContentChangingEventArgs^>(this, &MainPage::SampleTreeView_ContainerContentChanging);
}

void MainPage::SampleTreeView_ContainerContentChanging(ListViewBase^ sender, ContainerContentChangingEventArgs^ args)
{
    auto node = dynamic_cast<TreeNode^>(args->Item);
    if (node != nullptr)
    {
        auto data = dynamic_cast<FileSystemData^>(node->Data);
        if (data != nullptr)
        {
			if (data->IsFolder)
			{
				args->ItemContainer->Background = ref new SolidColorBrush(Windows::UI::Colors::Blue);
			}

            args->ItemContainer->AllowDrop = data->IsFolder;
        }
    }

	// Note: Would want to save these tokens to unload events later
	auto keydownRegistrationToken = args->ItemContainer->KeyDown += ref new Windows::UI::Xaml::Input::KeyEventHandler(this, &MainPage::ItemContainer_KeyDown);
	auto doubleClickRegistrationToken = args->ItemContainer->DoubleTapped += ref new Windows::UI::Xaml::Input::DoubleTappedEventHandler(this, &MainPage::OnDoubleTapped);
}

TreeNode^ MainPage::CreateFileNode(String^ name)
{
    auto data = ref new FileSystemData(name);
    auto treeNode = ref new TreeNode();
    treeNode->Data = data;
    return treeNode;
}

TreeNode^ MainPage::CreateFolderNode(String^ name)
{
    auto data = ref new FileSystemData(name);
    data->IsFolder = true;
    auto treeNode = ref new TreeNode();
    treeNode->Data = data;
    return treeNode;
}

/**
* Tied to TreeViewList Tapped event to detect clicks/taps on control and determine node from that.
*/
void MainPage::ListControl_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e)
{
	auto control = dynamic_cast<TreeView^>(sender);
	auto source = dynamic_cast<DependencyObject^>(e->OriginalSource);
	auto parent = FindVisualParent<TreeViewItem^>(source);

	if (parent != nullptr)
	{
		auto item = dynamic_cast<TreeNode^>(control->ItemFromContainer(parent));

		auto node = dynamic_cast<FileSystemData^>(item->Data);
		::OutputDebugString(L"Tapped on ");
		::OutputDebugString(node->Name->Data());
		::OutputDebugString(L"\n");
	}
}

/**
* The following two functions control the behavior of showing controls when hovering over an item using the VSM.
*/
void MainPage::UserControl_PointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	VisualStateManager::GoToState(static_cast<Control^>(sender), "HoverInlineCommandsVisible", true);
}


void MainPage::UserControl_PointerExited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	VisualStateManager::GoToState(static_cast<Control^>(sender), "HoverInlineCommandsInvisible", true);
}

/**
* The following two functions control the behavior of switching to edit mode and focusing on the textbox when the text is clicked on.
*/
void MainPage::TextBlock_PointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	auto item = dynamic_cast<TreeNode^>(dynamic_cast<FrameworkElement^>(e->OriginalSource)->DataContext);

	auto node = dynamic_cast<FileSystemData^>(item->Data);
	::OutputDebugString(L"Click on ");
	::OutputDebugString(node->Name->Data());
	::OutputDebugString(L"\n");
	node->IsEditing = true;

	auto grid = FindVisualParent<Grid^>(dynamic_cast<DependencyObject^>(sender));
	auto textbox = dynamic_cast<TextBox^>(grid->Tag);
	textbox->Focus(Windows::UI::Xaml::FocusState::Keyboard);
	textbox->SelectAll();
}

void MainPage::editorBox_LostFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto item = dynamic_cast<TreeNode^>(dynamic_cast<FrameworkElement^>(e->OriginalSource)->DataContext);

	auto node = dynamic_cast<FileSystemData^>(item->Data);
	::OutputDebugString(L"Focus lost on ");
	::OutputDebugString(node->Name->Data());
	::OutputDebugString(L"\n");
	node->IsEditing = false;
}

/*
* Start Editing when user hits enter on treeview item.
*/
void MainPage::ItemContainer_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == Windows::System::VirtualKey::Enter)
	{
		auto item = dynamic_cast<TreeNode^>(dynamic_cast<TreeViewItem^>(sender)->Content);

		auto node = dynamic_cast<FileSystemData^>(item->Data);
		::OutputDebugString(L"Enter Edit on ");
		::OutputDebugString(node->Name->Data());
		::OutputDebugString(L"\n");
		node->IsEditing = true;

		auto grid = FindVisualChild<Grid^>(dynamic_cast<DependencyObject^>(sender));
		auto textbox = dynamic_cast<TextBox^>(grid->Tag);
		textbox->Focus(Windows::UI::Xaml::FocusState::Keyboard);
		textbox->SelectAll();
	}
}

/*
* Commit change when the user hits enter key in textbox.
*/
void MainPage::editorBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == Windows::System::VirtualKey::Enter)
	{
		auto item = dynamic_cast<TreeNode^>(dynamic_cast<FrameworkElement^>(e->OriginalSource)->DataContext);

		auto node = dynamic_cast<FileSystemData^>(item->Data);
		::OutputDebugString(L"Enter Exit on ");
		::OutputDebugString(node->Name->Data());
		::OutputDebugString(L"\n");
		node->IsEditing = false;

		e->Handled = true;
		// Note: Will also cause a lost focus event, but we need that for mouse interaction too (clicking away)
	}
}

/*
* Allow double-clicking on entire row in order to enter edit mode (in case text is cleared)
*/
void MainPage::OnDoubleTapped(Platform::Object ^sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs ^e)
{
	auto item = dynamic_cast<TreeNode^>(dynamic_cast<TreeViewItem^>(sender)->Content);

	auto node = dynamic_cast<FileSystemData^>(item->Data);
	::OutputDebugString(L"Double Click Edit on ");
	::OutputDebugString(node->Name->Data());
	::OutputDebugString(L"\n");
	node->IsEditing = true;

	auto grid = FindVisualChild<Grid^>(dynamic_cast<DependencyObject^>(sender));
	auto textbox = dynamic_cast<TextBox^>(grid->Tag);
	textbox->Focus(Windows::UI::Xaml::FocusState::Keyboard);
	textbox->SelectAll();
}
