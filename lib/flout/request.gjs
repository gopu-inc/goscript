golem request
pub fn get_method(request: string): string { ret request.split(" ")[0] }
pub fn get_path(request: string): string { ret request.split(" ")[1] }
