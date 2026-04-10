module __builtin__

struct GetMod {
   inter: int,
   stringer: string,
   floater: float
}
/*
 function type of get mod and sizer use programme
 symplify developing goscript any sample
 use: typs("obj") type of -> result string 
*/
/* 
fn typs(obj) {
  lt p = new GetMod {
   inter: obj,
   striger: obj,
   floater: obj
   }
   
   lt m = obj = string
   lt mm = obj = int
   lt mmm = obj = float
   cn cbj = (if obj == mm  {
      ret obj + "int"
   }
   
   if obj == m {
      ret obj + "string"
   }
   if obj == mmm  {
      ret obj + "float"
   })
   
   ret cbj
}
*/
/*
 char one input create arguments
*/
fn inputln(arg) {
   if arg == 0 {
      while arg < 0 {
         arg = arg * 10
         println(arg)
      }
      for args in arg {
         while args < 0 {
            args = args * 10
            println(args)
            continue
         }
       }
    }
    ret arg
}
/*
 string compare all arguments is true and false
*/
fn __str(s1, s2) {
   ret s1 == s2
}

fn __dict(args) {
   ret "[" + args + "]"
}
fn __stri(s1, s2) {
   ret s1 > s2
}
fn __floater(ann: int) {
   ret ann + ".0"
}
