import '../models/income.dart';
import '../database/database_helper.dart'; // Local Database
import '../network/api_client.dart'; // Server API client

class IncomeRepository {
  final DatabaseHelper _databaseHelper = DatabaseHelper.instance;
  final ApiClient _apiClient = ApiClient();

  // Fetch income entries from the server and update the local database
  Future<List<Income>> getIncomes() async {
    List<Income> incomes = [];
    try {
      // First, try to fetch from the server
      incomes = await _apiClient.fetchIncomes();

      // Clear local database and insert newly fetched incomes
      await _databaseHelper.clearIncomes();
      for (var income in incomes) {
        await _databaseHelper.insertIncome(income);
      }
    } catch (e) {
      // If fetching from server fails, try to fetch from local database
      incomes = await _databaseHelper.getIncomes();
      if (incomes.isEmpty) {
        throw Exception(
            'Failed to load incomes from both server and local database');
      }
    }
    return incomes;
  }

  // Add an income entry
  Future<void> addIncome(Income income) async {
    try {
      // Add to server first
      var newIncome = await _apiClient.createIncome(income);
      // Then add to local database
      await _databaseHelper.insertIncome(newIncome);
    } catch (e) {
      rethrow;
    }
  }

  // Update an income entry
  Future<void> updateIncome(Income income) async {
    try {
      // Update server entry first
      await _apiClient.updateIncome(income);
      // Then update local database
      await _databaseHelper.updateIncome(income);
    } catch (e) {
      rethrow;
    }
  }

  // Delete an income entry
  Future<void> deleteIncome(String id) async {
    try {
      // Delete from server first
      await _apiClient.deleteIncome(id);
      // Then delete from local database
      await _databaseHelper.deleteIncome(id);
    } catch (e) {
      rethrow;
    }
  }
}
