import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:uuid/uuid.dart';
import '../models/income.dart';
import '../view_models/income_view_model.dart';

class AddIncomeView extends StatefulWidget {
  const AddIncomeView({super.key});

  @override
  // ignore: library_private_types_in_public_api
  _AddIncomeViewState createState() => _AddIncomeViewState();
}

class _AddIncomeViewState extends State<AddIncomeView> {
  final _formKey = GlobalKey<FormState>();
  final _amountController = TextEditingController();
  final _noteController = TextEditingController();
  String? _selectedCategory;
  DateTime? _selectedDate;

  @override
  void dispose() {
    _amountController.dispose();
    _noteController.dispose();
    super.dispose();
  }

  void _submitForm() {
    if (_formKey.currentState!.validate()) {
      final viewModel = Provider.of<IncomeViewModel>(context, listen: false);
      final income = Income(
        id: const Uuid().v4(),
        amount: double.parse(_amountController.text),
        category: _selectedCategory!,
        date: _selectedDate!,
        note: _noteController.text,
      );

      viewModel.addIncome(income);
      Navigator.pop(context);
    }
  }

  Future<void> _selectDate(BuildContext context) async {
    final DateTime? picked = await showDatePicker(
      context: context,
      initialDate: _selectedDate ?? DateTime.now(),
      firstDate: DateTime(2000),
      lastDate: DateTime(2101),
    );
    if (picked != null) {
      setState(() {
        _selectedDate = picked;
      });
    }
  }

  String? _validateDate(DateTime? date) {
    if (date == null) {
      return 'Please select a date';
    }
    return null; // No error
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Add New Income'),
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
              // Date picker
              ListTile(
                title: Text(
                    'Date: ${_selectedDate != null ? _selectedDate!.toLocal().toString().split(' ')[0] : 'Select Date'}'),
                trailing: const Icon(Icons.calendar_today),
                onTap: () => _selectDate(context),
              ),

              // Invisible validation widget for date
              Padding(
                padding: const EdgeInsets.all(0),
                child: TextFormField(
                  enabled: false, // Disable the text field
                  validator: (_) => _validateDate(_selectedDate),
                ),
              ),

              // Submit button
              ElevatedButton(
                onPressed: _submitForm,
                child: const Text('Save Income'),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
