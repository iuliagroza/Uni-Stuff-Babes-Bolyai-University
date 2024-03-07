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
using System.Configuration;

namespace Lab2
{
    public partial class Form1 : Form
    {
        private SqlConnection dbConnection;
        private SqlDataAdapter daParent, daChild;
        private DataSet tableData;
        private DataRelation drParentChild;
        private BindingSource bsParent, bsChild;

        public Form1()
        {
            InitializeComponent();
        }

        private string getConnectionString()
        {
            return ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString.ToString();
        }

        private string getDatabase()
        {
            return ConfigurationManager.AppSettings["Database"].ToString();
        }

        private string getParentTableName()
        {
            return ConfigurationManager.AppSettings["ParentTableName"].ToString();
        }

        private string getChildTableName()
        {
            return ConfigurationManager.AppSettings["ChildTableName"].ToString();
        }

        private string getParentSelectQuery()
        {
            return ConfigurationManager.AppSettings["ParentSelectQuery"].ToString();
        }

        private string getChildSelectQuery()
        {
            return ConfigurationManager.AppSettings["ChildSelectQuery"].ToString();
        }

        private string getParentReferencedKey()
        {
            return ConfigurationManager.AppSettings["ParentReferencedKey"].ToString();
        }

        private string getChildForeignKey()
        {
            return ConfigurationManager.AppSettings["ChildForeignKey"].ToString();
        }

        private string getParentSelectionQuery()
        {
            return ConfigurationManager.AppSettings["ParentSelectionQuery"].ToString();
        }

        private void parentTableView_SelectionChanged(object sender, EventArgs e)
        {
            if (parentTableView.SelectedRows.Count != 0)
            {
                DataGridViewRow selectedRow = parentTableView.SelectedRows[0];
                string selectCommandString = String.Format(getParentSelectionQuery(), selectedRow.Cells[0].Value);
                daChild.SelectCommand = new SqlCommand(selectCommandString, dbConnection);
                ReloadChildTableView();
            }
        }

        private void childTableView_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            if (e.Exception is InvalidConstraintException)
                MessageBox.Show("The parent id you provided does not exist!");
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
            SqlCommandBuilder builder = new SqlCommandBuilder(daChild);
            daChild.UpdateCommand = builder.GetUpdateCommand();
            daChild.InsertCommand = builder.GetInsertCommand();
            daChild.DeleteCommand = builder.GetDeleteCommand();
            try
            {
                daChild.Update(tableData, getChildTableName());
            }
            catch (SqlException sqlException)
            {
                if (sqlException.Number == 2627)
                    MessageBox.Show("There is column data that should be unique in the table!");
                else if (sqlException.Number == 547)
                    MessageBox.Show("There's no parent with the given id!");
                else
                    MessageBox.Show(sqlException.Message);
            }
            ReloadChildTableView();
        }

        private void ReloadChildTableView()
        {
            if (tableData.Tables[getChildTableName()] != null)
            {
                tableData.Tables[getChildTableName()].Clear();
            }
            daChild.Fill(tableData, getChildTableName());
            childTableView.DataSource = bsChild;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dbConnection = new SqlConnection(String.Format(getConnectionString(), getDatabase()));
            dbConnection.Open();

            tableData = new DataSet();

            daParent = new SqlDataAdapter(getParentSelectQuery(), dbConnection);
            daParent.Fill(tableData, getParentTableName());
            parentTableView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            daChild = new SqlDataAdapter(getChildSelectQuery(), dbConnection);
            daChild.Fill(tableData, getChildTableName());
            childTableView.SelectionMode = DataGridViewSelectionMode.FullRowSelect;

            DataColumn referenceId = tableData.Tables[getParentTableName()].Columns[getParentReferencedKey()];
            DataColumn foreignId = tableData.Tables[getChildTableName()].Columns[getChildForeignKey()];
            drParentChild = new DataRelation("FK_Parent_Child", referenceId, foreignId);
            tableData.Relations.Add(drParentChild);

            bsParent = new BindingSource();
            bsParent.DataSource = tableData;
            bsParent.DataMember = getParentTableName();

            bsChild = new BindingSource();
            bsChild.DataSource = bsParent;
            bsChild.DataMember = "FK_Parent_Child";

            parentTableView.DataSource = bsParent;
        }
    }
}