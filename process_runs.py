import argparse
import os
import ROOT


def main(args):
    # load everything needed
    ROOT.gROOT.ProcessLine(".x $HSEXP/LoadExperiment.C+")
    ROOT.gROOT.LoadMacro("TreeDataPi2.C+")
    ROOT.gROOT.LoadMacro("Pi2.C+")
    ROOT.gROOT.ProcessLine(".L RunHipo.C")

    # iterate through the given input files
    for item in args['filenames']:
        _, fname = os.path.split(item)
        folder = fname.split('.')[0]
        outputdir = os.path.join(args['output'], folder)
        print('Processing run: {}'.format(item))

        # check output path exists and make it otherwise
        if os.path.exists(outputdir):
            print('Skipping, path already exists: {}'.format(outputdir))
        else:
            # run the processline command 
            print('Making output directory: {}'.format(outputdir))
            os.makedirs(outputdir)
            
            # some filenaming for output
            outputfile = os.path.join(outputdir, "output.root")
            dirname = os.path.join(outputdir, "ParticleTrees")
            # add param for delta t cut
            ROOT.RunHipo(item, outputfile, dirname, args['nevents'])  


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='A program to run the HASPECT finalstate code on specific runs')
    parser.add_argument('-f', '--filenames',
                        help='Filename(s) for the input data',
                        nargs='*',
                        required=True)
    parser.add_argument('-o', '--output',
                        help='Path for output folder (should exist)',
                        required=True)
    parser.add_argument('-n', '--nevents',
                        help='Number of events to process',
                        required=False,
                        type=int,
                        default=1000000000)

    args = vars(parser.parse_args())
    main(args)
