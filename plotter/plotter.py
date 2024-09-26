#!/usr/bin/env python3
import pandas as pd
from matplotlib import pyplot as plt
import sys
import argparse
from pathlib import Path

class Plotter:
    def __init__(self, interactive: bool = False, short_x: bool = False, output: Path = Path("comparison_plot.png")) -> None:
        self.interactive = interactive
        self.short_x = short_x
        self.output = output

    def plot(self, csv_paths: "list[Path]"):
        
        for csv_path in csv_paths:
            infile = Path(csv_path)
            
            sort_name = csv_path.name.split('-data.csv')[0].capitalize()
            
            if not infile.exists():
                print(f'File \"{infile}\" not found.')
                continue

            # Read the input file
            df = pd.read_csv(infile)
            
            # Plot the data
            # TODO: Create conditionals for plots
            #       Only collect data thats needed
            #       
            plt.plot(df['size'], df['throughput'], label=sort_name)

        plt.title("Dispatch Sort Construction") # TODO: Make this name vairable for types of matrix & row/col/gen maj
        plt.xlabel('input size (n)')
        plt.ylabel('throughput (GFLOPS)')
        plt.ylim(0.0, 0.5)
        plt.legend(loc="upper right")
        if (self.short_x):
            plt.xlim(0, 1000)

        # Save the file and optionally show the figure
        print(f'Writing figure to \"{self.output}\".')
        plt.savefig(self.output)
        if self.interactive:
            plt.show()

def main():

    parser = argparse.ArgumentParser(description="Plots sorting algorithm performance data from a CSV and writes it to a file.")
    parser.add_argument("csv_files", help="The csv file(s) to plot.", nargs="+")
    parser.add_argument("-i", "--interactive", help="Display the plot in a window.", action="store_true")
    parser.add_argument("-sx", "--short-x", help="Render the first 1k results.", action="store_true")
    parser.add_argument("-o", "--output", help="Filename for the figure to output.", type=Path)
    args = parser.parse_args()

    csv_paths = [Path(csv_file) for csv_file in args.csv_files]
    # print(f'{csv_paths}')
    if args.output:
        plotter = Plotter(interactive=args.interactive, short_x=args.short_x, output=args.output)
    else:
        plotter = Plotter(interactive=args.interactive, short_x=args.short_x)
    plotter.plot(csv_paths)

if __name__ == "__main__":
    main()