# AcCoRD 2.0
AcCoRD (Actor-based Communication via Reaction-Diffusion) is a simulation tool for molecular communication. AcCoRD 2.0 is a completely redesigned version of the original simulator (built in C) using C++ and an object-orientated design. This version is still at pre-release stage, with not all of the original features re-implemented in the new version. Compiled for Windows only. Built using MSVS.

* Find example configuration files inside the simulations folder. 
* Find videos demonstrating the simulations here: https://youtube.com/playlist?list=PL55Vx_QaVKZS6qdoi66Zng4fkF8YPCw3p
* Find molecule population plots here: https://www.mediafire.com/folder/b9y9zb28rdtjq/AcCoRD_2.0

## Simulator Components
* AcCoRD simulates at the microscopic and mesoscopic scale
* Regions: Molecule owning volumes with a surface boundary (none, reflective, absorptive, adsorptive, membrane). Mesoscopic regions must be cuboidal, but microscopic regions can be cuboidal, spherical, or cylindrical.
* Surfaces: Non-molecule owning volumes or planes with a surface boundary.
* Reactions: Zeroth, first and second order reactions can be simulated in both microscopic and mesoscopic regions.
* Passive Actors: Observe molecules in the environment (position, count & observation time). They can observe entire or partial regions. Can be linked to a group of regions or be assigned a shape and observe all molecules within its boundary.
* Active Actors: Release molecules into the environment according to a user-defined bit-sequence, random bit-sequence or an average release rate. Bit sequences can be saved to file. Active actors can be points, rectangular surfaces, circular surfaces, boxes, spheres or cylinders. Molecules can be released from the surface of actors or within their volume.

## How To Run A Simulation?
1. Create a configuration file. They are in JSON format. Find example configuration files inside the simulations folder: https://github.com/Jackrekirby/AcCoRD2/tree/master/simulations . Output files will be created in the same directory as the configuration file.
2. Run the simulator. Pass the configuration file into the simulator via the command file, or run the pre-made batch files, which will run the simulator when placed inside the same folder as the configuration file. The log from the simulator is displayed to console and written to file, inside the seed folder.
3. Visualise the results. AcCoRD comes with a MATLAB script which can plot molecule count observed by passive actors over many realisations. Plot the environment before the simulation is run and create an animation of simulation. The MATLAB script file can be found inside the example configuration folders.

## New Features
* Addition of cylindrical microscopic regions.
* Microscopic region shapes can partially overlap eachother.
* Child - grandparent diffusion.
* New binary output file format reduces simulation run time and import times.
* Microscopic regions partitioned into uniform grid of subvolumes for improved second order reaction performance.
* Microscopic regions have individual microscopic time steps for greater user control over local accuracy. 
* Increased flexibility in defining microscopic region surfaces. A different microscopic surface can be defined per molecule type, per region and per relationship.
* Configuration files can be built using MATLAB.
* Object-oriented design approach to ease future feature addition.
* New MATLAB visualisation tools
* Reference variables in configuration files.
* Binary To JSON output file converter.
* Event priority to force events which occur at the same time to be executed in a user-defined order.
* Manual defining of region relationships to offer greater control.

## Planned Features
* Readdition of hybrid interface and mesoscopic-mesoscopic region diffusion.
* Intra-step boundary crossing probability.
* Addition of conditional absorption, and membrane crossing. 
* Addition of adsorbing surfaces.

# Licensing
Main AcCoRD 2.0 files are copyright 2021 by Jack Kirby under the "New BSD" license. For full details of licensing, including use of third-party code, please see LICENSE.txt
