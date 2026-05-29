// Exemple: Utilisation des imports d'impl

import math_shapes { impl Point, impl Rectangle }

fn main() {
    println("=== Test import impl ===\n")
    
    // Test Rectangle
    println("Test: Rectangle (10x20)")
    lt rect = new Rectangle {
        width: 10,
        height: 20
    }
    println("Area: " + rect::area())
    println("Perimeter: " + rect::perimeter())
    
    println("\nTest: Rectangle (5x15)")
    lt rect2 = new Rectangle {
        width: 5,
        height: 15
    }
    println("Area: " + rect2::area())
    println("Perimeter: " + rect2::perimeter())
    
    println("\nTest: Point")
    lt p = new Point {
        x: 3,
        y: 4
    }
    p::display()
    println("Distance squared: " + p::distance_squared())
    
    ret 0
}
