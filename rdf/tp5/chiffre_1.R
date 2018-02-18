library ("EBImage")
source ("rdfSegmentation.R")

# Chargement de l'image
image <- rdfReadGreyImage("rdf-chiffre-1-8bits.png")
solution <- rdfReadGreyImage("rdf-chiffre-1-8bits_classe_a_trouver.png")

# Q5

# Seuil trouvé à la question précédente
seuil <- 146
nbins <- 256

final_image <- (image - seuil/255) >= 0
display(final_image, method="raster")

# Q6

res <- (solution - final_image)

hres <- hist(as.vector (res), breaks = seq (1, 1, 1 / nbins))

acc1 = 0
acc2 = 0

# Accumulation de 2 à 256
for (i in 3:255) {
  acc1 = acc1 + hres$density[i]
}

# Accumulation de 1 à 256
for (j in 2:255) {
  acc2 = acc2 + hres$density[j]
}

# Taux d'erreur
err <- acc1/acc2