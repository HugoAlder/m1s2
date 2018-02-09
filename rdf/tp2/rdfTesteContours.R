# -----------------------------------------------------------------------
# Extraction d'attributs de contours,
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
source ("rdfContours.R")

# Chargement d'un contour
# nom <- "rdf-patate.txt"
# cont2 <- rdfChargeFichierContour (nom)

nom <- "rdf-triangle-20.png"
img <- rdfReadGreyImage(nom)
cont <- rdfContour(img)

# Afficher le contour
plot (cont, main = nom, type = "o", asp = 1, col = "red",
      ylim = rev (range (Im (cont))))

desc = fft(cont, inverse=TRUE)/length(cont)
desc = rdfAnnuleDescFourrier(desc, 1)
lines(fft(desc, inverse=TRUE), main = nom, type = "o", pch=22, lty=2, col = "blue")

corde = rdfAlgorithmeCorde(cont, 1)
lines(corde, main = nom, type = "o", pch=22, lty=2, col = "green")

# lines(fft(fft(cont),inverse=TRUE)/length(cont), main = nom, type = "o", pch=22, lty=2, col = "green"
# desc = fft(cont,inverse=TRUE)/length(cont)
# desc2 = rdfAnnuleDescFourrier(desc, 0.5)
# lines(fft(desc2, inverse=TRUE), main = nom, type = "o", pch=22, lty=2, col = "blue")
# desc3 = rdfAnnuleDescFourrier(desc, 0)
# lines(fft(desc3, inverse=TRUE), main = nom, type = "o", pch=22, lty=2, col = "green")

