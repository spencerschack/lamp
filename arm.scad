epsilon = 0.01;
wood_thickness = 3/4;

module wood() {
  c = rands(0, 0.1, 3);
  color([0.41 + c[0], 0.24 + c[1], 0.18 + c[2]]) children();
}

module dark_metal() color([0.2, 0.2, 0.2]) children();

$fn = 100;

module support(length = 16) {
  width = 2 * wood_thickness;
  channel = 3/8;
  screw_radius = 1/16;
  screw_depth = wood_thickness + 2 * epsilon;
  padding = 3/16 + screw_radius;
  module corners() {
    module move() translate([padding, padding, 0]) children();
    module reflect_x() translate([width, 0, 0]) scale([-1, 1, 1]) children();
    module reflect_y() translate([0, length, 0]) scale([1, -1, 1]) children();
    move() children();
    reflect_x() move() children();
    reflect_y() move() children();
    reflect_y() reflect_x() move() children();
  }
  module drill() {
    translate([0, 0, -epsilon])
      cylinder(screw_depth, screw_radius, screw_radius);
  }
  module bolt() {
    dark_metal()
      translate([0, 0, 0.4])
        cylinder(screw_depth + 0.4, screw_radius, screw_radius);
  }
  wood() difference() {
    cube([width, length, wood_thickness]);
    translate([(width - channel) / 2, -epsilon, wood_thickness - channel / 2])
      cube([channel, length + 2 * epsilon, channel / 2 + epsilon]);
    corners() drill();
  }
  corners() bolt();
}

rotate([55, 0, 0]) {
  support();
  translate([0, 0, 2 * wood_thickness]) scale([1, 1, -1]) support();
}
