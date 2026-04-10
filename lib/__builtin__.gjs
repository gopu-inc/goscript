module __builtin__

fn typs(obj) {
   if obj == int {
      ret "int"
   }
   if obj == string {
      ret "string"
   }
   if obj == float {
      ret "float"
   ret 0

