import os
import sys

from func import hello, myrand



if __name__ == "__main__":

    msg = ""

    if len(sys.argv) > 1 :
        msg = sys.argv[1]

    msg1 = hello(msg)
    print(msg1)

    for i in range(len(sys.argv)):
        print(">>{}, {}".format(i, sys.argv[i]))
