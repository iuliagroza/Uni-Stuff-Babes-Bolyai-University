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

  // The toMap and fromMap methods remain unchanged
  // ...

  // If you're serializing/deserializing to/from JSON or another format,
  // ensure the category is validated there as well
  // ...
}
