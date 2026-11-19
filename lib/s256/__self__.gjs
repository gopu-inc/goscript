golem s256

import s256.sha as hashmod

pub fn sha256(value: string): string {
    ret hashmod::sha256(value)
}

pub fn file_sha256(path: string): string {
    ret hashmod::file_sha256(path)
}
