# Load the necessary library for bitwise operations
library(bitops)

# Helper functions to perform bitwise operations as in C
func0 <- function(abcd) { bitOr(bitAnd(abcd[2], abcd[3]), bitAnd(bitNot(abcd[2]), abcd[4])) }
func1 <- function(abcd) { bitOr(bitAnd(abcd[4], abcd[2]), bitAnd(bitNot(abcd[4]), abcd[3])) }
func2 <- function(abcd) { bitXor(abcd[2], bitXor(abcd[3], abcd[4])) }
func3 <- function(abcd) { bitXor(abcd[3], bitOr(abcd[2], bitNot(abcd[4]))) }

# Function to calculate the table of constants
calctable <- function() {
  k <- numeric(64)
  for (i in 1:64) {
    k[i] <- as.integer(abs(sin(i)) * 2^32)
  }
  return(k)
}

# Function to perform left rotation
rol <- function(r, N) {
  bitOr(bitShiftL(r, N), bitShiftR(r, 32 - N))
}

# Main MD5 algorithm implementation
md5 <- function(msg) {
  # Initial MD5 values
  h0 <- c(0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476)
  ff <- list(func0, func1, func2, func3)
  M <- c(1, 5, 3, 7)
  O <- c(0, 1, 5, 0)
  rots <- list(
    c(7, 12, 17, 22),
    c(5, 9, 14, 20),
    c(4, 11, 16, 23),
    c(6, 10, 15, 21)
  )

  k <- calctable()
  h <- h0
  
  # Message padding
  msg2 <- charToRaw(msg)
  msg_len <- length(msg2)
  msg2 <- c(msg2, as.raw(0x80))
  while ((length(msg2) + 8) %% 64 != 0) {
    msg2 <- c(msg2, as.raw(0))
  }
  msg2 <- c(msg2, as.raw(rev(as.integer(8 * msg_len) %% 256)), rep(as.raw(0), 3))

  # Process the message in 512-bit chunks
  for (i in seq(1, length(msg2), by=64)) {
    chunk <- msg2[i:(i+63)]
    mm <- readBin(chunk, "integer", size=4, signed=FALSE, endian="little", n=16)
    
    abcd <- h
    
    for (p in 1:4) {
      fctn <- ff[[p]]
      rotn <- rots[[p]]
      m <- M[p]
      o <- O[p]
      
      for (q in 0:15) {
        g <- (m*q + o) %% 16 + 1
        f <- abcd[2] + rol(abcd[1] + fctn(abcd) + k[q + 16 * (p - 1) + 1] + mm[g], rotn[(q %% 4) + 1])
        abcd <- c(abcd[4], abcd[1:3])
        abcd[2] <- f
      }
    }
    
    h <- (h + abcd) %% 2^32
  }
  
  return(h)
}

# Convert the digest to hexadecimal format
md5_to_hex <- function(digest) {
  hex <- sapply(digest, function(x) sprintf("%08x", x))
  return(paste(hex, collapse=""))
}

# Main function to compute MD5
main <- function() {
  msg <- "The quick brown fox jumps over the lazy dog"
  digest <- md5(msg)
  hex_digest <- md5_to_hex(digest)
  cat("MD5 Digest: ", hex_digest, "\n")
}

# Run the main function
main()
