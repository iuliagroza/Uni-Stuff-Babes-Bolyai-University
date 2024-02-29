import 'dart:collection';
import 'package:flutter/foundation.dart';
import '../models/income.dart';
import '../database/database_helper.dart'; // Import the DatabaseHelper

class IncomeViewModel with ChangeNotifier {
  final DatabaseHelper _databaseHelper = DatabaseHelper.instance;
  final Map<String, Income> _incomesById = {};
  bool _hasError = false;
  String _errorMessage = '';

  // Getters for error properties
  bool get hasError => _hasError;
  String get errorMessage => _errorMessage;

  IncomeViewModel() {
    _loadIncomesFromDatabase();
  }

  Future<void> _loadIncomesFromDatabase() async {
    try {
      _hasError = false;
      _errorMessage = '';
      List<Income> incomes = await _databaseHelper.getIncomes();
      _incomesById.clear();
      for (var income in incomes) {
        _incomesById[income.id] = income;
      }
    } catch (e) {
      _hasError = true;
      _errorMessage = e.toString();
    }
    notifyListeners();
  }

  UnmodifiableListView<Income> get incomes =>
      UnmodifiableListView(_incomesById.values.toList());

  Future<void> addIncome(Income income) async {
    try {
      _hasError = false;
      _errorMessage = '';
      await _databaseHelper.insertIncome(income);
      _incomesById[income.id] = income;
    } catch (e) {
      _hasError = true;
      _errorMessage = e.toString();
    }
    notifyListeners();
  }

  Income? getIncomeById(String id) {
    return _incomesById[id];
  }

  Future<void> updateIncome(String id, Income updatedIncome) async {
    try {
      _hasError = false;
      _errorMessage = '';
      if (_incomesById.containsKey(id)) {
        await _databaseHelper.updateIncome(updatedIncome);
        _incomesById[id] = updatedIncome;
      }
    } catch (e) {
      _hasError = true;
      _errorMessage = e.toString();
    }
    notifyListeners();
  }

  Future<void> deleteIncome(String id) async {
    try {
      _hasError = false;
      _errorMessage = '';
      if (_incomesById.containsKey(id)) {
        await _databaseHelper.deleteIncome(id);
        _incomesById.remove(id);
      }
    } catch (e) {
      _hasError = true;
      _errorMessage = e.toString();
    }
    notifyListeners();
  }
}
