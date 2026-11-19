golem tar
pub fn pack(source: string, output: string): bool { ret gs_tar_pack(source, output) == 1 }
pub fn unpack(archive: string, destination: string): bool { ret gs_tar_unpack(archive, destination) == 1 }
