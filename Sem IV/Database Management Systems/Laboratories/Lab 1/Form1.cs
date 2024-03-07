using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab1
{
    public partial class Form1 : Form
    {
        private SqlConnection dbConnection;
        private SqlDataAdapter daVideoGameCompanies, daGames;
        private DataSet tableData;
        private DataRelation drVideoGameCompaniesGames;
        BindingSource bsVideoGameCompanies, bsGames;

        public Form1()
        {
            InitializeComponent();
        }

        private void ReloadGamesTableView()
        {
            if (tableData.Tables["Games"] != null)
            {
                tableData.Tables["Games"].Clear();
            }
            daGames.Fill(tableData, "Games");
            GamesView.DataSource = bsGames;
        }

        private void VideoGameCompaniesView_SelectionChanged(object sender, EventArgs e)
        {
            gidText.Clear();
            nameText.Clear();
            descriptionText.Clear();
            yearOfReleaseText.Clear();
            noOfPlayersText.Clear();
            ratingText.Clear();
            noOfDownloadsText.Clear();
            vidText.Clear();
            genidText.Clear();
            if (VideoGameCompaniesView.SelectedRows.Count != 0)
            {
                DataGridViewRow selectedRow = VideoGameCompaniesView.SelectedRows[0];
                daGames.SelectCommand = new SqlCommand("SELECT * FROM Games WHERE Vid = " + selectedRow.Cells[0].Value, dbConnection);
                ReloadGamesTableView();
            }
        }

        private void GamesView_SelectionChanged(object sender, EventArgs e)
        {
            if (GamesView.SelectedRows.Count != 0)
            {
                DataGridViewRow selectedRow = GamesView.SelectedRows[0];
                gidText.Text = selectedRow.Cells[0].Value.ToString();
                nameText.Text = selectedRow.Cells[1].Value.ToString();
                descriptionText.Text = selectedRow.Cells[2].Value.ToString();
                yearOfReleaseText.Text = selectedRow.Cells[3].Value.ToString();
                noOfPlayersText.Text = selectedRow.Cells[4].Value.ToString();
                ratingText.Text = selectedRow.Cells[5].Value.ToString();
                noOfDownloadsText.Text = selectedRow.Cells[6].Value.ToString();
                vidText.Text = selectedRow.Cells[7].Value.ToString();
                genidText.Text = selectedRow.Cells[8].Value.ToString();
            }
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            SqlCommand command = new SqlCommand("SET IDENTITY_INSERT Games ON;" + "INSERT INTO Games (Gid, Name, Description, YearOfRelease, NoOfPlayers, Rating, NoOfDownloads, Vid, Genid) " +
                "VALUES (@Gid, @Name, @Description, @YearOfRelease, @NoOfPlayers, @Rating, @NoOfDownloads, @Vid, @Genid)" + "SET IDENTITY_INSERT Games OFF;", dbConnection);
            if (gidText.Text.Length != 0)
            {
                try
                {
                    int gid = Int32.Parse(gidText.Text);
                    if (yearOfReleaseText.Text.Length != 0)
                    {
                        int year_of_release = Int32.Parse(yearOfReleaseText.Text);
                        if (noOfPlayersText.Text.Length != 0)
                        {
                            int no_of_players = Int32.Parse(noOfPlayersText.Text);
                            int rating;
                            if (ratingText.Text.Length != 0)
                                rating = Int32.Parse(ratingText.Text);
                            else
                                rating = 0;
                            if(noOfDownloadsText.Text.Length != 0)
                            {
                                int no_of_downloads = Int32.Parse(noOfDownloadsText.Text);

                                if(vidText.Text.Length != 0)
                                {
                                    int vid = Int32.Parse(vidText.Text);

                                    if(genidText.Text.Length != 0)
                                    {
                                        int genid = Int32.Parse(genidText.Text);

                                        command.Parameters.Add("@Gid", SqlDbType.Int);
                                        command.Parameters["@Gid"].Value = gid;
                                        command.Parameters.Add("@Name", SqlDbType.VarChar, 50);
                                        command.Parameters["@Name"].Value = nameText.Text;
                                        command.Parameters.Add("@Description", SqlDbType.VarChar, 255);
                                        command.Parameters["@Description"].Value = descriptionText.Text;
                                        command.Parameters.Add("@YearOfRelease", SqlDbType.Int);
                                        command.Parameters["@YearOfRelease"].Value = year_of_release;
                                        command.Parameters.Add("@NoOfPlayers", SqlDbType.Int);
                                        command.Parameters["@NoOfPlayers"].Value = no_of_players;
                                        command.Parameters.Add("@Rating", SqlDbType.Int);
                                        command.Parameters["@Rating"].Value = rating;
                                        command.Parameters.Add("@NoOfDownloads", SqlDbType.Int);
                                        command.Parameters["@NoOfDownloads"].Value = no_of_downloads;
                                        command.Parameters.Add("@Vid", SqlDbType.Int);
                                        command.Parameters["@Vid"].Value = vid;
                                        command.Parameters.Add("@Genid", SqlDbType.Int);
                                        command.Parameters["@Genid"].Value = genid;

                                        try
                                        {
                                            daGames.InsertCommand = command;
                                            daGames.InsertCommand.ExecuteNonQuery();
                                            ReloadGamesTableView();
                                        }
                                        catch (SqlException sqlException)
                                        {
                                            if (sqlException.Number == 2627)
                                                MessageBox.Show("gid must be unique.");
                                            else if (sqlException.Number == 547)
                                                MessageBox.Show("No company or genre with the given ID was found.");
                                            else
                                                MessageBox.Show(sqlException.Message);
                                        }
                                    }
                                    else
                                        MessageBox.Show("Please provide a genre ID.");
                                }
                                else
                                    MessageBox.Show("Please provide a company ID.");
                            }
                        }
                    }
                }
                catch (FormatException ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
                MessageBox.Show("Please provide a game ID.");
        }

        private void removeButton_Click(object sender, EventArgs e)
        {
            SqlCommand command = new SqlCommand("DELETE FROM Games WHERE Gid = @Gid", dbConnection);
            if (gidText.Text.Length != 0)
            {
                int gid = Int32.Parse(gidText.Text);
                command.Parameters.Add("@Gid", SqlDbType.Int);
                command.Parameters["@Gid"].Value = gid;
                try
                {
                    daGames.DeleteCommand = command;
                    int numberOfDeletedGames = daGames.DeleteCommand.ExecuteNonQuery();
                    if (numberOfDeletedGames == 0)
                    {
                        MessageBox.Show("No game with the given ID was found.");
                    }
                    else
                    {
                        ReloadGamesTableView();
                    }
                }
                catch (SqlException sqlException)
                {
                    MessageBox.Show(sqlException.ToString());
                }
            }
            else
                MessageBox.Show("Please provide a game ID.");
        }

        private void GamesView_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            if (e.Exception is InvalidConstraintException)
                MessageBox.Show("The company ID you provided does not exist.");
            else if (e.Exception is FormatException)
                MessageBox.Show(e.Exception.Message);
            else
                try
                {
                    throw e.Exception;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.ToString());
                }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            SqlCommand command = new SqlCommand("UPDATE Games " +
                "SET Vid = @Vid, Name = @Name, Description = @Description, " +
                "YearOfRelease = @YearOfRelease, NoOfPlayers = @NoOfPlayers, Rating = @Rating, NoOfDownloads = @NoOfDownloads, Genid = @Genid " +
                "WHERE Gid = @Gid", dbConnection);
            int gid = Int32.Parse(gidText.Text);
            int year_of_release = Int32.Parse(yearOfReleaseText.Text);
            int no_of_players = Int32.Parse(noOfPlayersText.Text);
            int rating = Int32.Parse(ratingText.Text);
            int no_of_downloads = Int32.Parse(noOfDownloadsText.Text);
            int vid = Int32.Parse(vidText.Text);
            int genid = Int32.Parse(genidText.Text);
            command.Parameters.Add("@Gid", SqlDbType.Int);
            command.Parameters["@Gid"].Value = gid;
            command.Parameters.Add("@Name", SqlDbType.VarChar, 50);
            command.Parameters["@Name"].Value = nameText.Text;
            command.Parameters.Add("@Description", SqlDbType.VarChar, 255);
            command.Parameters["@Description"].Value = descriptionText.Text;
            command.Parameters.Add("@YearOfRelease", SqlDbType.Int);
            command.Parameters["@YearOfRelease"].Value = year_of_release;
            command.Parameters.Add("@NoOfPlayers", SqlDbType.Int);
            command.Parameters["@NoOfPlayers"].Value = no_of_players;
            command.Parameters.Add("@Rating", SqlDbType.Int);
            command.Parameters["@Rating"].Value = rating;
            command.Parameters.Add("@NoOfDownloads", SqlDbType.Int);
            command.Parameters["@NoOfDownloads"].Value = no_of_downloads;
            command.Parameters.Add("@Vid", SqlDbType.Int);
            command.Parameters["@Vid"].Value = vid;
            command.Parameters.Add("@Genid", SqlDbType.Int);
            command.Parameters["@Genid"].Value = genid;
            try
            {
                daGames.UpdateCommand = command;
                int numberOfUpdatedGames = daGames.UpdateCommand.ExecuteNonQuery();
                if (numberOfUpdatedGames != 0)
                {
                    ReloadGamesTableView();
                }
                else
                {
                    MessageBox.Show("There is no game with the given ID.");
                }
            }
            catch (SqlException sqlException)
            {
                if (sqlException.Number == 2627)
                    MessageBox.Show("The game ID must be unique.");
                else if (sqlException.Number == 547)
                    MessageBox.Show("There's no company with the given ID.");
                else
                    MessageBox.Show(sqlException.Message);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dbConnection = new SqlConnection("Data Source=IULIA\\SQLEXPRESS;Initial Catalog=CloudGaming;Integrated Security=True");
            dbConnection.Open();

            daVideoGameCompanies = new SqlDataAdapter("SELECT * FROM VideoGameCompanies", dbConnection);
            tableData = new DataSet();
            daVideoGameCompanies.Fill(tableData, "VideoGameCompanies");
            VideoGameCompaniesView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            daGames = new SqlDataAdapter("SELECT * FROM Games", dbConnection);
            daGames.Fill(tableData, "Games");
            GamesView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            DataColumn VidCompany = tableData.Tables["VideoGameCompanies"].Columns["Vid"];
            DataColumn VidGame = tableData.Tables["Games"].Columns["Vid"];
            drVideoGameCompaniesGames = new DataRelation("FK_VIDEOGAMECOMPANIES_GAMES", VidCompany, VidGame);
            tableData.Relations.Add(drVideoGameCompaniesGames);

            bsVideoGameCompanies = new BindingSource();
            bsVideoGameCompanies.DataSource = tableData;
            bsVideoGameCompanies.DataMember = "VideoGameCompanies";

            bsGames = new BindingSource();
            bsGames.DataSource = bsVideoGameCompanies;
            bsGames.DataMember = "FK_VIDEOGAMECOMPANIES_GAMES";
            VideoGameCompaniesView.DataSource = bsVideoGameCompanies;
        }
    }
}