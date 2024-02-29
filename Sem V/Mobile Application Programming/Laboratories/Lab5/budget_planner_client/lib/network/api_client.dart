// ignore_for_file: avoid_print
import 'dart:developer';
import 'dart:convert';
import 'package:http/http.dart' as http;
import '../models/income.dart';

class ApiClient {
  final String baseUrl = 'http://127.0.0.1:8000';

  // Fetch incomes from the server
  Future<List<Income>> fetchIncomes() async {
    try {
      final response = await http.get(Uri.parse('$baseUrl/incomes/'));
      if (response.statusCode == 200) {
        List<dynamic> incomeList = json.decode(response.body);
        return incomeList.map((json) => Income.fromJson(json)).toList();
      } else {
        log('Failed to load incomes: ${response.statusCode} ${response.body}');
        throw Exception('Failed to load incomes');
      }
    } catch (e) {
      rethrow;
    }
  }

  // Add an income entry to the server
  Future<Income> createIncome(Income income) async {
    try {
      final response = await http.post(
        Uri.parse('$baseUrl/incomes/'),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
        },
        body: jsonEncode(income.toJson()),
      );
      if (response.statusCode == 201) {
        return Income.fromJson(json.decode(response.body));
      } else {
        log('Failed to create income: ${response.statusCode} ${response.body}');
        throw Exception('Failed to create income');
      }
    } catch (e) {
      rethrow;
    }
  }

  // Update an income entry on the server
  Future<void> updateIncome(Income income) async {
    try {
      final response = await http.put(
        Uri.parse('$baseUrl/incomes/${income.id}/'),
        headers: <String, String>{
          'Content-Type': 'application/json; charset=UTF-8',
        },
        body: jsonEncode(income.toJson()),
      );
      if (response.statusCode != 200) {
        log('Failed to update income: ${response.statusCode} ${response.body}');
        throw Exception('Failed to update income');
      }
    } catch (e) {
      rethrow;
    }
  }

  // Delete an income entry from the server
  Future<void> deleteIncome(String id) async {
    try {
      final response = await http.delete(
        Uri.parse('$baseUrl/incomes/$id/'),
      );
      if (response.statusCode != 204) {
        log('Failed to delete income: ${response.statusCode} ${response.body}');
        throw Exception('Failed to delete income');
      }
    } catch (e) {
      rethrow;
    }
  }
}
