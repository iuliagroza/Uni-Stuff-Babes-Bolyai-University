// ignore_for_file: use_build_context_synchronously

import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/income.dart';
import '../view_models/income_view_model.dart';

class EditIncomeView extends StatefulWidget {
  final Income income;

  const EditIncomeView({Key? key, required this.income}) : super(key: key);

  @override
  // ignore: library_private_types_in_public_api
  _EditIncomeViewState createState() => _EditIncomeViewState();
}

class _EditIncomeViewState extends State<EditIncomeView> {
  final _formKey = GlobalKey<FormState>();
  late TextEditingController _amountController;
  late TextEditingController _noteController;
  String? _selectedCategory;
  late DateTime _selectedDate;

  @override
  void initState() {
    super.initState();
    _amountController =
        TextEditingController(text: widget.income.amount.toString());
    _noteController = TextEditingController(text: widget.income.note);
    _selectedCategory = widget.income.category;
    _selectedDate = widget.income.date;
  }

  @override
  void dispose() {
    _amountController.dispose();
    _noteController.dispose();
    super.dispose();
  }

  void _submitForm() async {
    if (_formKey.currentState!.validate()) {
      final viewModel = Provider.of<IncomeViewModel>(context, listen: false);
      final updatedIncome = Income(
        id: widget.income.id,
        amount: double.parse(_amountController.text),
        category: _selectedCategory!,
        date: _selectedDate,
        note: _noteController.text,
      );

      try {
        // Show loading indicator
        showDialog(
          context: context,
          barrierDismissible: false,
          builder: (context) =>
              const Center(child: CircularProgressIndicator()),
        );

        // Await the completion of the update operation
        await viewModel.updateIncome(widget.income.id, updatedIncome);

        // Dismiss the loading indicator
        Navigator.pop(context);

        // Close the EditIncomeView and return to the previous screen
        Navigator.pop(context);
      } catch (e) {
        // Dismiss the loading indicator
        Navigator.pop(context);

        // Show an error message
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(
            content: Text('Failed to update income: ${e.toString()}'),
          ),
        );
      }
    }
  }

  void _selectDate(BuildContext context) async {
    final DateTime? picked = await showDatePicker(
      context: context,
      initialDate: _selectedDate,
      firstDate: DateTime(2000),
      lastDate: DateTime(2101),
    );
    if (picked != null && picked != _selectedDate) {
      setState(() {
        _selectedDate = picked;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Edit Income'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Form(
          key: _formKey,
          child: ListView(
            children: <Widget>[
              TextFormField(
                controller: _amountController,
                keyboardType: TextInputType.number,
                decoration: const InputDecoration(labelText: 'Amount'),
                validator: (value) {
                  if (value == null || value.isEmpty) {
                    return 'Please enter an amount';
                  }
                  if (double.tryParse(value) == null) {
                    return 'Please enter a valid number';
                  }
                  return null;
                },
              ),
              DropdownButtonFormField<String>(
                value: _selectedCategory,
                decoration: const InputDecoration(labelText: 'Category'),
                items: Income.categories.map((String category) {
                  return DropdownMenuItem<String>(
                    value: category,
                    child: Text(category),
                  );
                }).toList(),
                onChanged: (String? newValue) {
                  setState(() {
                    _selectedCategory = newValue;
                  });
                },
                validator: (value) =>
                    value == null ? 'Please select a category' : null,
              ),
              TextFormField(
                controller: _noteController,
                decoration: const InputDecoration(labelText: 'Note'),
              ),
              ListTile(
                title: Text(
                    'Date: ${_selectedDate.toLocal().toString().split(' ')[0]}'),
                trailing: const Icon(Icons.calendar_today),
                onTap: () => _selectDate(context),
              ),
              ElevatedButton(
                onPressed: _submitForm,
                child: const Text('Update Income'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
