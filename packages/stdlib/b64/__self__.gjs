golem b64
pub fn encode(data: string): string { ret gs_base64_encode(data) }
pub fn decode(data: string): string { ret gs_base64_decode(data) }
