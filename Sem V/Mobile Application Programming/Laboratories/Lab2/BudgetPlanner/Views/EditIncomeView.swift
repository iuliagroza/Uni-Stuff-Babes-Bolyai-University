//
//  EditIncomeView.swift
//  BudgetPlanner
//
//  Created by Iulia Groza on 30.10.2023.
//

import SwiftUI

struct EditIncomeView: View {
    @Environment(\.presentationMode) var presentationMode
    var viewModel: IncomeViewModel
    var income: Income
    
    @State private var updatedAmount: String
    @State private var updatedCategory: String
    @State private var updatedDate: Date
    @State private var updatedNotes: String
    @State private var showingAlert = false // To show an alert if needed
    
    let categories = ["Salary", "Pension", "Investments", "Savings", "Other"]
    
    init(viewModel: IncomeViewModel, income: Income) {
        self.viewModel = viewModel
        self.income = income
        _updatedAmount = State(initialValue: String(income.amount))
        _updatedCategory = State(initialValue: income.category)
        _updatedDate = State(initialValue: income.date)
        _updatedNotes = State(initialValue: income.notes)
    }
    
    var body: some View {
        NavigationView {
            Form {
                TextField("Amount", text: $updatedAmount)
                    .keyboardType(.decimalPad)
                
                Picker("Category", selection: $updatedCategory) {
                    ForEach(categories, id: \.self) {
                        Text($0)
                    }
                }
                
                DatePicker("Date", selection: $updatedDate)
                TextField("Notes", text: $updatedNotes)
                
                Button("Save Changes") {
                    if isAmountValid() {
                        var updatedIncome = income
                        updatedIncome.amount = Double(updatedAmount) ?? income.amount
                        updatedIncome.category = updatedCategory
                        updatedIncome.date = updatedDate
                        updatedIncome.notes = updatedNotes
                        viewModel.updateIncome(updatedIncome)
                        presentationMode.wrappedValue.dismiss()
                    } else {
                        showingAlert = true
                    }
                }
            }
            .navigationTitle("Edit Income")
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
        guard let amountValue = Double(updatedAmount) else {
            return false // Not a valid number
        }
        return amountValue > 0 // The amount is positive
    }
}




