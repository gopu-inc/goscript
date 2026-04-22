// test_sysf.gjs
println("=== Test de sysf et sh ===")

// sysf comme statement (pas d'assignation)
a = sysf "ls -la"
println(a)
// sh comme statement
sh "mkdir -p /tmp/goscript_test"
