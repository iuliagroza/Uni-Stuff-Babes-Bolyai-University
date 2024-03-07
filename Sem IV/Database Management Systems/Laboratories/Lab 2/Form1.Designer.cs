namespace Lab2
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.parentTableView = new System.Windows.Forms.DataGridView();
            this.childTableView = new System.Windows.Forms.DataGridView();
            this.updateButton = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.parentTableView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.childTableView)).BeginInit();
            this.SuspendLayout();

            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.AutoSize = true;
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.label1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.label2, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.parentTableView, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.childTableView, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.updateButton, 1, 2);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 509F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 88F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1108, 620);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.label1.Location = new System.Drawing.Point(3, 7);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(548, 16);
            this.label1.TabIndex = 0;
            this.label1.Text = "Parent Table";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.label2.Location = new System.Drawing.Point(557, 7);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(548, 16);
            this.label2.TabIndex = 1;
            this.label2.Text = "Child Table";
            // 
            // parentTableView
            // 
            this.parentTableView.AllowUserToAddRows = false;
            this.parentTableView.AllowUserToDeleteRows = false;
            this.parentTableView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.parentTableView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.parentTableView.Location = new System.Drawing.Point(3, 26);
            this.parentTableView.Name = "parentTableView";
            this.parentTableView.ReadOnly = true;
            this.parentTableView.RowHeadersWidth = 51;
            this.parentTableView.RowTemplate.Height = 24;
            this.parentTableView.Size = new System.Drawing.Size(548, 503);
            this.parentTableView.TabIndex = 2;
            this.parentTableView.SelectionChanged += new System.EventHandler(this.parentTableView_SelectionChanged);
            // 
            // childTableView
            // 
            this.childTableView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.childTableView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.childTableView.Location = new System.Drawing.Point(557, 26);
            this.childTableView.Name = "childTableView";
            this.childTableView.RowHeadersWidth = 51;
            this.childTableView.RowTemplate.Height = 24;
            this.childTableView.Size = new System.Drawing.Size(548, 503);
            this.childTableView.TabIndex = 3;
            this.childTableView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.childTableView_DataError);
            // 
            // updateButton
            // 
            this.updateButton.BackColor = System.Drawing.Color.Beige;
            this.updateButton.Location = new System.Drawing.Point(557, 535);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(118, 60);
            this.updateButton.TabIndex = 4;
            this.updateButton.Text = "Update Database";
            this.updateButton.UseVisualStyleBackColor = false;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Chocolate;
            this.ClientSize = new System.Drawing.Size(1108, 620);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.parentTableView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.childTableView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.DataGridView parentTableView;
        private System.Windows.Forms.DataGridView childTableView;
        private System.Windows.Forms.Button updateButton;
    }
}