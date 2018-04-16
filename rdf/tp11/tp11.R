source("readUSPS.R")
source("freeman.R")

library( "EBImage" )

# Lecture des images
img <- readUSPSdata("usps")

# Binarisation
seuil <- 0.5
bin <- (img[[1]] - seuil) >= 0

# Classes
classes <- img[[2]]

# Freeman
freemanAll <- function(bin) {
  res <- array(0, dim=c(42,1,11000))
  for (i in 1:11000) {
    res[,,i] <- freeman(bin[,,i])
  }
  res
}

levenshtein <- function(free1, free2) {
  
  # Casting en string
  str1 <- toString(free1)
  str2 <- toString(free2)
  
  # Levenshtein
  res <- stringdist::stringdist(str1, str2)
  res
  
}

res <- array(0, dim=c(1,42,11000))
for (i in 1:11000) {
  res[,,i] <- freeman(bin[,,i])
}

leven <- levenshtein(free1, free2)


