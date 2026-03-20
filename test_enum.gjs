enm Color {
    Red
    Green
    Blue
    Yellow
}

fn main() {
    println("=== ENUM TEST ===\n")
    
    lt colors = [Color::Red, Color::Green, Color::Blue, Color::Yellow]
    
    for i = 0; i < len(colors); i = i + 1 {
        lt color = colors[i]
        
        if color == Color::Red {
            println("   Rouge détecté!")
        } else if color == Color::Green {
            println("   Vert détecté!")
        } else if color == Color::Blue {
            println("   Bleu détecté!")
        } else if color == Color::Yellow {
            println("   Jaune détecté!")
        }
    }
    
    println("\n=== TEST RÉUSSI ===")
    ret 0
}
