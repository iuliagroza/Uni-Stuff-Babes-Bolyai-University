// ignore_for_file: avoid_print

import 'dart:convert';
// ignore: depend_on_referenced_packages
import 'package:web_socket_channel/web_socket_channel.dart';
import '../models/income.dart';

class WebSocketListener {
  final String _url;
  late WebSocketChannel _channel; // Marked as late
  Function(Income) onIncomeUpdate;

  WebSocketListener(this._url, {required this.onIncomeUpdate}) {
    _connect();
  }

  void _connect() {
    _channel = WebSocketChannel.connect(Uri.parse(_url));
    _channel.stream.listen(_onReceivingIncomeUpdate, onError: _onError);
  }

  void _onReceivingIncomeUpdate(dynamic message) {
    try {
      final Map<String, dynamic> incomeMap = json.decode(message);
      final Income updatedIncome = Income.fromJson(incomeMap);
      onIncomeUpdate(updatedIncome);
    } catch (e) {
      print("Error in receiving or parsing income data: $e");
    }
  }

  void _onError(error) {
    print("WebSocket error: $error");
  }

  void dispose() {
    _channel.sink.close();
  }
}
