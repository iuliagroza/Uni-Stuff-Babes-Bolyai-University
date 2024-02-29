// ignore_for_file: depend_on_referenced_packages

import 'package:path/path.dart';
import 'package:sqflite/sqflite.dart';
import 'package:budget_planner/models/income.dart'; // Import your Income model

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
    return await openDatabase(path,
        version: _databaseVersion, onCreate: _onCreate);
  }

  // SQL code to create the database table.
  Future _onCreate(Database db, int version) async {
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
    Database db = await database;
    await db.insert(table, income.toMap());
  }

  // Retrieve all incomes from the database.
  Future<List<Income>> getIncomes() async {
    Database db = await database;
    List<Map<String, dynamic>> maps = await db.query(table);

    return List.generate(maps.length, (i) {
      return Income.fromMap(maps[i]);
    });
  }

  // Update an income in the database.
  Future<void> updateIncome(Income income) async {
    Database db = await database;
    await db.update(table, income.toMap(),
        where: '$columnId = ?', whereArgs: [income.id]);
  }

  // Delete an income from the database.
  Future<void> deleteIncome(String id) async {
    Database db = await database;
    await db.delete(table, where: '$columnId = ?', whereArgs: [id]);
  }
}
