module Class

import __builtin__

pub struct BaseObject {
    id: int
    created_at: int
    classname: string
}

impl BaseObject {
    pub fn __new(name) {
        return new BaseObject {
            id: rand_c(),
            created_at: now(),
            classname: name
        }
    }

    pub fn inspect(self) {
        print("<Object ")
        print(self.classname)
        print(" #")
        print(self.id)
        println(">")
    }
}

pub fn create(name) {
    return BaseObject::__new(name)
}
