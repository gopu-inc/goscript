// lib/time/ft.gjs - Version minimale
module ft

pub fn str(s: any) {
   ret atoi_c(s)
}
pub fn sleep(seconds: int): int {
    lt pp = system_c("sleep " + seconds)
    ret pp
}
