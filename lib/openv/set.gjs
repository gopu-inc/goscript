module set

fn env(exp, value) {
   try {
      lt cmd = f"export '{exp}={value}'"
      sysf(cmd)
      ret true 
   } catch (e) {
      throw f"without {e}"
   }
   ret ""
}
