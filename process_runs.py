import argparse
import os
import ROOT
from pdb import set_trace


def main(args):
    # load everything needed
    ROOT.gROOT.ProcessLine(".x $CLAS12ROOT/RunRoot/LoadClas12Root.C")
    ROOT.gROOT.ProcessLine(".x $CHANSER/macros/Load.C")
    ROOT.gROOT.LoadMacro("Pi2.cpp+")
    ROOT.gROOT.ProcessLine(".L Run_Pi2.C")

    # iterate through the given input files
    for item in args['input']:
        _, fname = os.path.split(item)
        folder = fname.replace('.hipo', '')
        outputdir = os.path.join(args['output'], folder)
        print('Processing run: {}'.format(item))

        # check output path exists and make it otherwise
        if os.path.exists(outputdir):
            print('Skipping, path already exists: {}'.format(outputdir))
        else:
            # run the processline command 
            print('Making output directory: {}'.format(outputdir))
            os.makedirs(outputdir)
            
            # run the processing
            ROOT.Run_Pi2(item, args['config'], outputdir)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='A program to run the Chanser finalstate code on specific runs')
    parser.add_argument('-i', '--input',
                        help='Filename(s) for the input data',
                        nargs='*',
                        required=True)
    parser.add_argument('-o', '--output',
                        help='Path for output folder',
                        required=True)
    parser.add_argument('-c', '--config',
                        help='Path to finalstate config file',
                        required=True)
    args = vars(parser.parse_args())
    main(args)
