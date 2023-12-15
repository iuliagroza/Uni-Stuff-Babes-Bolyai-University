//
//  IncomeListView.swift
//  BudgetPlanner
//
//  Created by Iulia Groza on 30.10.2023.
//

import SwiftUI

struct IncomeListView: View {
    @ObservedObject var viewModel: IncomeViewModel
    
    var body: some View {
        NavigationView {
            VStack(spacing: 0) {
                Text(totalIncomeText())
                    .font(.largeTitle)
                    .fontWeight(.bold)
                    .padding(.top, 30)
                    .padding(.bottom, 30)
                ScrollView {
                    LazyVStack(spacing: 0) {
                        ForEach(viewModel.incomes) { income in
                            IncomeRowView(viewModel: viewModel, income: income)
                        }
                    }
                }
            }
            .navigationBarTitleDisplayMode(.inline)
            .toolbar {
                ToolbarItem(placement: .principal) {
                    VStack {
                        Spacer(minLength: 30)
                        Text("Income").font(.headline)
                    }
                }
                ToolbarItem(placement: .navigationBarTrailing) {
                    VStack {
                        Spacer(minLength: 30)
                        NavigationLink(destination: AddIncomeView(viewModel: viewModel)) {
                            Image(systemName: "plus").foregroundColor(Color.black)
                        }
                    }
                }
            }
        }
    }
    
    func deleteIncome(at offsets: IndexSet) {
        offsets.forEach { index in
            let income = viewModel.incomes[index]
            viewModel.deleteIncome(income)
        }
    }
    
    private func totalIncomeText() -> String {
            let total = viewModel.incomes.reduce(0) { $0 + $1.amount }
            // Format the total as currency
            let formatter = NumberFormatter()
            formatter.numberStyle = .currency
            formatter.locale = Locale.current // Adjust if necessary
            return formatter.string(from: NSNumber(value: total)) ?? "$\(total)"
        }

}

