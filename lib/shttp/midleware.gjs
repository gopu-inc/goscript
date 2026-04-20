// lib/shttp/middleware.gjs
import ft from "../time/ft"


module midleware
// Logger middleware
pub fn logger(): Middleware {
    ret lambda ctx {
        lt start = ft::sleep(null)
        lt method = ctx.request.method
        lt path = ctx.request.path
        
        // Continuer la chaîne
        ctx.next()
        
        lt duration = ft::sleep(null) - start
        println method + " " + path + " " + ctx.response.status + " " + duration + "ms"
    }
}

// CORS middleware
pub fn cors(): Middleware {
    ret lambda ctx {
        ctx.response.header("Access-Control-Allow-Origin", "*")
        ctx.response.header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS")
        ctx.response.header("Access-Control-Allow-Headers", "Content-Type, Authorization")
        
        if ctx.request.method == "OPTIONS" {
            ctx.response.status(204).send("")
            ret
        }
        
        ctx.next()
    }
}

// Static files middleware
pub fn static_files(root: string): Middleware {
    ret lambda ctx {
        lt path = ctx.request.path
        lt file_path = root + path
        
        if file_exists(file_path) {
            ctx.response.file(file_path)
        } else {
            ctx.next()
        }
    }
}

// Authentication middleware
pub fn auth(token: string): Middleware {
    ret lambda ctx {
        lt auth_header = ctx.request.headers["Authorization"]
        
        if auth_header == "Bearer " + token {
            ctx.next()
        } else {
            ctx.response.status(401).json({
                "error": "Unauthorized",
                "message": "Invalid or missing authentication token"
            })
        }
    }
}

// Basic Auth middleware
pub fn basic_auth(username: string, password: string): Middleware {
    ret lambda ctx {
        lt auth_header = ctx.request.headers["Authorization"]
        
        if auth_header && auth_header.starts_with("Basic ") {
            lt encoded = auth_header.substring(6)
            lt decoded = base64_decode(encoded)
            lt parts = decoded.split(":")
            
            if parts.length == 2 && parts[0] == username && parts[1] == password {
                ctx.next()
                ret
            }
        }
        
        ctx.response.status(401)
        ctx.response.header("WWW-Authenticate", "Basic realm=\"Restricted\"")
        ctx.response.send("Unauthorized")
    }
}

// Rate limiting middleware
pub fn rate_limit(max_requests: int, window_seconds: int): Middleware {
    lt requests = {}
    
    ret lambda ctx {
        lt ip = ctx.request.ip()
        lt now = time_c(null)
        
        // Nettoyer les vieilles requêtes
        if requests[ip] {
            requests[ip] = requests[ip].filter(lambda t { ret now - t < window_seconds })
        } else {
            requests[ip] = []
        }
        
        // Vérifier la limite
        if requests[ip].length >= max_requests {
            ctx.response.status(429).json({
                "error": "Too Many Requests",
                "message": "Rate limit exceeded. Try again in " + window_seconds + " seconds."
            })
            ret
        }
        
        // Ajouter la requête
        requests[ip].push(now)
        ctx.next()
    }
}

// Compression middleware
pub fn compress(): Middleware {
    ret lambda ctx {
        lt accept_encoding = ctx.request.headers["Accept-Encoding"]
        
        if accept_encoding && accept_encoding.contains("gzip") {
            ctx.response.header("Content-Encoding", "gzip")
            // La compression serait faite ici
        }
        
        ctx.next()
    }
}

// Recovery middleware (catch panics)
pub fn recovery(): Middleware {
    ret lambda ctx {
        // Dans un environnement réel, on utiliserait try-catch
        // Ici on simule avec un système de panic/recover
        ctx.next()
    }
}

// Body parser middleware
pub fn body_parser(): Middleware {
    ret lambda ctx {
        if ctx.request.method == "POST" || ctx.request.method == "PUT" || ctx.request.method == "PATCH" {
            lt content_type = ctx.request.headers["Content-Type"]
            
            if content_type && content_type.contains("application/json") {
                ctx.request.body_json = parse_json(ctx.request.body())
            } else if content_type && content_type.contains("application/x-www-form-urlencoded") {
                ctx.request.body_form = parse_form_data(ctx.request.body())
            }
        }
        
        ctx.next()
    }
}
