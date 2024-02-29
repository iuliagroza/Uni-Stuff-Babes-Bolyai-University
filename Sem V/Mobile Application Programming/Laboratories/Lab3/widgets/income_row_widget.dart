import 'package:flutter/material.dart';
import '../models/income.dart';
import '../view_models/income_view_model.dart';
import '../views/income_details_view.dart';
import '../views/edit_income_view.dart';
import 'package:provider/provider.dart';

class IncomeRowWidget extends StatelessWidget {
  final Income income;

  const IncomeRowWidget({Key? key, required this.income}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return ListTile(
      title: Text('Amount: \$${income.amount}'),
      subtitle: Text('Category: ${income.category}'),
      trailing: _buildPopupMenuButton(context),
      onTap: () {
        Navigator.push(
          context,
          MaterialPageRoute(
            builder: (context) => IncomeDetailsView(incomeId: income.id),
          ),
        );
      },
    );
  }

  Widget _buildPopupMenuButton(BuildContext context) {
    return PopupMenuButton<String>(
      onSelected: (String result) {
        switch (result) {
          case 'view':
            Navigator.push(
              context,
              MaterialPageRoute(
                builder: (context) => IncomeDetailsView(incomeId: income.id),
              ),
            );
            break;
          case 'edit':
            Navigator.push(
              context,
              MaterialPageRoute(
                builder: (context) => EditIncomeView(income: income),
              ),
            );
            break;
          case 'delete':
            _confirmDelete(context, income.id);
            break;
        }
      },
      itemBuilder: (BuildContext context) => <PopupMenuEntry<String>>[
        const PopupMenuItem<String>(
          value: 'view',
          child: Text('View Details'),
        ),
        const PopupMenuItem<String>(
          value: 'edit',
          child: Text('Edit'),
        ),
        const PopupMenuItem<String>(
          value: 'delete',
          child: Text('Delete'),
        ),
      ],
    );
  }

  void _confirmDelete(BuildContext context, String incomeId) {
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
                Provider.of<IncomeViewModel>(context, listen: false)
                    .deleteIncome(incomeId);
                Navigator.of(context).pop(); // Dismiss the dialog
              },
            ),
          ],
        );
      },
    );
  }
}
