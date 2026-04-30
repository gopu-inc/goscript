#!/usr/bin/env python3
import os
import sys
import requests
import tarfile
import platform
import subprocess

# --- Configuration ---
API_BASE = "https://gsql-badge.onrender.com"
MOD_DIR = "modules"
TOKEN_FILE = ".gpm_token"

class GPM:
    def __init__(self):
        if not os.path.exists(MOD_DIR):
            os.makedirs(MOD_DIR)

    def get_arch(self):
        # Mappe les noms Python vers tes dossiers serveur
        arch = platform.machine().lower()
        if arch in ['i386', 'i586', 'i686']:
            return "i686"
        return "x86_64"

    def get_token(self):
        if os.path.exists(TOKEN_FILE):
            with open(TOKEN_FILE, 'r') as f:
                return f.read().strip()
        return None

    def install(self, name, version="1.1.0", release="r0", is_public=True):
        mode = "public" if is_public else "private"
        arch = self.get_arch()
        
        # On tente d'abord l'architecture native, puis fallback x86_64
        archs_to_test = [arch, "x86_64"] if arch != "x86_64" else ["x86_64"]
        
        print(f"📦 Installation de {name} ({version})...")

        for target_arch in archs_to_test:
            url = f"{API_BASE}/package/download/{mode}/{name}/{version}/{release}/{target_arch}"
            print(f"🔍 Test {target_arch}...", end=" ", flush=True)

            headers = {}
            if mode == "private":
                token = self.get_token()
                if not token:
                    print("\n❌ Erreur: Token requis pour paquet privé.")
                    return
                headers["Authorization"] = f"Bearer {token}"

            try:
                with requests.get(url, headers=headers, stream=True) as r:
                    if r.status_code == 200:
                        print("✅ Trouvé !")
                        self.extract(r, name)
                        return True
                    else:
                        print(f"❌ Absent ({r.status_code})")
            except Exception as e:
                print(f"⚠️ Erreur connexion: {e}")

        print(f"❌ Impossible d'installer {name}")

    def extract(self, response, name):
        target_path = f"{name}.tar.bool"
        with open(target_path, 'wb') as f:
            for chunk in response.iter_content(chunk_size=8192):
                f.write(chunk)

        # Extraction
        dest_dir = os.path.join(MOD_DIR, name)
        if not os.path.exists(dest_dir):
            os.makedirs(dest_dir)

        try:
            with tarfile.open(target_path, "r:gz") as tar:
                tar.extractall(path=dest_dir)
            print(f"🚀 {name} déployé dans {dest_dir}")
        except Exception as e:
            # Si tarfile échoue (car ton .tar.bool est peut-être brut), on tente l'appel système
            print("⚠️ Extraction interne échouée, tentative via système...")
            subprocess.run(["tar", "-xf", target_path, "-C", dest_dir])

        if os.path.exists(target_path):
            os.remove(target_path)

# --- CLI Interface ---
if __name__ == "__main__":
    gpm = GPM()
    if len(sys.argv) < 2:
        print("Usage: python3 gpm.py install <package> [version]")
        sys.exit(1)

    command = sys.argv[1]
    if command == "install":
        pkg = sys.argv[2]
        ver = sys.argv[3] if len(sys.argv) > 3 else "1.1.0"
        gpm.install(pkg, ver)

