import fs
import ui

golem gpm

lt API_BASE = "https://gsql-badge.onrender.com"
lt MOD_DIR = "modules"

pub fn init_env(): bool { ret gs_fs_mkdir(MOD_DIR) == 1 }

pub fn install(name: string, version: string, release: string, is_public: bool): bool {
    ui::banner("GPM DEPLOY: " + name)
    lt mode = "private"
    if is_public { mode = "public" }
    lt v = version
    if v == "" { v = "1.1.0" }
    lt r = release
    if r == "" { r = "r0" }
    lt url = API_BASE + "/package/download/" + mode + "/" + name + "/" + v + "/" + r + "/x86_64"
    lt archive = name + ".tar.bool"
    if gs_http_download(url, archive, "") != 1 { ret false }
    lt success = gs_tar_unpack(archive, MOD_DIR)
    gs_fs_remove(archive)
    ret success == 1
}
