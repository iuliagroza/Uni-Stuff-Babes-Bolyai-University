// ignore_for_file: depend_on_referenced_packages
import 'dart:developer';
import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';
import 'package:budget_planner/models/income.dart';

class DatabaseHelper {
  static const _databaseName = "MyDatabase.db";
  static const _databaseVersion = 1;
  static const table = 'income_table';

  static const columnId = 'id';
  static const columnAmount = 'amount';
  static const columnCategory = 'category';
  static const columnDate = 'date';
  static const columnNote = 'note';

  // Make this a singleton class.
  DatabaseHelper._privateConstructor();
  static final DatabaseHelper instance = DatabaseHelper._privateConstructor();

  // Only have a single app-wide reference to the database.
  static Database? _database;
  Future<Database> get database async => _database ??= await _initDatabase();

  // Open the database and create it if it doesn't exist.
  _initDatabase() async {
    String path = join(await getDatabasesPath(), _databaseName);
    log('Database initialized at path: $path');
    return await openDatabase(path,
        version: _databaseVersion, onCreate: _onCreate);
  }

  // SQL code to create the database table.
  Future _onCreate(Database db, int version) async {
    log('Created a new database table: $table');
    await db.execute('''
          CREATE TABLE $table (
            $columnId TEXT PRIMARY KEY,
            $columnAmount DOUBLE NOT NULL,
            $columnCategory TEXT NOT NULL,
            $columnDate TEXT NOT NULL,
            $columnNote TEXT
          )
          ''');
  }

  // Helper methods for CRUD operations:

  // Insert an income into the database.
  Future<void> insertIncome(Income income) async {
    try {
      Database db = await database;
      var result = await db.insert(table, income.toMap());
      log('Inserted income into database: $result');
    } catch (e) {
      log('Error inserting income: $e');
      rethrow; // rethrowing the error after logging it
    }
  }

  // Retrieve all incomes from the database.
  Future<List<Income>> getIncomes() async {
    try {
      Database db = await database;
      List<Map<String, dynamic>> maps = await db.query(table);
      log('Fetched incomes: Found ${maps.length} entries');
      return List.generate(maps.length, (i) {
        return Income.fromMap(maps[i]);
      });
    } catch (e) {
      log('Error fetching incomes: $e');
      rethrow; // rethrowing the error after logging it
    }
  }

  // Update an income in the database.
  Future<void> updateIncome(Income income) async {
    try {
      Database db = await database;
      var result = await db.update(table, income.toMap(),
          where: '$columnId = ?', whereArgs: [income.id]);
      log('Updated income: $result');
    } catch (e) {
      log('Error updating income: $e');
      rethrow; // rethrowing the error after logging it
    }
  }

  // Delete an income from the database.
  Future<void> deleteIncome(String id) async {
    try {
      Database db = await database;
      var result =
          await db.delete(table, where: '$columnId = ?', whereArgs: [id]);
      log('Deleted income: $result');
    } catch (e) {
      log('Error deleting income: $e');
      rethrow; // rethrowing the error after logging it
    }
  }

  // Delete all incomes from the database.
  Future<void> clearIncomes() async {
    try {
      Database db = await database;
      var result = await db.delete(table); // This deletes all rows in the table
      log('Cleared all incomes from database: $result');
    } catch (e) {
      log('Error clearing incomes: $e');
      rethrow; // rethrowing the error after logging it
    }
  }
}
