import post
import get

// Ajout de 'lt' pour déclarer la variable
lt API = post::Env("CaTI", "MaGIC")

// 'API' contient le résultat de fs::append
if API {
    println("Env ajouté avec succès")
}

// Appel avec DEUX arguments (le nom ET le fichier)
lt EC = get::env("CaTI", ".openv")
println("La valeur lue est : " + EC)

