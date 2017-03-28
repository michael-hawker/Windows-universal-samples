//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "BooleanToVisibilityConverter.h"
#include "GlyphConverter.h"
#include "FileSystemData.h"

namespace SDKTemplate
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void SampleTreeView_ContainerContentChanging(Windows::UI::Xaml::Controls::ListViewBase^ sender, Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs^ args);
        TreeViewControl::TreeNode^ CreateFileNode(Platform::String^ name);
        TreeViewControl::TreeNode^ CreateFolderNode(Platform::String^ name);
		//void SampleTreeView_Loaded(Platform::Object ^ sender, Windows::UI::Xaml::RoutedEventArgs ^ e);
		void UserControl_PointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void UserControl_PointerExited(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void editorBox_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
		void editorBox_LostFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ItemContainer_KeyDown(Platform::Object ^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs ^ e);
		void TextBlock_PointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
		void ListControl_Tapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
		void OnDoubleTapped(Platform::Object ^sender, Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs ^e);
    };
}
