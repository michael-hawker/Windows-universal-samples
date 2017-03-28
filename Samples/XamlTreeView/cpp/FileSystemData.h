//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************
#pragma once
using namespace Windows::UI::Xaml::Data;

namespace SDKTemplate
{
    [Windows::UI::Xaml::Data::Bindable]
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class FileSystemData sealed :
		public Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    public:
        FileSystemData(Platform::String^ name)
        {
            this->Name = name;
        }
		virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property Platform::String^ Name
        {
            Platform::String^ get() { return name; }
			void set(Platform::String^ value) {
				if (name != value) {
					name = value; OnPropertyChanged("Name");
				}
			}
        }

		property Platform::Boolean IsEditing
		{
			Platform::Boolean get() { return isEditing; }
			void set(Platform::Boolean value) {
				if (isEditing != value) {
					isEditing = value; OnPropertyChanged("IsEditing");
				}
			}
		}

		property Platform::Boolean IsDraggedOver
		{
			Platform::Boolean get() { return isDraggedOver; }
			void set(Platform::Boolean value) {
				if (isDraggedOver != value) {
					isDraggedOver = value; OnPropertyChanged("IsDraggedOver");
				}
			}
		}

        property bool IsFolder
        {
            Platform::Boolean get() { return isFolder; }
			void set(Platform::Boolean value) {
				if (isFolder != value) {
					isFolder = value; OnPropertyChanged("IsFolder");
				}
			}
        }
    private:
        Platform::String^ name = nullptr;
		Platform::Boolean isEditing = false;
		Platform::Boolean isDraggedOver = false;
		Platform::Boolean isFolder = false;
		void OnPropertyChanged(Platform::String^ propertyName)
		{
			PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
		}
    };
}

