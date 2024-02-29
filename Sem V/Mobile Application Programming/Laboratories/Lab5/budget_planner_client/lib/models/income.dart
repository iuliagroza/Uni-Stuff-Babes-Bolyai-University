import 'package:intl/intl.dart';

class Income {
  String id;
  double amount;
  String category;
  DateTime date;
  String note;

  // Static list of predefined categories
  static const List<String> categories = [
    'Salary',
    'Pension',
    'Investments',
    'Savings',
    'Other'
  ];

  Income({
    required this.id,
    required this.amount,
    required this.category,
    required this.date,
    this.note = '',
  }) {
    // Ensure the category is one of the predefined options
    if (!categories.contains(category)) {
      throw ArgumentError('Invalid category: $category');
    }
  }

  // Convert an Income object into a Map. The keys must correspond to the names of the columns in the database.
  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'amount': amount,
      'category': category,
      'date': date.toIso8601String(), // Store date as a string
      'note': note,
    };
  }

  // Extract an Income object from a Map.
  static Income fromMap(Map<String, dynamic> map) {
    return Income(
      id: map['id'],
      amount: map['amount'],
      category: map['category'],
      date: DateTime.parse(map['date']),
      note: map['note'],
    );
  }

  // Convert a Income into a Map. The keys must correspond to the names of the
  // columns in the database.
  Map<String, dynamic> toJson() {
    // Create a DateFormatter
    final DateFormat formatter = DateFormat('yyyy-MM-dd');
    // Format the date according to the server's expected format
    final String formattedDate = formatter.format(date);

    return {
      'amount': amount,
      'category': category,
      'date': formattedDate, // Use the formatted date string
      'note': note,
    };
  }

  // Extract a Income object from a Map. The keys must correspond to the names of the
  // columns in the database.
  factory Income.fromJson(Map<String, dynamic> json) => Income(
        id: json['id'].toString(),
        amount: (json['amount'] as num).toDouble(),
        category: json['category'],
        date: DateTime.parse(json['date']),
        note: json['note'],
      );
}
