
// ============================================
// STRUCTD - Module avancé pour structures
// Héritage, méthodes, pattern matching
// ============================================

// ========== CLASSES AVEC HÉRITAGE ==========

// Classe de base Object
struct Object {
    name: string
}

// Méthodes de base pour Object
impl Object {
    fn to_string(self: Object): string {
        ret "Object(" + self.name + ")"
    }
    
    fn equals(self: Object, other: Object): bool {
        ret self.name == other.name
    }
    
    fn clone(self: Object): Object {
        ret new Object{name: self.name}
    }
}

// Exemple d'héritage
struct Person extends Object {
    age: int
    email: string
}

impl Person {
    fn to_string(self: Person): string {
        ret "Person(" + self.name + ", " + self.age + ")"
    }
    
    fn greet(self: Person): string {
        ret "Hello, I'm " + self.name + " and I'm " + self.age + " years old"
    }
    
    fn birthday(self: Person): Person {
        ret new Person{
            name: self.name,
            age: self.age + 1,
            email: self.email
        }
    }
}

struct Employee extends Person {
    salary: int
    position: string
}

impl Employee {
    fn to_string(self: Employee): string {
        ret "Employee(" + self.name + ", " + self.age + ", " + self.position + ")"
    }
    
    fn work(self: Employee): string {
        ret self.name + " is working as " + self.position
    }
    
    fn raise_salary(self: Employee, amount: int): Employee {
        ret new Employee{
            name: self.name,
            age: self.age,
            email: self.email,
            salary: self.salary + amount,
            position: self.position
        }
    }
}

// ========== UTILITAIRES GÉNÉRAUX ==========

// Pattern matching sur structure
pub fn match_struct(obj, patterns) {
    muts type_name = type_of(obj)
    muts i = 0
    while i < len(patterns) {
        if patterns[i].type == type_name {
            ret patterns[i].handler(obj)
        }
        i = i + 1
    }
    ret null
}

// Instanceof - vérifier le type
pub fn instance_of(obj, class_name: string): bool {
    ret type_of(obj) == class_name
}

// Obtenir la classe parente
pub fn parent_class(class_name: string): string {
    match class_name {
        "Employee" => ret "Person"
        "Person" => ret "Object"
        _ => ret ""
    }
}

// ========== UTILITAIRES STRUCTURE ==========

// Convertir structure en map
pub fn to_map(obj) {
    muts result = {}
    muts fields_list = fields(obj)
    muts i = 0
    while i < len(fields_list) {
        result[fields_list[i]] = get(obj, fields_list[i])
        i = i + 1
    }
    ret result
}

// Convertir map en structure
pub fn from_map(class_name: string, map) {
    match class_name {
        "Object" => ret new Object{name: map.name}
        "Person" => ret new Person{
            name: map.name,
            age: map.age,
            email: map.email
        }
        "Employee" => ret new Employee{
            name: map.name,
            age: map.age,
            email: map.email,
            salary: map.salary,
            position: map.position
        }
        _ => ret null
    }
}

// Sérialisation JSON
pub fn to_json(obj) {
    match type_of(obj) {
        "Object" => ret "{\"type\":\"Object\",\"name\":\"" + obj.name + "\"}"
        "Person" => ret "{\"type\":\"Person\",\"name\":\"" + obj.name + "\",\"age\":" + obj.age + ",\"email\":\"" + obj.email + "\"}"
        "Employee" => ret "{\"type\":\"Employee\",\"name\":\"" + obj.name + "\",\"age\":" + obj.age + ",\"email\":\"" + obj.email + "\",\"salary\":" + obj.salary + ",\"position\":\"" + obj.position + "\"}"
        "int" => ret obj
        "string" => ret "\"" + obj + "\""
        "bool" => ret obj ? "true" : "false"
        "array" => {
            muts result = "["
            muts i = 0
            while i < len(obj) {
                result = result + to_json(obj[i])
                if i < len(obj) - 1 {
                    result = result + ","
                }
                i = i + 1
            }
            ret result + "]"
        }
        _ => ret "null"
    }
}

// Clone profond
pub fn clone(obj) {
    match type_of(obj) {
        "Object" => ret new Object{name: obj.name}
        "Person" => ret new Person{
            name: obj.name,
            age: obj.age,
            email: obj.email
        }
        "Employee" => ret new Employee{
            name: obj.name,
            age: obj.age,
            email: obj.email,
            salary: obj.salary,
            position: obj.position
        }
        "array" => {
            muts result = []
            muts i = 0
            while i < len(obj) {
                result = push(result, clone(obj[i]))
                i = i + 1
            }
            ret result
        }
        _ => ret obj
    }
}

// Égalité profonde
pub fn equals(a, b): bool {
    if type_of(a) != type_of(b) {
        ret false
    }
    
    match type_of(a) {
        "Object" => ret a.name == b.name
        "Person" => ret a.name == b.name && a.age == b.age && a.email == b.email
        "Employee" => ret a.name == b.name && a.age == b.age && a.email == b.email && 
                         a.salary == b.salary && a.position == b.position
        "array" => {
            if len(a) != len(b) {
                ret false
            }
            muts i = 0
            while i < len(a) {
                if !equals(a[i], b[i]) {
                    ret false
                }
                i = i + 1
            }
            ret true
        }
        _ => ret a == b
    }
}

// Afficher structure
pub fn dump(obj) {
    println("=== STRUCTURE DUMP ===")
    println("Type: " + type_of(obj))
    println("JSON: " + to_json(obj))
    println("===================")
}

// ========== INITIALISATION ==========
info("structd module loaded - Advanced OOP features")
