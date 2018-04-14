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

# Remplissage d'une matrice 40*33*400
stackedFaces <- function(allFaces) {
  res = array(0, dim=c(40,33,400))
  for (i in 0:19)  {
    for (j in 0:19) {
      res[,,(i*20+j+1)] = allFaces[(1+j*33) : ((j+1)*33), (1+i*40) : ((i+1)*40)]
    }
  }
  res
}

# Probabilité qu'un pixel soit à 1 parmi les images de l'ensemble courant
probPerPixel <- function(stackedFaces, classCount) {
  res = array(0, dim=c(40,33))
  # Total des images de l'ensemble courant
  total = nbImages(classCount)
  for (i in 1:40) {
    for (j in 1:33) {
      sum = 0
      for (k in 1:40) {
        for (l in 1:10) {
          id = (k-1) * 10 + l
          if (classCount[k,l] == 1) {
            sum = sum + stackedFaces[i,j,id]
          }
        }
      }
      res[i,j] = sum/total
    }
  }
  res
}

# Obtention de l'entropie de chaque pixel de l'ensemble courant
getEntropy <- function(probPerPixel) {
  p = probPerPixel
  pcomp = 1 - probPerPixel
  H = -(log(p^p) + log(pcomp^pcomp))
  H
}

# Selection du meilleur pixel, celui qui a l'entropie la plus haute
bestPixel <- function(entropy) {
  res = which(entropy == max(entropy), arr.ind = TRUE)
  res[1,]
}

# Détermination des images qui possédent le pixel représentatif à 1
getSelectedImages <- function(bestPixel, stackedFaces, classCount) {
  bx = bestPixel[1]
  by = bestPixel[2]
  newClassCount = array(0, dim=c(40,10))
  for (i in 1:40) {
    stackedFacesI = array(0, dim=c(10))
    for (j in 1:10) {
      id = (i-1) * 10 + j
      # On ne prend que les images qui sont dans l'ensemble courant
      if (classCount[i,j] == 1)
        stackedFacesI[j] = stackedFaces[bx,by,id]
    }
    newClassCount[i,] = stackedFacesI
  }
  newClassCount
}

# Calcul du nombre d'images d'un sous-ensemble
nbImages <- function(classCount) {
  res = sum(classCount == 1)
  res
}

# Détermine si un sous-ensemble n'est constitué que d'une classe
# Retourne l'id de la classe si il ne reste que celle-ci, -1 sinon
hasUniqueClass <- function(classCount) {
  res = 0
  for (i in 1:40) {
    sum = 0

    # Nombre d'images d'une classe
    sum = sum(classCount[i,] == 1)
    
    if (sum != 0) {
      if (res == 0) {
        res = i
        lim = 1
      } else {
        res = -1
        break
      }
    }
  }
  res
}

# Inverse de classCount en tenant compte de l'ancien sous-ensemble
reverseClassCount <- function(oldClassCount, classCount) {
  res = array(0, dim=c(40,10))
  for (i in 1:40) {
    for (j in 1:10) {
      if (classCount[i,j] == 1)
        res[i,j] = 0
      else if (oldClassCount[i,j] == 0)
        res[i,j] = 0
      else
        res[i,j] = 1
    }
  }
  res
}

# Construction de l'arbre par récursion
getTree <- function(stackedFaces, classCount) {
  
  # Probabilité d'avoir un pixel à 1 pour chaque pixel de l'ensemble
  prob = probPerPixel(stackedFaces, classCount)
  
  # Calcul de l'entropie par pixel
  entropy = getEntropy(prob)
  
  # Pixel le plus représentatif
  bestpixel = bestPixel(entropy)
  
  # Images possédant ce pixel à 1
  leftClassCount = getSelectedImages(bestpixel, stackedFaces, classCount)
  
  # Images ne possédant pas ce pixel à 1
  rightClassCount = reverseClassCount(classCount, leftClassCount)
  
  # Noeud gauche
  left = hasUniqueClass(leftClassCount)
  if (left != -1) {
    print(paste("Class ok from left: ", left))
  } else {
    print("New branch from left")
    getTree(stackedFaces, leftClassCount)
  }
  
  # Noeud droit
  right = hasUniqueClass(rightClassCount)
  if (right != -1) {
    print(paste("Class ok from right : ", right))
  } else {
    print("New branch from right")
    getTree(stackedFaces, rightClassCount)
  }
  
  print("END")
  
}