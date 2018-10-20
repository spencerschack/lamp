wood_thickness = 0.75;
acrylic_width = 2;
acrylic_thickness = 0.05;
acrylic_length = 12;
overlap_height = 0.125;
overlap_width = 0.125;

module acrylic() color([1, 1, 1, 0.5]) children();

acrylic() cube([acrylic_width, acrylic_length, acrylic_thickness]);
acrylic() cube([overlap_width, acrylic_length, overlap_height]);
translate([acrylic_width - overlap_width, 0, 0])
  acrylic() cube([overlap_width, acrylic_length, overlap_height]);

dowel_size = 3/8;
dowel_offset = 2;
clip_width = 0.125;
clip_thickness = 0.25;
clip_overhang = 0.05;
clip_gap = (wood_thickness - dowel_size) / 2;
clip_height = clip_gap + dowel_size / 2 + clip_overhang;
clip_position = 0.25;

$fn = 100;

module clip() {
  translate([clip_position, 0, acrylic_thickness]) {
    difference() {
      acrylic()
        cube([clip_width, clip_thickness * 2 + dowel_size, clip_height]);
      rotate([0, 90, 0]) translate([-dowel_size / 2 - clip_gap, dowel_size / 2 + clip_thickness, -1]) cylinder(clip_width + 2, dowel_size / 2, dowel_size / 2);
    }
  }
}

clip();
