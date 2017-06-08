using System.ComponentModel;

namespace SDKTemplate
{
    public class FileSystemData : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        public FileSystemData(string name)
        {
            this.Name = name;
        }

        private string _name;
        public string Name
        {
            get { return this._name; }
            set
            {
                if (value != _name)
                {
                    _name = value;
                    OnPropertyChanged("Name");
                }
            }
        }

        private bool _isFolder;
        public bool IsFolder
        {
            get { return this._isFolder; }
            set
            {
                if (value != _isFolder)
                {
                    _isFolder = value;
                    OnPropertyChanged("IsFolder");
                }
            }
        }

        private bool _isEditing;
        public bool IsEditing
        {
            get { return this._isEditing; }
            set
            {
                if (value != _isEditing)
                {
                    _isEditing = value;
                    OnPropertyChanged("IsEditing");
                }
            }
        }

        private bool _isDraggedOver;
        public bool IsDraggedOver
        {
            get { return this._isDraggedOver; }
            set
            {
                if (value != _isDraggedOver)
                {
                    _isDraggedOver = value;
                    OnPropertyChanged("IsDraggedOver");
                }
            }
        }

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
