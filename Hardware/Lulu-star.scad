// Unit is mm
pcbRadius = 6.5;
ledWidth = 3;
ledHeight = 3;
pcbHeight = ledHeight/2;
tubeLength = 10;
tubeInner = 2;
tubeOuter = 2.2;

PCB();
translate([0, 0, ledHeight/4]) LED();
translate([0, 0, ledHeight/4]) tube();

module PCB() {
  color("Olive", 0.6){
    difference(){
      cylinder(pcbHeight, r1=pcbRadius, r2=pcbRadius, center=true);  
      translate([0, tubeLength/2, 0])
      cube([tubeOuter, tubeLength, pcbHeight],true);
     }
  }
}

module LED() {
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

module tube(){
 rotate([-90, 0, 0]){
   difference(){
     $fn = 30; // Number of fragments
     cylinder(tubeLength, tubeOuter/2, tubeOuter/2, center=false);
     cylinder(tubeLength, tubeInner/2, tubeInner/2, center=false);
     }
   }
}

