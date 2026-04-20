


pub fn encode(file: string, new_file: string) {
   lt result = sysf(f"base64 {file} >> {new_file}")
   ret result
}
fn main() {
   println("encode from fale : " + encode("file.txt", "fale") + " to " + sysf("cat fale"))
}
