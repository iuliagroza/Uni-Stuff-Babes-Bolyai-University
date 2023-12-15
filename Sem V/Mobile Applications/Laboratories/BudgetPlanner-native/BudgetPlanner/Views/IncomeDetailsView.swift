import SwiftUI

struct IncomeDetailsView: View {
    @ObservedObject var viewModel: IncomeViewModel
    var income: Income
    @State private var showingDeleteAlert = false
    
    var body: some View {
        Form {
            HStack {
                Text("Amount:")
                Spacer()
                Text("\(income.amount)")
            }
            
            HStack {
                Text("Category:")
                Spacer()
                Text(income.category)
            }
            
            HStack {
                Text("Date:")
                Spacer()
                Text(income.date, formatter: itemFormatter)
            }
            
            HStack {
                Text("Notes:")
                Spacer()
                Text(income.notes)
            }
            NavigationLink(destination: EditIncomeView(viewModel: viewModel, income: income)) {
                            Text("Edit")
                                .foregroundColor(.blue)
                        }
        }
        .navigationTitle("Income Details")
        .navigationBarItems(trailing: Button(action: {
            showingDeleteAlert = true
        }) {
            Image(systemName: "trash")
                .foregroundColor(.red)
        })
        .alert(isPresented: $showingDeleteAlert) {
            Alert(
                title: Text("Delete Income"),
                message: Text("Are you sure you want to delete this income? This action cannot be undone."),
                primaryButton: .destructive(Text("Delete")) {
                    viewModel.deleteIncome(income)
                },
                secondaryButton: .cancel(Text("Keep"))
            )
        }
    }
}

private let itemFormatter: DateFormatter = {
    let formatter = DateFormatter()
    formatter.dateStyle = .medium
    return formatter
}()
