## Tutorial1:
How to implement a simple detector using the old ASCII interface to describe the geometry (see Detector Geometry and Media for more details about this geometry interface)
See also Adding new detector for a detailed description of the detector class implementation, MC point class and the CMakeLists.txt

To run this tutorial:

After building FairRoot successfully go to the build directory and call the configuration script (config.sh or config.csh according to our shell)
cd to the Tutorial1/macros directory
run the following command: root run_tutorial1.C (you can also load the macro into root and then run it)
This will start a simulation session with Geant3 and create 10 events generated by a box generator, the input in the box generator can be chosen by the user, by default in this macro we use "pions" (see macro lines 20-22) for details.
To choose Geant4 you just have to change TGeant3 to TGeant4 in line 8 of the macro, or of you are loading the macro to root before exciting it you just give TGeant4 as second argument to the run_tutorial1 call, i.e:

```bash
root>.L run_tutorial1.C
root>run_tutorial(10, "TGeant4")
```
