import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'view_models/income_view_model.dart';
import 'views/income_list_view.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return ChangeNotifierProvider(
      create: (context) => IncomeViewModel(),
      child: MaterialApp(
        title: 'Budget Planner',
        theme: ThemeData(
          primarySwatch: Colors.blue,
          visualDensity: VisualDensity.adaptivePlatformDensity,
        ),
        home: const IncomeListView(),
      ),
    );
  }
}
