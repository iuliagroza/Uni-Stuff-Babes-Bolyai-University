//
//  AddIncomeView.swift
//  BudgetPlanner
//
//  Created by Iulia Groza on 30.10.2023.
//

import SwiftUI

struct AddIncomeView: View {
    @Environment(\.presentationMode) var presentationMode
    @ObservedObject var viewModel: IncomeViewModel
    @State private var amount: String = ""
    @State private var category: String = "Salary"
    @State private var date = Date()
    @State private var notes: String = ""
    @State private var showingAlert = false // To show an alert if needed
    
    let categories = ["Salary", "Pension", "Investments", "Savings", "Other"]
    
    var body: some View {
        NavigationView {
            Form {
                TextField("Amount", text: $amount)
                    .keyboardType(.decimalPad)
                
                Picker("Category", selection: $category) {
                    ForEach(categories, id: \.self) {
                        Text($0)
                    }
                }
                
                DatePicker("Date", selection: $date)
                TextField("Notes", text: $notes)
                
                Button("Add Income") {
                    if isAmountValid() {
                        let newIncome = Income(id: UUID().uuidString, amount: Double(amount) ?? 0, category: category, date: date, notes: notes)
                        viewModel.addIncome(newIncome)
                        presentationMode.wrappedValue.dismiss()
                    } else {
                        showingAlert = true
                    }
                }
            }
            .navigationTitle("Add Income")
            .alert(isPresented: $showingAlert) {
                Alert(
                    title: Text("Invalid Amount"),
                    message: Text("Please enter a positive number for the amount."),
                    dismissButton: .default(Text("OK"))
                )
            }
        }
    }
    
    private func isAmountValid() -> Bool {
        guard let amountValue = Double(amount) else {
            return false // Not a valid number
        }
        return amountValue > 0 // The amount is positive
    }
}

