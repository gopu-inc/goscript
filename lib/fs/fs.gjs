module_name fs

// Importe et ré-exporte toutes les fonctions
import_name search from "./search"
import_name open from "./open"
import_name read from "./read"
import_name write from "./write"
import_name mkdir from "./mkdir"
import_name cd from "./cd"
import_name rm from "./rm"
import_name cp from "./cp"
import_name mv from "./mv"
import_name chmod from "./chmod"

// Search
pub fn search_path(path: string): string { ret search::search_path(path) }
pub fn search_info(path: string): string { ret search::search_info(path) }
pub fn search_all(path: string): string { ret search::search_all(path) }
pub fn search_pattern(path: string, pattern: string): string { ret search::search_pattern(path, pattern) }
pub fn find_files(path: string, name: string): string { ret search::find_files(path, name) }
pub fn find_dirs(path: string, name: string): string { ret search::find_dirs(path, name) }
pub fn file_exists(path: string): string { ret search::file_exists(path) }
pub fn dir_exists(path: string): string { ret search::dir_exists(path) }
pub fn file_size(path: string): string { ret search::file_size(path) }
pub fn file_type(path: string): string { ret search::file_type(path) }
pub fn current_dir(): string { ret search::current_dir() }

// Read
pub fn read_file(path: string): string { ret open::read_file(path) }
pub fn read_lines(path: string): string { ret open::read_lines(path) }
pub fn read_bytes(path: string, count: string): string { ret read::bytes(path, count) }
pub fn count_lines(path: string): string { ret read::lines(path) }

// Write
pub fn write_file(path: string, content: string): string { ret write::file(path, content) }
pub fn append_file(path: string, content: string): string { ret write::append(path, content) }

// Mkdir
pub fn mkdir(path: string): string { ret mkdir::dir(path) }
pub fn mkdir_temp(): string { ret mkdir::temp() }

// Cd
pub fn cd(path: string): string { ret cd::to(path) }
pub fn cd_home(): string { ret cd::home() }
pub fn cd_up(): string { ret cd::up() }

// Rm
pub fn rm_file(path: string): string { ret rm::file(path) }
pub fn rm_dir(path: string): string { ret rm::dir(path) }

// Cp
pub fn cp_file(src: string, dst: string): string { ret cp::file(src, dst) }
pub fn cp_dir(src: string, dst: string): string { ret cp::dir(src, dst) }

// Mv
pub fn mv_file(src: string, dst: string): string { ret mv::file(src, dst) }
pub fn rename(old_name: string, new_name: string): string { ret mv::rename(old_name, new_name) }

// Chmod
pub fn chmod(path: string, mode: string): string { ret chmod::set(path, mode) }
pub fn make_executable(path: string): string { ret chmod::executable(path) }

