import os
import sys
import numpy
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

sys.path.insert(1, './module/')

from command import *
from display import *
from transform import *
from histogram import *
from filter import *
from FT import *

from colors import *

from typing import List


# Streamlit (website)


def main(argv:List[str], argc:int)->int:
    
    if argc==1:
        return 0
    
    if argc==2 and argv[-1]:
        help_()
        return 1

    filename1, filename2, opt, args = check(sys.argv)

    img1 = mpimg.imread(filename1)
    img2 = numpy.copy(img1)

    if opt:
        match opt:
            case "-g":
                img2 = greyscale(img1)

            case "-n":
                match args[0]:
                    case "gauss":
                        img2 = GaussianNoise(img1,float(args[1]),float(args[2]))
                    case "snp":
                        img2 = SaltnPepperNoise(img1, float(args[1]))

            case "-u":
                img2 = downsampling(img1, int(args[0]))
            case "-c":
                img2 = crop(img1, (int(args[0]),int(args[1])), int(args[2]), int(args[3]))
            case "-r":
                img2 = rotate(img1, float(args[0]))
            case "-f":
                img2 = flipping(img1)
            case "-m":
                img2 = reverse(img1)
            case "-z":
                img2 = scaling(img1, float(args[0]))

            case "-filt":
                n = None
                if len(args) > 2:
                    n = float(args[2]) 
                img2 = filtering(img1, args[0], args[1], n) 
            case "-sh":
                c = 1
                #img1 = greyscale(img1)
                img2 = sharpening(img1, args[0], args[1])
                #img2 = img1 + c*img2
            case "-corr":
                sub = mpimg.imread(args[1])
                img2 = crosscorrelation(img1, args[0], sub) 
  
            case "-h":
                histogram(img1, False) 
            case "-adj":
                img2 = adjustContrast(img1) 
            case "-eq":
                img2 = equalization(img1)
            case "-gamma":
                img1 = greyscale(img1)
                img2 = correctionGamma(img1, 1, 1/2)
            case "-neg":
                #img1 = greyscale(img1)
                img2 = negative(img1) 
            case "-th":
                img2 = hardthresholding(img1, float(args[0]))

            case "-ftfilt":
                if args[0] in ["lowpass", "glowpass", "highpass", "ghighpass"]:
                    img2 = ftfiltering(img1, args[0], float(args[1]))

                if args[0] in ["blowpass","bhighpass"]:
                    img2 = ftfiltering(img1, args[0], float(args[1]), float(args[2]))
                
                if args[0] in ["bandreject", "bandpass"]:
                    if args[1] in ["butterworth"]:
                        img2 = ftfiltering(img1, args[0], args[1], float(args[2]), float(args[3]), float(args[4]))
                    else:
                        img2 = ftfiltering(img1, args[0], args[1], float(args[2]), float(args[3]))

                if args[0] in ["homomorphic"]:
                        img2 = ftfiltering(img1, args[0], float(args[1]), float(args[2]), float(args[3]), float(args[4]))

            case "-umask":
                #img1 = greyscale(img1)
                img2 = UnsharpMasking(img1, float(args[0]), float(args[1]))
            case "-hfe":
                #img1 = greyscale(img1)
                img2 = HighFreqEmph(img1, float(args[0]), float(args[1]), float(args[2]))
            
            case "-fsh":
                img1 = greyscale(img1)
                img2 = LaplacianFilter(img1,-1)#float(args[0]))
        
    plt.axis('off')
    match len(img2.shape):
        case 2:
            plt.imshow(img2,  cmap='gray')
        case 3:
            plt.imshow(img2)
        case _:
            raise Exception(WARNINGIMAGESIZE) 
    plt.savefig(filename2)
    
    return 1


    # -
        # High pass filter
        # contrast adjustment 
        # negative
        # FT - Ideal low pass, Butterworth low pass, Gaussian low pass

    # Extra tools - Laplacian pyramid, pyramid denoising, wavelet decomposition/denoising





if __name__ == "__main__":

    print("\033[{}mIMGMagic 1.0.".format("1;35"))

    main(sys.argv, len(sys.argv))

    print("\n\033[{}mUse --help to list all available options.".format("1;30"))

