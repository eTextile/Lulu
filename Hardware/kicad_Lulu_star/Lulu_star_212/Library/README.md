# KiCad 3D Parts

## KiCad 3D parts using OpenScad and Wings3D
http://happyrobotlabs.com/posts/tutorials/tutorial-3d-kicad-parts-using-openscad-and-wings3d/

### This tutorial is using
- http://www.openscad.org/
- http://www.patrickmin.com/meshconv/
- http://www.wings3d.com/

### Step by step
- Make & export .stl from OpenScad
- Clean the .stl wth meshconv
  - $ meshconv -c stl INPUT_FILE.stl -o OUTPUT_FILE
- Open the cleaned .stl with wings3d
- Export it in VRML 2.0 (.wrl)
- Link the .wrl into KiCad part

## Workaround
https://github.com/openscad/openscad/issues/1304
