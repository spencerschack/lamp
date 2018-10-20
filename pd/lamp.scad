wood_width = 4;
wood_thickness = 0.75;
acrylic_width = 2;
acrylic_thickness = 0.125;
acrylic_width = 2;
overlap = 0.125;
wood_offset = acrylic_width / 2 - overlap;
lamp_height = 5 * 12;
lamp_width = wood_width * 2 + acrylic_width - overlap * 2;

module wood(adjust = 0) {
  color([0.41 + adjust, 0.24 + adjust, 0.18 + adjust]) children();
}

module acrylic() color("white", 0.75) children();

module vertical_wood(side, height) {
  difference() {
    wood() cube([wood_width, wood_thickness, height]);
    offset = side ? 0 : wood_width - acrylic_thickness;
    translate([offset, 0, 0]) {
      cube([overlap, acrylic_thickness, height]);
      translate([0, wood_thickness - acrylic_thickness, 0])
        cube([overlap, acrylic_thickness, height]);
    }
  }
}

module strip(height) {
  acrylic() cube([acrylic_width, acrylic_thickness, height]);
}

module section(height) {

  translate([-acrylic_width / 2, -wood_thickness / 2, 0])
    strip(height);

  translate([-acrylic_width / 2, wood_thickness / 2 - acrylic_thickness, 0])
    strip(height);

  translate([wood_offset, -wood_thickness / 2, 0])
    vertical_wood(true, height);

  translate([-wood_offset - wood_width, -wood_thickness / 2, 0])
    vertical_wood(false, height);

}

first_section = 20;
small_section = 6;

translate([0, 0, wood_thickness]) {

section(first_section);
translate([0, small_section, first_section]) section(small_section);
translate([0, 0, first_section]) rotate([-90, 0, 0]) section(small_section);
translate([0, -small_section, first_section + small_section]) section(small_section);
translate([0, 6, first_section + small_section]) rotate([90, 0, 0]) section(12);
translate([0, 0, first_section + 2 * small_section]) rotate([90, 0, 0]) section(small_section);
translate([0, 0, first_section + 12]) section(18);

}

module base(size) {
  wood()
    translate([-size / 2, -size / 2, 0])
      cube([size, size, wood_thickness]);
}

bottom_size = lamp_width + wood_thickness * 4;
bottom_chunk_size = (bottom_size - acrylic_width) / 2;
top_size = (bottom_size - wood_thickness) / 2 + wood_thickness;

module top_strip(offset) {
  wood(0.1)
    translate([offset, -top_size / 2, 0])
      cube([wood_thickness, top_size, wood_thickness]);
}

module top_chunk(offset) {
  wood(-0.1)
    translate([-lamp_width / 2, offset, 0])
      cube([lamp_width, top_size / 2 - wood_thickness / 2, wood_thickness]);
}

module bottom_chunk(offset) {
  wood()
    translate([offset, -bottom_size / 2, -wood_thickness])
      cube([bottom_chunk_size, bottom_size, wood_thickness]);
}

module bottom_strip(offset) {
  size = (bottom_size - wood_thickness) / 2 - 2.5;
  wood(0.1)
    translate([-acrylic_width / 2, offset + wood_thickness / 2, -wood_thickness])
      cube([acrylic_width, size, wood_thickness]);
}

translate([0, 0, wood_thickness]) {
  top_strip(lamp_width / 2);
  top_strip(-lamp_width / 2 - wood_thickness);
  top_chunk(wood_thickness / 2);
  top_chunk(-top_size / 2);
  bottom_chunk(acrylic_width / 2);
  bottom_chunk(-bottom_chunk_size - acrylic_width / 2);
  bottom_strip(2.5);
  bottom_strip(-6.75);
}
