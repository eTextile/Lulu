# KiCad 3D custom parts

## Using OpenScad and Wings3D
http://happyrobotlabs.com/posts/tutorials/tutorial-3d-kicad-parts-using-openscad-and-wings3d/

### Download and install
- http://www.openscad.org/
- http://www.patrickmin.com/meshconv/
- http://www.wings3d.com/

### Step by step
- Make & export .stl from OpenScad
- Clean the .stl wth meshconv
  - $ meshconv -c stl INPUT_FILE.stl -o OUTPUT_FILE
- Import the cleaned .stl in wings3D
- Export it in VRML 2.0 (.wrl)
- Link the .wrl into KiCad part

## Workaround
https://github.com/openscad/openscad/issues/1304
