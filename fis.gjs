;; Importation locale
(nm "fs")

(let contenu "Salut, ceci est écrit depuis GoScript !")
(write "test.txt" contenu)

(let lecture (read "test.txt"))
(print "Contenu du fichier :" lecture)
