//
//  main.swift
//  lab2_mv_simpson
//
//  Created by Victoria Samsonova on 6.05.24.
//

import Foundation

func function(x: Double) -> Double {
    return exp(x) + x
}

func countSimpson(a: Double, b: Double ) -> Double{
    return (b-a)*(function(x: a)+4*function(x: (a+b)/2)+function(x: b))/6.0
}

print("Значение определенного интеграла от функции y = exp(x) + x на отрезке [0, 1] равно: \(countSimpson(a: 0, b: 1))")

