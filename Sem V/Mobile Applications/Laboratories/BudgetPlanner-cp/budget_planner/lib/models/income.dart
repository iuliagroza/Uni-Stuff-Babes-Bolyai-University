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
}
