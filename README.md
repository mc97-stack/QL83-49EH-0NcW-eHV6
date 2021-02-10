Update (10/02): To accommodate for planned growth as this program develops, I am stepping back from building this repository to build a separate Maths and Physical Properties libraries, intended to be accessed by this program to aid in integrating an object-oriented approach. These separate libraries are currently planned to be separate repositories which will be a dependency of this program in order to function and will be hyperlinked within this readme file at the time that they are made.

# Process Model
A cross-platform command-line program written in the C programming language made to perform the computations required for the design, simulation and fabrication of standard industrial process equipment. The program can either present the calculated data either in console or exporting to a tab-delineated text file suitable for import into Microsoft Excel.

##  Product Properties
GitHub username: "mc97-stack".
GitHub Repository URL: "https://github.com/mc97-stack/QL83-49EH-0NcW-eHV6.git".

Development status: Under development (Research).

Repository visibility status: Public.

Features currently available:
- Topics 1 - 4 of B48BB (Process Engineering A (Fluid Statics and Dynamics))
- Topics 1 - 6 of B48BC (Process Engineering B (Thermodynamic Processes))
- Topics 1 - 3 of B48BD (Process Engineering C (Heat Transfer))

N.B. It should now, hopefully, be obvious the need for physical properties estimation methods within this program. The main source for these subroutines will be The Properties of Gases and Liquid (5th Edition) - B. E. Poling, J. P. O'Connell and J. Prausnitz and the NIST webbook. Chemical Engineering design (5th Edition) by R. Sinnott and G. Towler, Perry's Chemical Engineering Handbook (8th Edition) and Albright's Chemical Engineering Handbook (1st edition) will also be consulted for general correlations used as standard by process engineers and provide a reference dataset to validate the claims made by Poling, O'Connell and Prausnitz. The author hopes that the forthcoming period of silence is recognised as a significant workload for an individual.

N.B. The author is well aware of typo's, grammatical and reading errors in addition to hyperlink errors within the attached documentation. Whilst the internal hyperlink issue is an error made by TexStudio, the author will strive to ensure that the typo's, grammatical and reading errors are corrected in the next update which will cover thermal lagging calculations, film heat transfer coefficient estimation and production of the spectral radiance graph for a perfect blackbody.

##  MacOS Install (Using Xcode 11.6 or later)
1.  On the "Welcome" window, click "Clone an Existing Project".
2.  This repository is located at the URL: "https://github.com/mc97-stack/QL83-49EH-0NcW-eHV6".
3.  After allowing Xcode 11.6 to download and build repository, compile the project.
4.  Locate project product in finder to run program within terminal.

##  Windows Install (Using Visual Studio 2019) (Currently requires manual repository rebuilding)
1.  Ensure that "Mobile Development with C++" workload is installed in "Visual Studio Installer".
2.  On the "Welcome" window, click "Clone GitHub Repository".
3.  This repository is located at the URL: "https://github.com/mc97-stack/QL83-49EH-0NcW-eHV6".
4.  After allowing Visual Studio 2019 to download repository, compile the project.
5.  Locate the compiled project in file explorer with either command prompt or windows powershell.

##  Known bugs
Please refer to https://github.com/mc97-stack/QL83-49EH-0NcW-eHV6/issues for updates on known bugs and to report a bug.
