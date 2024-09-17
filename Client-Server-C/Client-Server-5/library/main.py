import os
import sys
import pickle

from typing import Tuple

from CryptoBox.asymetric.RSA import RSA
from CryptoBox.asymetric.ElGamal import ElGamal
from CryptoBox.asymetric.Rabin import Rabin

from CryptoBox.hash.hash import *

HASH = md5

def profile(x:str)->None:
	"""
		Function to create object (for encryption).
		Input:
			x - type of encryption 
		Output:
			None
	opt. 
	"""
	match x:
		case "-rsa":
			obj = RSA(1024) # 2048
		case "-elgamal":
			obj = ElGamal()
		case "-rabin":
			obj = Rabin()
		case _:
			raise Exception("\n\033[{}m[-]Error: Unknow cryptographic method (rsa, elgamal, rabin).".format("0;33"))
	
	filename = "./data/{}".format(HASH(x)[:16])
	with open(filename, 'wb') as w:
		pickle.dump(obj, w)
	
		
def temp(x:str)->None:
	"""
		Function to create a temporary file (for key exchange).
		Input:
			x - type of encryption
		Output:
			None 
	opt. 
	"""
	filename = "./data/{}".format(HASH(x)[:16])
	with open(filename, 'rb') as r:
		obj = pickle.load(r)
	
	temp = "./data/temp"
	with open(temp, 'w') as wfile:
		match x:
			case "-rsa":
				wfile.writelines(" ".join([str(obj.n), str(obj.e)]))
			case "-elgamal":
				wfile.writelines(" ".join([str(obj.p), str(obj.alpha), str(obj.exp)]))
			case "-rabin":
				wfile.writelines(str(obj.n))
			case _:
				raise Exception("\n\033[{}m[-]Error: Unknow cryptographic method (rsa, elgamal, rabin).".format("0;33"))
	

	
def encrypt(msg:str, key:Tuple[int], crypt:str)->None:
	"""
		Function to encrypt a message.
		Input:
			msg - message to encrypt
			key - key for encryption
			encrypt - type of encryption
		Output:
			None 
	opt. 
	"""
	filename = "./data/{}".format(HASH(crypt)[:16])
	with open(filename, 'rb') as r:
		obj = pickle.load(r)
	
	match crypt:
		case "-rsa":
			x = obj.encrypt(msg, key[:2])
		case "-elgamal":
			x = obj.encrypt(msg, key)
		case "-rabin":
			x = obj.encrypt(msg, key[0])
		case _:
			raise Exception("\n\033[{}m[-]Error: Unknow cryptographic method (rsa, elgamal, rabin).".format("0;33"))
	
	temp = "./data/temp-encrypt"
	with open(temp, 'w') as wfile:
		#wfile.write(str(len(x.encode("utf-8")))+"\n")
		wfile.write(x)
		

def decrypt(msg:str, crypt:str)->None:
	"""
		Function to decrypt a message.
		Input:
			msg - message to encrypt
			encrypt - type of encryption
		Output:
			None 
	opt. 
	"""
	filename = "./data/{}".format(HASH(crypt)[:16])
	with open(filename, 'rb') as r:
		obj = pickle.load(r)
	
	match crypt:
		case "-rsa":
			x = obj.decrypt(msg)
		case "-elgamal":
			x = obj.decrypt(msg)
		case "-rabin":
			x = obj.decrypt(msg)
		case _:
			raise Exception("\n\033[{}m[-]Error: Unknow cryptographic method (rsa, elgamal, rabin).".format("0;33"))
	
	temp = "./data/temp-decrypt"
	with open(temp, 'w') as wfile:
		#wfile.write(str(len(x.encode("utf-8")))+"\n")
		wfile.write(x)
		
def erase()->None:
	"""
		Function to ....
		Input:
			...
		Output:
			None 
	opt. 
	"""
	for filename in os.listdir("./data/"):
    		#os.remove(f)
    		os.remove(os.path.join("./data/", filename))
			

if __name__ == "__main__":
	
	# Create new key -> python3 ../library/main.py -key [-rsa/elgamal/rabin]
	if "-key" in sys.argv:
		profile(sys.argv[sys.argv.index("-key")+1])
	
	# Get public key -> python3 ../library/main.py -pub [-rsa/elgamal/rabin]	
	if "-pub" in sys.argv:
		temp(sys.argv[-1])
		
	# Encrypt a message -> python3 ../library/main.py -e message -k key1 key2 key3 [-rsa/elgamal/rabin]
	if "-e" in sys.argv:
		msg = sys.argv[sys.argv.index("-e")+1]
		PublicKey = ( int(sys.argv[sys.argv.index("-k")+1]), int(sys.argv[sys.argv.index("-k")+2]),  int(sys.argv[sys.argv.index("-k")+3]))
		crypt = sys.argv[-1]
		encrypt(msg, PublicKey, crypt)

	# Decrypt a message -> python3 ../library/main.py -d message [-rsa/elgamal/rabin]
	if "-d" in sys.argv:
		msg = sys.argv[sys.argv.index("-d")+1]
		crypt = sys.argv[-1]
		decrypt(msg, crypt)
		
	# Remove all files in ./data -> python3 ../library/main.py -erase
	if "-erase" in sys.argv:
		erase()

		
		

		

