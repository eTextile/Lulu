# KiCAD 3D Parts

## KiCAD 3D parts using OpenSCAD and Wings3D
http://happyrobotlabs.com/posts/tutorials/tutorial-3d-kicad-parts-using-openscad-and-wings3d/

### This tutorial is using meshconv
- http://www.openscad.org/
- http://www.patrickmin.com/meshconv/
- http://www.wings3d.com/

### Step by step
- Make & export .stl from OpenScad
- Clean the .stl wth meshconv
  - $ meshconv -c stl INPUTFILE.stl -o OUTPUTFILE
- Open the cleaned .stl with wings3d
- Export in VRML 2.0 (.wrl)
- Link the .wrl into KiCad part

## Workaround
https://github.com/openscad/openscad/issues/1304