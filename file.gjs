// module switchb

fn switch(a: int || float, b: int || float) {
   enm skip(
      pass
      break
      saute
      ok
   )
   type continue(
      skip::pass
      skip::break
      skip::saute
   )
   if a == int {
      ret continue.skip::break
   } elseif a == float {
      ret continue.skip::pass
   }
   if b == int {
      ret continue.skip::saute
   } elseif b == float {
      ret continue.skip::break
   }
ret skip::ok
}
pub fn constructor() {
   impl: 
        cn switch = switch(<param>)
        if switch >= 0 {
           ret f"{s}"
        } else {
           ret f"{e}"
        }
   eval:
       switch::<param>
}

   
        
