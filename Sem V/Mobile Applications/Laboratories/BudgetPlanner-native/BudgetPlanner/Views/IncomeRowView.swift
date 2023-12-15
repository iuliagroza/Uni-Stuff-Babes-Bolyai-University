//
//  IncomeRowView.swift
//  BudgetPlanner
//
//  Created by Iulia Groza on 30.10.2023.
//

import SwiftUI

struct IncomeRowView: View {
    @ObservedObject var viewModel: IncomeViewModel
    var income: Income
    @State private var activeLinkId: String?
    @State private var showingDeleteAlert = false

    func iconName(forCategory category: String) -> String {
        switch category {
        case "Salary":
            return "briefcase.fill"
        case "Pension":
            return "dollarsign.circle.fill"
        case "Investments":
            return "chart.pie.fill"
        case "Savings":
            return "banknote.fill"
        case "Other":
            return "questionmark.circle.fill"
        default:
            return "questionmark.circle.fill"
        }
    }

    var body: some View {
        VStack {
            HStack {
                Image(systemName: iconName(forCategory: income.category))
                    .foregroundColor(.purple)
                    .font(.system(size: 34))
                    .padding(.leading, 18)

                NavigationLink(destination: IncomeDetailsView(viewModel: viewModel, income: income),
                               tag: income.id,
                               selection: $activeLinkId) {
                    EmptyView()
                }
                .hidden()

                NavigationLink(destination: IncomeDetailsView(viewModel: viewModel, income: income)) {
                    HStack {
                        VStack(alignment: .leading, spacing: 18) {
                            Text(income.category)
                                .font(.headline)

                            HStack {
                                Text("$\(String(format: "%.2f", income.amount))")
                                    .font(.subheadline)
                                Text("|")
                                    .font(.subheadline)
                                    .foregroundColor(.gray)
                                Text("\(income.date, formatter: itemFormatter)")
                                    .font(.subheadline)
                            }
                        }
                        Spacer()
                    }
                    .padding()
                    .background(Color.white)
                }
                .buttonStyle(PlainButtonStyle())

                Menu {
                    Button("View Income Details") {
                        activeLinkId = income.id
                    }
                    Button("Delete", role: .destructive) {
                        showingDeleteAlert = true
                    }
                } label: {
                    Image(systemName: "ellipsis")
                        .imageScale(.large)
                        .rotationEffect(.degrees(90))
                        .foregroundColor(.gray)
                }
                .buttonStyle(BorderlessButtonStyle())

                Spacer().frame(width: 20)
            }
            .cardStyle()
        }
        .padding(.horizontal)
        .padding(.vertical, 5)
        .alert(isPresented: $showingDeleteAlert) {
            Alert(
                title: Text("Confirm Delete"),
                message: Text("Are you sure you want to delete this income?"),
                primaryButton: .destructive(Text("Delete")) {
                    viewModel.deleteIncome(income)
                },
                secondaryButton: .cancel()
            )
        }
    }
}

private let itemFormatter: DateFormatter = {
    let formatter = DateFormatter()
    formatter.dateFormat = "MMM dd, yyyy"
    return formatter
}()






