import gsql
import ui

fn main() {
    println(ui::green("--- Initialisation GSQL ---"))
     
    gsql::Ginit() 
    // 1. Création de la table 'users' dans la db 'master'
    lt users = gsql::create_table("master", "users")
    
    // 2. Insertion de données (format clé-valeur ou CSV)
    gsql::insert(users, "id=1,nom=Mauricio,role=admin")
    gsql::insert(users, "id=2,nom=Leo,role=user")
    
    gsql::insert(users, "id=3,nom=Diego,role=marchant")
    // 3. Requête (SELECT)
    println("Recherche de l'admin...")
    lt admin = gsql::select_where(users, "role=admin")
    println("Résultat : " + admin)
    lt pp = gsql::select_where(users, "nom=Leo")  
    println(pp)
}

