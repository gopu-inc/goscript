// Module: math_shapes
// Fournit des structures géométriques avec leurs implémentations

module math_shapes

struct Point {
    x: float,
    y: float
}

impl Point {
    fn distance_origin(self) {
        // Distance depuis l'origine (0, 0)
        ret (self.x * self.x + self.y * self.y) ^ 0.5
    }
    
    fn display(self) {
        println("Point(" + self.x + ", " + self.y + ")")
    }
}

struct Rectangle {
    width: int,
    height: int
}

impl Rectangle {
    fn area(self) {
        ret self.width * self.height
    }
    
    fn perimeter(self) {
        ret 2 * (self.width + self.height)
    }
}

// Exporter les implémentations
export { impl Point, impl Rectangle }
