﻿#pragma checksum "..\..\ViewSpecificApplications.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "ADDAA2551A394A5DEAE6A6009AA1320039F0B52B"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using JobbWPF;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;


namespace JobbWPF {
    
    
    /// <summary>
    /// ViewSpecificApplications
    /// </summary>
    public partial class ViewSpecificApplications : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 26 "..\..\ViewSpecificApplications.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox textBoxJobTitle;
        
        #line default
        #line hidden
        
        
        #line 27 "..\..\ViewSpecificApplications.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox textBoxCompanyName;
        
        #line default
        #line hidden
        
        
        #line 28 "..\..\ViewSpecificApplications.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox comboBoxCityName;
        
        #line default
        #line hidden
        
        
        #line 29 "..\..\ViewSpecificApplications.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox comboBoxStatusName;
        
        #line default
        #line hidden
        
        
        #line 30 "..\..\ViewSpecificApplications.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox textBoxDeadline;
        
        #line default
        #line hidden
        
        
        #line 31 "..\..\ViewSpecificApplications.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox textBoxMotivation;
        
        #line default
        #line hidden
        
        
        #line 32 "..\..\ViewSpecificApplications.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btnSearch;
        
        #line default
        #line hidden
        
        
        #line 33 "..\..\ViewSpecificApplications.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.DataGrid dataGrid;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/Jobb;component/viewspecificapplications.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\ViewSpecificApplications.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            
            #line 8 "..\..\ViewSpecificApplications.xaml"
            ((JobbWPF.ViewSpecificApplications)(target)).Loaded += new System.Windows.RoutedEventHandler(this.Window_Loaded);
            
            #line default
            #line hidden
            
            #line 8 "..\..\ViewSpecificApplications.xaml"
            ((JobbWPF.ViewSpecificApplications)(target)).SizeChanged += new System.Windows.SizeChangedEventHandler(this.Window_SizeChanged);
            
            #line default
            #line hidden
            return;
            case 2:
            this.textBoxJobTitle = ((System.Windows.Controls.TextBox)(target));
            
            #line 26 "..\..\ViewSpecificApplications.xaml"
            this.textBoxJobTitle.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.textBoxJobTitle_TextChanged);
            
            #line default
            #line hidden
            return;
            case 3:
            this.textBoxCompanyName = ((System.Windows.Controls.TextBox)(target));
            
            #line 27 "..\..\ViewSpecificApplications.xaml"
            this.textBoxCompanyName.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.textBoxCompanyName_TextChanged);
            
            #line default
            #line hidden
            return;
            case 4:
            this.comboBoxCityName = ((System.Windows.Controls.ComboBox)(target));
            
            #line 28 "..\..\ViewSpecificApplications.xaml"
            this.comboBoxCityName.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.comboBoxCityName_SelectionChanged);
            
            #line default
            #line hidden
            return;
            case 5:
            this.comboBoxStatusName = ((System.Windows.Controls.ComboBox)(target));
            
            #line 29 "..\..\ViewSpecificApplications.xaml"
            this.comboBoxStatusName.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.comboBoxStatusName_SelectionChanged);
            
            #line default
            #line hidden
            return;
            case 6:
            this.textBoxDeadline = ((System.Windows.Controls.TextBox)(target));
            
            #line 30 "..\..\ViewSpecificApplications.xaml"
            this.textBoxDeadline.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.textBoxDeadline_TextChanged);
            
            #line default
            #line hidden
            return;
            case 7:
            this.textBoxMotivation = ((System.Windows.Controls.TextBox)(target));
            
            #line 31 "..\..\ViewSpecificApplications.xaml"
            this.textBoxMotivation.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.textBoxMotivation_TextChanged);
            
            #line default
            #line hidden
            return;
            case 8:
            this.btnSearch = ((System.Windows.Controls.Button)(target));
            
            #line 32 "..\..\ViewSpecificApplications.xaml"
            this.btnSearch.Click += new System.Windows.RoutedEventHandler(this.btnSearch_Click);
            
            #line default
            #line hidden
            return;
            case 9:
            this.dataGrid = ((System.Windows.Controls.DataGrid)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}
