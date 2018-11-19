// Unit is mm
ledWidth = 3;       // OSRAM Oslon
ledHeight = 3;      // OSRAM Oslon
ledThickness = 0.6; // OSRAM Oslon

tubeInner = 2;
tubeOuter = 2.2;
tubeLength = 10;

translate([0, -0.3, 0]){
    translate([0, 0, -0.5]){
        rotate([90, 0, 0]){
            union(){
                LED();
                translate([0, 0, ledThickness/2]) tube();
            }
        }
    }
}

module LED() {
  color("red", 0.7){
      cube([ledWidth, ledHeight, ledThickness], center=true);
      difference(){
        translate([0, 0, 0.3])
        sphere(tubeInner/2, $fn=20, $fa=12, $fs=2); 
        translate([0, 0, -tubeInner/2])
        cube([tubeInner, tubeInner, tubeInner], center=true);
     }
   }
}

module tube(){
   difference(){
     $fn = 30; // Number of fragments
     cylinder(tubeLength, tubeOuter/2, tubeOuter/2, center=false);
     cylinder(tubeLength, tubeInner/2, tubeInner/2, center=false);
   }
}
