struct Rectangle {
    width: int,
    height: int
}

impl Rectangle {
    // Utilise -> au lieu de : pour le retour
    fn area(self) -> int {
        ret self.width * self.height
    }
    
    fn perimeter(self) -> int {
        ret (self.width + self.height) * 2
    }
    
    fn scale(self, factor: int) -> Rectangle {
        ret new Rectangle {
            width: self.width * factor,
            height: self.height * factor
        }
    }
}

fn main() {
    println("=== TEST RECTANGLE + BUILTIN ===")
    
    // Utilisation d'une constante du Built-in chargé auto
    println("Valeur de PI via builtin: " + PI)
    
    lt rect = new Rectangle {
        width: 10,
        height: 5
    }
    
    // Test des méthodes
    lt a = rect.area()
    println("Area: " + a)
    
    // Test d'une fonction utilitaire du builtin
    lt m = max(rect.width, rect.height)
    println("Max dimension: " + m)
    
    ret 0
}

