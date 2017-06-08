using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using OpenQA.Selenium.Appium.Windows;
using OpenQA.Selenium.Remote;
using System.Collections.Generic;
using OpenQA.Selenium.Appium;
using OpenQA.Selenium.Appium.MultiTouch;
using OpenQA.Selenium.Interactions;
using System.Threading;

namespace TreeViewTests
{
    [TestClass]
    public class TreeViewScenarios
    {
        #region Test Lifecycle Code
        // Note: append /wd/hub to the URL if you're directing the test at Appium
        protected const string WindowsApplicationDriverUrl = "http://127.0.0.1:4723";
        
        protected static WindowsDriver<WindowsElement> AppSession;

        [ClassInitialize]
        public static void Setup(TestContext context)
        {
            if (AppSession == null)
            {
                // Launch the test app
                DesiredCapabilities appCapabilities = new DesiredCapabilities();
                appCapabilities.SetCapability("app", "Microsoft.SDKSamples.XamlTreeView.CS_8wekyb3d8bbwe!App");
                appCapabilities.SetCapability("deviceName", "WindowsPC");
                AppSession = new WindowsDriver<WindowsElement>(new Uri(WindowsApplicationDriverUrl), appCapabilities);
                Assert.IsNotNull(AppSession);
                AppSession.Manage().Timeouts().ImplicitWait = TimeSpan.FromSeconds(4);
                
                // Maximize the test window
                AppSession.Manage().Window.Maximize();
            }
        }

        [ClassCleanup]
        public static void TearDown()
        {
            // Close the application and delete the session
            if (AppSession != null)
            {
                try
                {
                    AppSession.Close();

                    // This should throw if the window is closed successfully
                    var currentHandle = AppSession.CurrentWindowHandle;
                }
                catch { }

                AppSession.Quit();
                AppSession = null;
            }
        }

        [TestInitialize]
        public void Initialize()
        {
            // Reset the page state between tests
        }
        #endregion

        [TestMethod]
        public void TestMethod1()
        {
            var treeview = AppSession.FindElementByAccessibilityId("sampleTreeView");
            Assert.IsNotNull(treeview);

            // Get the top level elements
            var elements = treeview.FindElementsByClassName("ListViewItem");
            Assert.IsTrue(elements.Count > 0);

            // Get the WorkDocuments element (closed by default).
            var workDocumentsElement = elements[0];

            // Check the WorkDocuments element name.
            var workDocumentsElementParts = workDocumentsElement.FindElementsByClassName("TextBlock");
            var workDocumentsElementName = workDocumentsElementParts[workDocumentsElementParts.Count - 1].Text; // The last element contains the name
            Assert.AreEqual("Work Documents", workDocumentsElementName);

            // Checking the child element count is not obvious.
            // workDocumentsSubElements.Count does not actually reflect the number of child elements it has.
            // To check this, we must take the difference before and after opening the listview item.
            var elementCountSnapshot = elements.Count;
            Assert.IsTrue(elementCountSnapshot == 7);

            // Open the WorkDocument element
            workDocumentsElement.Click();

            // Re-retrieve the treeview elements to refresh the element count
            elements = treeview.FindElementsByClassName("ListViewItem");
            Assert.IsTrue(elements.Count > elementCountSnapshot);

            // Compare the updated element count to the snapshot from a moment ago.
            var workDocumentsElementsCount = elements.Count - elementCountSnapshot;

            // Since all of the elements are direct children of the treeview itself, we can discern
            // that the WorkDocuments child elements are indices 1 through 4.
            var workDocumentsElements = new List<AppiumWebElement>(elements).GetRange(1, workDocumentsElementsCount);
            Assert.IsTrue(workDocumentsElements.Count == 4);

            // Get the FeatureFunctionalSpec element (first child of WorkDocuments element)
            var featureFunctionalSpecElement = workDocumentsElements[0];

            // Check the FeatureFunctionalSpec element name.
            var featureFunctionalSpecElementParts = featureFunctionalSpecElement.FindElementsByClassName("TextBlock");
            var featureFunctionalSpecNameElement = featureFunctionalSpecElementParts[featureFunctionalSpecElementParts.Count - 1]; // The last element contains the name
            Assert.AreEqual("Feature Functional Spec", featureFunctionalSpecNameElement.Text);

            // Get the last element in the treeview
            var lastElement = elements[elements.Count - 1];

            // Drag/drop the FeatureFunctionalSpec element to the bottom of the TreeView
            AppSession.Mouse.MouseMove(featureFunctionalSpecElement.Coordinates);
            AppSession.Mouse.MouseDown(featureFunctionalSpecElement.Coordinates);

            // Offset the Y by 50px to put the element slightly below the last element before dropping
            AppSession.Mouse.MouseMove(lastElement.Coordinates, 0, 50);

            // Wait a tick for the action to complete.
            // Minimum supported time is 50ms (equal to one frame tick)
            Thread.Sleep(50);
            AppSession.Mouse.MouseUp(lastElement.Coordinates);

            // Re-retrieve the treeview elements to refresh it
            elements = treeview.FindElementsByClassName("ListViewItem");

            // Check the last element is now the featureFunctionalSpecElement
            lastElement = elements[elements.Count - 1];
            Assert.AreEqual(featureFunctionalSpecElement.Id, lastElement.Id);
        }
    }
}
