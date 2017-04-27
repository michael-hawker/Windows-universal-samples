using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Media;

namespace SDKTemplate
{
    public static class VisualTreeUtils
    {
        public static T FindVisualParent<T>(DependencyObject obj) where T : DependencyObject
        {
            DependencyObject parent = VisualTreeHelper.GetParent(obj);
            while (parent != null)
            {
                T typed = parent as T;
                if (typed != null)
                {
                    return typed;
                }
                parent = VisualTreeHelper.GetParent(parent);
            }
            return default(T);
        }

        public static T FindVisualChild<T>(DependencyObject obj, DependencyObject excludeTree) where T : DependencyObject
        {
            if (obj == excludeTree)
            {
                return default(T);
            }

            T typed = obj as T;
            if (typed != null)
            {
                return typed;
            }

            for (int childIndex = 0; childIndex < VisualTreeHelper.GetChildrenCount(obj); ++childIndex)
            {
                T target = FindVisualChild<T>(VisualTreeHelper.GetChild(obj, childIndex), excludeTree);
                if (target != null)
                {
                    return target;
                }
            }
            return default(T);
        }
        public static T FindVisualChild<T>(DependencyObject obj) where T : DependencyObject
        {
            return FindVisualChild<T>(obj, null);
        }

    }
}
