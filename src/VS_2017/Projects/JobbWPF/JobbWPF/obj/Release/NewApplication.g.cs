﻿#pragma checksum "..\..\NewApplication.xaml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "0A8F19308B4A19EA5C70DC63E0BA750C5286045B"
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
    /// NewApplication
    /// </summary>
    public partial class NewApplication : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 19 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox applicationValue;
        
        #line default
        #line hidden
        
        
        #line 20 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox companyValue;
        
        #line default
        #line hidden
        
        
        #line 21 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox deadlineValue;
        
        #line default
        #line hidden
        
        
        #line 22 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox motivationValue;
        
        #line default
        #line hidden
        
        
        #line 24 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox comboBox_townID;
        
        #line default
        #line hidden
        
        
        #line 25 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox comboBox_statusID;
        
        #line default
        #line hidden
        
        
        #line 27 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label lbl_townName;
        
        #line default
        #line hidden
        
        
        #line 28 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Label lbl_statusName;
        
        #line default
        #line hidden
        
        
        #line 29 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btnSave;
        
        #line default
        #line hidden
        
        
        #line 30 "..\..\NewApplication.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button btnCancel;
        
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
            System.Uri resourceLocater = new System.Uri("/Jobb;component/newapplication.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\NewApplication.xaml"
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
            
            #line 8 "..\..\NewApplication.xaml"
            ((JobbWPF.NewApplication)(target)).Loaded += new System.Windows.RoutedEventHandler(this.Window_Loaded);
            
            #line default
            #line hidden
            
            #line 8 "..\..\NewApplication.xaml"
            ((JobbWPF.NewApplication)(target)).Closing += new System.ComponentModel.CancelEventHandler(this.Window_Closing);
            
            #line default
            #line hidden
            return;
            case 2:
            this.applicationValue = ((System.Windows.Controls.TextBox)(target));
            
            #line 19 "..\..\NewApplication.xaml"
            this.applicationValue.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.applicationValue_TextChanged);
            
            #line default
            #line hidden
            return;
            case 3:
            this.companyValue = ((System.Windows.Controls.TextBox)(target));
            
            #line 20 "..\..\NewApplication.xaml"
            this.companyValue.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.companyValue_TextChanged);
            
            #line default
            #line hidden
            return;
            case 4:
            this.deadlineValue = ((System.Windows.Controls.TextBox)(target));
            
            #line 21 "..\..\NewApplication.xaml"
            this.deadlineValue.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.deadlineValue_TextChanged);
            
            #line default
            #line hidden
            return;
            case 5:
            this.motivationValue = ((System.Windows.Controls.TextBox)(target));
            
            #line 22 "..\..\NewApplication.xaml"
            this.motivationValue.TextChanged += new System.Windows.Controls.TextChangedEventHandler(this.motivationValue_TextChanged);
            
            #line default
            #line hidden
            return;
            case 6:
            this.comboBox_townID = ((System.Windows.Controls.ComboBox)(target));
            
            #line 24 "..\..\NewApplication.xaml"
            this.comboBox_townID.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.comboBox_townID_SelectionChanged);
            
            #line default
            #line hidden
            return;
            case 7:
            this.comboBox_statusID = ((System.Windows.Controls.ComboBox)(target));
            
            #line 25 "..\..\NewApplication.xaml"
            this.comboBox_statusID.SelectionChanged += new System.Windows.Controls.SelectionChangedEventHandler(this.comboBox_statusID_SelectionChanged);
            
            #line default
            #line hidden
            return;
            case 8:
            this.lbl_townName = ((System.Windows.Controls.Label)(target));
            return;
            case 9:
            this.lbl_statusName = ((System.Windows.Controls.Label)(target));
            return;
            case 10:
            this.btnSave = ((System.Windows.Controls.Button)(target));
            
            #line 29 "..\..\NewApplication.xaml"
            this.btnSave.Click += new System.Windows.RoutedEventHandler(this.btnSave_Clicked);
            
            #line default
            #line hidden
            return;
            case 11:
            this.btnCancel = ((System.Windows.Controls.Button)(target));
            
            #line 30 "..\..\NewApplication.xaml"
            this.btnCancel.Click += new System.Windows.RoutedEventHandler(this.btnCancel_Clicked);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

