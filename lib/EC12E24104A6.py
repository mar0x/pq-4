import cadquery as cq
from Helpers import show
import FreeCAD
import FreeCADGui as Gui
from cq_cad_tools import FuseObjs_wColors, GetListOfObjects, restore_Main_Tools, \
 exportSTEP, close_CQ_Example, exportVRML, saveFCdoc, z_RotateObject, Color_Objects, \
 CutObjs_wColors, checkRequirements
import shaderColors

wp = cq.Workplane("XY").workplane(offset=0.0).moveTo(0.0, 0.0)

metal_base = wp.rect(12.4, 13.2, True).extrude(4).translate((0, 0, 1))

yfillet_metal_base = metal_base.translate((0, 0, 0)).edges("|Y").fillet(0.5)
metal_base = metal_base.edges("|Z").fillet(1.5)

metal_base = metal_base.intersect(yfillet_metal_base)

metal_hub = wp.circle(3.4).extrude(5).translate((0, 0, 5))
metal_hub_base = wp.circle(5).extrude(4).translate((0, 0, 1))
metal_hub_base = metal_hub_base.union(metal_hub)
metal_hub_base = metal_hub_base.faces(">Z[1]").fillet(0.5)
metal_hub_base = metal_hub_base.faces(">Z").chamfer(1, 0.2)

metal_base = metal_base.union(metal_hub_base)

out = wp.rect(11.4, 13.2, True).extrude(3).translate((0, 0, 1.5))
out = out.edges("|Y").fillet(0.5)
metal_base = metal_base.cut(out)


plastic_base = wp.rect(11.4, 13.2, True).extrude(4.5)

# yfillet_base = base.translate((0, 0, 0)).edges("|Y").fillet(0.5)
plastic_base = plastic_base.edges("|Z").fillet(1.5)

# plastic_base = base.intersect(yfillet_base)

out = wp.rect(7.5, 13.2, True).extrude(1.5)
metal_base = metal_base.cut(out)
plastic_base = plastic_base.cut(out)


out = wp.rect(12.4, 10.5, True).extrude(1.5)
plastic_base = plastic_base.cut(out)


lock = wp.circle(0.5).extrude(0.5)
l = lock.translate((4.2, 5.1, 4.5))
metal_base = metal_base.cut(l)
plastic_base = plastic_base.union(l)

l = lock.translate((4.2, -5.1, 4.5))
metal_base = metal_base.cut(l)
plastic_base = plastic_base.union(l)

l = lock.translate((-4.2, 5.1, 4.5))
metal_base = metal_base.cut(l)
plastic_base = plastic_base.union(l)

l = lock.translate((-4.2, -5.1, 4.5))
metal_base = metal_base.cut(l)
plastic_base = plastic_base.union(l)


out = wp.rect(12.4, 4, True).extrude(4.5)
metal_base = metal_base.cut(out.translate((0, 7.25, 0)))
metal_base = metal_base.cut(out.translate((0, -7.25, 0)))


out = wp.rect(12.4, 7.5, True).extrude(2)
metal_base = metal_base.cut(out)


shaft = wp.circle(3).extrude(20)
out = wp.rect(6,6).extrude(7).translate((0, -4.5, 13))

shaft = shaft.cut(out)
shaft = shaft.faces(">Z").chamfer(1)

metal_base = metal_base.cut(shaft)
plastic_base = plastic_base.cut(shaft)

out = wp.circle(2).extrude(12)
shaft = shaft.cut(out)

shaft = shaft.union(plastic_base)

v = (2.5, 7.5, 0)
#v = (0, 0, 0)

base = metal_base.translate(v)
shaft = shaft.translate(v)

show(base)
show(shaft)

doc = FreeCAD.ActiveDocument
objs = GetListOfObjects(FreeCAD, doc)

body_color = shaderColors.named_colors["white body"].getDiffuseFloat()
top_color = shaderColors.named_colors["black body"].getDiffuseFloat()
led_green_color = shaderColors.named_colors["led green"].getDiffuseFloat()
led_red_color = shaderColors.named_colors["led red"].getDiffuseFloat()
pins_color = shaderColors.named_colors["metal grey pins"].getDiffuseFloat()

Color_Objects(Gui, objs[0], pins_color)
Color_Objects(Gui, objs[1], top_color)
