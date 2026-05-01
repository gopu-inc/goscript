import os
import os.env


fn main() {

   lt envs = env::getenv("API_KEY_ENV")
   println(envs)
}
