#!/usr/bin/env python3
import pandas as pd
from matplotlib import pyplot as plt
import sys
import argparse
import numpy as np
from pathlib import Path

class Plotter:
    def __init__(self, interactive: bool = False, short_x: bool = False, output: Path = Path("comparison_plot.png")) -> None:
        self.interactive = interactive
        self.short_x = short_x
        self.output = output

    def plot(self, csv_paths: "list[Path]"):
        
        for csv_path in csv_paths:
            infile = Path(csv_path)
            
            sort_name = csv_path.name.split('-.csv')[0].capitalize()
            
            if not infile.exists():
                print(f'File \"{infile}\" not found.')
                continue

            # Read the input file
            df = pd.read_csv(infile, skipinitialspace=True) # ignores whitespace


            if 'm' not in df.columns or 'n' not in df.columns:
                # print(df.columns)
                print(f'File \"{infile}\" is missing necessary columns (m, n). Skipping.')
                continue

            # Create a dataframe for the size of the matrix
            df['size'] = df['m'] * df['n']

            print(df['size'])

            # Check which matrix is being observed
            square_matrices = df[df['m'] == df['n']]
            print(square_matrices)
            rectangular_matrices = df[df['m'] != df['n']]
            print(rectangular_matrices)


            # Plotting matrices
            plt.plot(df['size'], df['GB_per_s'], label=f"{sort_name}", linestyle='-')


        
        df['isSquare'] = np.where(df['m'] != df['n'], "Rectangle", "Square") # np.where

        n=0

        if "scc" in str(infile):
            df['mType'] = "Both Col Major"
        elif "scr" in str(infile):
            df['mType'] = "A = Col Maj, B = Row Maj"
        elif "src" or "rrc" in str(infile):
            df['mType'] = "A = row Maj, B = Col Maj"
            if "rrc" in str(infile): n=1
        elif "srr" in str(infile):
            df['mType'] = "Both Row Major"
        elif "sgg" in str(infile):
            df['mType'] = "Both General Stride"
            
        
        plt.title("" + df['isSquare'][n] +"; "+ df['mType'][0] + " Matrix")
        plt.xlabel('Matrix size (m*n)')
        plt.ylabel('Throughput (GB/s)')
        plt.ylim(0.0, 300.0)
        plt.legend(loc="upper right")
        if (self.short_x):
            plt.xlim(0, 1000)

        # Save the file and optionally show the figure
        print(f'Writing figure to \"{self.output}\".')
        plt.savefig(self.output)
        if self.interactive:
            plt.show()

def main():

    parser = argparse.ArgumentParser(description="Plots matrix performance data from a CSV and writes it to a file.")
    parser.add_argument("csv_files", help="The csv file(s) to plot.", nargs="+")
    parser.add_argument("-i", "--interactive", help="Display the plot in a window.", action="store_true")
    parser.add_argument("-sx", "--short-x", help="Render the first 1k results.", action="store_true")
    parser.add_argument("-o", "--output", help="Filename for the figure to output.", type=Path)
    args = parser.parse_args()

    csv_paths = [Path(csv_file) for csv_file in args.csv_files]
    print(f'{csv_paths}')
    if args.output:
        plotter = Plotter(interactive=args.interactive, short_x=args.short_x, output=args.output)
    else:
        plotter = Plotter(interactive=args.interactive, short_x=args.short_x)
    plotter.plot(csv_paths)

if __name__ == "__main__":
    main()