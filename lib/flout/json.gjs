module json

pub fn parse(json_str: string): string {
    lt cmd = "echo \"$1\" | python3 -c \"import json,sys; print(json.loads(sys.stdin.read()))\" 2>/dev/null"
    lt result = await cmd
    ret result
}
