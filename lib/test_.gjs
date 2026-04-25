import http.__self__
import http.client

fn main() {
    println("=== TEST DU PACKAGE HTTP ===")
    
    // Accès au module racine (via __self__.gjs)
    println("Version HTTP : " + __self__::VERSION)
    
    // Accès aux sous-modules avec ::
    println("\nExécution d'une requête GET...")

    lt response = client::get("https://www.google.com/url?q=https://httpbin.org/&sa=U&sqi=2&ved=2ahUKEwjAh92GwoGUAxXRXkEAHcvmHNAQFnoECBAQAQ&usg=AOvVaw3K5N0e-erjTFd-w6Beo-zn")    
    lt res = client::post("https://www.google.com/url?q=https://httpbin.org/&sa=U&sqi=2&ved=2ahUKEwjAh92GwoGUAxXRXkEAHcvmHNAQFnoECBAQAQ&usg=AOvVaw3K5N0e-erjTFd-w6Beo-zn", "meta")
    println("POST exec ")
   
   // Affichage natif
    println(response)
    println(res)
    ret 0
}

