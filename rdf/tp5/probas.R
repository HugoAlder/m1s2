library ("EBImage")
source ("rdfSegmentation.R")

# Chargement des images Q2 - Q3 - Q4
image <- rdfReadGreyImage("2classes_100_100_8bits_2016.png")
omega1 <- rdfReadGreyImage("2classes_100_100_8bits_omega1_2016.png")
omega2 <- rdfReadGreyImage("2classes_100_100_8bits_omega2_2016.png")

# Chargement des images Q5
image <- rdfReadGreyImage("rdf-chiffre-0-8bits.png")
omega1 <- rdfReadGreyImage("rdf-chiffre-0-8bits_omega1.png")
omega2 <- rdfReadGreyImage("rdf-chiffre-0-8bits_omega2.png")

nbins <- 256

h <- hist (as.vector (image), breaks = seq (0, 1, 1 / nbins))
h1 <- hist (as.vector (omega1), breaks = seq (0, 1, 1 / nbins))
h2 <- hist (as.vector (omega2), breaks = seq (0, 1, 1 / nbins))

# Q2

# Nombre de pixels total
total <- sum(h$counts)

# Nombre de pixels d'une classe / total
pw1 = sum(h1$counts) / total
pw2 = sum(h2$counts) / total

# Q3

# 142 = 141
X = 142


# Nombre de pixels de niveau de gris X de l'image de base / total
pXI = h$counts[X] / total

# Nombre de pixels d'une classe de niveau de gris X / nombre de pixels de cette classe
pXw1 = h1$counts[X] / sum(h1$counts)
pXw2 = h2$counts[X] / sum(h2$counts)

# Q4

# Pour le seuil X calcul de l'erreur d'assignation
somme1 = 0:255 # pE1 soit pw1X
somme2 = 0:255 # pE2 soit pw2X
erreur = 0:255 # pX

# Recherche du minimum
minimum_erreur = 1;
seuil_minimum_erreur = 0;

for (X in 1:255) 
{
  somme1[X+1] = sum(h1$counts[(X+1):256])/sum(h1$counts[1:256])
  somme1[X+1] = somme1[X+1] * omega1
  
  somme2[X+1] = sum(h2$counts[1:(X+1)])/sum(h2$counts[1:256])
  somme2[X+1] = somme2[X+1] * omega2
  
  erreur[X+1] = somme1[X+1] + somme2[X+1]
  
  # Seuil corrrespondant à l'erreur minimale
  if (erreur[X+1] < minimum_erreur ) {
    seuil_minimum_erreur = X
    minimum_erreur = erreur[X+1]
  }
}

final_image <- (image - seuil_minimum_erreur/255) >= 0
display(final_image, method="raster")