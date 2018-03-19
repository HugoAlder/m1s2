# Chargement de la base de noms d'animaux
source ("rdfAnimaux.txt")

n <- length(noms)

# Transforme un charactere en un entier correspondant à sa position dans l'alphabet
str2int <- function(x) { strtoi(charToRaw(x), 16L) -96 }

test <- str2int("test")

# La matric mat indique si une lettre est presente dans chaque mot du fichier rdfAnimaux.txt
# Colonne = mot
# Ligne = lettre
mat = matrix(rep(0, 26 * n), nrow = 26, ncol = n);
for (i in 1:n)
{
  c = str2int(noms[i]);
  mat[c, i] <- 1;
}

# Occurence d'au moins une lettre par mot
h <- vector(mode = "integer", length = 26)
for (i in 1:n)
{
  c = str2int(noms[i]);
  h[c] = h[c] + 1;
}

# Lettre la plus utilisee : e
maximum <- max(h)
maxchar <- match(maximum, h)