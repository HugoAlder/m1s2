# -----------------------------------------------------------------------
# Segmente par seuillage ,
# Module RdF, reconnaissance de formes
# Copyleft (C) 2016, Universite Lille 1
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
# RÃ©pertoire de travail
source ("rdfSegmentation.R")

# Chargement de l'image
nom <- "2classes_100_100_8bits_2016.png"
image <- rdfReadGreyImage (nom)

# Calcul et affichage de son histogramme
nbins <- 256
h <- hist (as.vector (image), freq=FALSE, breaks = seq (0, 1, 1 / nbins))

# Segmentation par binarisation 0.5
seuil <- 0.5
binaire50 <- (image - seuil) >= 0

# Segmentation par binarisation 0.55
seuil <- 0.55
binaire55 <- (image - seuil) >= 0

# Segmentation par binarisation 0.6
seuil <- 0.6
binaire60 <- (image - seuil) >= 0

# Affichage des images binarisées
#display (binaire50, method="raster")
#display (binaire55, method="raster")
display (binaire60, method="raster")


