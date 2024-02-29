//
//  ContentView.swift
//  BudgetPlanner
//
//  Created by Iulia Groza on 06.11.2023.
//

import SwiftUI

struct NavBarView: View {
    var body: some View {
        TabView {
            // Budget View
            Text("Budget View")
                .tabItem {
                    Image(systemName: "wallet.pass.fill")
                        .foregroundColor(.purple)
                    Text("Budget")
                }

            // Income View
            Text("Income View")
                .tabItem {
                    Image(systemName: "arrow.down.circle.fill")
                        .foregroundColor(.purple)
                    Text("Income")
                }

            // Expenses View
            Text("Expenses View")
                .tabItem {
                    Image(systemName: "arrow.up.circle.fill")
                        .foregroundColor(.purple)
                    Text("Expenses")
                }

            // Theme View
            Text("Theme View")
                .tabItem {
                    Image(systemName: "paintbrush.fill")
                        .foregroundColor(.purple)
                    Text("Theme")
                }
        }
        .accentColor(.purple)
    }
}

struct NavBarView_Previews: PreviewProvider {
    static var previews: some View {
        NavBarView()
    }
}

