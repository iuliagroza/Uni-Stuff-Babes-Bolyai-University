import 'dart:collection';
import 'package:flutter/foundation.dart';
import '../models/income.dart';
import '../repositories/income_repository.dart';
import '../network/web_socket_listener.dart';

class IncomeViewModel with ChangeNotifier {
  final IncomeRepository _incomeRepository = IncomeRepository();
  final Map<String, Income> _incomesById = {};
  late WebSocketListener _webSocketListener; // Declare the WebSocketListener

  bool _hasError = false;
  String _errorMessage = '';

  // Getters for error properties
  bool get hasError => _hasError;
  String get errorMessage => _errorMessage;

  // Constructor
  IncomeViewModel() {
    _loadIncomes();
    _initializeWebSocketListener(); // Initialize WebSocketListener
  }

  // Initialize and handle WebSocketListener
  void _initializeWebSocketListener() {
    _webSocketListener = WebSocketListener(
      'ws://127.0.0.1:8000/ws/incomes/',
      onIncomeUpdate: (Income updatedIncome) {
        _updateIncomeLocally(updatedIncome);
      },
    );
  }

  // Update incomes with new data from WebSocket
  void _updateIncomeLocally(Income updatedIncome) {
    if (_incomesById.containsKey(updatedIncome.id)) {
      _incomesById[updatedIncome.id] = updatedIncome;
    } else {
      _incomesById[updatedIncome.id] =
          updatedIncome; // Handle new income if necessary
    }
    notifyListeners(); // Notify listeners to update UI
  }

  // Load incomes from the repository
  Future<void> _loadIncomes() async {
    try {
      _hasError = false;
      _errorMessage = '';
      List<Income> incomes = await _incomeRepository.getIncomes();
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

  // Get a list of incomes as an unmodifiable list view
  UnmodifiableListView<Income> get incomes =>
      UnmodifiableListView(_incomesById.values.toList());

  // Add an income entry
  Future<void> addIncome(Income income) async {
    try {
      _hasError = false;
      _errorMessage = '';
      await _incomeRepository.addIncome(income);
      _incomesById[income.id] = income;
    } catch (e) {
      _hasError = true;
      _errorMessage = e.toString();
    }
    notifyListeners();
  }

  // Get a single income by id
  Income? getIncomeById(String id) {
    return _incomesById[id];
  }

  // Update an income entry
  Future<void> updateIncome(String id, Income updatedIncome) async {
    try {
      _hasError = false;
      _errorMessage = '';
      if (_incomesById.containsKey(id)) {
        await _incomeRepository.updateIncome(updatedIncome);
        _incomesById[id] = updatedIncome;
      }
    } catch (e) {
      _hasError = true;
      _errorMessage = e.toString();
    }
    notifyListeners();
  }

  // Delete an income entry
  Future<void> deleteIncome(String id) async {
    try {
      _hasError = false;
      _errorMessage = '';
      if (_incomesById.containsKey(id)) {
        await _incomeRepository.deleteIncome(id);
        _incomesById.remove(id);
      }
    } catch (e) {
      _hasError = true;
      _errorMessage = e.toString();
    }
    notifyListeners();
  }

  // Make sure to dispose WebSocket when ViewModel is disposed
  @override
  void dispose() {
    _webSocketListener.dispose();
    super.dispose();
  }
}
