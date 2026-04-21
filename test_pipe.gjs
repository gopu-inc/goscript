// La commande 'sysf' reçoit la sortie précédente via le pipe
println(sysf("ls -la") |> sysf("grep .gjs") |> sysf("wc -l"))
