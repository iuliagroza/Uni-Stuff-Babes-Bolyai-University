import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../view_models/income_view_model.dart';
import 'edit_income_view.dart';

class IncomeDetailsView extends StatelessWidget {
  final String incomeId;

  const IncomeDetailsView({Key? key, required this.incomeId}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    // Fetch the income from the ViewModel based on the ID.
    final viewModel = Provider.of<IncomeViewModel>(context);
    final income = viewModel.getIncomeById(incomeId);

    // If the income with the given ID does not exist, show an error.
    if (income == null) {
      return Scaffold(
        appBar: AppBar(
          title: const Text('Income Details'),
        ),
        body: const Center(
          child: Text('Income not found.'),
        ),
      );
    }

    return Scaffold(
      appBar: AppBar(
        title: const Text('Income Details'),
        actions: [
          IconButton(
            icon: const Icon(Icons.edit),
            onPressed: () {
              // Navigate to the EditIncomeView with the selected income.
              Navigator.push(
                context,
                MaterialPageRoute(
                  builder: (context) => EditIncomeView(income: income),
                ),
              );
            },
          ),
          IconButton(
            icon: const Icon(Icons.delete),
            onPressed: () => _confirmDelete(context, viewModel, income.id),
          ),
        ],
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Text('Amount: \$${income.amount}',
                style: Theme.of(context).textTheme.titleLarge),
            Text('Category: ${income.category}',
                style: Theme.of(context).textTheme.titleMedium),
            Text('Date: ${income.date.toLocal().toString().split(' ')[0]}',
                style: Theme.of(context).textTheme.titleMedium),
            const SizedBox(height: 16),
            Text('Note:', style: Theme.of(context).textTheme.titleMedium),
            Text(income.note, style: Theme.of(context).textTheme.bodyMedium),
          ],
        ),
      ),
    );
  }

  // Helper method to show a confirmation dialog before deletion
  void _confirmDelete(
      BuildContext context, IncomeViewModel viewModel, String incomeId) {
    showDialog(
      context: context,
      builder: (BuildContext context) {
        return AlertDialog(
          title: const Text('Confirm Delete'),
          content: const Text('Are you sure you want to delete this income?'),
          actions: <Widget>[
            TextButton(
              child: const Text('Cancel'),
              onPressed: () {
                Navigator.of(context).pop(); // Dismiss the dialog
              },
            ),
            TextButton(
              child: const Text('Delete'),
              onPressed: () {
                // Perform the delete operation
                viewModel.deleteIncome(incomeId);
                Navigator.of(context).pop(); // Dismiss the dialog
                Navigator.of(context).pop(); // Return to the previous screen
              },
            ),
          ],
        );
      },
    );
  }
}
