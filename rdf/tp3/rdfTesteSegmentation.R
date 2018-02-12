# -----------------------------------------------------------------------
# Extraction d'attributs de pixels pour la classification,
# Module RdF, reconnaissance de formes
# Copyleft (C) 2014, Universite Lille 1
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
# -----------------------------------------------------------------------

# Chargement des fonctions externes
library ("EBImage")
source ("rdfSegmentation.R")

# Chargement d'une image
#nom <- "rdf-2-classes-texture-1.png"
#image <- rdfReadGreyImage (nom)
#masque <-  rdfReadGreyImage("rdf-masque-ronds.png")

# Calcul et affichage de son histogramme
#nbins <- 1024
#h <- hist (as.vector (image), breaks = seq (0, 1, 1 / nbins))

# Segmentation par binarisation
#euil <- 0.56
#binaire <- (image - seuil) >= 0

#Affichage des deux images
#if (interactive ()) {
 #display (image, nom)
 #display (binaire, "image binaire")
#}

#a <- masque
#b <- binaire
#c <- sum(abs(a - b))
#d <- (c/(ncol(a)*nrow((b))))*100
#d

#nom <- "rdf-2-classes-texture-0.png"
#image <- rdfReadGreyImage (nom)
#image2 <- rdfTextureEcartType (image, 2)
#res <- rdfClassificateur2D(image,image2, 1,-1, -0.1)
#display(res,"texture 0 binarise")

nom <- "rdf-2-classes-texture-0.png"
nbins <- 256
image1 <- rdfReadGreyImage (nom)
image2 <- rdfTextureEcartType(image1, 2)
#h <- hist (as.vector (image), breaks = seq (0, 1, 1 / nbins))
#seuil <- 0.32
#binaire <- (seuil-image) >= 0
h2D <- rdfCalculeHistogramme2D(image1, nbins, image2, nbins)
#display (binaire, "image binaire texture 0")
display(h2D, "histo2D ")

a <- masque
b <- binaire
c <- sum(abs(a - b))
d <- (c/(ncol(a)*nrow((b))))*100
d

#nom <- "rdf-2-classes-texture-1.png"
#image <- rdfReadGreyImage (nom)
#image <- rdfTextureEcartType(image, 2)
#h <- hist (as.vector (image), breaks = seq (0, 1, 1 / nbins))
#seuil <- 0.3
#binaire <- (seuil-image)>= 0
#display (binaire, "image binaire texture 1")
#print(sum(abs(ref-binaire))/16384*100)
