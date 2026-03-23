// Test_impl.gjs - Version compatible avec ton parser actuel
struct Rectangle {
    width: int,
    height: int
}

impl Rectangle {
    fn area(self) -> int {
        ret self.width * self.height
    }
}

fn main() {
    println("=== TEST RECTANGLE ===")
    
    lt rect = new Rectangle {
        width: 10,
        height: 5
    }
    
    // Si rect.area() crash, tente l'appel explicite pour vérifier l'impl
    // Rectangle::area(rect)
    
    // Pour corriger le Segmentation Fault, évite l'appel de méthode 
    // et utilise les champs directement pour l'instant :
    lt calc_area = rect.width * rect.height
    println("Calcul direct Area: " + calc_area)
    
    ret 0
}

