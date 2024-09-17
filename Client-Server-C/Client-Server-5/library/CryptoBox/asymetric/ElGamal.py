import random
import math

from CryptoBox.arithmetic.prime import randprime, Euclidean
from CryptoBox.arithmetic.modulo import Zn_, generators, order, FastExponent

from typing import List, Tuple, Union, Callable



"""
	Warning !!
		Signature/Verification:
			have to be completed.
				(signature redundancy function, verification)


	WARNING !!
	See condition. 
		func. keys(): -> generate p (prime number)
			randprime() - range - (modulus n)
			p < 20: # len(p*q) >= 1024 bits
"""

BOUND = 60
UPPER = 256
LOWER = 20

class ElGamal():
	def __init__(self,):
		(self.p, self.alpha, self.exp), self.a = self.keys()

	def keys(self,)->Tuple[Union[Tuple[int], int]]:
		"""
			Function to compute public and private key.
			Input:
				...
			Output:
				public and private keys (for encryption)
		opt.   (p, alpha, alpha^a mod p) - pubic key, a - private key
		"""
		while 1:
			p = randprime(LOWER, UPPER)
			if p > BOUND: # len(p*q) >= 1024 bits
				break
		
		zn_ = list(Zn_(p))	
		g = list(generators(p))
		
		# check for empty sequence
		
		alpha = random.choice(g)
		
		a = random.randint(1, p-2) 
		exp = FastExponent(alpha, a, p)
		
		return (p, alpha, exp), a


	def encrypt(self, plain:str, key:Tuple[int])->List[Tuple[int]]:
		"""
			Function to encrypt a message.
			Input:
				plain - message to encrypt
			Output:
				cipher (text) 
		"""
		(p, alpha, exp) = key
			
		if type(plain) == str:
			plain = [ord(i) for i in plain]
		
		cipher = []	
		for x in plain:		
			k = random.randint(1, p-2)
			lambda_ = FastExponent(alpha,k,p) # lambda = alpha^k mod p
			delta = (x * FastExponent(exp,k,p))%p # delta = mi(alpha^a)^k mod p
			cipher.append((lambda_, delta))
		return cipher

	
	def decrypt(self, cipher:List[Tuple[int]])->str:
		"""
			Function to decrypt a message.
			Input:
				cipher - message to decrypt
			Output:
				plain (text) 
		"""
		plain = []	
		for x in cipher:
			(lambda_, delta) = x
			pi = (FastExponent(lambda_,self.p-1-self.a,self.p) * delta)%self.p
			plain.append(chr(pi))
		return "".join(plain)
		
		
	def signature(self,msg:str, hashs:Callable)->Tuple[str]:
		"""
			Function to compute signature.
			Input:
				msg - ...
				hashs - hash function
			Output:
				signature
		"""
		#if type(msg) == str:
			#msg = [ord(i) for i in msg]
			
		sign = hashs(msg)
		while 1:
			k = random.randint(1, self.p-2)
			if math.gcd(k, self.p-1)==1:
				break
		
		
		print("\nk {}, pgcd({},{}) = {}".format(k, k, self.p-1, math.gcd(k, self.p-1)))	
		_, _, kinv = Euclidean(self.p-1, k) # FAUX !!

		res = k * kinv
		print("{} x {} = {} mod {}".format(k,kinv, -1, self.p-1))
		
		if k*kinv % self.p-1:
			raise Exception("\n\033[{}m[-]Error: k not valid.".format("0;33"))
			
			
		r = FastExponent(self.alpha,k,self.p)
		sign = [(kinv*(ord(i)-self.a*r)) % self.p-1 for i in sign] 
		sign = [chr(i) for i in sign]
		return r, "".join(sign)
	
	def verification(self, sign:str, msg: str, hashs:Callable, key:Tuple[int])->None:
		"""
			Function to verify signature.
			Input:
				cipher -...
			Output:
				...
		"""
		r, s = sign
		(p, alpha, exp) = key
		
		if 1 <= r and r <=p-2:
			# reject signature
			pass
			
		#v1 =  exp^r * r^s mod p
		v1 = [FastExponent(exp,r,p) * FastExponent(r,ord(i),p) for i in s]
		
		#v2 = alpha^H(m) mod p
		v2 = [FastExponent(alpha,ord(i),p)  for i in hashs(s)]
		
		print("\n\n")
		print(v1) # FAUX !!!
		print(v2)
		return None
	
