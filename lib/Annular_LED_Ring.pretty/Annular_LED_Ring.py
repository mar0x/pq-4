import cadquery as cq
from Helpers import show
import FreeCAD
import FreeCADGui as Gui
import ImportGui

import sys, os

# from https://github.com/easyw/kicad-3d-models-in-freecad.git
sys.path.append("/Users/max_romanov/projects/kicad-3d-models-in-freecad/cadquery/FCAD_script_generator/_tools")

from cq_cad_tools import FuseObjs_wColors, restore_Main_Tools, z_RotateObject
import exportPartToVRML as expVRML
import shaderColors

# see https://www.ebay.com/itm/1-3-Annular-LED-Ring-Display-Green-Bars-Red-Dot-Rotary-Encoder-or-Clock/251437248842

size_x = 24
size_y = 24
size_z = 15
hole_d = 11

body_height = 5
led_height = 3
top_height = 0.1

# low profile value is 5
# pcb_depth = 5

# original value is 2.5
pcb_depth = 2.5

wp = cq.Workplane("XY").workplane(offset=0.0).moveTo(0.0, 0.0)

base = wp.rect(size_x, size_y, True).extrude(size_z)
hole = wp.circle(hole_d / 2).extrude(size_z)
base = base.cut(hole)

base = base.edges("|Z").fillet(1)

out = wp.rect(size_x - 1, size_y - 1, True).extrude(size_z - body_height + 1)
hole = wp.circle((hole_d + 1) / 2).extrude(size_z - body_height + 1)
out = out.cut(hole)

out = out.edges("|Z").fillet(1)

base = base.cut(out)

base = base.cut(wp.rect(18.4, size_y, True).extrude(size_z - body_height))
base = base.cut(wp.rect(size_x, 18.4, True).extrude(size_z - body_height))

base = base.cut(wp.rect(22, size_y, True).extrude(pcb_depth))
base = base.cut(wp.rect(size_x, 22, True).extrude(pcb_depth))

led = wp.rect(1.5, 3.5, True).extrude(led_height)
led = led.translate((0, 9.75, size_z - led_height))
led = led.rotate((0,0,0), (0, 0, 13), 3)

out = wp.rect(12, 12, True).extrude(size_z)
led = led.cut(out.translate((6, 6, 0)))

led = led.rotate((0,0,0), (0, 0, 13), -6)
led = led.cut(out.translate((-6, 6, 0)))

led = led.rotate((0,0,0), (0, 0, 13), 3)

green_led = led.rotate((0,0,0), (0, 0, 13), -140)

for a in range(-120, 160, 20):
    green_led = green_led.union(led.rotate((0,0,0), (0, 0, 13), a))

red_led = wp.circle(1).extrude(led_height).translate((0, -9, size_z - led_height))

leg = wp.circle(0.7).extrude(size_z)
leg = leg.translate((size_x / 2 - 1, size_y / 2 - 1, 0))

out = wp.rect(size_x, size_y, True).extrude(pcb_depth)
base = base.cut(out.translate((1, 1, 0)))
base = base.cut(out.translate((-1, -1, 0)))

base = base.union(leg)
base = base.cut(green_led)
base = base.cut(red_led)

top_rect = wp.rect(size_x, size_y, True).extrude(top_height).translate((0, 0, size_z - top_height))

top = base.translate((0, 0, 0)).intersect(top_rect)

out = wp.circle(0.75).extrude(top_height).translate((0, 0, size_z - top_height))
top = top.cut(out.translate((-size_x / 2 + 1.5, -size_y / 2 + 1.5, 0)))
top = top.cut(out.translate((size_x / 2 - 1.5, -size_y / 2 + 1.5, 0)))
top = top.cut(out.translate((-size_x / 2 + 1.5, size_y / 2 - 1.5, 0)))
top = top.cut(out.translate((size_x / 2 - 1.5, size_y / 2 - 1.5, 0)))

base = base.cut(top_rect)

v = (8.89, 9.8, -pcb_depth)

base = base.translate(v).rotate((0,0,0), (0, 0, 13), -90)
top = top.translate(v).rotate((0,0,0), (0, 0, 13), -90)
green_led = green_led.translate(v).rotate((0,0,0), (0, 0, 13), -90)
red_led = red_led.translate(v).rotate((0,0,0), (0, 0, 13), -90)

pin = wp.rect(0.6, 0.6, True).extrude(11).translate((0, 0, -1 - pcb_depth))
pin = pin.faces("<Z").chamfer(0.1)

pins = pin.translate((0, 0, 0))

for r in range(1, 8):
    pins = pins.union(pin.translate((0,  -r * 2.54, 0)))

obj2show = [
    base,
    top,
    green_led,
    red_led,
    pins
]
color_names = [
    "white body",
    "black body",
    "led green",
    "led red",
    "metal grey pins"
]

for o in obj2show:
    show(o)

doc = FreeCAD.ActiveDocument
objs = doc.Objects[:]

material_subst = { }

def setColor(obj, color):
    o = Gui.ActiveDocument.getObject(obj.Name)

    o.ShapeColor = color
    o.LineColor = color
    o.PointColor = color
    o.DiffuseColor = color

    return o.DiffuseColor[0]

for i in range(0, len(objs)):
    color_name = color_names[i]
    color = shaderColors.named_colors[color_name].getDiffuseFloat()
    c = setColor(objs[i], color)

    material_subst[c[:-1]] = color_names[i]

while len(objs) > 1:
    FuseObjs_wColors(FreeCAD, Gui, doc.Name, objs[0].Name, objs[1].Name)
    del objs
    objs = doc.Objects[:]

CheckedModelName = "Annular_LED_Ring"

doc.Label = CheckedModelName
objs[0].Label = CheckedModelName
restore_Main_Tools()

#rotate if required
#rotation = all_params[model]['rotation']
#if (rotation != 0):
#    z_RotateObject(doc, rotation)

script_dir = os.path.dirname(os.path.realpath(__file__))

file_name = script_dir + os.sep + CheckedModelName

ImportGui.export(objs, file_name + '.step')

# scale and export Vrml model
scale = 1 / 2.54

export_objects, color_keys = expVRML.determineColors(Gui, objs, material_subst)
colored_meshes = expVRML.getColoredMesh(Gui, export_objects, scale)

expVRML.writeVRMLFile(colored_meshes, file_name + '.wrl', color_keys)

# Save the doc in Native FC format
doc.saveAs(file_name + '.FCStd')

