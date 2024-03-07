namespace Lab1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.VideoGameCompaniesView = new System.Windows.Forms.DataGridView();
            this.GamesView = new System.Windows.Forms.DataGridView();
            this.VideoGameCompaniesLabel = new System.Windows.Forms.Label();
            this.GamesLabel = new System.Windows.Forms.Label();
            this.GidLabel = new System.Windows.Forms.Label();
            this.NameLabel = new System.Windows.Forms.Label();
            this.DescriptionLabel = new System.Windows.Forms.Label();
            this.YearOfReleaseLabel = new System.Windows.Forms.Label();
            this.NoOfPlayersLabel = new System.Windows.Forms.Label();
            this.RatingLabel = new System.Windows.Forms.Label();
            this.NoOfDownloadsLabel = new System.Windows.Forms.Label();
            this.VidLabel = new System.Windows.Forms.Label();
            this.GenidLabel = new System.Windows.Forms.Label();
            this.gidText = new System.Windows.Forms.TextBox();
            this.nameText = new System.Windows.Forms.TextBox();
            this.descriptionText = new System.Windows.Forms.TextBox();
            this.yearOfReleaseText = new System.Windows.Forms.TextBox();
            this.noOfPlayersText = new System.Windows.Forms.TextBox();
            this.ratingText = new System.Windows.Forms.TextBox();
            this.noOfDownloadsText = new System.Windows.Forms.TextBox();
            this.vidText = new System.Windows.Forms.TextBox();
            this.genidText = new System.Windows.Forms.TextBox();
            this.addButton = new System.Windows.Forms.Button();
            this.removeButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            ((System.ComponentModel.ISupportInitialize)(this.VideoGameCompaniesView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GamesView)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // VideoGameCompaniesView
            // 
            this.VideoGameCompaniesView.AllowUserToAddRows = false;
            this.VideoGameCompaniesView.AllowUserToDeleteRows = false;
            this.VideoGameCompaniesView.BackgroundColor = System.Drawing.Color.Snow;
            this.VideoGameCompaniesView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.VideoGameCompaniesView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.VideoGameCompaniesView.Location = new System.Drawing.Point(3, 22);
            this.VideoGameCompaniesView.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.VideoGameCompaniesView.Name = "VideoGameCompaniesView";
            this.VideoGameCompaniesView.ReadOnly = true;
            this.VideoGameCompaniesView.RowHeadersWidth = 51;
            this.VideoGameCompaniesView.RowTemplate.Height = 24;
            this.VideoGameCompaniesView.Size = new System.Drawing.Size(716, 551);
            this.VideoGameCompaniesView.TabIndex = 0;
            this.VideoGameCompaniesView.SelectionChanged += new System.EventHandler(this.VideoGameCompaniesView_SelectionChanged);
            // 
            // GamesView
            // 
            this.GamesView.AllowUserToAddRows = false;
            this.GamesView.AllowUserToDeleteRows = false;
            this.GamesView.BackgroundColor = System.Drawing.Color.Snow;
            this.GamesView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.GamesView.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GamesView.Location = new System.Drawing.Point(725, 22);
            this.GamesView.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.GamesView.Name = "GamesView";
            this.GamesView.RowHeadersWidth = 51;
            this.GamesView.RowTemplate.Height = 24;
            this.GamesView.Size = new System.Drawing.Size(534, 551);
            this.GamesView.TabIndex = 1;
            this.GamesView.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.GamesView_DataError);
            this.GamesView.SelectionChanged += new System.EventHandler(this.GamesView_SelectionChanged);
            // 
            // VideoGameCompaniesLabel
            // 
            this.VideoGameCompaniesLabel.AutoSize = true;
            this.VideoGameCompaniesLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.VideoGameCompaniesLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.VideoGameCompaniesLabel.Location = new System.Drawing.Point(3, 0);
            this.VideoGameCompaniesLabel.Name = "VideoGameCompaniesLabel";
            this.VideoGameCompaniesLabel.Size = new System.Drawing.Size(716, 20);
            this.VideoGameCompaniesLabel.TabIndex = 2;
            this.VideoGameCompaniesLabel.Text = "VideoGameCompanies";
            // 
            // GamesLabel
            // 
            this.GamesLabel.AutoSize = true;
            this.GamesLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GamesLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.GamesLabel.Location = new System.Drawing.Point(725, 0);
            this.GamesLabel.Name = "GamesLabel";
            this.GamesLabel.Size = new System.Drawing.Size(534, 20);
            this.GamesLabel.TabIndex = 3;
            this.GamesLabel.Text = "Games";
            // 
            // GidLabel
            // 
            this.GidLabel.AutoSize = true;
            this.GidLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GidLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.GidLabel.Location = new System.Drawing.Point(3, 0);
            this.GidLabel.Name = "GidLabel";
            this.GidLabel.Size = new System.Drawing.Size(129, 31);
            this.GidLabel.TabIndex = 4;
            this.GidLabel.Text = "Gid";
            // 
            // NameLabel
            // 
            this.NameLabel.AutoSize = true;
            this.NameLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.NameLabel.Font = new System.Drawing.Font("Microsoft YaHei", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.NameLabel.Location = new System.Drawing.Point(3, 31);
            this.NameLabel.Name = "NameLabel";
            this.NameLabel.Size = new System.Drawing.Size(129, 31);
            this.NameLabel.TabIndex = 5;
            this.NameLabel.Text = "Name";
            // 
            // DescriptionLabel
            // 
            this.DescriptionLabel.AutoSize = true;
            this.DescriptionLabel.Dock = System.Windows.Forms.DockStyle.Left;
            this.DescriptionLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.DescriptionLabel.Location = new System.Drawing.Point(368, 0);
            this.DescriptionLabel.Name = "DescriptionLabel";
            this.DescriptionLabel.Size = new System.Drawing.Size(93, 31);
            this.DescriptionLabel.TabIndex = 6;
            this.DescriptionLabel.Text = "Description";
            // 
            // YearOfReleaseLabel
            // 
            this.YearOfReleaseLabel.AutoSize = true;
            this.YearOfReleaseLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.YearOfReleaseLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.YearOfReleaseLabel.Location = new System.Drawing.Point(368, 31);
            this.YearOfReleaseLabel.Name = "YearOfReleaseLabel";
            this.YearOfReleaseLabel.Size = new System.Drawing.Size(114, 31);
            this.YearOfReleaseLabel.TabIndex = 7;
            this.YearOfReleaseLabel.Text = "YearOfRelease";
            // 
            // NoOfPlayersLabel
            // 
            this.NoOfPlayersLabel.AutoSize = true;
            this.NoOfPlayersLabel.Dock = System.Windows.Forms.DockStyle.Left;
            this.NoOfPlayersLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.NoOfPlayersLabel.Location = new System.Drawing.Point(3, 62);
            this.NoOfPlayersLabel.Name = "NoOfPlayersLabel";
            this.NoOfPlayersLabel.Size = new System.Drawing.Size(99, 31);
            this.NoOfPlayersLabel.TabIndex = 8;
            this.NoOfPlayersLabel.Text = "NoOfPlayers";
            // 
            // RatingLabel
            // 
            this.RatingLabel.AutoSize = true;
            this.RatingLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.RatingLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.RatingLabel.Location = new System.Drawing.Point(368, 62);
            this.RatingLabel.Name = "RatingLabel";
            this.RatingLabel.Size = new System.Drawing.Size(114, 31);
            this.RatingLabel.TabIndex = 9;
            this.RatingLabel.Text = "Rating";
            // 
            // NoOfDownloadsLabel
            // 
            this.NoOfDownloadsLabel.AutoSize = true;
            this.NoOfDownloadsLabel.Dock = System.Windows.Forms.DockStyle.Left;
            this.NoOfDownloadsLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.NoOfDownloadsLabel.Location = new System.Drawing.Point(3, 93);
            this.NoOfDownloadsLabel.Name = "NoOfDownloadsLabel";
            this.NoOfDownloadsLabel.Size = new System.Drawing.Size(129, 31);
            this.NoOfDownloadsLabel.TabIndex = 10;
            this.NoOfDownloadsLabel.Text = "NoOfDownloads";
            // 
            // VidLabel
            // 
            this.VidLabel.AutoSize = true;
            this.VidLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.VidLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.VidLabel.Location = new System.Drawing.Point(368, 93);
            this.VidLabel.Name = "VidLabel";
            this.VidLabel.Size = new System.Drawing.Size(114, 31);
            this.VidLabel.TabIndex = 18;
            this.VidLabel.Text = "Vid";
            // 
            // GenidLabel
            // 
            this.GenidLabel.AutoSize = true;
            this.GenidLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.GenidLabel.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.GenidLabel.Location = new System.Drawing.Point(3, 124);
            this.GenidLabel.Name = "GenidLabel";
            this.GenidLabel.Size = new System.Drawing.Size(129, 106);
            this.GenidLabel.TabIndex = 18;
            this.GenidLabel.Text = "Genid";
            // 
            // gidText
            // 
            this.gidText.Dock = System.Windows.Forms.DockStyle.Left;
            this.gidText.Location = new System.Drawing.Point(138, 2);
            this.gidText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.gidText.Name = "gidText";
            this.gidText.Size = new System.Drawing.Size(224, 27);
            this.gidText.TabIndex = 11;
            // 
            // nameText
            // 
            this.nameText.Dock = System.Windows.Forms.DockStyle.Left;
            this.nameText.Location = new System.Drawing.Point(138, 33);
            this.nameText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.nameText.Name = "nameText";
            this.nameText.Size = new System.Drawing.Size(224, 27);
            this.nameText.TabIndex = 12;
            // 
            // descriptionText
            // 
            this.descriptionText.Dock = System.Windows.Forms.DockStyle.Left;
            this.descriptionText.Location = new System.Drawing.Point(488, 2);
            this.descriptionText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.descriptionText.Name = "descriptionText";
            this.descriptionText.Size = new System.Drawing.Size(224, 27);
            this.descriptionText.TabIndex = 13;
            // 
            // yearOfReleaseText
            // 
            this.yearOfReleaseText.Dock = System.Windows.Forms.DockStyle.Left;
            this.yearOfReleaseText.Location = new System.Drawing.Point(488, 33);
            this.yearOfReleaseText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.yearOfReleaseText.Name = "yearOfReleaseText";
            this.yearOfReleaseText.Size = new System.Drawing.Size(224, 27);
            this.yearOfReleaseText.TabIndex = 14;
            // 
            // noOfPlayersText
            // 
            this.noOfPlayersText.Dock = System.Windows.Forms.DockStyle.Left;
            this.noOfPlayersText.Location = new System.Drawing.Point(138, 64);
            this.noOfPlayersText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.noOfPlayersText.Name = "noOfPlayersText";
            this.noOfPlayersText.Size = new System.Drawing.Size(224, 27);
            this.noOfPlayersText.TabIndex = 15;
            // 
            // ratingText
            // 
            this.ratingText.Dock = System.Windows.Forms.DockStyle.Left;
            this.ratingText.Location = new System.Drawing.Point(488, 64);
            this.ratingText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.ratingText.Name = "ratingText";
            this.ratingText.Size = new System.Drawing.Size(224, 27);
            this.ratingText.TabIndex = 16;
            // 
            // noOfDownloadsText
            // 
            this.noOfDownloadsText.Dock = System.Windows.Forms.DockStyle.Left;
            this.noOfDownloadsText.Location = new System.Drawing.Point(138, 95);
            this.noOfDownloadsText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.noOfDownloadsText.Name = "noOfDownloadsText";
            this.noOfDownloadsText.Size = new System.Drawing.Size(224, 27);
            this.noOfDownloadsText.TabIndex = 17;
            // 
            // vidText
            // 
            this.vidText.Dock = System.Windows.Forms.DockStyle.Left;
            this.vidText.Location = new System.Drawing.Point(488, 95);
            this.vidText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.vidText.Name = "vidText";
            this.vidText.Size = new System.Drawing.Size(224, 27);
            this.vidText.TabIndex = 19;
            // 
            // genidText
            // 
            this.genidText.Dock = System.Windows.Forms.DockStyle.Left;
            this.genidText.Location = new System.Drawing.Point(138, 126);
            this.genidText.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.genidText.Name = "genidText";
            this.genidText.Size = new System.Drawing.Size(224, 27);
            this.genidText.TabIndex = 19;
            // 
            // addButton
            // 
            this.addButton.BackColor = System.Drawing.Color.Beige;
            this.addButton.Dock = System.Windows.Forms.DockStyle.Left;
            this.addButton.FlatAppearance.BorderColor = System.Drawing.Color.Beige;
            this.addButton.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.addButton.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.addButton.Location = new System.Drawing.Point(3, 2);
            this.addButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(224, 66);
            this.addButton.TabIndex = 20;
            this.addButton.Text = "Add Game";
            this.addButton.UseVisualStyleBackColor = false;
            this.addButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // removeButton
            // 
            this.removeButton.BackColor = System.Drawing.Color.Beige;
            this.removeButton.Dock = System.Windows.Forms.DockStyle.Left;
            this.removeButton.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.removeButton.Location = new System.Drawing.Point(3, 72);
            this.removeButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.removeButton.Name = "removeButton";
            this.removeButton.Size = new System.Drawing.Size(224, 66);
            this.removeButton.TabIndex = 21;
            this.removeButton.Text = "Remove Game";
            this.removeButton.UseVisualStyleBackColor = false;
            this.removeButton.Click += new System.EventHandler(this.removeButton_Click);
            // 
            // updateButton
            // 
            this.updateButton.BackColor = System.Drawing.Color.Beige;
            this.updateButton.Dock = System.Windows.Forms.DockStyle.Left;
            this.updateButton.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.updateButton.Location = new System.Drawing.Point(3, 142);
            this.updateButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(224, 86);
            this.updateButton.TabIndex = 22;
            this.updateButton.Text = "Update Game";
            this.updateButton.UseVisualStyleBackColor = false;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 57.21078F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 42.78922F));
            this.tableLayoutPanel1.Controls.Add(this.VideoGameCompaniesLabel, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.GamesLabel, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.VideoGameCompaniesView, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.GamesView, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel3, 1, 2);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 25F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1262, 809);
            this.tableLayoutPanel1.TabIndex = 23;
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 4;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel2.Controls.Add(this.NameLabel, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.GidLabel, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.gidText, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.vidText, 3, 3);
            this.tableLayoutPanel2.Controls.Add(this.DescriptionLabel, 2, 0);
            this.tableLayoutPanel2.Controls.Add(this.VidLabel, 2, 3);
            this.tableLayoutPanel2.Controls.Add(this.descriptionText, 3, 0);
            this.tableLayoutPanel2.Controls.Add(this.noOfDownloadsText, 1, 3);
            this.tableLayoutPanel2.Controls.Add(this.nameText, 1, 1);
            this.tableLayoutPanel2.Controls.Add(this.NoOfDownloadsLabel, 0, 3);
            this.tableLayoutPanel2.Controls.Add(this.ratingText, 3, 2);
            this.tableLayoutPanel2.Controls.Add(this.YearOfReleaseLabel, 2, 1);
            this.tableLayoutPanel2.Controls.Add(this.noOfPlayersText, 1, 2);
            this.tableLayoutPanel2.Controls.Add(this.RatingLabel, 2, 2);
            this.tableLayoutPanel2.Controls.Add(this.yearOfReleaseText, 3, 1);
            this.tableLayoutPanel2.Controls.Add(this.NoOfPlayersLabel, 0, 2);
            this.tableLayoutPanel2.Controls.Add(this.GenidLabel, 0, 4);
            this.tableLayoutPanel2.Controls.Add(this.genidText, 1, 4);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 577);
            this.tableLayoutPanel2.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 5;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel2.Size = new System.Drawing.Size(716, 230);
            this.tableLayoutPanel2.TabIndex = 4;
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 1;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel3.Controls.Add(this.updateButton, 0, 2);
            this.tableLayoutPanel3.Controls.Add(this.addButton, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.removeButton, 0, 1);
            this.tableLayoutPanel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel3.Location = new System.Drawing.Point(725, 577);
            this.tableLayoutPanel3.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 3;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle());
            this.tableLayoutPanel3.Size = new System.Drawing.Size(534, 230);
            this.tableLayoutPanel3.TabIndex = 5;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Chocolate;
            this.ClientSize = new System.Drawing.Size(1262, 809);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.VideoGameCompaniesView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GamesView)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            this.tableLayoutPanel3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView VideoGameCompaniesView;
        private System.Windows.Forms.DataGridView GamesView;
        private System.Windows.Forms.Label VideoGameCompaniesLabel;
        private System.Windows.Forms.Label GamesLabel;
        private System.Windows.Forms.Label GidLabel;
        private System.Windows.Forms.Label NameLabel;
        private System.Windows.Forms.Label DescriptionLabel;
        private System.Windows.Forms.Label YearOfReleaseLabel;
        private System.Windows.Forms.Label NoOfPlayersLabel;
        private System.Windows.Forms.Label RatingLabel;
        private System.Windows.Forms.Label NoOfDownloadsLabel;
        private System.Windows.Forms.Label VidLabel;
        private System.Windows.Forms.Label GenidLabel;
        private System.Windows.Forms.TextBox gidText;
        private System.Windows.Forms.TextBox nameText;
        private System.Windows.Forms.TextBox descriptionText;
        private System.Windows.Forms.TextBox yearOfReleaseText;
        private System.Windows.Forms.TextBox noOfPlayersText;
        private System.Windows.Forms.TextBox ratingText;
        private System.Windows.Forms.TextBox noOfDownloadsText;
        private System.Windows.Forms.TextBox vidText;
        private System.Windows.Forms.TextBox genidText;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.Button removeButton;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
    }
}