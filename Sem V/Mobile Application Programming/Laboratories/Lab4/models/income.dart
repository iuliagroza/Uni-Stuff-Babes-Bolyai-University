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
}
