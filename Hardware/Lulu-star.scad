// Unit is mm
pcbRadius = 7;
ledWidth = 3; // OSRAM Oslon
ledHeight = 3; // OSRAM Oslon
pcbHeight = ledHeight/2;
tubeLength = 5;
tubeInner = 2;
tubeOuter = 2.2;
pos = 2;

pinInner = 1;
difference(){
  PCB();
  connector();
}
translate([0, pos, ledHeight/4]) LED();
translate([0, pos, ledHeight/4]) tube();


module PCB() {
  color("Olive", 0.6){
    difference(){
      cylinder(pcbHeight, r1=pcbRadius, r2=pcbRadius, center=true);  
      translate([0, pos + tubeLength/2, 0])
      cube([ledWidth, tubeLength, pcbHeight],true);
     }
  }
}

module LED() {
  color("red", 0.6){
    rotate([90, 0, 0]){
      translate([0, 0, tubeInner/4])
      cube([ledWidth, ledHeight, 1], true);
      difference(){
      sphere(tubeInner/2, $fn=20, $fa=12, $fs=2); 
      translate([0, 0, tubeInner/2])
      cube([tubeInner, tubeInner, tubeInner], true);
      }
    }
  }
}

module tube(){
 rotate([-90, 0, 0]){
   difference(){
     $fn = 30; // Number of fragments
     cylinder(tubeLength, tubeOuter/2, tubeOuter/2, center=false);
     cylinder(tubeLength, tubeInner/2, tubeInner/2, center=false);
     }
   }
}

module connector(){
    $fn = 30; // Number of fragments
    translate([1.27, 0, -tubeLength/2])
    cylinder(tubeLength, pinInner/2, pinInner/2, center=false);
    translate([-1.27, 0, -tubeLength/2])
    cylinder(tubeLength, pinInner/2, pinInner/2, center=false);
    
    translate([1.27, -2.54, -tubeLength/2])
    cylinder(tubeLength, pinInner/2, pinInner/2, center=false);
    translate([-1.27, -2.54, -tubeLength/2])
    cylinder(tubeLength, pinInner/2, pinInner/2, center=false);
    
    translate([1.27, -5.08, -tubeLength/2])
    cylinder(tubeLength, pinInner/2, pinInner/2, center=false);
    translate([-1.27, -5.08, -tubeLength/2])
    cylinder(tubeLength, pinInner/2, pinInner/2, center=false);
}


