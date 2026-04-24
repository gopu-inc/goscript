module xzip

// Compresse une chaîne et la retourne en Base64
pub fn compress(data: string): string {
    lt cmd = "python3 -c \"import gzip, base64, sys; print(base64.b64encode(gzip.compress(sys.argv[1].encode())).decode())\" '" + data + "'"
    ret sysf(cmd)
}

// Décompresse une chaîne Base64 (compressée en gzip) vers le texte original
pub fn decompress(b64_data: string): string {
    lt cmd = "python3 -c \"import gzip, base64, sys; print(gzip.decompress(base64.b64decode(sys.argv[1])).decode())\" '" + b64_data + "'"
    ret sysf(cmd)
}

