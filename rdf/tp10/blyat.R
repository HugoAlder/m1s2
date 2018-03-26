library ("EBImage")

# Chargement d'une image en niveaux de gris
rdfReadGreyImage <- function (nom) {
  image <- readImage (nom)
  if (length (dim (image)) == 2) {
    image
  } else {
    channel (image, 'red')
  }
}

allFacesName = rdfReadGreyImage("allFaces.png");

stackedFaces <- array(0, dim=c(40,33,400));
for (i in 0:19)  {
  for (j in 0:19) {
    stackedFaces[,,(i*20+j+1)] = imageAllFaces[(1+j*33) : ((j+1)*33), (1+i*40) : ((i+1)*40)]
  }
}