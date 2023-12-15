//
//  CardStyleModifier.swift
//  BudgetPlanner
//
//  Created by Iulia Groza on 05.11.2023.
//

import SwiftUI

extension View {
    func cardStyle(backgroundColor: Color = .white, cornerRadius: CGFloat = 18) -> some View {
        self
            .background(backgroundColor)
            .cornerRadius(cornerRadius)
            .shadow(color: .gray, radius: 2, x: 0.5, y: 2) // Adjust shadow to your liking
    }
}

