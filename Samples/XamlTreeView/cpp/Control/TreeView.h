#pragma once
#include "TreeNode.h"
#include "ViewModel.h"
#include "TreeViewItem.h"

namespace TreeViewControl {
    public ref class TreeViewEventArgs sealed
    {
    public:
        TreeViewEventArgs() {}

        property Object^ Item
        {
            Object^ get() { return item; };
            void set(Object^ value) { item = value; };
        }

        property bool IsHandled
        {
            bool get() { return isHandled; };
            void set(bool value) { isHandled = value; };
        }

		property TreeNode^ ItemBelow
		{
			TreeNode^ get() { return itemBelow; };
			void set(TreeNode^ value) { itemBelow = value; };
		}

		property TreeNode^ ItemAbove
		{
			TreeNode^ get() { return itemAbove; };
			void set(TreeNode^ value) { itemAbove = value; };
		}

    private:
        Object^ item = nullptr;
        bool isHandled = false;
		TreeNode^ itemBelow;
		TreeNode^ itemAbove;
	};


    ref class TreeView;
    [Windows::Foundation::Metadata::WebHostHidden]
    public delegate void TreeViewEventHandler(TreeView^ sender, TreeViewEventArgs^ args);

    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class TreeView sealed : Windows::UI::Xaml::Controls::ListView
    {
    public:
        TreeView();

		//This event is used to expose an alternative to itemclick to developers.
		event TreeViewEventHandler^ TreeViewItemClick;
		//This event is used to expose an alternative to item Drop to developers.
		event TreeViewEventHandler^ TreeViewDrop;

        //This RootNode property is used by the TreeView to handle additions into the TreeView and
        //accurate VectorChange with multiple 'root level nodes'. This node will not be placed
        //in the flatViewModel, but has it's vectorchanged event hooked up to flatViewModel's
        //handler.
        property TreeNode^ RootNode
        {
            TreeNode^ get() { return rootNode; };
        }

        void TreeView_OnItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ args);

        void TreeView_DragItemsStarting(Platform::Object^ sender, Windows::UI::Xaml::Controls::DragItemsStartingEventArgs^ e);

        void TreeView_DragItemsCompleted(Windows::UI::Xaml::Controls::ListViewBase^ sender, Windows::UI::Xaml::Controls::DragItemsCompletedEventArgs^ args);

        void ExpandNode(TreeNode^ targetNode);

        void CollapseNode(TreeNode^ targetNode);

    protected:
        void PrepareContainerForItemOverride(DependencyObject^ element, Object^ item) override;
        Windows::UI::Xaml::DependencyObject^ GetContainerForItemOverride() override;

        void OnDrop(Windows::UI::Xaml::DragEventArgs^ e) override;
        void OnDragOver(Windows::UI::Xaml::DragEventArgs^ e) override;

    private:
        TreeNode^ rootNode;
        ViewModel^ flatViewModel;

    internal:
        TreeViewItem^ draggedTreeViewItem;
    };
}

