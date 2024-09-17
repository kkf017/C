import os
import sys

from colors import *

from typing import List, Tuple, Union



def exists(filename:str)->bool:
    """
        Function that check if a file exists.
        Input:
            filename - name of the file
        Output:
            boolean
    """
    filename =  os.path.abspath(filename)
    if not os.path.exists(filename):
        return False
    return True



def n(args:List[str])->bool:
    """
        Function that check arguments for -n option.
        Input:
            args - arguments for command
                    -n gauss mean sigma      
                    -n snp prob
        Output:
            booleen
    """
    match args[0]:
        case "gauss":
            if len(args) < 3 or not args[1].replace(".", "").isnumeric() or not args[2].replace(".", "").isnumeric():
                return False
        case "snp":
            if len(args) < 2 or not args[1].replace(".", "").isnumeric():
                return False
        case _:
            return False
    return True

def u(args:List[str])->bool:
    """
        Function that check arguments for -u option.
        Input:
            args - arguments for command
                    -u fact
        Output:
            booleen
    """
    if len(args) < 1 or not args[0].replace(".", "").isnumeric():
        return False
    return True

def c(args:List[str])->bool:
    """
        Function that check arguments for -c option.
        Input:
            args - arguments for command
                    -c x0 y0 width height 
        Output:
            booleen
    """
    if len(args) < 4 or not args[0].replace(".", "").isnumeric() or not args[1].replace(".", "").isnumeric() or not args[2].replace(".", "").isnumeric() or not args[3].replace(".", "").isnumeric():
        return False
    return True

def r(args:List[str])->bool:
    """
        Function that check arguments for -r option.
        Input:
            args - arguments for command
                    -r degre
        Output:
            booleen
    """
    if len(args) < 1 or not args[0].replace(".", "").isnumeric():
        return False
    return True

def z(args:List[str])->bool:
    """
        Function that check arguments for -z option.
        Input:
            args - arguments for command
                    -z fact
        Output:
            booleen
    """
    if len(args) < 1 or not args[0].replace(".", "").isnumeric():
        return False
    return True

def filt(args:List[str])->bool:
    """
        Function that check arguments for -filt option.
        Input:
            args - arguments for command
                    -filt [filter] [padding] [args]
                        [filter] : lowpass, highpass, avg, gauss
                        [padding] : ‘reflect’, ‘constant’, ‘nearest’, ‘mirror’, ‘wrap’
                        [args] : n for lowpass 
                                 sigma for gaussian(opt.)
        Output:
            booleen
    """
    if len(args) < 2:
        return False
    if args[0]== "avg" and len(args) < 3:
        return False
    if not args[0] in ["lowpass", "highpass", "avg", "gauss"]:
        return False
    if not args[1] in ["reflect", "constant", "nearest", "mirror", "wrap"]:
        return False
    if len(args) > 2 and not args[2].replace(".", "").isnumeric():
        return False
    return True


def sh(args:List[str])->bool:
    """
        Function that check arguments for -sh option.
        Input:
            args - arguments for command
                    -sh [filter] [padding] 
                        [filter] : laplacian, sobel, roberts
                        [padding] : ‘reflect’, ‘constant’, ‘wrap’  //...‘nearest’, ‘mirror’
        Output:
            booleen
    """
    if len(args) < 2:
        return False
    if not args[0] in ["laplacian", "sobel", "roberts"]:
        return False
    if not args[1] in ["reflect", "constant", "wrap"]: # "nearest", "mirror",
        return False
    return True


def corr(args:List[str])->bool:
    """
        Function that check arguments for -corr option.
        Input:
            args - arguments for command
                    -corr [filter] [image] 
                        [filter] : laplacian, sobel, roberts
                        [image] : subimage to find in main image.
        Output:
            booleen
    """
    if len(args) < 2:
        return False
    if not exists(args[1]):
        return False
    if not args[0] in ["laplacian", "sobel", "roberts"]:
        return False
    return True


def gamma(args:List[str])->bool:
    """
        Function that check arguments for -gamma option.
        Input:
            args - arguments for command
                    -gamma c gamma 
                        c, gamma : parameters of the formula
        Output:
            booleen
    """
    if len(args) < 2:
        return False
    if not args[0].replace(".", "").isnumeric() and not args[1].replace(".", "").isnumeric():
        return False
    return True


def th(args:List[str])->bool:
    """
        Function that check arguments for -th option.
        Input:
            args - arguments for command
                    -th threshold
                        threshold : threshold of the function
        Output:
            booleen
    """
    if len(args) < 1:
        return False
    if not args[0].replace(".", "").isnumeric():
        return False
    return True


def ftfilt(args:List[str])->bool:
    """
        Function that check arguments for -ftfilt option.
        Input:
            args - arguments for command
                    -ftfilt [filter] [args] 
                        [filter] : lowpass, blowpass, glowpass, highpass, bhighpass, ghighoass, bandreject, bandpass, homomorphic
                        [args] : parameters of each filter (opt.)
        Output:
            booleen
    """
    if not args[0] in ["lowpass", "blowpass", "glowpass", "highpass", "bhighpass", "ghighpass", "bandreject", "bandpass", "homomorphic"]:
        return False

    if (args[0]=="blowpass" or args[0]=="bhighpass"):
        if len(args) < 3 or not args[1].replace(".", "").isnumeric() or not args[2].replace(".", "").isnumeric():
            return False

    if (args[0]=="lowpass" or args[0]=="glowpass" or args[0]=="highpass" or args[0]=="ghighpass"):
            if len(args) < 2 or not args[1].replace(".", "").isnumeric():
                return False

    if (args[0]=="bandreject" or args[0]=="bandpass"):
        if (len(args) < 4) or not args[2].replace(".", "").isnumeric() or not args[3].replace(".", "").isnumeric():
            return False

    if (args[0]=="bandreject" or args[0]=="bandpass") and (args[1]=="butterworth"):
        if (len(args) < 5) or not args[-1].replace(".", "").isnumeric():
            return False

    if (args[0]=="homomorphic"):
        if (len(args) < 5) or not args[1].replace(".", "").isnumeric() or not args[2].replace(".", "").isnumeric() or not args[3].replace(".", "").isnumeric() or not args[4].replace(".", "").isnumeric():
            return False
    return True


def umask(args:List[str])->bool:
    """
        Function that check arguments for -umask option.
        Input:
            args - arguments for command
                    -umask D0 k
                        D0 : cutoff freq.
                        k - parameter
                                k=1 - unsharp masking
                                k>1 - highboost filtering
        Output:
            booleen
    """
    if len(args) < 2:
        return False
    if not args[0].replace(".", "").isnumeric() or not args[1].replace(".", "").isnumeric():
        return False
    return True

def hfe(args:List[str])->bool:
    """
        Function that check arguments for -hfe option.
        Input:
            args - arguments for command
                    -hfe D0 k
                        D0 : cutoff freq.
                        k1, k2 - parameter
                                k1 = 1
                                k2=1 - unsharp masking
                                k2>1 - highboost filtering
        Output:
            booleen
    """
    if len(args) < 3:
        return False
    if not args[0].replace(".", "").isnumeric() or not args[1].replace(".", "").isnumeric() or not args[2].replace(".", "").isnumeric():
        return False
    return True


def fsh(args:List[str])->bool:
    """
        Function that check arguments for -hfe option.
        Input:
            args - arguments for command
                    -fsh c
                        c : constant.
        Output:
            booleen
    """
    if len(args) < 1: # or not args[0].replace(".", "").isnumeric():
        return False
    return True


def check(argv:List[str])->Tuple[Union[str, List[str]]]:
    """
        Function that check input command.
        Input:
        Output:
            None

        imgmagic img1 img2 [OPTION] [ARGS]
    """

    # TERMINER !!! - add --help command

    filename1 = None
    filename2 = None
    opt = None
    args = []
    
    if len(argv) < 3:
        sys.exit("\n\033[{}mWARNING: Syntax error.\n\n\033[{}mUse --help to list all available options.".format("0;31", "1;30"))
    
    if not exists(argv[1]):
         sys.exit("\n\033[{}mWARNING: {} does not exist.\n\n\033[{}mUse --help to list all available options.".format("0;31", argv[1], "1;30"))

    filename1 = argv[1]
    filename2 = argv[2]

    if len(argv) > 3:
        opt = argv[3]
        if len(argv) > 4:
            args = argv[4:]

        match opt:
            case "-g":
                pass
            case "-n":
                if not (len(args) > 0 and n(args)):
                    sys.exit(WARNINGPARSING)
            case "-u":
                if not (len(args) > 0 and u(args)):
                    sys.exit(WARNINGPARSING)
            case "-c":
                if not (len(args) > 0 and c(args)):
                    sys.exit(WARNINGPARSING)
            case "-r":
                if not (len(args) > 0 and r(args)):
                    sys.exit(WARNINGPARSING)
            case "-z":
                if not (len(args) > 0 and z(args)):
                    sys.exit(WARNINGPARSING)
            case "-f":
                pass
            case "-m":
                pass
            case "-filt":
                if not (len(args) > 0 and filt(args)):
                    sys.exit(WARNINGPARSING)
            case "-sh":
                if not (len(args) > 0 and sh(args)):
                    sys.exit(WARNINGPARSING)
            case "-corr":
                if not (len(args) > 0 and corr(args)):
                    sys.exit(WARNINGPARSING)
            case "-h":
                pass
            case "-adj":
                pass
            case "-eq":
                pass
            case "-gamma":
                if not (len(args) > 0 and gamma(args)):
                    sys.exit(WARNINGPARSING)
            case "-neg":
                pass
            case "-th":
                if not (len(args) > 0 and th(args)):
                    sys.exit(WARNINGPARSING)
            case "-ftfilt":
                if not (len(args) > 0 and ftfilt(args)):
                    sys.exit(WARNINGPARSING)
            case "-umask":
                if not (len(args) > 0 and umask(args)):
                    sys.exit(WARNINGPARSING)  
            case "-hfe":
                if not (len(args) > 0 and hfe(args)):
                    sys.exit(WARNINGPARSING) 
            case "-fsh":
                if not (len(args) > 0 and fsh(args)):
                    sys.exit(WARNINGPARSING)  
            case _:
                sys.exit(WARNINGPARSING)
    
    return filename1, filename2, opt, args



def help_()->None:
    #print("\033[{}mIMGMagic 1.0.".format("1;35"))
    print("\n\033[{}mCommand:- imgmagic img1 img2 [OPTION] [ARGS]".format("0;34"))
    print("\033[{}m\t with img1 img2 path of input/output image.".format("0;34"))

   
    print("\n\033[{}m-g \tConvert RGB image to greyscale.".format("0;37"))

    print("\n\033[{}m-n [noise] [args] \tAdd noise to image. \n\twith \t[noise]: type of noise (gauss, snp).\n\t\t[args]: arguments. \n\t\t\t\tmean, sigma for gaussian noise \n\t\t\t\tprob for salt and pepper noise".format("0;37"))

    print("\n\033[{}m-u [fact] \tPerform downsampling on image. \n\twith \t[fact]: factor of downsampling.".format("0;37"))

    print("\n\033[{}m-c [x0] [y0] [width] [height]  \tCrop the image. \n\twith \t[x0],[y0]: Coordiante of starting point.\n\t\t[width],[height]: width and height of cropped image.".format("0;37"))

    print("\n\033[{}m-r [deg] \tRotate the image. \n\twith \t[deg]: angle of rotation.".format("0;37"))

    print("\n\033[{}m-z [scale] \tScale the image. \n\twith \t[scale]: factor of scaling.".format("0;37"))

    print("\n\033[{}m-m \tReverse the image.".format("0;37"))

    print("\n\033[{}m-f \tFlip the image.".format("0;37"))

    print("\n\033[{}m-filt [filter] [padding] [args] \tPerform filtering on image. \n\twith \t[filter]: type of filter (lowpass, highpass, avg, gauss).\n\t\t[padding]: type of padding (reflect, constant, nearest, mirror, wrap). \n\t\t[args]: arguments for each type of filter.".format("0;37"))

    print("\n\033[{}m-sh [filter] [padding]\tPerform sharpening on image. \n\twith \t[filter]: type of filter (laplacian, sobel, roberts).\n\t\t[padding]: type of padding (reflect, constant, wrap).".format("0;37"))

    print("\n\033[{}m-corr [filter] [sub] \tPerform cross correlation. \n\twith \t[filter]: type of filter (laplacian, sobel, roberts). \n\t\t[sub]: subimage to find in the main image.".format("0;37"))

    print("\n\033[{}m-h \tCompute histogram of the image.".format("0;37"))

    print("\n\033[{}m-adj \tPerform contrast adjustment of the image.".format("0;37"))

    print("\n\033[{}m-neg \tPerform image equalization.".format("0;37"))

    print("\n\033[{}m-eq \tCompute negative of the image.".format("0;37"))

    print("\n\033[{}m-gamma [c] [gamma] \tPerform gamma correction. \n\twith \t[c], [gamma]: parameters of gamma correction.".format("0;37"))

    print("\n\033[{}m-th \tPerform thresholding with Fourier transform.".format("0;37"))

    print("\n\033[{}m-ftfilt [filter] [args] \tPerform FT filtering on image. \n\twith \t[filter]: type of filter (lowpass, blowpass, glowpass, highpass, bhighpass, ghighoass, bandreject, bandpass, homomorphic). \n\t\t[args]: arguments for each type of filter.".format("0;37"))

    print("\n\033[{}m-umask [cutoff] [k] \tPerform unsharp masking. \n\twith \t[cutoff],[k]: parameters.".format("0;37"))

    print("\n\033[{}m-hfe [cutoff] [k1] [k2] \tPerform high frequency emphasis. \n\twith \t[cutoff],[k1],[k2]: constant.".format("0;37"))

    print("\n\033[{}m-fsh [c] \tCompute FT laplacian. \n\twith \t[c]: constant.".format("0;37"))


    #print("\n\033[{}mUse --help to list all available options.".format("1;30"))
 


