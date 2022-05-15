# DAZ Studio SDK 4.5+

## Mac64 

If you ever tried to compile a DAZ plugin on a recent Mac, you'll realize it's not straight forward as you need very specific version of XCode and the Command Line Tools. This repo is replicating the informations from [this post](https://www.daz3d.com/forums/discussion/89071/compiling-daz-sdk-for-macosx-latest-version) by Samurle: 
- Replacing `std::` with `std::__1` where required (in Qt headers)


## Build the samples

```zsh
cmake ..
```

In order to run the application (standalone) sample run:

```zsh
DYLD_LIBRARY_PATH="/Users/$(whoami)/Daz 3D/Applications/DAZ 3D/DAZStudio4 64-bit/Frameworks/" ./SDK_SceneLoaderApp $DUFFILE

# SAMPLE OUTPUT
# Scene Statistics:
#	Total Number of Nodes in Scene: 233
#	Figures in Scene: 2
#	Cameras in Scene: 0
#	Lights in Scene: 0
#	Total Vertices in Scene: 17020
#	Total Facets in Scene: 16720
```
