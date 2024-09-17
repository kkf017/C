import random

from typing import List

def hello(x:str)->str:
	return "Hello, {}.".format(x)

if __name__ == "__main__":
	x = hello("U")
	print(x)
