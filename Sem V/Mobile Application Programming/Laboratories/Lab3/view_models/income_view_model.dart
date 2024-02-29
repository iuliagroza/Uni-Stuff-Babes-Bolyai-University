import 'dart:collection';
import 'package:flutter/foundation.dart';
import 'package:uuid/uuid.dart';
import '../models/income.dart';

class IncomeViewModel with ChangeNotifier {
  // Using a map to facilitate easy lookup of incomes by ID.
  final Map<String, Income> _incomesById = {};

  IncomeViewModel() {
    // Prepopulate with 5 incomes
    _addPredefinedIncome(1000, 'Salary', DateTime.now(), 'Monthly salary');
    _addPredefinedIncome(200, 'Savings',
        DateTime.now().subtract(const Duration(days: 30)), 'Project X');
    _addPredefinedIncome(500, 'Investments', DateTime.now(), 'Stocks');
    _addPredefinedIncome(300, 'Salary',
        DateTime.now().subtract(const Duration(days: 5)), 'Birthday gift');
    _addPredefinedIncome(150, 'Other',
        DateTime.now().subtract(const Duration(days: 1)), 'Lottery winnings');
  }

  void _addPredefinedIncome(
      double amount, String category, DateTime date, String note) {
    addIncome(Income(
      id: const Uuid().v4(),
      amount: amount,
      category: category,
      date: date,
      note: note,
    ));
  }

  // Expose an unmodifiable view of incomes to prevent direct modification from outside.
  UnmodifiableListView<Income> get incomes =>
      UnmodifiableListView(_incomesById.values.toList());

  // Create operation
  void addIncome(Income income) {
    _incomesById[income.id] = income;
    notifyListeners(); // Notify listeners to rebuild the UI where necessary
  }

  // Read operation
  Income? getIncomeById(String id) {
    return _incomesById[id];
  }

  // Update operation
  void updateIncome(String id, Income updatedIncome) {
    if (_incomesById.containsKey(id)) {
      _incomesById[id] = updatedIncome;
      notifyListeners(); // Notify listeners to rebuild the UI where necessary
    }
  }

  // Delete operation
  void deleteIncome(String id) {
    if (_incomesById.containsKey(id)) {
      _incomesById.remove(id);
      notifyListeners(); // Notify listeners to rebuild the UI where necessary
    }
  }
}
