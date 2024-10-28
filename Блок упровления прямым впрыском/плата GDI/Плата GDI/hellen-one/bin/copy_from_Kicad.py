#!/usr/bin/env python
############################################################################################
# Hellen-One: A script to copy exported frame files from Kicad into project.
# (c) andreika <prometheus.pcb@gmail.com>
############################################################################################

import os, sys, errno
import csv, re
import glob, shutil

# for internal layers, we are using established Altium naming convention:
# https://www.candorind.com/gerber-file-extensions/
# also recognized by JLCPCB: https://support.jlcpcb.com/article/29-suggested-naming-patterns

if len(sys.argv) < 6:
    print ("Error! Please specify the project type, base folder, gerber folder, name and rev.")
    sys.exit(1)
type = sys.argv[1]
project_base = sys.argv[2]
gerber_rel_path = sys.argv[3]
name = sys.argv[4]
rev = sys.argv[5]
num_layers = int(sys.argv[6]) if (len(sys.argv) > 6 and sys.argv[6] != "") else 4

prefix = "hellen"
project_path = project_base + "/" + prefix + name
if (":" in type):
    (type, prefix) = type.split(":")
    project_path = project_base

if (type == "frames"):
    base_path = project_path + "/boards/" + prefix + name + "-" + rev
    src_path = base_path + "/" + gerber_rel_path
    dst_path = base_path + "/frame"
    src_name = src_path + "/" + prefix + name
    dst_name = dst_path + "/" + name
else: # modules
    src_path = project_base + "/hellen1-" + name + "/" + gerber_rel_path
    dst_path = "modules/" + name + "/" + rev
    src_name = src_path + "/hellen1-" + name
    dst_name = dst_path + "/" + name

fixRotationsPath = "bin/jlc_kicad_tools/cpl_rotations_db.csv"

fixFootprintsPath = "kicad/footprints.csv"

pat_module = re.compile(r'^[Mm]odule-([\w\-]+)-([\w\.]+)')

#################################################

print ("Copying frame " + name + "-" + rev + " to the repository (" + dst_path + ")...")

def mkdir_p(path):
	try:
		os.makedirs(path)
	except OSError as exc:
		if exc.errno == errno.EEXIST and os.path.isdir(path):
			pass
		else:
			raise

mkdir_p(dst_path)

# copy gerbers
print ("Reading gerbers from " + src_name + "*.*")
gerbers = [ ".GTL", ".GTO", ".GTP", ".GTS", ".GBL", ".GBO", ".GBS", ".GBP", ".GM1", ".DRL" ]
if (num_layers >= 4):
	gerbers += [ ".G2", ".G3" ]
for g in gerbers:
	copied = False
	gl = g.lower()
	for gPath in glob.glob(src_name + "*" + gl):
		print ("* Copying " + name + gl + "...")
		# keepout layer is a special case
		if (g == ".GM1"):
			# currently the "edge cuts" layer is used as a frame border
			if (type == "frames"):
				shutil.copyfile(gPath, dst_name + ".GM15")
			shutil.copyfile(gPath, dst_name + ".GKO")
		elif (g == ".G2"):
			# using Altium naming convention
			shutil.copyfile(gPath, dst_name + ".G1")
		elif (g == ".G3"):
			# using Altium naming convention
			shutil.copyfile(gPath, dst_name + ".G2")
		else:
			shutil.copyfile(gPath, dst_name + g)
		copied = True
	if not copied:
		if (g == ".DRL"):
			print ("* Skipping Drill for " + name + "...")
		elif (g == ".GBP"):
			print ("* Skipping Bottom Paste for " + name + "...")
		elif (g == ".G2" or g == ".G3"):
			print ("* Skipping Internal Layer " + g + " for " + name + "...")
		else:
			print ("Error! Gerber " + g + " not found for " + name + "!")
			sys.exit(2)

if (type == "modules"):
	# copy the module border layer
	shutil.copyfile(src_name + "-Module_Edge.gbr", dst_name + ".GM15")
	# print default (empty) keepout layer
	with open(dst_name + ".GKO", "w") as keepout_file:
		keepout_file.write("%FSLAX25Y25*%\n%MOIN*%\nG70*\nG01*\nG75*\nM02*\n")

# copy the schematic
shutil.copyfile(src_name + ".pdf", dst_name + "-schematic.pdf")
# copy the VRML 3D components
shutil.copyfile(src_name + ".wrl", dst_name + "-vrml.wrl")

footprint_LUT = dict()

print ("Reading footprint replacement table...")
with open(fixFootprintsPath, 'rt') as f_f:
	reader = csv.reader(f_f, delimiter=',')
	for row in reader:
		footprint_LUT[row[0]] = row[1]

bom = dict()

print ("Copying BOM...")
with open(src_name + ".csv", 'rt') as src_f, open(dst_name + "-BOM.csv", 'w') as dst_f:
	dst_f.write("Comment,Designator,Footprint,LCSC Part #\n")
	reader = csv.reader(src_f, delimiter=',')
	# skip header
	next(src_f)
	for row in reader:
		comment = row[0]
		des = row[1]
		footprint = row[2]
		lcsc = row[3]
		if footprint in footprint_LUT:
			footprint = footprint_LUT[footprint]
		# remove kicad library prefix from the footprint names (such as "hellen-one-common:")
		footprint = re.sub(r"[^\:]+\:", "", footprint)
		bom[des] = footprint
		print ("* " + des + " " + footprint)
		mod = pat_module.match(comment)
		if mod:
			print ("*** Module detected!")
			comment = "Module:" + mod.group(1) + "/" + mod.group(2)
		dst_f.write("\"" + comment + "\",\"" + des + "\",\"" + footprint + "\",\"" + lcsc + "\"\n")

print ("Reading rotations...")
rotations = {}
# read rotations csv (to undo weird JLC's angles which are not footprint-oriented)
with open(fixRotationsPath, 'rt') as f:
	next(f)
	reader = csv.reader(f, delimiter=',')
	for row in reader:
		rotations[row[0]] = float(row[1])

print ("Copying CPL...")
with open(src_name + "-all-pos.csv", 'rt') as src_f, open(dst_name + "-CPL.csv", 'w') as dst_f:
	dst_f.write("Designator,Mid X,Mid Y,Layer,Rotation,Ref-X(mm),Ref-Y(mm)\n")
	reader = csv.reader(src_f, delimiter=',')
	# skip header
	next(src_f)
	for row in reader:
		# Ref,Val,Package,PosX,PosY,Rot,Side
		des = row[0]
		posx = row[3]
		posy = row[4]
		rot = float(row[5])
		side = row[6]
		print ("* " + des)
		# fix kicad's negative x coord for bottom-placed components
		if (side.lower() == "bottom"):
			posx = str(-float(posx))
		if des not in bom:
			print ("copy_from_Kicad.py: Error! Designator [" + des + "] was not found in the BOM file!")
			sys.exit(2)
		if bom[des]:
			for r in rotations:
				if re.match(r, bom[des]):
					rot += rotations[r]
					rot = rot % 360.0
					print ("* fixing rotations for " + des)
		side = side.capitalize() 
		dst_f.write(des + "," + posx + "mm," + posy + "mm," + side + "," + str(rot) + "," + posx + "mm," + posy + "mm\n")

print ("Done!")
