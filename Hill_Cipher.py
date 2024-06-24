# Create a 5x5 matrix using a secret key
def create_matrix(key):
    key = key.upper()
    matrix = [[0 for i in range (5)] for j in range(5)]
    letters_added = []
    row = 0
    col = 0
    # add the key to the matrix
    for letter in key:
        if letter not in letters_added:
            matrix[row][col] = letter
            letters_added.append(letter)
        else:
            continue
        if (col==4):
            col = 0
            row += 1
        else:
            col += 1
    #Add the rest of the alphabet to the matrix
    # A=65 ... Z=90
    for letter in range(65,91):
        if letter==74: # I/J are in the same position
                continue
        if chr(letter) not in letters_added: # Do not add repeated letters
            letters_added.append(chr(letter))
            
    #print (len(letters_added), letters_added)
    index = 0
    for i in range(5):
        for j in range(5):
            matrix[i][j] = letters_added[index]
            index+=1
    return matrix
#Code to separate same letters:
#Add fillers if the same letter is in a pair 
def separate_same_letters(message): 
index = 0 
while (index<len(message)): 
l1 = message[index] 
if index == len(message)-1: 
message = message + 'X' 
index += 2 
continue 
l2 = message[index+1] 
if l1==l2: 
message = message[:index+1] + "X" + message[index+1:] 
index +=2 
return message
Code to encrypt and decrypt a message

#Return the index of a letter in the matrix 
#This will be used to know what rule (1-4) to apply 
def indexOf(letter,matrix): 
for i in range (5): 
try:
 index = matrix[i].index(letter) 
return (i,index) 
except: 
continue 
#Implementation of the playfair cipher 
#If encrypt=True the method will encrypt the message 
# otherwise the method will decrypt 
def playfair(key, message, encrypt=True): 
inc = 1 
if encrypt==False: 
inc = -1 
matrix = create_matrix(key) 
message = message.upper() 
message = message.replace(' ','') 
message = separate_same_letters(message) 
cipher_text=' ' 
for (l1, l2) in zip(message[0::2], message[1::2]): 
row1,col1 = indexOf(l1,matrix) 
row2,col2 = indexOf(l2,matrix) 
if row1==row2: #Rule 2, the letters are in the same row 
cipher_text += matrix[row1][(col1+inc)%5] + matrix[row2][(col2+inc)%5] 
elif col1==col2:# Rule 3, the letters are in the same column 
	cipher_text += matrix[(row1+inc)%5][col1] + matrix[(row2+inc)%5][col2] 
else: #Rule 4, the letters are in a different row and column 
cipher_text += matrix[row1][col2] + matrix[row2][col1] 
return cipher_text 
if __name__=='__main__': 
# a sample of encryption and decryption 
print ('Encripting') 
print ( playfair('secret', 'my secret message')) 
print ('Decrypting') 
print ( playfair('secret', 'LZECRTCSITCVAHBT', False))
HiLL Cipher

import numpy
def create_matrix_from(key):
m=[[0] * 3 for i in range(3)] 
for i in range(3): 
for j in range(3): 
m[i][j] = ord(key[3*i+j]) % 65 
return m
# C = P*K mod 26 
def encrypt(P, K): 
C=[0,0,0] 
C[0] = (K[0][0]*P[0] + K[1][0]*P[1] + K[2][0]*P[2]) % 26 
C[1] = (K[0][1]*P[0] + K[1][1]*P[1] + K[2][1]*P[2]) % 26 
C[2] = (K[0][2]*P[0] + K[1][2]*P[1] + K[2][2]*P[2]) % 26 
return C

def Hill(message, K): 
cipher_text = [] 
#Transform the message 3 characters at a time 
for i in range(0,len(message), 3): 
P=[0, 0, 0] 
#Assign the corresponding integer value to each letter 
for j in range(3): 
P[j] = ord(message[i+j]) % 65 
#Encript three letters 
C = encrypt(P,K) 
#Add the encripted 3 letters to the final cipher text 
for j in range(3): 
cipher_text.append(chr(C[j] + 65))
#Repeat until all sets of three letters are processed. 
#return a string 
return "".join(cipher_text)

def MatrixInverse(K): 
det = int(numpy.linalg.det(K)) 
det_multiplicative_inverse = pow(det, -1, 26) 
K_inv = [[0] * 3 for i in range(3)] 
for i in range(3): 
for j in range(3): 
Dji = K 
Dji = numpy.delete(Dji, (j), axis=0) 
Dji = numpy.delete(Dji, (i), axis=1) 
det = Dji[0][0]*Dji[1][1] - Dji[0][1]*Dji[1][0] 
K_inv[i][j] = (det_multiplicative_inverse * pow(-1,i+j) * det) % 26
return K_inv

if __name__ == "__main__": 
message = "MYSECRETMESSAGE" 
key = "RRFVSVCCT" 
#Create the matrix K that will be used as the key 
K = create_matrix_from(key) 
print(K) 
# C = P * K mod 26 
cipher_text = Hill(message, K) 
print ('Cipher text: ', cipher_text) 
# Decrypt 
# P = C * K^-1 mod 26 
K_inv = MatrixInverse(K) 
plain_text = Hill(cipher_text, K_inv) 
print ('Plain text: ', plain_text)
# K x K^-1 equals the identity matrix 
M = (numpy.dot(K,K_inv)) 
for i in range(3): 
for j in range(3): 
M[i][j] = M[i][j] % 26 
print(M)
