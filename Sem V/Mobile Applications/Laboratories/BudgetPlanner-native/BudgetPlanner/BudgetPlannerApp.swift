//
//  BudgetPlannerApp.swift
//  BudgetPlanner
//
//  Created by Iulia Groza on 29.10.2023.
//

import SwiftUI

@main
struct BudgetPlannerApp: App {
    @StateObject private var viewModel = IncomeViewModel()
    
    var body: some Scene {
        WindowGroup {
            IncomeListView(viewModel: viewModel)
        }
    }
}
