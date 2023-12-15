//
//  IncomeViewModel.swift
//  BudgetPlanner
//
//  Created by Iulia Groza on 30.10.2023.
//

import Foundation

class IncomeViewModel: ObservableObject {
    @Published var incomes: [Income] = []
    
    init() {
            // Prepopulate with 5 incomes
            self.incomes = [
                Income(id: UUID().uuidString, amount: 5000, category: "Salary", date: Date(), notes: "Salary from month May"),
                Income(id: UUID().uuidString, amount: 1500, category: "Pension", date: Date().addingTimeInterval(-86400), notes: ""),
                Income(id: UUID().uuidString, amount: 300, category: "Investments", date: Date().addingTimeInterval(-2 * 86400), notes: "Stocks investments"),
                Income(id: UUID().uuidString, amount: 1200, category: "Salary", date: Date().addingTimeInterval(-3 * 86400), notes: ""),
                Income(id: UUID().uuidString, amount: 450, category: "Other", date: Date().addingTimeInterval(-4 * 86400), notes: "Gift from a friend")
            ]
        }
    
    func addIncome(_ income: Income) {
        incomes.append(income)
    }
    
    func updateIncome(_ updatedIncome: Income) {
        if let index = incomes.firstIndex(where: { $0.id == updatedIncome.id }) {
            incomes[index] = updatedIncome
        }
    }
    
    func deleteIncome(_ income: Income) {
        incomes.removeAll { $0.id == income.id }
    }
}
