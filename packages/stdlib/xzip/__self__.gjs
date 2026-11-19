golem xzip
pub fn compress(data: string): string { ret gs_gzip_compress(data) }
pub fn decompress(data: string): string { ret gs_gzip_decompress(data) }
