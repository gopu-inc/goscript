// Module switch avec types avancés

// Énumération pour les résultats
enm SwitchResult {
    Match,
    Default,
    Error,
    Break,
    Continue
}

// Type alias pour les cas
type Case = [any, any]

// Structure pour le switch
struct Switch {
    value: any,
    cases: []Case,
    default_value: any
}

// Implémentation du switch
impl Switch {
    pub fn new(value: any) Switch {
        ret Switch{
            value: value,
            cases: [],
            default_value: nil
        }
    }
    
    pub fn case(self, pattern: any, result: any) Switch {
        lt new_cases = self.cases
        new_cases = new_cases + [[pattern, result]]
        ret Switch{
            value: self.value,
            cases: new_cases,
            default_value: self.default_value
        }
    }
    
    pub fn default(self, result: any) Switch {
        ret Switch{
            value: self.value,
            cases: self.cases,
            default_value: result
        }
    }
    
    pub fn exec(self) any {
        for i = 0; i < len(self.cases); i = i + 1 {
            lt pattern = self.cases[i][0]
            lt result = self.cases[i][1]
            
            if self.value == pattern {
                ret result
            }
        }
        
        if self.default_value != nil {
            ret self.default_value
        }
        
        ret SwitchResult::Error
    }
}

// Fonction utilitaire exportée
pub fn match_value(value: any, cases: []Case, default_val: any) any {
    lt sw = Switch::new(value)
    
    for i = 0; i < len(cases); i = i + 1 {
        sw = sw.case(cases[i][0], cases[i][1])
    }
    
    sw = sw.default(default_val)
    ret sw.exec()
}

// Export des fonctions publiques
export {
    Switch,
    SwitchResult,
    Case,
    match_value
}
