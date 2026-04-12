module upload

pub fn file(url: string, file_path: string): string {
    lt cmd = "sh -c \"curl -s -X POST -F 'file=@" + file_path + "' " + url + "\""
    lt result = await cmd
    ret result
}

pub fn file_with_name(url: string, file_path: string, field_name: string): string {
    lt cmd = "sh -c \"curl -s -X POST -F '" + field_name + "=@" + file_path + "' " + url + "\""
    lt result = await cmd
    ret result
}
