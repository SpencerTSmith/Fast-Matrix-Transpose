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
            
            sort_name = csv_path.name.split('-.csv')[0].capitalize()
            
            if not infile.exists():
                print(f'File \"{infile}\" not found.')
                continue

            # Read the input file
            df = pd.read_csv(infile)


            if 'n' not in df.columns or 'm' not in df.columns:
                print(f'File \"{infile}\" is missing necessary columns (m, n). Skipping.')
                continue

            # Create a dataframe for the size of the matrix
            df['size'] = df['m'] * df['n']
            
            # Check which matrix is being observed
            square_matrices = df[df['m'] == df['n']]
            rectangular_matrices = df[df['m'] != df['n']]

            # Plotting square matrices
            if not square_matrices.empty:
                plt.plot(df['size'], square_matrices['GB_per_s'], label=f"{sort_name} (Square)", linestyle='-')

            # Plotting rectangular matrices
            if not rectangular_matrices.empty:
                plt.plot(df['size'], rectangular_matrices['GB_per_s'], label=f"{sort_name} (Rectangular)", linestyle='--')

        plt.title("Matrix Throughput Comparison")
        plt.xlabel('Matrix size (m*n)')
        plt.ylabel('Throughput (GB/s)')
        plt.ylim(0.0, 25.0)
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
    # print(f'{csv_paths}')
    if args.output:
        plotter = Plotter(interactive=args.interactive, short_x=args.short_x, output=args.output)
    else:
        plotter = Plotter(interactive=args.interactive, short_x=args.short_x)
    plotter.plot(csv_paths)

if __name__ == "__main__":
    main()