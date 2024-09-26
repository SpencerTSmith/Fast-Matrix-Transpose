<!--- coppied form lab-00 --->
# Plotter

I have upgraded the plotter so that you can pass it a file name and it will plot that file. Rather than the original functionality which required editing the python script when you wanted to change the file to be plotted. (Credit. William Willson lab-00)

## Activating a Python Virtual Environment

```bash
source ~/.venv/user-env/bin/activate
```

## Installing the Required Packages

With a python virtual environment activated, `cd` into this directory and run:

```bash
pip install -r requirements.txt
```
## Running the Plotter

Then you can run the plotter with:

```bash
./plotter.py <csv_filename>
# e.g. ./plotter.py data/example.csv
```

## More on Python Virtual Environments

For Linux/WSL users, I *highly* recommend setting up a [python virtual environment](https://realpython.com/python-virtual-environments-a-primer/) for any project you work on. Once you have a grasp on the `venv` module, I also recommend [virtualenv](https://virtualenv.pypa.io/en/latest/) which extends the functionality of `venv`.

