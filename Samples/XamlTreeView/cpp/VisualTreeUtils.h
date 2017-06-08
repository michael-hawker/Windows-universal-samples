#pragma once

template<typename T>
T FindVisualParent(_In_ Windows::UI::Xaml::DependencyObject ^obj)
{
	Windows::UI::Xaml::DependencyObject^ parent = Windows::UI::Xaml::Media::VisualTreeHelper::GetParent(obj);
	while (parent != nullptr)
	{
		T typed = dynamic_cast<T>(parent);
		if (typed != nullptr)
		{
			return typed;
		}
		parent = Windows::UI::Xaml::Media::VisualTreeHelper::GetParent(parent);
	}
	return nullptr;
}

template<typename T>
T FindVisualChild(_In_ Windows::UI::Xaml::DependencyObject^ obj, _In_ Windows::UI::Xaml::DependencyObject^ excludeTree)
{
	if (obj == excludeTree)
	{
		return nullptr;
	}

	T typed = dynamic_cast<T>(obj);
	if (typed != nullptr)
	{
		return typed;
	}

	for (int childIndex = 0; childIndex < Windows::UI::Xaml::Media::VisualTreeHelper::GetChildrenCount(obj); ++childIndex)
	{
		T target = FindVisualChild<T>(Windows::UI::Xaml::Media::VisualTreeHelper::GetChild(obj, childIndex), excludeTree);
		if (target != nullptr)
		{
			return target;
		}
	}
	return nullptr;
}

template<typename T>
T FindVisualChild(_In_ Windows::UI::Xaml::DependencyObject^ obj)
{
	return FindVisualChild<T>(obj, nullptr);
}
