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

stackedFaces <- array(0, dim=c(40,33,400))
for (i in 0:19)  {
  for (j in 0:19) {
    stackedFaces[,,(i*20+j+1)] = allFacesName[(1+j*33) : ((j+1)*33), (1+i*40) : ((i+1)*40)]
  }
}

# Sum of the pixels of value 1 for each person's face
stackedFacesI <- function(stackedFaces) {
  # Moyenne par pixel d'une personne
  res <- array(0, dim=c(40,33,40))
  for (i in 1:40) {
    # Pour une personne
    tmp <- array(0, dim=c(40,33))
    for (j in 1:10) {
      for (k in 1:40) {
        for (l in 1:33) {
          # Id photo
          id <- (i-1) * 10 + j
          tmp[k,l] <- tmp[k,l] + stackedFaces[k,l,id]
        }
      }
    }
    res[,,i] <- tmp
  }
  res
}

# Find the entropy of each pixel for a face's photo set
entropyPerPixel <- function(addedPixels) {
  res <- array(0, dim=c(40,33,40))
  for (i in 1:40) {
    for (j in 1:40) {
      for (k in 1:33) {
        # Probability of this pixel's value to be 1
        prob <- addedPixels[j,k,i]/10
        res[j,k,i] = - (log2(prob) + log2(1 - prob))
      }
    }
  }
  res
}

# Find pixel with lowest entropy - put in res list - format (i, j, entropy value)
bestPixel <-function(entropyPerPixel) {
  res <- list()
  for (i in 1:40) {
    min <- 9999
    min_i <- 0
    min_j <- 0
    for (j in 1:40) {
      for (k in 1:33) {
        if (entropyPerPixel[j,k,i] < min) {
          min <- entropyPerPixel[j,k,i]
          min_i <- j
          min_j <- k
        }
      }
    }
    tmp <- c(min_i, min_j, min)
    res <- c(res, list(tmp))
  }
  res
}

stackedFacesI <- stackedFacesI(stackedFaces)
entropyPerPixel <- entropyPerPixel(stackedFacesI)
bestPixel <- bestPixel(entropyPerPixel)

