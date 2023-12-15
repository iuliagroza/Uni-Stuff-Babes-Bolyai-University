import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/income.dart';
import '../view_models/income_view_model.dart';
import 'income_details_view.dart';
import 'add_income_view.dart';
import '../widgets/income_row_widget.dart';

class IncomeListView extends StatelessWidget {
  const IncomeListView({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Incomes'),
        actions: <Widget>[
          IconButton(
            icon: const Icon(Icons.add),
            onPressed: () {
              Navigator.push(
                context,
                MaterialPageRoute(builder: (context) => const AddIncomeView()),
              );
            },
          ),
        ],
      ),
      body: Consumer<IncomeViewModel>(
        builder: (context, viewModel, child) {
          return ListView.builder(
            itemCount: viewModel.incomes.length,
            itemBuilder: (context, index) {
              Income income = viewModel.incomes[index];
              return InkWell(
                onTap: () {
                  Navigator.push(
                    context,
                    MaterialPageRoute(
                      builder: (context) =>
                          IncomeDetailsView(incomeId: income.id),
                    ),
                  );
                },
                child: IncomeRowWidget(income: income),
              );
            },
          );
        },
      ),
    );
  }
}
