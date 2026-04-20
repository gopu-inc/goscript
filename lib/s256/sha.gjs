module sha


fn sum(file: string, nf: string) -> string {
   if file == file || nf == nf {
      lt cmd = f"md5sum {file} >> {nf}"
      sysf(cmd)
      ret "ok"
   } else { 
      println("you are not definield 'file' patch >> sum('file', <- ..)")
   }
  ret 0
}
