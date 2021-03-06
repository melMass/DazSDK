# DAZ Studio SDK 4.5+

For now there is only the Mac64 version, as the official version is not working by default. If you are using another OS, use the official ones as they work out of the box.

## Mac64

If you ever tried to compile a DAZ plugin on a recent Mac, you'll realize it's not straight forward as you need very specific version of XCode and the Command Line Tools. This repo is replicating the informations from [this post](https://www.daz3d.com/forums/discussion/89071/compiling-daz-sdk-for-macosx-latest-version) by Samurle: 
- Replacing `std::` with `std::__1` where required (in Qt headers)
