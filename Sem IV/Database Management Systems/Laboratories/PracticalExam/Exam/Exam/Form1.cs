using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Exam
{
    public partial class Form1 : Form
    {
        DataSet dataset;
        SqlDataAdapter playersAdapter, cardsAdapter;
        BindingSource playersBindingSource, cardsBindingSource;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dataset = new DataSet();

            // Connection String
            string connectionString = "Data Source=IULIA\\SQLEXPRESS;Initial Catalog=Cards;Integrated Security=True";

            // Set up Players Adapter and fill Dataset
            playersAdapter = new SqlDataAdapter("SELECT * FROM Players", connectionString);
            playersAdapter.Fill(dataset, "Players");

            // Set up Cards Adapter and fill Dataset
            cardsAdapter = new SqlDataAdapter("SELECT * FROM Cards", connectionString);
            cardsAdapter.Fill(dataset, "Cards");

            // Commands for update operations
            SqlCommandBuilder commands = new SqlCommandBuilder(cardsAdapter);

            // Bind Players to DataGridView
            playersBindingSource = new BindingSource();
            playersBindingSource.DataSource = dataset;
            playersBindingSource.DataMember = "Players";
            dgvPlayers.DataSource = playersBindingSource;

            // Bind Cards to DataGridView
            cardsBindingSource = new BindingSource();
            cardsBindingSource.DataSource = dataset;
            cardsBindingSource.DataMember = "Cards";
            dgvCards.DataSource = cardsBindingSource;

            // Assuming there is a ForeignKey relationship named "FK_Cards_Players" from Cards to Players on PlayerID
            dataset.Relations.Add("FK_Cards_Players",
                                  dataset.Tables["Players"].Columns["PlayerID"],
                                  dataset.Tables["Cards"].Columns["PlayerID"]);

            // Whenever the current player changes, change the filter for the Cards view
            playersBindingSource.CurrentChanged += (s, ev) =>
            {
                if (playersBindingSource.Current != null)
                {
                    string filter = $"PlayerID = {((DataRowView)playersBindingSource.Current)["PlayerID"]}";
                    cardsBindingSource.Filter = filter;
                }
                else
                {
                    cardsBindingSource.Filter = "";
                }
            };
        }


        private void btnSave_Click(object sender, EventArgs e)
        {
            // Save changes
            try
            {
                cardsBindingSource.EndEdit();
                cardsAdapter.Update(dataset, "Cards");
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error: " + ex.Message);
            }
        }
    }
}
