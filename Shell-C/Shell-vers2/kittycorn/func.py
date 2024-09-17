import random

def hello(msg:str)->str:
    return "Hello, from {}.".format(msg)


def myrand(n:int)->str:
    return "My random number: {}.".format(random.randint(0,n))
    
