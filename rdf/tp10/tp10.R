source("functions.R")

allFaces = rdfReadGreyImage("allFaces.png")

# ClassCount initial : on prend toutes les images
classCount = array(1, dim=c(40,10))

# Regroupement des images
stackedfaces = stackedFaces(allFaces)

# Fonction récursive principale
getTree(stackedfaces, classCount)







