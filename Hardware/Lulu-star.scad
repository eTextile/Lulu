height = 5;

translate([0, 0, height/2]) PCB();
translate([0, 0, 5]) LED();
translate([0, 1, 5]) tube();


module LED() {
  rotate([90, 0, 0]){
    cube([10, 10, 2], true);
    difference(){
    translate([0, 0, -1])
    sphere(4, $fn = 0, $fa=12, $fs=2); 
    translate([0, 0, 5])
    cube([10, 10, 10], true);
    }
  }
}

module PCB() {
    color("Olive", 0.5){
  difference(){
    cylinder(height, r1=20, r2=20, center=true);  
    translate([0, 10, 0])
    cube([10, 20, height],true);
   }
}
}

module tube(){
 rotate([-90, 0, 0]){
   difference(){
     cylinder(20, 5, 5, center=false);
     cylinder(20, 4.5, 4.5, center=false);
     }
   }
}

