﻿#region License

// Copyright Notice. Copyright 2008-2012 Northwestern University
// ("caBIG® Participant"). AIM Plugin for ClearCanvas conforms
// to caBIG® technical specifications and is part of the caBIG® initiative. The
// software subject to this notice and license includes human readable source
// code form, machine readable, binary, object code form and related
// documentation (the "caBIG® Software").
//
// This caBIG® Software License (the "License") is between the National Cancer
// Institute (NCI) and You. "You (or "Your") shall mean a person or an entity,
// and all other entities that control, are controlled by, or are under common
// control with the entity. "Control" for purposes of this definition means (i)
// the direct or indirect power to cause the direction or management of such
// entity, whether by contract or otherwise, or (ii) ownership of fifty percent
// (50%) or more of the outstanding shares, or (iii) beneficial ownership of
// such entity.
//
// Provided that You agree to the conditions described below, NCI grants You a
// non-exclusive, worldwide, perpetual, fully-paid-up, no-charge, irrevocable,
// transferable and royalty-free right and license in its rights in the caBIG®
// Software, including any copyright or patent rights therein, to (i) use,
// install, disclose, access, operate, execute, reproduce, copy, modify,
// translate, market, publicly display, publicly perform, and prepare
// derivative works of the caBIG® Software in any manner and for any purpose,
// and to have or permit others to do so; (ii) make, have made, use, practice,
// sell, and offer for sale, import, and/or otherwise dispose of caBIG®
// Software (or portions thereof); (iii) distribute and have distributed to and
// by third parties the caBIG® Software and any modifications and derivative
// works thereof; and (iv) sublicense the foregoing rights set out in (i), (ii)
// and (iii) to third parties, including the right to license such rights to
// further third parties. For sake of clarity, and not by way of limitation,
// NCI shall have no right of accounting or right of payment from You or Your
// sublicensees for the rights granted under this License. This License is
// granted at no charge to You. Your downloading, copying, modifying,
// displaying, distributing or use of caBIG® Software constitutes acceptance of
// all of the terms and conditions of this Agreement. If you do not agree to
// such terms and conditions, you have no right to download, copy, modify,
// display, distribute or use the caBIG® Software.
//
// 1. Your redistributions of the source code for the caBIG® Software must retain
// the above copyright notice, this list of conditions and the disclaimer and
// limitation of liability of Article 6 below. Your redistributions in object
// code form must reproduce the above copyright notice, this list of conditions
// and the disclaimer of Article 6 in the documentation and/or other materials
// provided with the distribution, if any.
//
// 2. Your end-user documentation included with the redistribution, if any, must
// include the following acknowledgment: "This product includes software
// developed by Vladimir Kleper, Skip Talbot and Pattanasak Mongkolwat,
// Northwestern University."
// If You do not include such end-user documentation, You shall include this
// acknowledgment in the caBIG® Software itself, wherever such third-party
// acknowledgments normally appear.
//
// 3. You may not use the names "Northwestern University",
// "The National Cancer Institute", "NCI", "Cancer Bioinformatics Grid" or
// "caBIG®" to endorse or promote products derived from this caBIG® Software.
// This License does not authorize You to use any trademarks, service marks,
// trade names, logos or product names of either caBIG® Participant, NCI or
// caBIG®, except as required to comply with the terms of this License.
//
// 4. For sake of clarity, and not by way of limitation, You are not prohibited by
// this License from incorporating this caBIG® Software into Your proprietary
// programs and into any third party proprietary programs. However, if You
// incorporate the caBIG® Software into third party proprietary programs, You
// agree that You are solely responsible for obtaining any permission from such
// third parties required to incorporate the caBIG® Software into such third
// party proprietary programs and for informing Your sublicensees, including
// without limitation Your end-users, of their obligation to secure any
// required permissions from such third parties before incorporating the caBIG®
// Software into such third party proprietary software programs. In the event
// that You fail to obtain such permissions, You agree to indemnify NCI for any
// claims against NCI by such third parties, except to the extent prohibited by
// law, resulting from Your failure to obtain such permissions.
//
// 5. For sake of clarity, and not by way of limitation, You may add Your own
// copyright statement to Your modifications and to the derivative works, and
// You may provide additional or different license terms and conditions in
// Your sublicenses of modifications of the caBIG® Software, or any derivative
// works of the caBIG® Software as a whole, provided Your use, reproduction,
// and distribution of the Work otherwise complies with the conditions stated
// in this License.
//
// 6. THIS caBIG® SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
// WARRANTIES (INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE
// DISCLAIMED. IN NO EVENT SHALL NCI OR THE NORTHWESTERN UNIVERSITY OR ITS
// AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS caBIG® SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#endregion

using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

using ClearCanvas.Common.Utilities;

namespace AIM.Annotation.View.WinForms
{
	public partial class AimDetailsControl : UserControl, INotifyPropertyChanged
	{
		private event EventHandler<ShowAimAnnotationEventArg> _showAnnotationClicked;
		private static readonly Color _labelColor = Color.FromKnownColor(KnownColor.ControlLight);
		private string _aimName;
		private string _aimUid;
		private string[] _aeList;
		private string[] _ioList;
		private bool _isAnnotationSelected;

		public AimDetailsControl()
		{
			InitializeComponent();

			_linkOpenImageAnnotation.DataBindings.Add("Enabled", this, "IsLinkEnabled", true, DataSourceUpdateMode.OnPropertyChanged);

			var aimNameBinding = new Binding("Text", this, "AimName", true);
			aimNameBinding.Format +=
				delegate(object sender, ConvertEventArgs e)
					{
						if (e.DesiredType == typeof (string))
						{
							e.Value = string.Format("Name: {0}", AimName);
							_lblAimName.Font = new Font(_lblAimName.Font.FontFamily, _lblAimName.Font.Size,
							                                 _isAnnotationSelected ? FontStyle.Bold : FontStyle.Regular, _lblAimName.Font.Unit);

						}
					};
			_lblAimName.DataBindings.Add(aimNameBinding);
			_lblAimName.ShowToolTipChanged += OnLblAimNameShowToolTipChanged;
		}

		void OnLblAimNameShowToolTipChanged(object sender, EventArgs e)
		{
			_toolTip.SetToolTip(_lblAimName, _lblAimName.ShowToolTip ? _lblAimName.ToolTipText : null);
		}

		internal event EventHandler<ShowAimAnnotationEventArg> ShowAimAnnotationClicked
		{
			add { _showAnnotationClicked += value; }
			remove { _showAnnotationClicked -= value; }
		}

		public string AimName
		{
			get { return _aimName; }
			internal set
			{
				if (_aimName == value)
					return;

				_aimName = value;
				NotifyPropertyChanged("AimName");
			}
		}

		public string ToolTipText
		{
			get { return _lblAimName.ToolTipText; }
			set { _lblAimName.ToolTipText = value; }
		}

		public string AimUid
		{
			get { return _aimUid; }
			internal set
			{
				if (_aimUid == value)
					return;

				_aimUid = value;
				NotifyPropertyChanged("AimUid");
				NotifyPropertyChanged("IsLinkEnabled");
			}
		}

		public bool IsLinkEnabled
		{
			get { return !string.IsNullOrEmpty(_aimUid); }
			internal set { }
		}

		public string[] AnnatomicEntities
		{
			get { return _aeList; }
			set
			{
				if (_aeList == value)
					return;

				_aeList = value;
				UpdateFlowPanel(_flowPanelAe, _aeList);
			}
		}

		public string[] ImagingObservations
		{
			get { return _ioList; }
			set
			{
				if (_ioList == value)
					return;

				_ioList = value;
				UpdateFlowPanel(_flowPanelIo, _ioList);
			}
		}

		public bool IsAnnotationSelected
		{
			get { return _isAnnotationSelected; }
			set
			{
				if (_isAnnotationSelected == value)
					return;

				_isAnnotationSelected = value;
				NotifyPropertyChanged("AimName");
			}
		}

		private void UpdateFlowPanel(FlowLayoutPanel flowPanel, string[] listOfValues)
		{
			flowPanel.SuspendLayout();
			flowPanel.Controls.Clear();

			if (listOfValues != null)
			{
				foreach (var s in listOfValues)
				{
					var label = new Label();
					label.AutoEllipsis = true;
					if (flowPanel.Controls.Count != 0 && flowPanel.Controls[flowPanel.Controls.Count - 1].BackColor != _labelColor)
						label.BackColor = _labelColor;
					label.Size = new Size(flowPanel.ClientSize.Width - label.Margin.Horizontal, 17);
					label.TabIndex = flowPanel.Controls.Count;
					label.Text = s;
					label.TextAlign = ContentAlignment.MiddleLeft;

					flowPanel.Controls.Add(label);
				}
			}
			flowPanel.ResumeLayout();
		}

		protected void RemoveLabelFromFlowPanel(FlowLayoutPanel flowPanel)
		{
			if (flowPanel.Controls.Count > 0)
				flowPanel.Controls.RemoveAt(flowPanel.Controls.Count - 1);
			flowPanel.Update();
		}

		private void OnTableLayoutPanelSizeChanged(object sender, EventArgs e)
		{
			_linkOpenImageAnnotation.Location = new Point(_linkOpenImageAnnotation.Location.X, _tableLayoutPanel.Location.Y + _tableLayoutPanel.Size.Height + 8);
		}

		#region INotifyPropertyChanged Members

		public event PropertyChangedEventHandler PropertyChanged;

		#endregion

		private void NotifyPropertyChanged(String info)
		{
			EventsHelper.Fire(PropertyChanged, this, new PropertyChangedEventArgs(info));
		}

		private void OnFlowPanelAeClientSizeChanged(object sender, EventArgs e)
		{
			AdjustChildrenControlWidth(_flowPanelAe);
		}

		private void OnFlowPanelIoClientSizeChanged(object sender, EventArgs e)
		{
			AdjustChildrenControlWidth(_flowPanelIo);
		}

		private static void AdjustChildrenControlWidth(Control parent)
		{
			foreach (Control control in parent.Controls)
			{
				control.Width = parent.ClientSize.Width - control.Margin.Horizontal;
			}
		}

		private void OnOpenAnnotationLinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
		{
			EventsHelper.Fire(_showAnnotationClicked, this, new ShowAimAnnotationEventArg(_aimUid));
		}
	}

	internal class ShowAimAnnotationEventArg : EventArgs
	{
		public ShowAimAnnotationEventArg(string aimUid)
		{
			AimUid = aimUid;
		}

		public string AimUid { get; set; }
	}
}
